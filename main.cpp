#include "mainwindow.h"
#include "instruction.h"
#include "play.h"
#include "difficulty.h"
#include "tetrisboard.h"
#include "shape.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //initialize all windows but only show mainwindow first
    MainWindow w;
    w.show();

    Instructions s;
    Difficulty d;
    Play p;

    //these connections open and close all the windows
    QObject::connect(&w, SIGNAL(InstructionsOpen()), &s, SLOT(ShowInstructionsWindow()));
    QObject::connect(&s, SIGNAL(backClick()), &w, SLOT(ShowMainWindow()));
    QObject::connect(&w, SIGNAL(PlayOpen()), &p, SLOT(ShowPlayWindow()));
    QObject::connect(&p, SIGNAL(TransmitBackClickPlay()), &w, SLOT(ShowMainWindow()));
    QObject::connect(&w, SIGNAL(DifficultyOpen()), &d, SLOT(ShowDifficultyWindow()));
    QObject::connect(&d, SIGNAL(TransmitSaveClick()), &w, SLOT(ShowMainWindow()));

    //these change the game modes
    QObject::connect(&d, SIGNAL(ModeSignal1()), &w, SLOT(saveMode1()));
    QObject::connect(&d, SIGNAL(ModeSignal2()), &w, SLOT(saveMode2()));
    QObject::connect(&d, SIGNAL(ModeSignal3()), &w, SLOT(saveMode3()));
    QObject::connect(&w, SIGNAL(sendMode1()), &p, SLOT(receiveMode1()));
    QObject::connect(&w, SIGNAL(sendMode2()), &p, SLOT(receiveMode2()));
    QObject::connect(&w, SIGNAL(sendMode3()), &p, SLOT(receiveMode3()));

    //plays background music
    QMediaPlayer* music = new QMediaPlayer();
    music->setMedia((QUrl("qrc:/new/prefix1/tetrismusic.mp3")));
    music->setVolume(50);
    music->play();

    //connection to Instructions window to change volume
    QObject::connect(&s, SIGNAL(Volume(int)), music, SLOT(setVolume(int)));


    return a.exec();
}
