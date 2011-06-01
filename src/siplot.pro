# -------------------------------------------------
# Project created by QtCreator 2011-04-05T15:42:48
# -------------------------------------------------
TARGET = siplot
TEMPLATE = app
SOURCES += main.cpp \
    fparser.cpp \
    mainwindow.cpp \
    settingsview.cpp \
    funcview.cpp \
    formulaview.cpp \
    function.cpp \
    aboutdialog.cpp \
    manualdialog.cpp \
    functionsview.cpp \
    cparser.cpp \
    gfunction.cpp
HEADERS += inernal.h \
    function.h \
    fparser.h \
    mainwindow.h \
    settingsview.h \
    funcview.h \
    formulaview.h \
    aboutdialog.h \
    manualdialog.h \
    functionsview.h \
    cparser.h \
    gfunction.h
FORMS += settingsview.ui \
    funcview.ui \
    formulaview.ui \
    aboutdialog.ui \
    manualdialog.ui \
    functionsview.ui
OBJECTS_DIR = obj$${SUFFIX_STR}
INCLUDEPATH += /usr/include/qwt/
QWTLIB = qwt$${SUFFIX_STR}
LIBS += -L$${QWT_ROOT}/lib \
    -l$${QWTLIB}
