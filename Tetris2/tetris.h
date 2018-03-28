#ifndef TETRIS_H
#define TETRIS_H

#include <cstdlib>
#include <QtCore>
enum TetrisType{N,S,Z,I,L,O,J,T};//没有方块和七种方块

class Tetris
{
public:
    Tetris();
    void setTetrisType(TetrisType inType);
    void setType(TetrisType t){this->type = t;}
    void setRandomType();
    int getX(int i) const {return x[i];}
    int getY(int i) const {return y[i];}
    int getMinX() const;
    int getMinY() const;
    int getMaxX() const;
    int getMaxY() const;
    TetrisType getType(){return type;}
    void rotated();
    void setX(int i, int inX){x[i] = inX;}
    void setY(int i, int inY){y[i] = inY;}

private:
    int x[4], y[4];
    TetrisType type;
};

#endif // TETRIS_H
