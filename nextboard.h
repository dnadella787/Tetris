#ifndef NEXTBOARD_H
#define NEXTBOARD_H

#include <QWidget>
#include "shape.h"
//#include "TetrisBoard.h"
#include <QDesktopWidget>

class NextBoard : public QWidget
{
    Q_OBJECT
public:
    // constructor
    explicit NextBoard(int cols = 4, int rows = 3, QWidget *parent = nullptr);
    // destructor
    ~NextBoard();
    //play class is a friend so it can get the next block from TetrisBoard
    friend class Play;
protected:
    void paintEvent(QPaintEvent *);
public slots:
    //slot to change value of afterBlock inside NextBoard from TetrisBoard
    void changeValue(int x);
signals:

    void ChangeAfterBlock(int x);
private:
    //deskto obj to size objects properly
    QDesktopWidget desktop;

    //the board itself that is written into
    std::vector<std::vector<Shape*> > board;
    //board size
    int COLS, ROWS;

    //index of block that is next
    int blockAfter;

    //all possible shapes
    Shape *I_shape;
    Shape *J_shape;
    Shape *L_shape;
    Shape *O_shape;
    Shape *S_shape;
    Shape *T_shape;
    Shape *Z_shape;
    Shape *empty;

    //gives the shapes the proper color
    void Shape_Coordinates();

    //removes current block
    void eraseBlock();
    //places the next block
    void putBlock();

};

#endif // NEXTBOARD_H
