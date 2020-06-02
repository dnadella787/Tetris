#include "tetrisboard.h"

TetrisBoard::TetrisBoard(int cols, int rows, QWidget *parent) : QWidget(parent),
    board_col(cols), board_row(rows) {
    blockAfterSlider = new QSlider();
    blockAfterSlider->setRange(0,7);
    //calling the coordinate of every shape
    Shape_Coordinates();
    //setting the board size
    setFixedSize(board_col * 30, board_row * 30);
    //creating the board
    for (int row = 0; row < board_row; ++row) {
        board.push_back(std::vector<Shape*>(board_col));
    }
    //connecting the timer
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(moveDown()));
    //calling new game
    newGame();
}

void TetrisBoard::makeNewBlock() {
    //Type of Block
    Shape *Shapes[] = {I_shape, J_shape, L_shape, O_shape, S_shape, T_shape, Z_shape};
    srand(time(nullptr));
    //rand number
    newBlock = rand() % 7;
    blockAfter = rand() % 7;

    blockAfterSlider->setValue(blockAfter);

    shape = Shapes[newBlock];
    next_shape = Shapes[blockAfter];

    // at the middle of column
    shape_col = (board_col - shape->get_col()) / 2;
    // at the end of row
    shape_row = 0;

    next_shape_col = (board_col - (next_shape->get_col())) / 2;
    next_shape_row = 0;
}
//determining the next shape
void TetrisBoard::changeNextBlock(){
    shape = next_shape;
    shape_col = next_shape_col;
    shape_row = next_shape_row;
    _timer->start(1000 - level * 100);
    //amonog them choose one
    Shape *Shapes[] = {I_shape, J_shape, L_shape, O_shape, S_shape, T_shape, Z_shape};
    srand(time(nullptr));
    blockAfter = rand() % 7;
    blockAfterSlider->setValue(blockAfter);

    next_shape = Shapes[blockAfter];

}
//defining the coordinate of all the shape and color
void TetrisBoard::Shape_Coordinates(){
    //I
    I_shape = new Shape(1, 4, "#00D7FF");
    I_shape->now_filled(0, 0);
    I_shape->now_filled(0, 1);
    I_shape->now_filled(0, 2);
    I_shape->now_filled(0, 3);

    // J
    J_shape = new Shape(3, 2, "#3A64C8");
    J_shape->now_filled(0, 0);
    J_shape->now_filled(0, 1);
    J_shape->now_filled(1, 1);
    J_shape->now_filled(2, 1);

    // L
    L_shape = new Shape(3, 2, "#FFA200");
    L_shape->now_filled(0, 0);
    L_shape->now_filled(1, 0);
    L_shape->now_filled(2, 0);
    L_shape->now_filled(0, 1);

    // O
    O_shape = new Shape(2, 2, "#FFEF00");
    O_shape->now_filled(0, 0);
    O_shape->now_filled(1, 0);
    O_shape->now_filled(0, 1);
    O_shape->now_filled(1, 1);

    // S
    S_shape = new Shape(3, 2, "#09FF00");
    S_shape->now_filled(1, 0);
    S_shape->now_filled(2, 0);
    S_shape->now_filled(0, 1);
    S_shape->now_filled(1, 1);

    // T
    T_shape = new Shape(3, 2, "#DD00FF");
    T_shape->now_filled(0, 0);
    T_shape->now_filled(1,0);
    T_shape->now_filled(2,0);
    T_shape->now_filled(1, 1);

     // Z
    Z_shape = new Shape(3, 2, "#FF0000");
    Z_shape->now_filled(0, 0);
    Z_shape->now_filled(1, 0);
    Z_shape->now_filled(1,1);
    Z_shape->now_filled(2,1);

     //empty
    empty = new Shape(1, 1, Qt::black);
    empty->now_filled(0, 0);

}
//destructor
TetrisBoard::~TetrisBoard(){
    delete shape;
    delete I_shape;
    delete J_shape;
    delete L_shape;
    delete O_shape;
    delete S_shape;
    delete T_shape;
    delete Z_shape;
    delete empty;
}
//calling new game
void TetrisBoard::newGame(){
    gameover = false;

    for (int row = 0; row < board_row; ++row)
    {
        for (int col = 0; col < board_col; ++col)
        {
            board[row][col] = empty;
        }
    }

    score = 0;
    line = 0;

    makeNewBlock(); //create the block

    if (templevel == 1) { //easy level, by default
        level = 1 + score / 40;
    }
    else if (templevel == 3) {//medium
        level = 3 + score / 40;
    }
    else if (templevel == 5) { //hard
        level = 5 + score / 40;
    }

    if (line % 3 == 0) { //increase the speed
        _timer->start(1000 - level*100);
    }

    emit scorechanged(score); //emits the score
    emit levelchanged(level); //emits the level
    emit linechanged(line);//emits the line

    _timer->stop(); //stops the timer

    update();
}

