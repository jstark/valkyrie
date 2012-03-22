#include <boost/python.hpp>
#include <string>

/* VK HEADERS */
#include "version.h"
#include "node.h"


using namespace boost::python;
using valkyrie::Version;
using valkyrie::Node;

BOOST_PYTHON_MODULE (pyvalkyrie)
{
    // version
    class_<Version>("Version", no_init)
            .def("major", &Version::getMajor)
            .staticmethod("major")
            .def("minor", &Version::getMinor)
            .staticmethod("minor")
            .def("patch", &Version::getPatch)
            .staticmethod("patch")
            .def("is_at_least", &Version::isAtLeast)
            .staticmethod("is_at_least")
            .def("name", &Version::getVersion)
            .staticmethod("name")
    ;

    // node
    class_<Node>("Node", init<int, double, double, double>())
            .def("id", &Node::get_id)
            .def("x" , &Node::get_x)
            .def("y" , &Node::get_y)
            .def("z" , &Node::get_z)
    ;
}


