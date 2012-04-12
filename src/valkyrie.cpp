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

namespace
{
    EntityDb<Model> models;
}

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
    shared_ptr<Model> realModel = models.find(mid);
    if (realModel)
    {
        return realModel->createNode(nid, x, y, z);
    }
    return kActionFailed | kActionErrorIdDoesNotExist;
}
