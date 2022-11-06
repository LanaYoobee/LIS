QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += sql

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    login.cpp \
    main.cpp \
    mainscreen.cpp \
    openwall_crypt/crypt_blowfish.c \
    openwall_crypt/crypt_gensalt.c \
    openwall_crypt/wrapper.c \
    qtbcrypt.cpp

HEADERS += \
    login.h \
    mainscreen.h \
    openwall_crypt/crypt.h \
    openwall_crypt/crypt_blowfish.h \
    openwall_crypt/crypt_gensalt.h \
    openwall_crypt/ow-crypt.h \
    openwall_crypt/x86.S \
    qtbcrypt.h

FORMS += \
    login.ui \
    mainscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \

