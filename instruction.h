#ifndef _Instructions_H
#define _Instructions_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QPixmap>
#include <QGridLayout>
#include <QPushButton>

class Instructions : public QMainWindow
{
    Q_OBJECT
public:
    //constructor
    explicit Instructions(QWidget *parent = nullptr);
    //destructor
    ~Instructions();
signals:
    //set volume signal
    void Volume(int value);
    //click back signal
    void backClick();

public slots:
    //show the Instructions window
    void ShowInstructionsWindow();
    //change volume
    void changeVolume(int value);
    void VolumeChange(int value);
    //go back to mainwindow
    void TransmitBackClickInstructions();

private:
    //handles all connections
    void Connections();

    //music related fields
    QLabel* vol;
    QLabel* vol_value;
    int volume;
    QSlider* music_slider;


    //keybindings/instructions
    QLabel* bind_title;
    QLabel* bind_space;
    QLabel* bind_side;
    QLabel* bind_up;
    QLabel* bind_down;
    QLabel* space_instruc;
    QLabel* up_instruc;
    QLabel* down_instruc;
    QLabel* side_instruc;

    //exit button
    QPushButton* back_button;

    //layout fields
    QVBoxLayout* layout_one;
    QHBoxLayout* layout_two;

    QHBoxLayout* layout_space;
    QHBoxLayout* layout_side;
    QHBoxLayout* layout_up;
    QHBoxLayout* layout_down;

    QWidget* widget;

    //used to make window size
    QDesktopWidget desktop;
};



#endif // Instructions_H
