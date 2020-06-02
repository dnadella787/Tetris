#include "shape.h"

Shape::Shape(int cols, int rows, QColor color)
    : shape_col(cols)
    , shape_row(rows)
    , color(color)
{
    //making everything empty
   empty_coordinate();

    //draws the block with 30 x 30 sized
    block = new QPixmap(30, 30);
    QPainter painter;
    painter.begin(block);
    //setting the color
    painter.fillRect(block->rect(), color);
    //setting the boundary as darkGray
    painter.setPen(Qt::darkGray);
    painter.drawRect(0, 0, 30, 30);

}

void Shape::empty_coordinate(){
    for (int row = 0; row < shape_row; ++row){
        std::vector<bool> line;

        for (int col = 0; col < shape_col; ++col){
            line.push_back(false);
        }
        //creating row x col sized vector filled with false
        block_coordinate.push_back(line);
    }
}
Shape::~Shape(){
    delete block;
}

//returns the col
int Shape::get_col() const{
    return shape_col;
}

//returns the row
int Shape::get_row() const{
    return shape_row;
}
//returns the coordinate
bool Shape::filled(int col, int row) const
{
    return block_coordinate[row][col];
}
//now changes the false into true
void Shape::now_filled(int col, int row ){
    block_coordinate[row][col] = true;
}
//draw the square or block
void Shape::block_drawing(int col, int row, QPainter *painter){
    painter->drawPixmap(col * 30, row * 30, *block);

}
//draws the square or block for the next drawing
void Shape::nextBoard_drawing(int col, int row, QPainter *painter){
    painter->drawPixmap(col * 15, row * 15, *block);
}
//coordinate for the next shape
void Shape::newBlockCoordinates(int row, int col){
    int newRow = col;
    int newCol = row;

    std::vector<std::vector<bool>> newBlockCoordinates(newRow);

    for (size_t i = 0; i < newBlockCoordinates.size(); i++){
        newBlockCoordinates[i].resize(newCol);
    }


    for (int i = 0; i < shape_row; ++i) {
        for (int j = 0; j < shape_col; ++ j){
            newBlockCoordinates[j][newCol - 1 - i] = filled(j, i);
        }
    }

    shape_col = newCol;
    shape_row = newRow;
    block_coordinate = newBlockCoordinates;
}

