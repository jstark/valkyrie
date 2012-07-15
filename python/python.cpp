#include <Python.h>
#include "valkyrie.h"


// exception object
static PyObject *ValkyrieError;

#define RETURN_ERROR_IF_CALLED_WITH_ARGS \
	if (!PyArg_ParseTuple(args, "")) \
		return NULL;

#define RETURN_ERROR_IF(condition) \
    if (condition) \
        return NULL;

#define THROW_EXCEPTION_IF(condition, message) \
    if ((condition)) {\
        PyErr_SetString(ValkyrieError, message);\
        return NULL;\
    }

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

static PyObject* vk_version(PyObject *self, PyObject *args)
{
    RETURN_ERROR_IF_CALLED_WITH_ARGS
    return Py_BuildValue("s", VKApiVersion());
}

static PyObject* vk_is_at_least_version(PyObject *self, PyObject *args)
{
    int major = 0; 
    int minor = 0;
    int patch = 0;

    int ok = PyArg_ParseTuple(args, "i|ii", &major, &minor, &patch);
    if (!ok) return NULL;
    THROW_EXCEPTION_IF(major < 0, "Given major version is less than Zero!");
    THROW_EXCEPTION_IF(minor < 0, "Given minor version is less than Zero!");
    THROW_EXCEPTION_IF(patch < 0, "Given patch version is less than Zero!");
    
    return PyLong_FromLong(VKApiVersionIsAtLeast(major, minor, patch));
}

static int is_error_code(int code, const char **err_msg)
{
    *err_msg = VKErrorMessage(code);
    return (*err_msg) ? 1 : 0;
}

static PyObject* vk_model_create(PyObject *self, PyObject *args)
{
    const char *model_name = NULL;
    int model_id = 0;
    int ok = PyArg_ParseTuple(args, "i|s", &model_id, &model_name);
    if (!ok) return NULL;

    int code = VKModelCreate(model_id, model_name);

    const char *error_msg = NULL;
    THROW_EXCEPTION_IF(is_error_code(code, &error_msg), error_msg);
    return PyLong_FromLong(code);
}

static PyMethodDef ValkyrieMethods[] = {
	{"major_version", vk_major_version, METH_VARARGS, "Valkyrie API major version"},
	{"minor_version", vk_minor_version, METH_VARARGS, "Valkyrie API minor version"},
	{"patch_version", vk_patch_version, METH_VARARGS, "Valkyrie API patch version"},
    {"version", vk_version, METH_VARARGS, "Valkyrie API version"},
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
    PyObject *ref = NULL;

    ref = PyModule_Create(&valkyriemodule);
    if (!ref)
    {
        return NULL;
    }

    ValkyrieError = PyErr_NewException("valkyrie.error", NULL, NULL);
    Py_INCREF(ValkyrieError);
    PyModule_AddObject(ref, "error", ValkyrieError);
	return ref;
}
