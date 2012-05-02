#-------------------------------------------------
#
# Project created by QtCreator 2012-03-19T13:29:07
#
#-------------------------------------------------

QT       += core gui
QT       += webkit network

INCLUDEPATH += "C:/curl-7.21.6-devel-mingw32/include"
INCLUDEPATH += "C:/jsoncpp-src-0.6.0-rc2/include"
#LIBS += -L"C:/curl-7.21.6-devel-mingw32/lib" -lcurl
win32:LIBS += -L"C:/curl-7.24.0-ssl-sspi-zlib-static-bin-w32" -lcurl

DEFINES += CURL_STATICLIB

TARGET = renrentest
#CONFIG   += console

TEMPLATE = app


SOURCES += main.cpp \
    src/librrapi/Utility.cpp \
    src/librrapi/UsersAPI.cpp \
    src/librrapi/StatusAPI.cpp \
    src/librrapi/RRAPI.cpp \
    src/librrapi/PhotosAPI.cpp \
    src/librrapi/PayAPI.cpp \
    src/librrapi/PagesAPI.cpp \
    src/librrapi/NotificationsAPI.cpp \
    src/librrapi/Method.cpp \
    src/librrapi/MD5.cpp \
    src/librrapi/InvitationsAPI.cpp \
    src/librrapi/FriendsAPI.cpp \
    src/librrapi/Config.cpp \
    src/librrapi/AdminAPI.cpp \
    src/libhttp/Response.cpp \
    src/libhttp/RequestParam.cpp \
    src/libhttp/Request.cpp \
    json/lib_json/json_writer.cpp \
    json/lib_json/json_valueiterator.inl \
    json/lib_json/json_value.cpp \
    json/lib_json/json_reader.cpp \
    json/lib_json/json_internalmap.inl \
    json/lib_json/json_internalarray.inl \
    renrentest.cpp \
    logindialog.cpp \
    mylabel.cpp \
    exchangethread.cpp \
    mybasedata.cpp \
    object.cpp \
    statuswidget.cpp \
    downloadfun.cpp \
    commentwidget.cpp

HEADERS += \
    src/librrapi/Utility.h \
    src/librrapi/Method.h \
    src/librrapi/MD5.h \
    src/librrapi/Config.h \
    src/libhttp/Http.h \
    include/UsersAPI.h \
    include/StatusAPI.h \
    include/RRAPI.h \
    include/RRAPI \
    include/Result.h \
    include/PhotosAPI.h \
    include/Permission.h \
    include/PayAPI.h \
    include/PagesAPI.h \
    include/NotificationsAPI.h \
    include/InvitationsAPI.h \
    include/Global.h \
    include/FriendsAPI.h \
    include/AdminAPI.h \
    json/writer.h \
    json/value.h \
    json/reader.h \
    json/json.h \
    json/forwards.h \
    json/features.h \
    json/config.h \
    json/autolink.h \
    json/lib_json/json_tool.h \
    json/lib_json/json_batchallocator.h \
    renrentest.h \
    logindialog.h \
    mylabel.h \
    exchangethread.h \
    mybasedata.h \
    object.h \
    statuswidget.h \
    downloadfun.h \
    commentwidget.h

OTHER_FILES += \
    src/json/lib_json/sconscript \
    json/lib_json/sconscript \
    html/test2.html \
    html/form.html \
    html/debug.html

FORMS += \
    renrentest.ui \
    logindialog.ui \
    statuswidget.ui \
    commentwidget.ui

RESOURCES += \
    html.qrc \
    images/images.qrc




