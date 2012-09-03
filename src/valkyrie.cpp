#include "valkyrie.h"
#include "entity.h"
#include "model.h"
#include "node.h"
#include "rod.h"
#include "property.h"
#include "force.h"
#include "staticanalysis.h"
#include <string>
#include <map>
#include <memory>

using valkyrie::EntityDb;
using valkyrie::Model;
using valkyrie::StaticAnalysisResults;
using valkyrie::StaticAnalysis;

using std::map;

namespace
{
    typedef EntityDb<Model> ModelDB;
    ModelDB models;

    typedef std::map<std::shared_ptr<Model>, std::shared_ptr<StaticAnalysisResults> > ResultsDB;
    ResultsDB results;
}

#define TRY_CREATE(what, mid, ...) \
    std::shared_ptr<Model> realModel = models.find(mid); \
    if (realModel) { \
        return realModel->create##what(__VA_ARGS__);\
    }\
    return kActionFailed | kActionErrorIdAlreadyExists;

extern "C" int VKModelCreate(int mid, const char *name)
{
    if (models.find(mid))
    {
        return kActionFailed | kActionErrorIdAlreadyExists;
    }
    models.add(std::make_shared<Model>(mid, std::string(name ? name : "")));
    return kActionOK;
}

extern "C" int VKModelCreateNode(int mid, int nid, double x, double y, double z)
{
    TRY_CREATE(Node, mid, nid, x, y, z)
}

extern "C" int VKModelCreateMaterial(int modelid, int matid, double E, double rho, const char *name)
{
    TRY_CREATE(Material, modelid, matid, E, rho, name);
}

extern "C" int VKModelCreateProperty(int mid, int pid, int matid, double A, const char *name)
{
    TRY_CREATE(Property, mid, pid, matid, A, name);
}

extern "C" int VKModelCreateRod(int mid, int rid, int pid, int n1, int n2)
{
    TRY_CREATE(Rod, mid, rid, pid, n1, n2);
}

extern "C" int VKModelCreateSpc(int mid, int sid, int dofs, int nid)
{
    TRY_CREATE(Spc, mid, sid, dofs, nid);
}

extern "C" int VKModelCreateForce(int mid, int fid, int nid, double magn, double nx, double ny, double nz)
{
    TRY_CREATE(Force, mid, fid, nid, magn, nx, ny, nz);
}

#define RETURN_ERROR_IF_MID_IS_NOT_FOUND_OR_FUN_IS_NULL \
    auto model = models.find(mid);\
    if (!model) {\
        return kActionFailed | kActionErrorIdDoesNotExist;\
    }\
    if (!fun) return kActionFailed;


extern "C" int VKModelPerformStaticAnalysis(int mid)
{
    auto model = models.find(mid);
    if (!model)
    {
        return kActionFailed | kActionErrorIdDoesNotExist;
    }

    auto res = std::make_shared<StaticAnalysisResults>();
    StaticAnalysis analysis;
    int result = analysis.analyze(*model, *res);

    if (result == kStaticAnalysisFailure)
    {
        return kActionFailed | kStaticAnalysisFailure;
    } else
    {
        results[model] = res;
    }

    return kActionOK;
}

namespace {
    struct for_each_nodal_result
    {
        for_each_nodal_result(VK_FOR_EACH_NODAL_RESULT_FUNCTION fun, void *data)
            : fun_(fun), data_(data) {}

        void operator()(const StaticAnalysisResults::nodal_result_item &item)
        {
            const valkyrie::NodalResults &res = item.second;
            fun_(item.first, res.ux, res.uy, res.uz, res.reactionX, res.reactionY, res.reactionZ, data_);
        }

        VK_FOR_EACH_NODAL_RESULT_FUNCTION fun_;
        void *data_;
    };

    struct for_each_element_result
    {
        for_each_element_result(VK_FOR_EACH_ELEMENT_RESULT_FUNCTION fun, void *data)
            : fun_(fun), data_(data) {}

        void operator()(const StaticAnalysisResults::element_result_item &item)
        {
            const valkyrie::ElementalResults &res = item.second;
            fun_(item.first, res.stress, res.strain, res.force, data_);
        }

        VK_FOR_EACH_ELEMENT_RESULT_FUNCTION fun_;
        void *data_;
    };
}

extern "C" int VKStaticAnalysisForEachNodalResult(int mid, VK_FOR_EACH_NODAL_RESULT_FUNCTION fun, void *data)
{
    auto model = models.find(mid);
    if (!model)
    {
        return kActionFailed | kActionErrorIdDoesNotExist;
    }

    auto iter = results.find(model);
    if (iter == results.end())
    {
        return kActionFailed | kStaticAnalysisResultsMissing;
    }

    auto res = iter->second;
    std::for_each(res->beginNodalResults(), res->endNodalResults(), for_each_nodal_result(fun, data));
    return kActionOK;
}

