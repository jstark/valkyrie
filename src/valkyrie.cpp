#include "valkyrie.h"
#include "entity.h"
#include "model.h"
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

using valkyrie::EntityDb;
using valkyrie::Model;
using std::map;
using boost::shared_ptr;

struct VKModel { int id; };

struct VKModel *VKModelAlloc()
{
    return static_cast<struct VKModel *>(calloc(1, sizeof(VKModel)));
}

struct VKModel *VKModelInit(struct VKModel *model, int id)
{
    model->id = id;
    return model;
}

struct VKModel *VKModelDealloc(struct VKModel *model)
{
    free(model);
    return NULL;
}

namespace
{
    EntityDb<Model> models;
}

extern "C" struct VKModel* VKModelCreate(int id, const char *name)
{
    if (models.find(id))
    {
        return NULL;
    }

    struct VKModel *proxy = VKModelAlloc();
    proxy = VKModelInit(proxy, id);
    models.add(shared_ptr<Model>(new Model(id, std::string(name ? name : ""))));
    return proxy;
}

extern "C" int VKModelCreateNode(struct VKModel *model, int nid, double x, double y, double z)
{
    if (model)
    {
        int id = model->id;
        shared_ptr<Model> realModel = models.find(id);
        if (realModel)
        {
            return realModel->createNode(nid, x, y, z);
        }
    }
    return kActionFailed;
}

extern "C" int VKModelDestroy(struct VKModel* model)
{
    if (model)
    {
        int id = model->id;
        VKModelDealloc(model);
        return models.remove(id);
    }
    return kActionFailed;
}
