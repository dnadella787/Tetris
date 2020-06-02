#include "difficulty.h"

Difficulty::Difficulty(QWidget *parent) : QMainWindow(parent)
{

   this->setWindowTitle("Difficulty");

   window = new QWidget;
   layout = new QVBoxLayout;

   Title = new QLabel("Choose Level of Difficulty");
   currDifficulty = new QLabel("Current Difficulty: Easy");
   Easy = new QPushButton("Easy");
   Medium = new QPushButton("Medium");
   Hard = new QPushButton("Hard");
   SaveDifficulty = new QPushButton("Save");


   QRect screenSize = desktop.availableGeometry(this);

   const double screen_width = screenSize.width();
   const double screen_height = screenSize.height();
   const QSize button_size = QSize(screenSize.width()* 0.1f, screenSize.height() *0.07f);
   const QSize save_button_size = QSize(screenSize.width()* 0.07f, screenSize.height() *0.03f);

   layout->addWidget(Title);
   layout->addWidget(currDifficulty);
   layout->addWidget(Easy);
   layout->addWidget(Medium);
   layout->addWidget(Hard);
   layout->addWidget(SaveDifficulty);
   layout->setAlignment(SaveDifficulty, Qt::AlignCenter);

   // set styles and alignments of widgets
   Title->setAlignment(Qt::AlignCenter);
   Title->setStyleSheet("font: bold 25px; border-style: outset; border-width: 2px; border-radius: 10px; color: #00FFFF");
   Title->setFixedHeight(screenSize.height() * 0.06f);

   currDifficulty->setAlignment(Qt::AlignCenter);
   currDifficulty->setStyleSheet("font: bold 15px; border-style: outset; border-width: 2px; border-radius: 10px; color: #24FF00");
   currDifficulty->setFixedHeight(screenSize.height() * 0.06f);

   Easy->setMinimumSize(button_size);
   Easy->setStyleSheet("QPushButton{ background-color:  #24FF00; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                           "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                           "QPushButton:hover:!pressed {color: white}");

   Medium->setMinimumSize(button_size);
   Medium->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                         "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                         "QPushButton:hover:!pressed {color: white}");

   Hard->setMinimumSize(button_size);
   Hard->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                           "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                           "QPushButton:hover:!pressed {color: white}");

   SaveDifficulty->setFixedSize(save_button_size);
   SaveDifficulty->setStyleSheet("QPushButton{ font-weight: bold; background-color:  #ABEBC6}"
                                              "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                                              "QPushButton:hover:!pressed {color: #A9A9A9}");

   // set up connections of each button on difficulty window
   QObject::connect(SaveDifficulty,SIGNAL(clicked()),this,SLOT(HandleSaveButton()));
   QObject::connect(Easy, SIGNAL(clicked()), this, SLOT(ChangeEasyColor()));
   QObject::connect(Medium, SIGNAL(clicked()), this, SLOT(ChangeMediumColor()));
   QObject::connect(Hard, SIGNAL(clicked()), this, SLOT(ChangeHardColor()));

   // add background image
   QPixmap background(":/new/prefix1/TetrisBackground.png");
   background = background.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
   QPalette palette;
   palette.setBrush(QPalette::Background, background);
   this->setPalette(palette);

   // set margin and spacing
   layout->setContentsMargins(screen_width*0.05f, screen_height*0.02f, screen_width*0.05f, screen_height*0.05f);
   layout->setSpacing(screen_height *.03f);

   this->setFixedSize(QSize(screenSize.width()* 0.3f, screenSize.height() *0.7f));

   window->setLayout(layout);
   this->setCentralWidget(window);
}

void Difficulty::HandleSaveButton() {
   // send signal of save button click
   emit TransmitSaveClick();
   // send signal of current mode to mainwindow
   if (EasyClicked == true) {
       emit ModeSignal1();
   }
   else if (MediumClicked == true) {
       emit ModeSignal2();
   }
   else if (HardClicked == true) {
       emit ModeSignal3();
   }
   // close difficulty window
   this->close();
}

void Difficulty::ChangeEasyColor() {
   // set EasyClicked to true and false for others
   EasyClicked = true;
   MediumClicked = false;
   HardClicked = false;

   // change button styles upon click
   Easy->setStyleSheet("QPushButton{ background-color: #24FF00; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                       "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                       "QPushButton:hover:!pressed {color: white}");

   currDifficulty->setText("Current Difficulty: Easy");
   currDifficulty->setStyleSheet("font: bold 15px; border-style: outset; border-width: 2px; border-radius: 10px; color: #24FF00");

   Medium->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                         "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                         "QPushButton:hover:!pressed {color: white}");

   Hard->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                       "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                       "QPushButton:hover:!pressed {color: white}");
}

void Difficulty::ChangeMediumColor() {
   // set MediumClicked to true and false for others
   MediumClicked = true;
   EasyClicked = false;
   HardClicked = false;

   // change button styles upon click
   Medium->setStyleSheet("QPushButton{ background-color: #F800FF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                         "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                         "QPushButton:hover:!pressed {color: white}");

   currDifficulty->setText("Current Difficulty: Medium");
   currDifficulty->setStyleSheet("font: bold 15px; border-style: outset; border-width: 2px; border-radius: 10px; color: #F800FF");

   Easy->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                       "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                       "QPushButton:hover:!pressed {color: white}");

   Hard->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                       "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                       "QPushButton:hover:!pressed {color: white}");
}

void Difficulty::ChangeHardColor() {
   // set HardClicked to true and false for others
   HardClicked = true;
   EasyClicked = false;
   MediumClicked = false;

   // change button styles upon click
   Hard->setStyleSheet("QPushButton{ background-color: #FF0000; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                       "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                       "QPushButton:hover:!pressed {color: white}");

   currDifficulty->setText("Current Difficulty: Hard");
   currDifficulty->setStyleSheet("font: bold 15px; border-style: outset; border-width: 2px; border-radius: 10px; color: #FF0000");

   Easy->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                       "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                       "QPushButton:hover:!pressed {color: white}");

   Medium->setStyleSheet("QPushButton{ background-color: #00FFFF; border-style: outset; border-width: 2px; border-radius: 10px; border-color: black; font: bold 15px }"
                         "QPushButton:pressed { background-color: #92a8d1; border-style: inset }"
                         "QPushButton:hover:!pressed {color: white}");
}


void Difficulty::ShowDifficultyWindow() {
   // show current window
   this->show();
}


//destructor
Difficulty::~Difficulty(){
    delete window;
    delete layout;
    delete title_logo;
    delete Title;
    delete Easy;
    delete Medium;
    delete Hard;
    delete SaveDifficulty;
    delete currDifficulty;
}



