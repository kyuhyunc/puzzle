
#include "mainwindow.h"
	
	/** @mainpage CSCI 102 Homework #4
	 *  @section purpose Purpose/Overview
	 *	  PA4 puzzle game GUI implementation assignment
	 */

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	
	MainWindow w;

	w.show();	

	return a.exec();
}
