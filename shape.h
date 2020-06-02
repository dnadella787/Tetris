#ifndef _SHAPE_H
#define _SHAPE_H
#include <QColor>
#include <QPainter>
#include <vector>

class Shape
{
public:
    Shape(int cols, int rows, QColor color);
    //creating the empty vector with rows by cols
    void empty_coordinate();
    //destructor
    virtual ~Shape();
    //returns the column
    int get_col() const;
    //returns the row
    int get_row() const;
    //check whether the specific coordinate is empty or not
    bool filled(int col, int row) const;
    //filling the specific coordinate
    void now_filled(int col, int row );
    //draw the block
    void block_drawing(int col, int row, QPainter *painter);
    //draw the next block
    void nextBoard_drawing(int col, int row, QPainter *painter);
    //creating the empty vector of the new block
    void newBlockCoordinates(int row, int col);

private:
    int shape_col;
    int shape_row;
    QColor color;
    std::vector<std::vector<bool> > block_coordinate;
    QPixmap *block;
};

#endif // SHAPE_H
