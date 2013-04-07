#ifndef GUITILE_H
#define GUITILE_H
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QObject>
#include <QGraphicsItem>
#include <iostream>


class GUITile : public QObject, public QGraphicsRectItem{
		Q_OBJECT
				
public:
    GUITile(int nx, int ny, int w, int h, int n, QString Qn);
    void setX( int nx );
    void setY( int ny );
    int getX();
    int getY();
    int getNumber();
//  void move(int windowMaxX, int windowMaxY );
    
    QGraphicsSimpleTextItem Qnumber;
    
    void operator=(const GUITile &rhs);

signals:
		void myPressSignal(int number);

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
