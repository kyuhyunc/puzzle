#ifndef GUITILE_H
#define GUITILE_H
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QGraphicsItem>

class GUITile : public QGraphicsRectItem {
public:
    GUITile(int nx, int ny, int w, int h, int n, QString Qn);
    void setX( int nx );
    void setY( int ny );
    int getX();
    int getY();
    int getNumber();
  //  QGraphicsSimpleTextItem getQnumber();
    void move(int windowMaxX, int windowMaxY );
    
    QGraphicsSimpleTextItem Qnumber;

private:
    int x;
    int y;
    int width;
    int height;
    int number;


};

#endif // GUITILE_H
