#include <boost/python.hpp>
#include "valkyrie.h"
#include "node.h"

using namespace boost::python;
using valkyrie::Node;

BOOST_PYTHON_MODULE (pyvalkyrie)
{
    def("major_version", VKApiMajorVersion);
    def("minor_version", VKApiMinorVersion);
    def("patch_version", VKApiPatchVersion);
    def("version", VKApiVersion);
    def("is_at_least_version", VKApiVersionIsAtLeast);

    // node
    class_<Node>("Node", init<int, double, double, double>())
            .def("id", &Node::get_id)
            .def("x" , &Node::get_x)
            .def("y" , &Node::get_y)
            .def("z" , &Node::get_z)
    ;

}


