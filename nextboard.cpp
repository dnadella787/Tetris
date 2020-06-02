#include "nextboard.h"

NextBoard::NextBoard(int cols, int rows, QWidget *parent) : QWidget(parent), COLS(cols), ROWS(rows){
    //set the shapes
    Shape_Coordinates();

    //make vector of appropriate size
    for (int row = 0; row < ROWS; ++row) {
        board.push_back(std::vector<Shape*>(COLS));
    }

    //make them empty at first
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            board[row][col] = empty;
        }
    }

    //place the block
    putBlock();

    //repaint the block
    update();
}

void NextBoard::paintEvent(QPaintEvent *){
    QPainter painter;

    //paints each block what it is set to be
    painter.begin(this);
    for (int row = 0; row < ROWS; ++row){
        for (int col = 0; col < COLS; ++col){
            board.at(row).at(col)->nextBoard_drawing(col, row, &painter);
        }
    }
    painter.end();
}

void NextBoard::Shape_Coordinates(){
    //I
    I_shape = new Shape(1, 4, "#00D7FF");

    // J
    J_shape = new Shape(3, 2, "#3A64C8");

    // L
    L_shape = new Shape(3, 2, "#FFA200");

    // O
    O_shape = new Shape(2, 2, "#FFEF00");

    // S
    S_shape = new Shape(3, 2, "#09FF00");

    // T
    T_shape = new Shape(3, 2, "#DD00FF");

     // Z
    Z_shape = new Shape(3, 2, "#FF0000");

     //empty
    empty = new Shape(1, 1, Qt::black);

}

//sets all vector values to be empty
inline void NextBoard::eraseBlock(){
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            board[i][j] = empty;
        }
    }
}

//changes values in board vector based on the value of the index value of BlockAfter
void NextBoard::putBlock(){
    if (blockAfter == 0){
        for (int i = 0; i < 4; i++){
            board[1][i] = I_shape;
        }
    }
    else if (blockAfter == 1){
        board[2][1] = J_shape;
        for(int i = 0; i < 3; i++){
            board[i][2] = J_shape;
        }
    }
    else if (blockAfter == 2){
        board[2][2] = L_shape;
        for (int i = 0; i < 3; i++){
            board[i][1] = L_shape;
        }
    }
    else if (blockAfter == 3){
        for(int i = 1; i < 3; i++){
            for (int j = 1; j < 3; j++){
                board[j][i] = O_shape;
            }
        }
    }
    else if (blockAfter == 4){
        for (int i = 1; i < 3; i++){
            board[1][i] = S_shape;
        }
        for (int i = 0; i < 2; i++){
            board[2][i] = S_shape;
        }
    }
    else if (blockAfter == 5){
        board[1][1] = T_shape;
        for(int i = 0; i < 3; i++){
            board[2][i] = T_shape;
        }
    }
    else if (blockAfter == 6){
        for (int i = 0; i < 2; i++){
            board[1][i] = Z_shape;
        }
        for (int i = 1; i < 3; i++){
            board[2][i] = Z_shape;
        }
    }
}



//change blockAfter value via the connect statement from
void NextBoard::changeValue(int x){
    blockAfter = x;
    //update the board
    eraseBlock();
    putBlock();
    update();
}

NextBoard::~NextBoard() {
    delete I_shape;
    delete J_shape;
    delete L_shape;
    delete O_shape;
    delete S_shape;
    delete T_shape;
    delete Z_shape;
    delete empty;
}
