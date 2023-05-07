# set cmake version  设置cmake版本
cmake_minimum_required(VERSION 3.17.0)

# set project name   项目名变量
set(PRO_NAME mainScriptNodeWinPro)

# project name   设置项目名
project(${PRO_NAME})

message("-- project = '${PRO_NAME}'")

# set cpp standard to c++11 minimum  设置c++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# find head file in build directory  设置头文件库查找目录
set(CMAKE_INCLUDE_CURRENT_DIR ON)


# set cmake auto run qt  设置cmake的qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# qt路径变量
set(QT5_COMPILERS_DIR "D:Qt/Qt5.12.6/5.12.6/msvc2017")

# set qt5 path  设置qt5的路径
set(CMAKE_PREFIX_PATH QT5_COMPILERS_DIR)

# 输出信息
message("-- Qt5 Compilers = '${QT5_COMPILERS_DIR}'")

# get src file 获取当前文件路径下的cpp文件
aux_source_directory(. DIR_SRCS)

# find qt5 include 查找qt5的头文件
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

# add python include dir and library   python库的路径变量和头文件路径变量
set(PYTHON_DIR "C:/Program Files (x86)/Python37-32")
set(PYTHON_INCLUDE_DIR ${PYTHON_DIR}/include)
set(PYTHON_LIBRARY_DIR ${PYTHON_DIR}/libs)


message("-- PYTHON_INCLUDE_DIR = '${PYTHON_INCLUDE_DIR}'")
message("-- PYTHON_LIBRARY_DIR = '${PYTHON_LIBRARY_DIR}'")

# add include dir ${CMAKE_CURRENT_SOURCE_DIR}/source  添加头文件目录
include_directories(${PYTHON_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/source)
link_directories(${PYTHON_LIBRARY_DIR})  # 链接python库目录


# 在Windows系统设置环境变量
# if(CMAKE_HOST_WIN32)
#     set(SYS_ENV_PATH $ENV{PATH} ${QT5_COMPILERS_DIR}/bin ${PYTHON_DIR} ${PYTHON_DIR}/script ${PROJECT_SOURCE_DIR}/pythonLib)
#     set(ENV{PATH} "${SYS_ENV_PATH}")
#     message("-- WINDOWS system ENV = '$ENV{PATH}'")
# endif()

# build exe file  构建exe文件
add_executable(${PRO_NAME} ${DIR_SRCS})

# link qt5 include and library "mainWinLib" and "scriptEditorWinLib"
# 链接到qt5库、mainWinLib库、scriptEditorWinLib库、pyLibs库、nodeEditorWinLib库、_tkinter库、python3库、python37库
target_link_libraries(${PRO_NAME} Qt5::Widgets Qt5::Core Qt5::Gui
                                    mainWinLib scriptEditorWinLib pyLibs nodeEditorWinLib 
                                    _tkinter python3 python37)


# target_link_libraries(${PRO_NAME} concrt140 libclang msvcp140 pyside2.abi3 shiboken2.abi3 ucrtbase vcamp140 vccorlib140 vcomp140 vcruntime140)

# add sub dir "source"  添加子文件夹
add_subdirectory(source)
