#-------------------------------------------------
#
# Project created by QtCreator 2011-09-01T21:01:02
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = Thingamabob
TEMPLATE = app

SOURCES += main.cpp\
    Log.cpp \
    LogView.cpp \
    MainWindow.cpp \
    Direct3dWidget.cpp \
    ILogReader.cpp \
    Device.cpp \
    LogWriter.cpp \
    SwapChain.cpp \
    WinUtils.cpp \
    GraphicsInfrastructure.cpp \
    CppHelpers.cpp \
    Adapter.cpp \
    Texture2d.cpp \
    RenderTargetView.cpp \
    Engine.cpp \
    VertexShader.cpp \
    PixelShader.cpp \
    ShaderCode.cpp \
    InputLayout.cpp \
    Vertex.cpp \
    VertexBuffer.cpp

HEADERS  += \
    Log.h \
    LogView.h \
    MainWindow.h \
    Direct3dWidget.h \
    ILogReader.h \
    Device.h \
    LogWriter.h \
    SwapChain.h \
    WinUtils.h \
    GraphicsInfrastructure.h \
    CppHelpers.h \
    Adapter.h \
    Texture2d.h \
    RenderTargetView.h \
    Engine.h \
    IEngineView.h \
    VertexShader.h \
    PixelShader.h \
    ShaderCode.h \
    InputLayout.h \
    Vertex.h \
    VertexBuffer.h \
    Global.h

FORMS    += \
    MainWindow.ui

LIBS += -L"\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Lib\x86" -ldxgi -ld3d11 -ld3dcompiler -ld3dx11d -ld3dx9d -ldxerr -ldxguid -lwinmm -lcomctl32

INCLUDEPATH += "C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include"

OTHER_FILES += .fx


























































































