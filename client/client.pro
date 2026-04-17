QT += widgets
QT += printsupport
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    graph.cpp \
    main.cpp \
    avtorisation.cpp \
    net.cpp \
    qcustomplot.cpp \
    registration.cpp \
    resmail.cpp \
    task.cpp

HEADERS += \
    avtorisation.h \
    graph.h \
    net.h \
    qcustomplot.h \
    registration.h \
    resmail.h \
    task.h

FORMS += \
    avtorisation.ui \
    graph.ui \
    registration.ui \
    resmail.ui \
    task.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
