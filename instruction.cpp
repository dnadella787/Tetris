#include "instruction.h"

Instructions::Instructions(QWidget *parent) : QMainWindow(parent)
{

    this->setWindowTitle("Instruction");

    //set size of objects to computer based specifics
    QRect screenSize = desktop.availableGeometry(this);

    //const variables
    const double screen_width = screenSize.width();
    const double screen_height = screenSize.height();
    const QSize button_size = QSize(screenSize.width()* 0.07f, screenSize.height() *0.035f);


    //initializations
    volume = 50;
    widget = new QWidget();
    layout_one = new QVBoxLayout();
    layout_two = new QHBoxLayout();
    layout_up = new QHBoxLayout();
    layout_down = new QHBoxLayout();
    layout_space = new QHBoxLayout();
    layout_side = new QHBoxLayout();

    back_button = new QPushButton("Back");


    //set all QLabels to output the proper instructions and key
    back_button = new QPushButton("Back");

    bind_title = new QLabel("Keys:");
    bind_title->setStyleSheet("QLabel {Color: #00FFFF; font: 15pt; font-weight: bold}");
    bind_title->setAlignment(Qt::AlignCenter);
    bind_space = new QLabel("Space");
    bind_space->setStyleSheet("QLabel {Color: #00FFFF; font: 9pt; font-weight: bold}");
    bind_up = new QLabel("Up");
    bind_up->setStyleSheet("QLabel {Color: #00FFFF; font: 9pt; font-weight: bold}");
    bind_down = new QLabel("Down");
    bind_down->setStyleSheet("QLabel {Color: #00FFFF; font: 9pt; font-weight: bold}");
    bind_side = new QLabel("Right/Left");
    bind_side->setStyleSheet("QLabel {Color: #00FFFF; font: 9pt; font-weight: bold}");


    space_instruc = new QLabel("Press to instantly drop the shape");
    space_instruc->setStyleSheet("QLabel {Color: #00FFFF; font: 9pt; font-weight: bold}");
    up_instruc = new QLabel("Press to rotate shape clockwise");
    up_instruc->setStyleSheet("QLabel {Color: #00FFFF; font: 9pt; font-weight: bold}");
    down_instruc = new QLabel("Press to quickly drop the shape");
    down_instruc->setStyleSheet("QLabel {Color: #00FFFF; font: 9pt; font-weight: bold}");
    side_instruc = new QLabel("Press to move shape right/left");
    side_instruc->setStyleSheet("QLabel {Color: #00FFFF; font: 9pt; font-weight: bold}");


    //volume label
    vol = new QLabel("Volume");
    vol->setStyleSheet("QLabel {Color:  #00FFFF; font: 15pt ; font-weight: bold}");
    vol->setAlignment(Qt::AlignCenter);

    //current value of volume
    vol_value = new QLabel(QString::number(volume));
    vol_value->setStyleSheet("QLabel {Color:  #00FFFF; font: 13pt ; font-weight: bold}");

    //slider for music
    music_slider = new QSlider(Qt::Horizontal);
    music_slider->setRange(0,100);
    music_slider->setValue(50); //preset to be 50


    //add all members to layout_one, the main layout
    layout_one->addWidget(bind_title);


    layout_two->addWidget(vol_value);
    layout_two->addWidget(music_slider);


    layout_one->addLayout(layout_space);
    layout_one->addLayout(layout_up);
    layout_one->addLayout(layout_side);
    layout_one->addLayout(layout_down);
    layout_one->addWidget(vol);
    layout_one->addLayout(layout_two);
    layout_one->addWidget(back_button);
    layout_one->setAlignment(back_button, Qt::AlignCenter);


    layout_up->addWidget(bind_up);
    layout_up->addWidget(up_instruc);
    layout_space->addWidget(bind_space);
    layout_space->addWidget(space_instruc);
    layout_side->addWidget(bind_side);
    layout_side->addWidget(side_instruc);
    layout_down->addWidget(bind_down);
    layout_down->addWidget(down_instruc);


    layout_one->setContentsMargins(screen_width*0.05f, screen_height*0.02f, screen_width*0.05f, screen_height*0.05f);
    layout_one->setSpacing(30);

    //set screen size
    this->setFixedSize(QSize(screen_width * 0.3f, screen_height * 0.7f));

    //style back button
    back_button->setStyleSheet("QPushButton{ font-weight: bold; background-color:  #ABEBC6}"
                                "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                                "QPushButton:hover:!pressed {color: #A9A9A9}");
    //set size
    back_button->setFixedSize(button_size);

    widget->setLayout(layout_one);
    this->setCentralWidget(widget);

    //add tetris background to main window
    QPixmap background(":/new/prefix1/TetrisBackground.png");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    //set up connections
    Connections();
}

void Instructions::Connections(){
    //if music slider value changes, then set the value of the volume label to be the value of the slider
    QObject::connect(music_slider, SIGNAL(valueChanged(int)), vol_value, SLOT(setNum(int)));
    //if music slider value changes then the internal volume integer is changed
    QObject::connect(music_slider, SIGNAL(valueChanged(int)), this, SLOT(changeVolume(int)));
    //if music slider value changes then change the volume in main.cpp
    QObject::connect(music_slider, SIGNAL(valueChanged(int)), this, SLOT(VolumeChange(int)));
    //go back
    QObject::connect(back_button, SIGNAL(clicked()), this, SLOT(TransmitBackClickInstructions()));
}

//go back by closing this window and emitting a black click that causes mainwindow shows
void Instructions::TransmitBackClickInstructions(){
    emit backClick();
    this->close();
}

//change volume in main
void Instructions::VolumeChange(int value){
    emit Volume(value);
}

//show the Instructions window
void Instructions::ShowInstructionsWindow(){
    this->show();
}

//set volume to be the value from music_slider
void Instructions::changeVolume(int value){
    this->volume = value;
}

//destructor
Instructions::~Instructions(){
    delete vol;
    delete vol_value;
    delete music_slider;


    //keybindings/instructions
    delete bind_title;
    delete bind_space;
    delete bind_side;
    delete bind_up;
    delete bind_down;
    delete space_instruc;
    delete up_instruc;
    delete down_instruc;
    delete side_instruc;

    //exit button
    delete back_button;


    //layout fields
    delete layout_one;
    delete layout_two;

    delete layout_space;
    delete layout_side;
    delete layout_up;
    delete layout_down;

    delete widget;
    delete layout_one;
}
