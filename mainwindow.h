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
    explicit MainWindow();
    ~MainWindow();

		void createBoard();
		QHBoxLayout *createTopLayout();
		QHBoxLayout *createHeurLayout();
		QListView *createSolution();
		
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
		
		int size, initMoves, seed;
		Board *b;
		 
		QList<GUITile*> Qtiles;
		 
public slots:
    void gameStart();
 		void MoveTile(int tileNum);
 		void Qcheat();


};

#endif // MAINWINDOW_H
