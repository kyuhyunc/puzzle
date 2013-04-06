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
#include <QGraphicsSimpleTextItem>

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
//		QTextEdit *getErrMsg();
//		QTextEdit *getErrMsg(QString msg);
		
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
		
		int size, initMoves, seed;
		Board *b;
		 
public slots:
    void gameStart();


};

#endif // MAINWINDOW_H
