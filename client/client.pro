QT += widgets
QT += printsupport
QT += core network testlib
DEFINES += CATCH_CONFIG_MAIN
CONFIG += c++17
INCLUDEPATH += /usr/include/nlohmann

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    codereset.cpp \
    fstr.cpp \
    graph.cpp \
    inpnwpass.cpp \
    main.cpp \
    avtorisation.cpp \
    ncrct.cpp \
    net.cpp \
    no_format_input.cpp \
    pdtmail.cpp \
    qcustomplot.cpp \
    registration.cpp \
    resmail.cpp \
    sstr.cpp \
    task.cpp \
    wrong_code.cpp \
    wrong_mail.cpp \
    wrong_registration.cpp

HEADERS += \
    avtorisation.h \
    client.h \
    codereset.h \
    fstr.h \
    graph.h \
    inpnwpass.h \
    ncrct.h \
    net.h \
    no_format_input.h \
    pdtmail.h \
    qcustomplot.h \
    registration.h \
    resmail.h \
    sstr.h \
    task.h \
    wrong_code.h \
    wrong_mail.h \
    wrong_registration.h

FORMS += \
    avtorisation.ui \
    codereset.ui \
    fstr.ui \
    graph.ui \
    inpnwpass.ui \
    ncrct.ui \
    no_format_input.ui \
    pdtmail.ui \
    registration.ui \
    resmail.ui \
    sstr.ui \
    task.ui \
    wrong_code.ui \
    wrong_mail.ui \
    wrong_registration.ui

TEST_SOURCES = tst_disconect_test.qml

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    tst_test.qml
