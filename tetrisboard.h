#ifndef _TETRISBOARD_H
#define _TETRISBOARD_H

#include <QtWidgets>
#include <QPainter>
#include "shape.h"
#include "difficulty.h"
#include "nextboard.h"
#include <QTimer>
#include <QSlider>

class Difficulty;

class TetrisBoard : public QWidget
{
    Q_OBJECT

public:
    //constructor
    //@ col = 10, rows = 20 the size of the tetrisboard
    TetrisBoard(int cols = 10, int rows = 20, QWidget *parent = nullptr);
    ~TetrisBoard();

    //now play is accessible
    friend class Play;
signals:
    //signals the next shape
    void changeNextShape();
    //signals the change of score
    void scorechanged(int score);
    //signals the change pf line
    void linechanged(int line);
    //signals the change of level
    void levelchanged(int level);

public slots:
    //newGame
    void newGame();
    //determine whether the shape can move down
    bool moveDown();
    //pause the game
    void pause();
    //play the game
    void play();
    //difficulty_level(easy)
    void setMode1();
    //difficulty_level(medium)
    void setMode2();
    //difficulty_level(hard)
    void setMode3();

protected:
    //draws the board
    void paintEvent(QPaintEvent *);
    //enables user to manipulate the shape using the key
    void keyPressEvent(QKeyEvent* event);

private:
    //Diffuclty d
    Difficulty d;
    //score, line, level
    int score;
    int line;
    int templevel = 1;
    int level;
    //index of newBlock
    int newBlock;
    //index of block after
    int blockAfter;
    //QSlier
    QSlider* blockAfterSlider;

    //board column
    int board_col;
    //board row
    int board_row;
    //shape col
    int shape_col;
    //shape row
    int shape_row;
    //next shape col and row
    int next_shape_col;
    int next_shape_row;
    //game over
    bool gameover;
    //Shape pointer (including all the shapes)
    Shape *shape;
    Shape *next_shape;
    Shape *I_shape;
    Shape *J_shape;
    Shape *L_shape;
    Shape *O_shape;
    Shape *S_shape;
    Shape *T_shape;
    Shape *Z_shape;
    Shape *empty;
    //tetris board bector
    std::vector<std::vector<Shape*>> board;
    //Timer
    QTimer *_timer = new QTimer();


    //keypress helper functions
    void moveLeft();
    void moveRight();
    void rotate();
    void hardDrop();

    void makeNewBlock();
    void changeNextBlock();

    //internal check map functions
    bool row_check(int row);
    bool col_check(int col);

    //repaint/update helper functions
    inline void block_erase();
    void put_block(bool clear = false);

    bool line_check(int row);

    void removeLine();
    void message();

    void Shape_Coordinates();

};

#endif
