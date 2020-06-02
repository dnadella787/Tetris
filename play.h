#ifndef _PLAY_H
#define _PLAY_H

#include "tetrisboard.h"
#include "shape.h"
#include <QMainWindow>
#include <QGridLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QFrame>
#include <QWidget>
#include <QTimer>
#include "nextboard.h"
#include "difficulty.h"

class TetrisBoard;

class Play : public QMainWindow
{
    Q_OBJECT

public:
    Play(QWidget *parent = nullptr);
    ~Play();

signals:
    // send signal of play button click
    void TransmitBackClickPlay();

    //send received current mode from difficulty.h to tetrisboard.h
    void resendMode1();
    void resendMode2();
    void resendMode3();

public slots:
    /*
    Function that executes when play button is clicked from mainwindow
    opens play window
    */
    void ShowPlayWindow();

    /*
    sends signal "TransmitBackClickPlay()"
    closes current play window
    */
    void TransmitBackPlay();

    // receive current mode from difficulty.h
    void receiveMode1();
    void receiveMode2();
    void receiveMode3();

private:
    Difficulty d;
    TetrisBoard *board;
    QLabel *score_label;
    QLCDNumber *score;
    QLabel *line_label;
    QLCDNumber *line;
    QLabel* next_label;
    NextBoard *next;
    QLabel *difficulty_label;
    QLabel *difficulty;
    QLabel *level_label;
    QLCDNumber *level;
    QPushButton *play;
    QPushButton *pause;
    QPushButton *home;

    /*
    Contains all of the connections associated with Play class
    */
    void Connections();

    /*
    Function that initializes Tetrisboard
    start new game and set focus to board
    */
    void initializeBoard();

private slots:

};
#endif // PLAY_H
