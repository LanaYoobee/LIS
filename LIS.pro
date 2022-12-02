QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
QT += sql
QT += network

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bookdetails.cpp \
    browse.cpp \
    createaccount.cpp \
    imagefromurl.cpp \
    login.cpp \
    main.cpp \
    mainscreen.cpp \
    maintainusers.cpp \
    openwall_crypt/crypt_blowfish.c \
    openwall_crypt/crypt_gensalt.c \
    openwall_crypt/wrapper.c \
    qtbcrypt.cpp \
    searchbooks.cpp \
    viewaccount.cpp

HEADERS += \
    bookdetails.h \
    browse.h \
    createaccount.h \
    imagefromurl.h \
    login.h \
    mainscreen.h \
    maintainusers.h \
    openwall_crypt/crypt.h \
    openwall_crypt/crypt_blowfish.h \
    openwall_crypt/crypt_gensalt.h \
    openwall_crypt/ow-crypt.h \
    openwall_crypt/x86.S \
    qtbcrypt.h \
    searchbooks.h \
    viewaccount.h

FORMS += \
    bookdetails.ui \
    browse.ui \
    createaccount.ui \
    login.ui \
    mainscreen.ui \
    maintainusers.ui \
    searchbooks.ui \
    viewaccount.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \

