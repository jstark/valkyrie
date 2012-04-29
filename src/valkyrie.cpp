#include "valkyrie.h"
#include "entity.h"
#include "model.h"
#include "staticanalysis.h"
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

using valkyrie::EntityDb;
using valkyrie::Model;
using valkyrie::StaticAnalysisResults;
using valkyrie::StaticAnalysis;

using std::map;
using boost::shared_ptr;

namespace
{
    typedef EntityDb<Model> ModelDB;
    ModelDB models;

    typedef std::map<shared_ptr<Model>, shared_ptr<StaticAnalysisResults> > ResultsDB;
    ResultsDB results;
}

#define TRY_CREATE(what, mid, ...) \
    shared_ptr<Model> realModel = models.find(mid); \
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
    models.add(shared_ptr<Model>(new Model(mid, std::string(name ? name : ""))));
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

extern "C" int VKModelPerformStaticAnalysis(int mid)
{
    shared_ptr<Model> model = models.find(mid);
    if (!model)
    {
        return kActionFailed | kActionErrorIdDoesNotExist;
    }

    shared_ptr<StaticAnalysisResults> res(new StaticAnalysisResults);
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
    shared_ptr<Model> model = models.find(mid);
    if (!model)
    {
        return kActionFailed | kActionErrorIdDoesNotExist;
    }

    ResultsDB::const_iterator iter = results.find(model);
    if (iter == results.end())
    {
        return kActionFailed | kStaticAnalysisResultsMissing;
    }

    shared_ptr<StaticAnalysisResults> res = iter->second;
    std::for_each(res->beginNodalResults(), res->endNodalResults(), for_each_nodal_result(fun, data));
    return kActionOK;
}

extern "C" int VKStaticAnalysisForEachElementResult(int mid, VK_FOR_EACH_ELEMENT_RESULT_FUNCTION fun, void *data)
{
    shared_ptr<Model> model = models.find(mid);
    if (!model)
    {
        return kActionFailed | kActionErrorIdDoesNotExist;
    }

    ResultsDB::const_iterator iter = results.find(model);
    if (iter == results.end())
    {
        return kActionFailed | kStaticAnalysisResultsMissing;
    }

    shared_ptr<StaticAnalysisResults> res = iter->second;
    std::for_each(res->beginElementResults(), res->endElementResults(), for_each_element_result(fun, data));
    return kActionOK;
}
