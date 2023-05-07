#ifndef CATCHPYSTD_H
#define CATCHPYSTD_H

#include "PythonNew.h"
#include <string>

// 设置命名空间变量
#define _REPYSTD_BEGIN \
    namespace repystd  \
    {
#define _REPYSTD_END }

_REPYSTD_BEGIN

// 捕捉python的控制台输出
class CatchStdData
{
public:
    CatchStdData(void);
    ~CatchStdData(void);

    CatchStdData(const CatchStdData &c) = delete;
    CatchStdData &operator=(const CatchStdData &c) = delete;

    // 添加py的库路径
    void addPyLib(char *lib, PyObject *(*initfunc)());

    // 设置py的初始化
    void setStd(void);

    // 执行pyton的脚本
    void pyRunString(std::string &code);

    // 获取标准输出和错误
    std::string getOut(void);
    std::string getErr(void);

    // 退出python
    void exitCatch(void);

private:
    PyObject *mod;
    PyObject *mainMod;
    PyObject *temp;
    PyObject *newStdout;
    PyObject *tempErr;
    PyObject *newStderr;
    std::string *outData;
    std::string *errData;
    bool isExitCatch;

    // 重新设置标准输出和错误输出
    int _setStdout();
    int _setStderr();
};

_REPYSTD_END
#endif // !CATCHPYSTD_H
