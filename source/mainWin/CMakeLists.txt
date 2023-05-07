# get include file   获取头文件
set(QT_MAINWIN_INCLUDE
    include/dockWin.h
    include/mainWindow.h
)

# get src file    获取cpp文件
set(QT_MAINKWIN_SRC
    src/dockWin.cpp
    src/mainWindow.cpp
)

# 构建mainWinLib静态库
add_library(mainWinLib STATIC ${QT_MAINKWIN_SRC} ${QT_MAINWIN_INCLUDE})

# 链接到qt5的库
target_link_libraries(mainWinLib Qt5::Widgets Qt5::Core Qt5::Gui)