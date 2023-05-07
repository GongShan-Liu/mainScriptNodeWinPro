# get include file  添加头文件
set(QT_SCRIPTEDITORWIN_INCLUDE
    include/feedbackFrame.h
    include/scriptEditorWidgets.h
    include/scriptTextFrame.h
)

# get src file 添加cpp文件
set(QT_SCRIPTEDITORWIN_SRC
    src/feedbackFrame.cpp
    src/scriptEditorWidgets.cpp
    src/scriptTextFrame.cpp
)

# 链接到pyside2的dll库
# link_directories(${PROJECT_SOURCE_DIR}/pythonLib)

# PROJECT_SOURCE_DIR
# message("test = '${PROJECT_SOURCE_DIR}'")

# 构建scriptEditorWinLib静态库
add_library(scriptEditorWinLib STATIC ${QT_SCRIPTEDITORWIN_SRC} ${QT_SCRIPTEDITORWIN_INCLUDE})

# 链接到qt5的库
target_link_libraries(scriptEditorWinLib Qt5::Widgets Qt5::Core Qt5::Gui)
# target_link_directories(scriptEditorWinLib ${PROJECT_SOURCE_DIR}/pythonLib)