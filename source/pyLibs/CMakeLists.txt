# get include and src  获取头文件和cpp文件
set(PY_CATCHPYSTD_INCLUDE
    include/catchpystd.h
)


set(PY_CATCHPYSTD_SRC
    src/catchpystd.cpp
)

# 构建pyLibs静态库
add_library(pyLibs STATIC ${PY_CATCHPYSTD_INCLUDE} ${PY_CATCHPYSTD_SRC})
