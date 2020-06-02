#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Tetris Main Menu");


    //initializations
    window = new QWidget;
    layout = new QVBoxLayout;

    Title = new QLabel("Tetris");
    title_logo = new QLabel();
    PlayGame = new QPushButton("Play");
    Levels = new QPushButton("Difficulty");
    Instructions = new QPushButton("Instruction");


    //code to create logo
    logo.load(":/new/prefix1/logo.png");
    title_logo->setPixmap(logo);
    title_logo->setScaledContents( true );
    title_logo->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );


    //add widgets to layout
    layout->addWidget(title_logo);
    layout->addWidget(PlayGame);
    layout->addWidget(Levels);
    layout->addWidget(Instructions);


    //customize buttons using CSS style
    PlayGame->setStyleSheet("QPushButton{ background-color:  #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 25px }"
                        "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                        "QPushButton:hover:!pressed {color: white}");

    Levels->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 25px }"
                                "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                                "QPushButton:hover:!pressed {color: white}");

    Instructions->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 25px }"
                               "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                               "QPushButton:hover:!pressed {color: white}");




    //set size of objects to computer based specifics
    QRect screenSize = desktop.availableGeometry(this);

    //const variables
    const double screen_width = screenSize.width();
    const double screen_height = screenSize.height();
    const QSize title_logo_size = QSize(screenSize.width()* 0.2f, screenSize.height() *0.17f);
    const QSize button_size = QSize(screenSize.width()* 0.2f, screenSize.height() *0.1f);

    //for logo
    title_logo->setFixedSize(title_logo_size);
    layout->setContentsMargins(screen_width*0.05f, screen_height*0.02f, screen_width*0.05f, screen_height*0.05f);
    title_logo->setContentsMargins(0,0,0,screen_height*0.7f);
    layout->setSpacing(screen_height *.03f);

    //for buttons
    PlayGame->setMinimumSize(button_size);
    Levels->setMinimumSize(button_size);
    Instructions->setMinimumSize(button_size);

    //for main window
    this->setFixedSize(QSize(screen_width * 0.3f, screen_height * 0.7f));


    //add layout and widget to MainWindow
    window->setLayout(layout);
    this->setCentralWidget(window);

    //add tetris background to main window
    QPixmap background(":/new/prefix1/TetrisBackground.png");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    Connections();
}


void MainWindow::Connections() {
    QObject::connect(Instructions,SIGNAL(clicked()),this,SLOT(TransmitInstructionsOpen()));
    QObject::connect(PlayGame, SIGNAL(clicked()), this, SLOT(TransmitPlayOpen()));
    QObject::connect(Levels, SIGNAL(clicked()), this , SLOT(TransmitDifficultyOpen()));
}

void MainWindow::ShowMainWindow(){
    this->show();
}

void MainWindow::TransmitPlayOpen(){
    this->hide();
    emit PlayOpen();
}


void MainWindow::TransmitInstructionsOpen(){
    this->hide();
    emit InstructionsOpen();
}

void MainWindow::TransmitDifficultyOpen(){
    this->hide();
    emit DifficultyOpen();
}

void MainWindow::saveMode1() {
    emit sendMode1();
}

void MainWindow::saveMode2() {
    emit sendMode2();
}

void MainWindow::saveMode3() {
    emit sendMode3();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete window;
    delete layout;

    //objects in mainwindow
    delete title_logo;
    delete Title;
    delete PlayGame;
    delete Levels;
    delete Instructions;

    //music related objects
    delete playlist;
    delete music;
}

