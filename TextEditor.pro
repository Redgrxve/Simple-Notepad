QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += "src/"

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/tabbuttonwidget.cpp \
    src/tabtextwidget.cpp \
    src/textfileeditwidget.cpp \
    src/unsavedfilesdialog.cpp

HEADERS += \
    src/mainwindow.h \
    src/tabbuttonwidget.h \
    src/tabtextwidget.h \
    src/textfileeditwidget.h \
    src/unsavedfilesdialog.h \
    src/utils.h

FORMS += \
    src/mainwindow.ui \
    src/tabbuttonwidget.ui \
    src/tabtextwidget.ui \
    src/textfileeditwidget.ui \
    src/unsavedfilesdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src/resources.qrc
