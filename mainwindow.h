#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QList>
#include <QLabel>
#include <QTextEdit>
#include <QRadioButton>
#include <QListView>
#include <QString>
#include <QGraphicsItem>
#include <QStandardItemModel>
#include <QTimer>
#include <QTimeLine>
#include <QObject>

#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <deque>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>

#include "board.h"
#include "puzzle_heur.h"
#include "puzzle_solver.h"
#include "pmminlist.h"

#include "guitile.h"

#define WINDOW_MAX_X 250
#define WINDOW_MAX_Y 250

using namespace std;

class MainWindow : public QWidget {
    Q_OBJECT
    
public:
		/**  Default constructor  \n
		 *	QWidget, window, will be the biggest screen that will save Gridlayout. \n
		 *  This Gridlayout contains all top layout, heuristic layout, solution layout, QGraphicscene etc.
		 */
    explicit MainWindow();
 		/**  Default destructor */
    ~MainWindow();

		/** Create the board with using all the private variables */
		void createBoard();
		
		/** Create the top layout that will be contained in Gridlayout 
		 * 	@return QHBoxLayout that has boxes for input
	   */
		QHBoxLayout *createTopLayout();
		
		/** Create the heuristic layout that will be contained in Gridlayout
		 * 	@return QHBoxLayout that has radio buttons for starting algorithm
	   */
		QHBoxLayout *createHeurLayout();
		
    void show();
    
private:
    QGraphicsScene *scene;
    QGraphicsView *view;

    //Here is my implementation
    QWidget *window;

		// layouts
		QGridLayout *layout; // main layout    
    QHBoxLayout *topLayout; // top input text board layout
    QHBoxLayout *heurLayout; // heuristic radio buttons layout
    
    // etc
    QStandardItemModel *model; // for saving solList
    QListView *solList; // list for displaying solutions
    QTextEdit *errMsg; // get error message
    
		// buttons
    QPushButton *startGame;
		QPushButton *quitGame;	
		QPushButton *aAlg;
		
		// text boxes
		QTextEdit *boardSize;
		QTextEdit *startingMoves;
		QTextEdit *seedValue;
		
		// labels for topLayout 
		QLabel *boardSizeLabel;
	  QLabel *startingMovesLabel;
  	QLabel *seedValueLabel;
  	
  	// radio buttons for heurLayout
 		QRadioButton *man_heur;
		QRadioButton *out_heur;
		
    QTimer *timer;
		double timerCnt;
		int direction;
		int tempTileNum;
			
		int size, initMoves, seed;
		Board *b;
		 
		QList<GUITile*> Qtiles;
		 
public slots:
		/** Slot member fuction for starting the game \n
		 * 	In this function, it will check whether there are incorrect or invalid values
	   */
    void gameStart();
    
    /** Move the tile that has particular number. This is for moving instantly (no sliding)
		 * 	@param tileNum number of the tile
	   */
 		void MoveTile(int tileNum);

    /** Move the tile that has particular number. This is for moving in sliding
		 * 	@param tileNum number of the tile
	   */
 		void AnimateTile(int tileNum);

 		/** Actual function that will move the tile little by little considering the timer */
 		void SlidingTile();
 		
 		/** Function that will show the list of solutions in sequence order */
 		void Qcheat();
};

#endif // MAINWINDOW_H
