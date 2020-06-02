
#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QDesktopWidget>
#include <QRect>
#include <QSize>
#include <QMediaPlaylist>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void InstructionsOpen();
    void PlayOpen();
    void DifficultyOpen();
    void sendMode1();
    void sendMode2();
    void sendMode3();

public slots:
    void ShowMainWindow();
    void TransmitInstructionsOpen();
    void TransmitPlayOpen();
    void TransmitDifficultyOpen();
    void saveMode1();
    void saveMode2();
    void saveMode3();

private:

    void Connections();

    Ui::MainWindow *ui;

    //deskto obj to size objects properly
    QDesktopWidget desktop;


    //widget and layout object to add buttons and logo to
    QWidget* window;
    QVBoxLayout* layout;


    //objects in mainwindow
    QPixmap logo;
    QLabel* title_logo;
    QLabel* Title;
    QPushButton* PlayGame;
    QPushButton* Levels;
    QPushButton* Instructions;


    //music related objects
    QMediaPlaylist* playlist;
    QMediaPlayer* music;


};
#endif // MAINWINDOW_H
