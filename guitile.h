#ifndef GUITILE_H
#define GUITILE_H
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QGraphicsItem>
#include <QObject>
#include <iostream>


class GUITile : public QGraphicsRectItem, public QObject {
public:
    GUITile(int nx, int ny, int w, int h, int n, QString Qn);
    void setX( int nx );
    void setY( int ny );
    int getX();
    int getY();
    int getNumber();
  //  QGraphicsSimpleTextItem getQnumber();
  //  void move(int windowMaxX, int windowMaxY );
    
    QGraphicsSimpleTextItem Qnumber;
    
    void operator=(const GUITile &rhs);

signals:
		void myPressSignal();

protected:
		void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    int x;
    int y;
    int width;
    int height;
    int number;


};

#endif // GUITILE_H
