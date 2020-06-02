#include "play.h"

Play::Play(QWidget *parent)
    : QMainWindow(parent), board(new TetrisBoard)
{

    this->setWindowTitle("Play Window");

    QWidget *widget = new QWidget;
    score_label = new QLabel("Score:");
    score = new QLCDNumber(5);
    score->setStyleSheet("background-color: white");
    score ->setSegmentStyle(QLCDNumber::Filled);

    line_label = new QLabel("Lines:");
    line = new QLCDNumber(5);
    line->setStyleSheet("background-color: white");
    line ->setSegmentStyle(QLCDNumber::Filled);

    next_label = new QLabel("Next Piece:");
    next = new NextBoard();
    next->setFixedSize(QSize(60, 45));

    difficulty_label = new QLabel("Difficulty:");
    difficulty = new QLabel("Easy");
    difficulty->setStyleSheet("Color: #24FF00; font: 9pt");

    level_label = new QLabel("Level");
    level = new QLCDNumber();
    level->setStyleSheet("background-color: white");

    play = new QPushButton("Play");
    play->setStyleSheet("QPushButton{ background-color:  #ABEBC6; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black }"
                        "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                        "QPushButton:hover:!pressed {color: white}");
    pause = new QPushButton("Pause");
    pause->setStyleSheet("QPushButton{ background-color:  #ABEBC6; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black }"
                         "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                         "QPushButton:hover:!pressed {color: white}");
    home = new QPushButton("Main");
    home->setStyleSheet("QPushButton{ background-color:  #ABEBC6; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black }"
                        "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                        "QPushButton:hover:!pressed {color: white}");

    QGridLayout *layout = new QGridLayout;


    // place widgets on specific coordinates of QGridLayout
    // place board on left column
    // place score display and buttons on right column
    layout->addWidget(score_label, 0, 3);
    layout->addWidget(score, 1, 3);
    layout->addWidget(line_label, 2, 3);
    layout->addWidget(line, 3, 3);
    layout->addWidget(next_label, 4,3);
    layout->addWidget(next, 5, 3, Qt::AlignCenter);
    layout->addWidget(difficulty_label, 6, 3);
    layout->addWidget(difficulty, 7, 3, Qt::AlignCenter);
    layout->addWidget(level_label, 8, 3);
    layout->addWidget(level, 9, 3);
    layout->addWidget(play, 10, 3);
    layout->addWidget(pause, 11, 3);
    layout->addWidget(home, 12, 3);
    layout->addWidget(board, 0, 0, 13, 3);
    next->blockAfter = next->blockAfter;

    widget->setStyleSheet("background-color: #7DB2C5");
    widget->setLayout(layout);
    this->setCentralWidget(widget);

    Connections();
    initializeBoard();
}


void Play::Connections(){
    QObject::connect(board->blockAfterSlider, SIGNAL(valueChanged(int)), next, SLOT(changeValue(int)));

    // set connections for buttons on the right column of Play class
    QObject::connect(home, SIGNAL(clicked()), this, SLOT(TransmitBackPlay()));
    QObject::connect(pause, SIGNAL(clicked()), board, SLOT(pause()));
    QObject::connect(play, SIGNAL(clicked()), board, SLOT(play()));

    // update score, line, and level on QLCD widgets
    QObject::connect(board, &TetrisBoard::scorechanged, score, QOverload<int>::of(&QLCDNumber::display));
    QObject::connect(board, &TetrisBoard::linechanged, line, QOverload<int>::of(&QLCDNumber::display));
    QObject::connect(board, &TetrisBoard::levelchanged, level, QOverload<int>::of(&QLCDNumber::display));

    // send current difficulty mode to TetrisBoard class
    QObject::connect(this, SIGNAL(resendMode1()), board, SLOT(setMode1()));
    QObject::connect(this, SIGNAL(resendMode2()), board, SLOT(setMode2()));
    QObject::connect(this, SIGNAL(resendMode3()), board, SLOT(setMode3()));
}

void Play::TransmitBackPlay(){
    emit TransmitBackClickPlay();
    this->close();
}


void Play::ShowPlayWindow(){
    this->show();
    initializeBoard();
}

void Play::initializeBoard()
{
    board->newGame();
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    board->setFocus();
}

void Play::receiveMode1() {
    // send current mode: easy to board
    difficulty->setText("Easy");
    difficulty->setStyleSheet("Color: #24FF00; font: 9pt");
    emit resendMode1();
}

void Play::receiveMode2() {
    // send current mode: medium to board
    difficulty->setText("Medium");
    difficulty->setStyleSheet("Color: #F800FF; font: 9pt");
    emit resendMode2();
}

void Play::receiveMode3() {
    // send current mode: hard to board
    difficulty->setText("Hard");
    difficulty->setStyleSheet("Color: #FF0000; font: 9pt");
    emit resendMode3();
}


Play::~Play() {
    delete board;
    delete score_label;
    delete score;
    delete line_label;
    delete line;
    delete next_label;
    delete next;
    delete difficulty_label;
    delete difficulty;
    delete level_label;
    delete level;
    delete play;
    delete pause;
    delete home;
}

