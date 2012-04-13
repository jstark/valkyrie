#include "force.h"

using valkyrie::Force;

Force::Force(int id, const std::string &name, shared_ptr<Node> n, double magn, double nx, double ny, double nz)
    : Entity(id, name), n_(n), magnitude_(magn), nx_(nx), ny_(ny), nz_(nz)
{
}
