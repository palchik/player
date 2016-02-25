QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mediaplayrer
TEMPLATE = app

HEADERS += \
    player.h \
    controls.h \
    video.h \
    audipplayer.h \
    mainwin.h

SOURCES += \
    player.cpp \
    main.cpp \
    controls.cpp \
    video.cpp \
    audipplayer.cpp \
    mainwin.cpp

FORMS +=

RESOURCES += \
    images.qrc
