QT += widgets

SOURCES += main.cpp \
    mainwidget.cpp \
    EM7180.cpp \
    EM7180_Master.cpp \
    gui.cpp \
    i2c_comm.cpp

HEADERS += \
    mainwidget.h \
    EM7180.h \
    EM7180_Master.h \
    gui.h \
    i2c_comm.h \
    bcm2835.h

RESOURCES +=

LIBS += -lbcm2835 -lpthread

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/qopenglwidget
INSTALLS += target

FORMS += \
    mainwidget.ui
