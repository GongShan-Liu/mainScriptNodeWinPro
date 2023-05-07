#ifndef PYTHONNEW_H
#define PYTHONNEW_H

// 避免python库和qt库的slots冲突
#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")

#endif