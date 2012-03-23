#include <boost/python.hpp>
#include <string>

/* VK HEADERS */
#include "version.h"
#include "node.h"
#include "model.h"


using namespace boost::python;
using namespace valkyrie;

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
            .add_property("id", &Node::get_id)
            .add_property("x" , &Node::get_x)
            .add_property("y" , &Node::get_y)
            .add_property("z" , &Node::get_z)
    ;

     // model
    class_<Model>("Model", init<const std::string&>())
            .add_property("name", &Model::get_name)
            .def("__str__", &Model::get_name)
            .def("add_node", &Model::addNode)
    ;
}


