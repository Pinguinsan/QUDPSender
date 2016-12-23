#-------------------------------------------------
#
# Project created by QtCreator 2016-12-22T17:11:22
#
#-------------------------------------------------

QT += core gui
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = QUDPSender

TEMPLATE = app

#!android {
#
#    LIBS += -ltjlutils
#
#    INCLUDEPATH += include/
#
#    SOURCES += src/main.cpp\
#               src/mainwindow.cpp
#
#    HEADERS  += include/mainwindow.h
#
#    FORMS    += forms/mainwindow.ui
#
#}

android {

    CONFIG += MOBILITY
    MOBILITY +=

    LIB_SOURCE_BASE = /opt/GitHub/tjlutils

    INCLUDEPATH += include/ \
                   $${LIB_SOURCE_BASE}/generalutilities/include/ \
                   $${LIB_SOURCE_BASE}/tstream/include/ \
                   $${LIB_SOURCE_BASE}/udpclient/include/ \
                   $${LIB_SOURCE_BASE}/prettyprinter/include/


    SOURCES +=  src/main.cpp\
                src/mainwindow.cpp \
                $${LIB_SOURCE_BASE}/udpclient/src/udpclient.cpp \
                $${LIB_SOURCE_BASE}/generalutilities/src/generalutilities.cpp

    HEADERS  += include/mainwindow.h\
                $${LIB_SOURCE_BASE}/udpclient/include/udpclient.h \
                $${LIB_SOURCE_BASE}/generalutilities/include/generalutilities.h \
                $${LIB_SOURCE_BASE}/tstream/include/tstream.h

    FORMS    += forms/mainwindow.ui

    #RESOURCES += resources/icons.qrc

}

HEADERS += \
    include/qudpsenderstrings.h \
    include/qudpsendericons.h

SOURCES += \
    src/qudpsendericons.cpp

RESOURCES += \
    resources/icons.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
