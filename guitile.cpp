#include "guitile.h"

#define x_letter_scale 0.32
#define y_letter_scale 0.18
#define speed 1

QFont tempFont("Times", 60, QFont::Bold);

GUITile::GUITile(int nx, int ny, int w, int h, int n) :
	QGraphicsRectItem(nx, ny, w, h) {
	x = nx;
	y = ny;
	width = w;
	height = h;
	number = n;
	QString temp;
	temp.setNum(number);
	Qnumber.setText(temp);
	cnt = 0;
		
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

int GUITile::getLength()
{
	return width;
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
	QGraphicsItem::mousePressEvent(event); //Call the ancertor

	emit myPressSignal(number); //Emits the signal
}

void GUITile::move(int direction)
{
	//std::cout << "count :" << cnt << std::endl;
	// move to south
	if(direction == 0){
		//std::cout << "to south" << std::endl;
		if(cnt < width)	y+=speed;
//		if(y>288) y = 288;
		//std::cout << y << std::endl;
	}
	// move to east
	else if(direction == 1){
		//std::cout << "to east" << std::endl;
		if(cnt < width) x+=speed;
	}
	// move to north
	else if(direction == 2){
		//std::cout << "to north" << std::endl;
		if(cnt < width) y-=speed;
	}
	// move to west
	else if(direction == 3){
		//std::cout << "to west" << std::endl;
		if(cnt < width) x-=speed;
	}
	Qnumber.setPos( x+(width*x_letter_scale), y+(height*y_letter_scale) );

	QPointF p(x,y);
	QRectF r( rect() );
  r.moveTo(p);
  setRect( r );
	
	// counting in order to stop sliding 
	cnt ++;
}

void GUITile::operator=(const GUITile &rhs)
{
	  x = rhs.x;
    y = rhs.y;
    width = rhs.width;
    height = rhs.height;
    number = rhs.number;
}

