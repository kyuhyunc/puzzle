#ifndef GUITILE_H
#define GUITILE_H
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QString>
#include <QObject>
#include <QGraphicsItem>
#include <QFont>

#include <iostream>


class GUITile : public QObject, public QGraphicsRectItem{
		Q_OBJECT
				
public:
		/**  Default constructor		 
		 *  @param nx left top location of the tile(x-location)
		 *  @param ny left top location of the tile(y-location)
		 *  @param w width of the tile
		 *  @param h height of the tile
 		 *  @param n number of the tile
		 */
    GUITile(int nx, int ny, int w, int h, int n);

    /** Set x-location 
 		 *	@param nx x location of left top of the tile
     */
    void setX( int nx );
    
    /** Set y-location 
 		 *	@param ny y location of left top of the tile
     */
    void setY( int ny );
    
    /** Get x-location 
      * @return x-location 
      */
    int getX();

    /** Get yx-location 
      * @return y-location
      */
    int getY();
    
    /** Get length of the tile
      * @return Length of the tile (either width or height)
      */
    int getLength();

    /** Get the number of the tile 
      * @return Tile number
      */
    int getNumber();
    
    /** Move the tile in proper direction
    	*	@param Direction direction number (0:N, 1:W, 2:S, 3:E)
      */
	  void move(int direction);
    
    // Qnumber using QGraphicsSimpleTextItem
    QGraphicsSimpleTextItem Qnumber;
   	int cnt; // for sliding
   	   
 	  /** = operator 
 	  	*	@param rhs Right hand side GUITile class
 	  	*/
    void operator=(const GUITile &rhs);

signals:
	  /** Signal for detecting the click of corresponding tile
 	  	*	@param number Tile number
 	  	*/
		void myPressSignal(int number);

protected:
	  /** Inherited mouse click event function */
		void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    int x;
    int y;
    int width;
    int height;
    int number;
};

#endif // GUITILE_H