void TetrisBoard::paintEvent(QPaintEvent *){
    QPainter painter;

    painter.begin(this);
    for (int row = 0; row < board_row; ++row){
        for (int col = 0; col < board_col; ++col){
            board[row][col]->block_drawing(col, row, &painter);
        }
    }
    painter.end();
}

void TetrisBoard::pause() {
    _timer->stop(); //stops the time
}

void TetrisBoard::play() {
    _timer->start(1000 - level*100); //changes level
    this->setFocus();
}

bool TetrisBoard::moveDown(){
    for (int c = 0; c < shape->get_col(); ++c){
        int r;
        //finding the lowest piece
        for (r = shape->get_row() - 1; r >= 0; --r){
            if (shape->filled(c, r)){
                break;
            }
        }

        int col = c + shape_col;
        int row = r + shape_row;

        if (row + 1 == board_row || (row_check(row) && board[row + 1][col] != empty)){
            if (shape_row < 1) {
                //gameover
                 gameover = true;
                _timer->stop();
                if(gameover) {
                    message();
                }
            }
            else {
                removeLine(); //remove line
                for (size_t i = 0; i < board.at(0).size(); i++) {
                    if(board.at(0).at(i) != empty) {
                        gameover = true;
                    }
                }
                if(gameover){
                    _timer->stop();
                    message(); //gameover message
                    return false;
                }
                changeNextBlock();

            }
            update();
            return false;
        }
    }
    block_erase();
    ++shape_row; //shifts the coordinate
    put_block();
    update();
    return true;
}

 void TetrisBoard::moveLeft(){
     //if the shape is already at the very left dont do anything
     if (shape_col <= 0){
         return;
     }

     //go through every row the current shape is occupying
     for (int i = 0; i < shape->get_row(); i++){
         int j;
         //now go to the left most block in each of these rows
         for (j = 0; j < shape->get_col(); j++){
             //if this position is filled then exit on this position
             if (shape->filled(j, i)){
                 break;
             }
         }

         //find thte position of the left most blocks in the piece in reference to the entire map
         int col = j + shape_col;
         int row = i + shape_row;

         //if the same block found to be filled one column to the left, and same row is not empty, don't do anything
         if (board.at(row).at(col - 1) != empty)
             return;
     }

     //remove the block
     block_erase();

     //move current shape column one to the left.
     shape_col--;

     //place the block
     put_block();

     //update
     update();
 }

 void TetrisBoard::moveRight(){
     //if right most piece of shape is already at the right dont do anything
     if(shape_col + shape->get_col() >= 10){
         return;
     }

     //go through all rows the shape occupies
     for(int i = 0; i < shape->get_row(); i++){
         int j;
         //find the right most block in each row
         //thats why start at right
         for(j = shape->get_col() - 1; j >= 0; j--){
             //if this block is filled then break
             if (shape->filled(j,i)){
                 break;
             }
         }

         //find the positon of the right most blocks of the piece in reference to the map
         int row = i + shape_row;
         int col = j + shape_col;

         //if the position one to the right is  not empty, do nothing.
         if(board[row][(col + 1)] != empty){
             return;
         }
     }

     //erase the block
     block_erase();

     //change the column to one to the right
     shape_col++;

     //replace all the blocks now
     put_block();

     //update
     update();
 }