extern "C" int VKStaticAnalysisForEachElementResult(int mid, VK_FOR_EACH_ELEMENT_RESULT_FUNCTION fun, void *data)
{
    auto model = models.find(mid);
    if (!model)
    {
        return kActionFailed | kActionErrorIdDoesNotExist;
    }

    auto iter = results.find(model);
    if (iter == results.end())
    {
        return kActionFailed | kStaticAnalysisResultsMissing;
    }

    auto res = iter->second;
    std::for_each(res->beginElementResults(), res->endElementResults(), for_each_element_result(fun, data));
    return kActionOK;
}

extern "C" const char *VKErrorMessage(int errcode)
{
    if ((errcode & kActionOK) || (errcode & kStaticAnalysisSuccess))
    {
        return NULL;
    } else if (errcode & kActionErrorInvalidArgs)
    {
        return "Invalid argument";
    } else if (errcode & kActionErrorIdAlreadyExists)
    {
        return "Id already exists";
    } else if (errcode & kStaticAnalysisResultsMissing)
    {
        return "No results exist";
    } else if (errcode & kStaticAnalysisFailure)
    {
        return "Static analysis failed";
    } else
    {
        abort();
        return NULL;
    }
}

extern "C" int VKDofCode(int x, int y, int z)
{
    int code = 0;

    if (x) code |= kTranslateXDof;
    if (y) code |= kTranslateYDof;
    if (z) code |= kTranslateZDof;

    LOG("[VKDofCode]{x = %d, y = %d, z = %d, dof = %d}\n", x, y, z, code);
    return code;
}

static const char *s_label_nodeid = "Node ID";
static const char *s_label_UX = "UX";
static const char *s_label_UY = "UY";
static const char *s_label_UZ = "UZ";
static const char *s_label_ReactX = "React X";
static const char *s_label_ReactY = "React Y";
static const char *s_label_ReactZ = "React Z";
static const char *s_label_elementid = "Rod ID";
static const char *s_label_stress = "Stress";
static const char *s_label_strain = "Strain";
static const char *s_label_force = "Force";

static void s_print_nodal(int nid, double ux, double uy, double uz, double react_x, double react_y, double react_z, void *data)
{
    printf("% 8d\t% 8.3le\t% 8.3le\t% 8.3le\t% 8.3le\t% 8.3le\t% 8.3le\n",
           nid, ux, uy, uz, react_x, react_y, react_z);
}

static void s_print_elemental(int nid, double stress, double strain, double force, void *data)
{
    printf("% 8d\t% 8.3le\t% 8.3le\t% 8.3le\n",
           nid, stress, strain, force);
}

extern "C" int VKStaticAnalysisPrintResults(int mid)
{
    printf("%8s\t%8s\t%8s\t%8s\t%8s\t%8s\t%8s\n",
           s_label_nodeid,
           s_label_UX,
           s_label_UY,
           s_label_UZ,
           s_label_ReactX,
           s_label_ReactY,
           s_label_ReactZ);
    int ret = VKStaticAnalysisForEachNodalResult(mid, s_print_nodal, NULL);
    if (ret & kActionFailed)
    {
        return ret;
    }
    printf("%8s\t%8s\t%8s\t%8s\n",
           s_label_elementid,
           s_label_stress,
           s_label_strain,
           s_label_force);
    ret = VKStaticAnalysisForEachElementResult(mid, s_print_elemental, NULL);
    return ret;
}

extern "C" int VKModelForEachNode(int mid, VK_FOR_EACH_MODEL_NODE_FUNCTION fun, void *data)
{
    RETURN_ERROR_IF_MID_IS_NOT_FOUND_OR_FUN_IS_NULL
    std::for_each(model->beginNodes(), model->endNodes(), 
            [&](const typename EntityDb<valkyrie::Node>::pair_type &p) { 
                fun(p.second->get_id(), p.second->get_x(), p.second->get_y(), p.second->get_z(), data); 
            });
    return kActionOK;

}

extern "C" int VKModelForEachRod(int mid, VK_FOR_EACH_MODEL_ROD_FUNCTION fun, void *data)
{
    RETURN_ERROR_IF_MID_IS_NOT_FOUND_OR_FUN_IS_NULL
    std::for_each(model->beginElems(), model->endElems(),
            [&](const typename EntityDb<valkyrie::Rod>::pair_type &p) {
                  fun(p.second->get_id(),
                      p.second->get_property()->get_id(),
                      p.second->get_node1()->get_id(),
                      p.second->get_node2()->get_id());
            });
    return kActionOK;
}

extern "C" int VKModelForEachForce(int mid, VK_FOR_EACH_MODEL_FORCE_FUNCTION fun, void *data)
{
    RETURN_ERROR_IF_MID_IS_NOT_FOUND_OR_FUN_IS_NULL
    std::for_each(model->beginForces(), model->endForces(),
            [&](const typename EntityDb<valkyrie::Force>::pair_type &p) {
                  fun(p.second->get_id(),
                      p.second->get_magnitude(),
                      p.second->get_nx(),
                      p.second->get_ny(),
                      p.second->get_nz(),
                      p.second->get_node()->get_id());
            });
    return kActionOK;
}

extern "C" int VKModelForEachSpc(int mid, VK_FOR_EACH_MODEL_SPC_FUNCTION fun, void *data)
{
    RETURN_ERROR_IF_MID_IS_NOT_FOUND_OR_FUN_IS_NULL
    return kActionOK;
}

