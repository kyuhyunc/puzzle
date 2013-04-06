#ifndef GUITILE_H
#define GUITILE_H
#include <QGraphicsRectItem>

class GUITile : public QGraphicsRectItem {
public:
    GUITile(int nx, int ny, int w, int h, int n);
    void setX( int nx );
    void setY( int ny );
    int getX();
    int getY();
    int getNumber();
    void move(int windowMaxX, int windowMaxY );

private:
    int x;
    int y;
    int width;
    int height;
    int number;

};

#endif // GUITILE_H
