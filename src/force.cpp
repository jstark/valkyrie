#include "force.h"
#include "node.h"
#include <cmath>

using valkyrie::Force;
using valkyrie::Node;

Force::Force(int id, const std::string &name, std::shared_ptr<Node> n, double magn, double nx, double ny, double nz)
    : Entity(id, name), n_(n), magnitude_(magn), nx_(nx), ny_(ny), nz_(nz)
{
}

static int unit_vector(double x, double y, double z, double *nx, double *ny, double *nz)
{
    int ret = 0;

    double len = std::sqrt(x*x + y*y + z*z);

    if (len < 1.0e-6)
    {
        return 1; // error
    }

    *nx = x/len;
    *ny = y/len;
    *nz = z/len;

    return ret;
}

std::shared_ptr<Force> valkyrie::try_create_force(int fid, std::shared_ptr<Node> n, double magn, double nx, double ny, double nz)
{
    std::shared_ptr<Force> f;
    if (n && !unit_vector(nx, ny, nz, &nx, &ny, &nz))
    {
        LOG("[ctor][force]{fid = %d, node = %d, magnitude = %le, nx = %le, ny = %le, nz = %le}\n", fid, n->get_id(), magn, nx, ny, nz);
        f = std::make_shared<Force>(fid, "", n, magn, nx, ny, nz);
    }
    return f;
}
