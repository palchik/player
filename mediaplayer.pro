QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mediaplayrer
TEMPLATE = app

HEADERS += \
    player.h \
    controls.h \
    video.h \
    multiplayer.h \
    audipplayer.h

SOURCES += \
    player.cpp \
    main.cpp \
    controls.cpp \
    video.cpp \
    multiplayer.cpp \
    audipplayer.cpp

FORMS +=

RESOURCES += \
    images.qrc
