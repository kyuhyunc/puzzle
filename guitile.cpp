#include "guitile.h"

GUITile::GUITile(int nx, int ny, int w, int h, int n, QString Qn) :
	QGraphicsRectItem(nx, ny, w, h) {
	x = nx;
	y = ny;
	width = w;
	height = h;
	number = n;
	Qnumber.setText(Qn);
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
/*
QGraphicsSimpleTextItem GUITile::getQnumber()
{
	return Qnumber;
}*/
