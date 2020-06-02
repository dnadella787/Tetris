#ifndef _DIFFICULTY_H
#define _DIFFICULTY_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDesktopWidget>


class Difficulty : public QMainWindow
{
   Q_OBJECT
public:
   explicit Difficulty(QWidget *parent = nullptr);
   ~Difficulty();
public slots:
  /*
  Function that shows the difficulty window
  Receives connection from difficulty button from mainwindow.h
  */
  void ShowDifficultyWindow();

  /*
  Function that saves difficulty mode
  and sends user back to the mainwindow
  */
  void HandleSaveButton();

  /*
  Change style of button color upon click
  Change screen text display of current difficulty to "easy"
  */
  void ChangeEasyColor();

  /*
  Change style of button color upon click
  Change screen text display of current difficulty to "medium"
  */
  void ChangeMediumColor();

  /*
  Change style of button color upon click
  Change screen text display of current difficulty to "hard"
  */
  void ChangeHardColor();

signals:
  // send signal of save button click
   void TransmitSaveClick();

   // send signal of current mode
   void ModeSignal1();
   void ModeSignal2();
   void ModeSignal3();

private:
  QWidget* window;
  QVBoxLayout* layout;
  QPixmap logo;
  QLabel* title_logo;
  QLabel* Title;
  QPushButton* Easy;
  QPushButton* Medium;
  QPushButton* Hard;
  QPushButton* SaveDifficulty;
  QDesktopWidget desktop;
  QLabel* currDifficulty;
  bool EasyClicked = false;
  bool MediumClicked = false;
  bool HardClicked = false;

};

#endif // DIFFICULTY_H


