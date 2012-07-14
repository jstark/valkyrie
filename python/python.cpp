#include <Python.h>
#include "valkyrie.h"

#define RETURN_ERROR_IF_CALLED_WITH_ARGS \
	if (!PyArg_ParseTuple(args, "")) \
		return NULL;

#define RETURN_ERROR_IF(condition) \
    if (condition) \
        return NULL;

static PyObject* vk_major_version(PyObject *self, PyObject *args)
{
	RETURN_ERROR_IF_CALLED_WITH_ARGS
	return PyLong_FromLong(VKApiMajorVersion());
}

static PyObject* vk_minor_version(PyObject *self, PyObject *args)
{
	RETURN_ERROR_IF_CALLED_WITH_ARGS
	return PyLong_FromLong(VKApiMinorVersion());
}

static PyObject* vk_patch_version(PyObject *self, PyObject *args)
{
	RETURN_ERROR_IF_CALLED_WITH_ARGS
	return PyLong_FromLong(VKApiPatchVersion());
}

static PyObject* vk_is_at_least_version(PyObject *self, PyObject *args)
{
    int major = 0; 
    int minor = 0;
    int patch = 0;

    int ok = PyArg_ParseTuple(args, "i|ii", &major, &minor, &patch);
    if (!ok) return NULL;
    RETURN_ERROR_IF(major < 0);
    RETURN_ERROR_IF(minor < 0);
    RETURN_ERROR_IF(patch < 0);
    
    return PyLong_FromLong(VKApiVersionIsAtLeast(major, minor, patch));
}

static PyObject* vk_model_create(PyObject *self, PyObject *args)
{
    const char *model_name = NULL;
    int model_id = 0;
    int ok = PyArg_ParseTuple(args, "i|s", &model_id, &model_name);
    if (!ok) return NULL;

    return PyLong_FromLong(VKModelCreate(model_id, model_name));
}

static PyMethodDef ValkyrieMethods[] = {
	{"major_version", vk_major_version, METH_VARARGS, "Valkyrie API major version"},
	{"minor_version", vk_minor_version, METH_VARARGS, "Valkyrie API minor version"},
	{"patch_version", vk_patch_version, METH_VARARGS, "Valkyrie API patch version"},
    {"is_at_least_version", vk_is_at_least_version, METH_VARARGS, "Checks if API version is at least the given version."},
    {"create_model", vk_model_create, METH_VARARGS, "Create a new FE model, with id and name"}, 
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef valkyriemodule = {
	PyModuleDef_HEAD_INIT,
	"valkyrie",
	NULL,
	-1,
	ValkyrieMethods
};

PyMODINIT_FUNC
PyInit_valkyrie(void)
{
	return PyModule_Create(&valkyriemodule);
}
