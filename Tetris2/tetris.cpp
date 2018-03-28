#include "tetris.h"

Tetris::Tetris()
{
    setTetrisType(N);
}
void Tetris::setTetrisType(TetrisType inType)
{
    type = inType;
    int tetrisid = (int)type;
    switch(tetrisid)
    {
    case 1:
        x[0] = -1, y[0] =1;
        x[1] = 0, y[1] =1;
        x[2] = 0, y[2] =0;
        x[3] = 1, y[3] =0;
        break;
    case 2:
        x[0] = -1, y[0] =0;
        x[1] = 0, y[1] =0;
        x[2] = 0, y[2] =1;
        x[3] = 1, y[3] =1;
        break;
    case 3:
        x[0] = 0, y[0] =-1;
        x[1] = 0, y[1] =0;
        x[2] = 0, y[2] =1;
        x[3] = 0, y[3] =2;
        break;
    case 4:
        x[0] = 0, y[0] =-1;
        x[1] = 0, y[1] =0;
        x[2] = 0, y[2] =1;
        x[3] = 1, y[3] =1;
        break;
    case 5:
        x[0] = 0, y[0] =0;
        x[1] = 1, y[1] =0;
        x[2] = 0, y[2] =1;
        x[3] = 1, y[3] =1;
        break;
    case 6:
        x[0] = 0, y[0] =-1;
        x[1] = 0, y[1] =0;
        x[2] = 0, y[2] =1;
        x[3] = -1, y[3] =1;
        break;
    case 7:
        x[0] = -1, y[0] =0;
        x[1] = 0, y[1] =0;
        x[2] = 0, y[2] =1;
        x[3] = 1, y[3] =0;
        break;
    case 0:
    default:
        x[0] = 0, y[0] =0;
        x[1] = 0, y[1] =0;
        x[2] = 0, y[2] =0;
        x[3] = 0, y[3] =0;
        break;
    }
}
void Tetris::setRandomType()
{
    int Ttypeid = qrand()%7 + 1;
    setTetrisType((TetrisType)Ttypeid);
}

int Tetris::getMinX() const
{
    int min = x[0];
    for(int i=1; i<4;i++)
        min = qMin(min,x[i]);
    return min;
}
int Tetris::getMinY() const
{
    int min = y[0];
    for(int i=1;i<4;i++)
        min = qMin(min,y[i]);
    return min;
}
int Tetris::getMaxX() const
{
    int max = x[0];
    for(int i=1;i<4;i++)
        max = qMax(max,x[i]);
    return max;
}
int Tetris::getMaxY() const
{
    int max = y[0];
    for(int i=0; i<4; i++)
        max = qMax(max,y[i]);
    return max;
}
void Tetris::rotated()
{
    if(type == O)
        return;
    Tetris result;
    result.type = type;
    for(int i=0; i<4; i++)
    {
        result.setX(i,-getY(i));
        result.setY(i,getX(i));
    }
    for(int i=0; i<4; i++)
    {
        setX(i,result.getX(i));
        setY(i,result.getY(i));
    }
}
