#include "PyLibs/include/catchpystd.h"
#include <iostream>

_REPYSTD_BEGIN

// 获取标准输出和错误的数据
static std::string getOutData;
static std::string getErrData;

// definition class
static PyTypeObject CatchOut;
static PyTypeObject CatchErr;

// function of CatchOutObj
static PyObject *CatchOutObj_write(PyObject *self, PyObject *args)
{
    char *data;
    if (!PyArg_ParseTuple(args, "s", &data))
        return NULL;

    getOutData += data;
    return PyLong_FromLong(getOutData.size());
};

// function of CatchErrObj
static PyObject *CatchErrObj_write(PyObject *self, PyObject *args)
{
    char *data;
    if (!PyArg_ParseTuple(args, "s", &data))
        return NULL;

    getErrData += data;
    return PyLong_FromLong(getErrData.size());
};

static PyObject *CatchOutObj_flush(PyObject *self, PyObject *args)
{
    // no-op
    return Py_BuildValue("");
}

static PyObject *CatchErrObj_flush(PyObject *self, PyObject *args)
{
    // no-op
    return Py_BuildValue("");
}

// methods
static PyMethodDef CatchOutMeth[] =
    {
        {"write", (PyCFunction)CatchOutObj_write, METH_VARARGS, "sys.stdout.write"},
        {"flush", (PyCFunction)CatchOutObj_flush, METH_VARARGS, "sys.stdout.flush"},
        {NULL}};

// methods
static PyMethodDef CatchErrMeth[] =
    {
        {"write", (PyCFunction)CatchErrObj_write, METH_VARARGS, "sys.stderr.write"},
        {"flush", (PyCFunction)CatchErrObj_flush, METH_VARARGS, "sys.stderr.flush"},
        {NULL}};

// class
class CatchOutObj
{
public:
    PyObject_HEAD
};

// class
class CatchErrObj
{
public:
    PyObject_HEAD
};

// definitiom module  py模块
static PyModuleDef repystdMod =
    {
        PyModuleDef_HEAD_INIT,
        "Repystd Module",
        "Catch out and error in sys.std",
        -1,
        0};

// 初始化 repystd模块函数
PyMODINIT_FUNC PyInit_repystd(void)
{
    // definition class
    CatchOut.ob_base = {PyObject_HEAD_INIT(NULL) 0};
    CatchOut.tp_name = "CatchOutErr";
    CatchOut.tp_basicsize = sizeof(CatchOutObj);
    CatchOut.tp_itemsize = 0;
    CatchOut.tp_new = PyType_GenericNew;
    CatchOut.tp_doc = "Document of CatchOutErr Class.";
    CatchOut.tp_methods = CatchOutMeth;
    CatchOut.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;

    CatchErr.ob_base = {PyObject_HEAD_INIT(NULL) 0};
    CatchErr.tp_name = "CatchOutErr";
    CatchErr.tp_basicsize = sizeof(CatchErrObj);
    CatchErr.tp_itemsize = 0;
    CatchErr.tp_new = PyType_GenericNew;
    CatchErr.tp_doc = "Document of CatchOutErr Class.";
    CatchErr.tp_methods = CatchErrMeth;
    CatchErr.tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;

    // init CatchOutErr 判断CatchOut和CatchErr的pyType能否读取
    if (PyType_Ready(&CatchOut) < 0)
        return NULL;

    if (PyType_Ready(&CatchErr) < 0)
        return NULL;

    // +1 引用+1
    Py_INCREF(&CatchOut);
    Py_INCREF(&CatchErr);

    // create module  创建py模块
    PyObject *m = PyModule_Create(&repystdMod);
    if (m == NULL)
    {
        return NULL;
    }
    else
    {

        // class add to module  把catchOut类添加到模块
        if (PyModule_AddObject(m, "CatchOut", (PyObject *)&CatchOut) < 0)
        {
            // 引用-1
            Py_XDECREF(&CatchOut);
            Py_XDECREF(&CatchErr);
            Py_XDECREF(m);
            return NULL;
        }

        // 把catchErr类添加到模块
        if (PyModule_AddObject(m, "CatchErr", (PyObject *)&CatchErr) < 0)
        {
            // 引用-1
            Py_XDECREF(&CatchOut);
            Py_XDECREF(&CatchErr);
            Py_XDECREF(m);
            return NULL;
        }
    }

    // 返回模块指针
    return m;
}

CatchStdData::CatchStdData(void)
{
    temp = 0;
    newStdout = 0;
    tempErr = 0;
    newStderr = 0;
    outData = &getOutData;
    errData = &getErrData;

    isExitCatch = false;
}

CatchStdData::~CatchStdData(void)
{
    if (!isExitCatch)
        exitCatch();
}

void CatchStdData::addPyLib(char *lib, PyObject *(*initfunc)())
{
    PyImport_AppendInittab(lib, initfunc);
}

void CatchStdData::setStd(void)
{
    if (!Py_IsInitialized())
    {
        //Py_SetPath((wchar_t *)"E:/Script/PySide2/v1.0/pyside3_install/py3.7-qt5.12.6-32bit-release/lib/site-packages");
        PyImport_AppendInittab("repystd", PyInit_repystd);

        // init python
        Py_Initialize();

        PyImport_ImportModule("repystd");
    }

    _setStdout();
    _setStderr();
}

void CatchStdData::pyRunString(std::string &code)
{
    *outData = "";
    *errData = "";
    
    PyRun_SimpleString(code.c_str());

    if (outData->size() != 0)
    {
        outData->erase(outData->size() - 1, outData->size());
    }

    if (errData->size() != 0)
    {
        errData->erase(errData->size() - 1, errData->size());
    }

    if (*outData == "" && *errData == "")
    {

        code = "print(" + code + ")";
        PyRun_SimpleString(code.c_str());

        if (*errData == "" && *outData != "")
        {
            outData->erase(outData->size() - 1, outData->size());
            *outData = "# result: " + *outData + "  #";
        }
        else
        {
            *outData = "";
            *errData = "";
        }
    }
}

std::string CatchStdData::getOut(void)
{
    return *outData;
}

std::string CatchStdData::getErr(void)
{
    return *errData;
}

void CatchStdData::exitCatch(void)
{
    if (newStdout)
    {
        if (temp)
        {
            PySys_SetObject("stdout", temp);
            temp = 0;
        }  

        Py_XDECREF(newStdout);
        Py_XDECREF(temp);
        newStdout = 0;
    }

    if (newStderr)
    {
        if (tempErr)
        {
            PySys_SetObject("stderr", tempErr);
            tempErr = 0;
        }

        Py_XDECREF(newStderr);
        Py_XDECREF(tempErr);
        newStderr = 0;
    }

    if (Py_IsInitialized())
    {
        Py_Finalize();
    }

    // std::cout << "eixtCatch" << std::endl;
    isExitCatch = true;
}

int CatchStdData::_setStdout()
{
    if (!newStdout)
    {
        temp = PySys_GetObject("stdout");
        newStdout = CatchOut.tp_new(&CatchOut, 0, 0);
    }
    else
    {
        return -1;
    }

    PySys_SetObject("stdout", newStdout);
    return 0;
}

int CatchStdData::_setStderr()
{
    if (!newStderr)
    {
        tempErr = PySys_GetObject("stderr");
        newStderr = CatchErr.tp_new(&CatchErr, 0, 0);
    }
    else
    {
        return -1;
    }

    PySys_SetObject("stderr", newStderr);
    return 0;
}

_REPYSTD_END
