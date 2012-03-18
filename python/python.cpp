#include <boost/python.hpp>

const char* test()
{
    return "test!";
}

BOOST_PYTHON_MODULE (pyvalkyrie)
{
    using namespace boost::python;
    def("test", test);
}


