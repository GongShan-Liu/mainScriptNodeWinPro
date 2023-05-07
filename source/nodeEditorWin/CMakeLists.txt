set(QT_NODEEDITORWIN_INCLUDE
    include/nodeEditorView.h
    include/NodeGraphicsObject.h
    include/NodeConnectionObject.h
    include/NodeEditScene.h
    include/NodeLineEditWidget.h
    include/NodePort.h
)

set(QT_NODEEDITORWIN_SRC
    src/nodeEditorView.cpp
    src/NodeGraphicsObject.cpp
    src/NodeConnectionObject.cpp
    src/NodeEditScene.cpp
    src/NodeLineEditWidget.cpp
    src/NodePort.cpp
)

# find qt5 include
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

add_library(nodeEditorWinLib STATIC ${QT_NODEEDITORWIN_INCLUDE} ${QT_NODEEDITORWIN_SRC})

# link qt5 include and library "mainWinLib" and "scriptEditorWinLib"
target_link_libraries(nodeEditorWinLib Qt5::Widgets Qt5::Core Qt5::Gui)