void TetrisBoard::rotate(){
    //first erase the block
    block_erase();
    //create new boundaries and rotate the shape
    shape->newBlockCoordinates(shape->get_row(), shape->get_col());

    //go through all rows in the shape
    for (int r = 0; r < shape->get_row(); ++r) {
        //go through all columns in the shape
        for (int c = 0; c < shape->get_col(); ++c) {
            //if the new rows that the block would occupy are outside of the map scope, set shape back to original orientation
            //if the new columns that the block would occupy are outside of of the map scope, set shape back to original orientation
            //if specific position are not empty, then set shape back to original orientation
            if (!row_check(r + shape_row) || !col_check(c + shape_col) || (shape->filled(c, r)  && board[(r + shape_row)][(c + shape_col)] != empty)) {
                shape->newBlockCoordinates(shape->get_row(), shape->get_col());
                put_block();
                return;
            }
        }
    }
}

void TetrisBoard::hardDrop(){
    //continue the move down function until it returns false, i.e. when bottom is reached
    while(moveDown()){}
}

//defining the key
void TetrisBoard::keyPressEvent(QKeyEvent* event){
     switch(event->key()){
     case Qt::Key_Left:
         moveLeft();//move left
         break;
     case Qt::Key_Right:
         moveRight(); //move right
         break;
     case Qt::Key_Down:
         moveDown();//move down
         break;
     case Qt::Key_Up:
         rotate();//rotate
         break;
     case Qt::Key_Space:
         hardDrop(); //drop when space is pressed
         break;
     default:
         QWidget::keyPressEvent(event);
     }

 }
//check the row
bool TetrisBoard::row_check(int row){
    return row >= 0 && row < board_row;
}
//check the column
bool TetrisBoard::col_check(int col){
    return col >= 0 && col < board_col;
}
//erase the block
inline void TetrisBoard::block_erase(){
    put_block(true);
}
//putting the block
void TetrisBoard::put_block(bool clear){
    Shape *block = clear ? empty : shape;

    for (int r = 0, row = shape_row; r < shape->get_row(); ++r, ++row){
        for (int c = 0, col = shape_col; c < shape->get_col(); ++c, ++col){
            if (row_check(row) && col_check(col) && shape->filled(c, r)){
                board[row][col] = block;
            }
        }
    }
}

//difficulty level
void TetrisBoard::setMode1() {
    templevel = 1;
}

void TetrisBoard::setMode2() {
    templevel = 3;
}

void TetrisBoard::setMode3() {
    templevel = 5;
}

bool TetrisBoard::line_check(int row) {
    int count = 0;
    for(int col = 0; col < board_col; col++) {
        if(board[row][col] != empty) {
            ++count;
        }
    }
    return count == board_col; //if count equals board_col, the row is filled with the shape
}

void TetrisBoard::removeLine() {
    std::vector<Shape*>empty_line(board_col, empty);
    for(int row = 0; row < board_row; ++row) {
        if(line_check(row)) {
            board.erase(board.begin() + row); //erase the line
            board.insert(board.begin() + 1, empty_line);//insert the new line
            score = score + 10;
            line = line + 1;
            if (line % 3 == 0) {
                level++; //increases level
            }
        }
    }

//emitting score, line, level
    emit scorechanged(score);
    emit linechanged(line);
    emit levelchanged(level);

}

void TetrisBoard::message() {
    newGame();
    _timer->stop();
    QMessageBox::information(this, qApp->applicationDisplayName(), tr("Game Over")); //gameover message
}
