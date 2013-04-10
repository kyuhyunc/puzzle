#include "guitile.h"

#define x_letter_scale 0.34
#define y_letter_scale 0.2

QFont tempFont("Times", 60, QFont::Bold);

GUITile::GUITile(int nx, int ny, int w, int h, int n, QString Qn) :
	QGraphicsRectItem(nx, ny, w, h) {
	x = nx;
	y = ny;
	width = w;
	height = h;
	number = n;
	Qnumber.setText(Qn);
	
	// setting postion for the number inside of each tile
	Qnumber.setPos( nx+(w*x_letter_scale), ny+(h*y_letter_scale) );
	Qnumber.setFont(tempFont);
}

void GUITile::setX( int nx )
{
	x = nx;
}

void GUITile::setY( int ny )
{
	y = ny;
}

int GUITile::getX()
{
	return x;
}

int GUITile::getY()
{
	return y;
}

int GUITile::getNumber()
{
	return number;
}

void GUITile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	//QGraphicsItem::mousePressEvent(event); //Call the ancertor

	emit myPressSignal(number); //Emits the signal
}

void GUITile::operator=(const GUITile &rhs)
{
	  x = rhs.x;
    y = rhs.y;
    width = rhs.width;
    height = rhs.height;
    number = rhs.number;
}

