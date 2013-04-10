#include "mainwindow.h"
#define x_letter_scale 0.32
#define y_letter_scale 0.18
#define speed 1

QBrush redBrush(Qt::red);
QBrush blueBrush(Qt::blue);
QBrush blkBrush(Qt::black);
QBrush greenBrush(Qt::green);
QBrush whiteBrush(Qt::white);
	
MainWindow::MainWindow()  {
	//Biggest layout that will include every other layout and widget	
	layout = new QGridLayout;
	//We need a scene and a view to do graphics in QT
	scene = new QGraphicsScene();
	view = new QGraphicsView( scene );
	b = NULL;

//	view->setFixedSize(288,288);
	view->setFixedSize(432,432);
	
	//This sets the size of the window and gives it a title.
	view->setFixedSize( WINDOW_MAX_X*2, WINDOW_MAX_Y*2 );
	view->setWindowTitle("3*3 or 4*4 Puzzle Game");

	// topLayout for text input board	
	topLayout = createTopLayout();
	
	// start and quit button
	startGame = new QPushButton("Start the game");
	quitGame = new QPushButton("Quit");	
	//startGame->setFixedSize(100,20);
	//quitGame->setFixedSize(100,20);
	
	// radio button for heuristic method
	heurLayout = createHeurLayout();

	// A* algorithm button
	aAlg = new QPushButton("A* algorithm");
	//aAlg->setFixedSize(100,20);
	
	// solution list
	solList = createSolution();
	
	// error message
	errMsg = new QTextEdit;
	errMsg->setMinimumHeight(30);
	errMsg->setReadOnly(true);

	// placing layouts and widgets in the main layout by using gridlayout
	layout->addLayout(topLayout,0,0);
	layout->addLayout(heurLayout,1,0);
	layout->addWidget(startGame,2,0); // buttons
	layout->addWidget(aAlg,2,1);
	layout->addWidget(solList,3,1);
	layout->addWidget(errMsg,4,0);
	layout->addWidget(quitGame,4,1);
	layout->addWidget(view,3,0);

	// window that will get layout that has every thing
	window = new QWidget;

	// setting layout in the main window
	// window > layout(Gridlayout) = other layouts + widgets
	window->setLayout(layout);	
	
	// setting a timer
  timer = new QTimer(this);

	// connecting start button to game start function
  connect(startGame, SIGNAL(clicked()), this, SLOT(gameStart()));
	
	// connecting quit button to terminate the program
	connect(quitGame, SIGNAL(clicked()), qApp, SLOT(quit()));
	
	// connecting A* algorithm button to Qcheat function
	connect(aAlg, SIGNAL(clicked()), this, SLOT(Qcheat()));
	
}

QHBoxLayout *MainWindow::createTopLayout() 
{
	
	// top layout for three inputs, size, moves and seed value.
	QHBoxLayout *topLayout = new QHBoxLayout;
	
	boardSize = new QTextEdit;
	startingMoves = new QTextEdit;
	seedValue = new QTextEdit;

	// set the size of text boxes
	boardSize->setMaximumSize(60,20);
	startingMoves->setMaximumSize(60,20);
	seedValue->setMaximumSize(60,20);

	// disable scroll bars for each box
	boardSize->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	boardSize->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	startingMoves->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	startingMoves->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	seedValue->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	seedValue->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

/*
	boardSize->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	startingMoves->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	seedValue->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	boardSize->setWordWrapMode(QTextOption::NoWrap);
	startingMoves->setWordWrapMode(QTextOption::NoWrap);
	seedValue->setWordWrapMode(QTextOption::NoWrap);
*/
	// disable tab inside of the box as an input
	boardSize->setTabChangesFocus(true);
	startingMoves->setTabChangesFocus(true);
	seedValue->setTabChangesFocus(true);

	// label for the box
	boardSizeLabel = new QLabel(tr("Board Size"));
	startingMovesLabel = new QLabel(tr("Starting Moves"));
  seedValueLabel = new QLabel(tr("Seed Value"));

	topLayout->addWidget(boardSizeLabel);
	topLayout->addWidget(boardSize);
	topLayout->addWidget(startingMovesLabel);
	topLayout->addWidget(startingMoves);
	topLayout->addWidget(seedValueLabel);
	topLayout->addWidget(seedValue);	
	
	return topLayout;
}

QHBoxLayout *MainWindow::createHeurLayout()
{
	QHBoxLayout *heurLayout = new QHBoxLayout;
	
	man_heur = new QRadioButton("Manhattan heuristic");
	out_heur = new QRadioButton("Out-of-place heuristic");
	
	heurLayout->addWidget(man_heur);
	heurLayout->addWidget(out_heur);
	
	return heurLayout;			
}

QListView *MainWindow::createSolution()
{
	QListView *solList = new QListView;
	
	solList->setMaximumWidth(130);
	
	return solList;
}

void MainWindow::gameStart()
{ 

	// if the game is not the first time, deallocation for previous board is necessary
	if(b != NULL){
		delete b;
		model->clear();
		b = NULL;
	}
	
  for(QList<GUITile*>::iterator it=Qtiles.begin();it!=Qtiles.end();++it){
    		delete *it;
  }
  Qtiles.clear();  

	QString size_= boardSize->toPlainText();
	QString initMoves_= startingMoves->toPlainText();
	QString seed_= seedValue->toPlainText();
	
	bool ok_1 = true; //*ok is set to false; otherwise *ok is set to true.
	bool ok_2 = true; //*ok is set to false; otherwise *ok is set to true.
	bool ok_3 = true; //*ok is set to false; otherwise *ok is set to true.
		
	size = size_.toInt(&ok_1,10);
	initMoves = initMoves_.toInt(&ok_2,10);
	seed = seed_.toInt(&ok_3,10);
	
	if(ok_1 == false){
		errMsg->setPlainText("Improper Size");
	}
	else if(size != 9 && size != 16){
		errMsg->setPlainText("Improper Size. Size must be either 9 or 16"); 
	}
	else if(ok_2 == false){
		errMsg->setPlainText("Improper Starting moves");
	}
	else if(ok_3 == false){
		errMsg->setPlainText("Improper Seed value!"); 
	}	
	else if(initMoves < 1 || seed <1){
		errMsg->setPlainText("Too small Starting moves or Seed value!");
	}
	else{
		errMsg->setPlainText("Game starts"); 
		createBoard();			
	}
	
	/*cout << "size : " << size << endl;
	cout << "initMoves : " << initMoves << endl;
	cout << "seed : " << seed << endl;*/
}

void MainWindow::createBoard()
{
	Board b_(size,initMoves,seed);
	b = new Board(b_);
	int *tiles = b->getTiles();
	
	GUITile *tile;
	
	int length = 0;
	int dim = static_cast<int>(sqrt(size));
	
	if(b->solved() == true){
		errMsg->setPlainText("Puzzle is already solved. Put bigger Seed and Starting moves value");
	}
	else{
		// board size 288 * 288
		if(size == 9){
			// if size is 9, size of each tile is 96
			length = (96*3)/2;
		}
		else if(size == 16){
			// if size is 16, then size of each tile is 72
			length = (72*3)/2;
		}
	
		// display initial board
		for(int i=0;i<size;i++){
			QString Qnumber;
			Qnumber.setNum(tiles[i]);
		
			// don't need to dynamically allocate it.??? yes, lets save these into temp list and delete 
			tile = new GUITile(length*(i%dim),length*(i/dim),length,length,tiles[i], Qnumber); // creating tiles
				
			if(tiles[i] == 0){
				//tile->setBrush(blkBrush);
				tile->setBrush(whiteBrush);
				//tile->Qnumber.setBrush(blkBrush);
				tile->Qnumber.setBrush(whiteBrush);
			}
			else{
				tile->setBrush(blueBrush);
				tile->Qnumber.setBrush(whiteBrush);
			}
		
			scene->addItem(tile);
			// adding number inside of the tiles
			scene->addItem(&tile->Qnumber);

			// pushing back tile to QList for deallocation
			Qtiles.push_back(tile);

			// move a tile instictly
			//connect(Qtiles[i],SIGNAL(myPressSignal(int)),this,SLOT(MoveTile(int)));
			// move a tile my animation
			connect(Qtiles[i],SIGNAL(myPressSignal(int)),this,SLOT(AnimateTile(int)));
		}
	}
}

void MainWindow::MoveTile(int tileNum)
{
	// reset the Qlist to save updated board
  for(QList<GUITile*>::iterator it=Qtiles.begin();it!=Qtiles.end();++it){
    	delete *it;
  }
  
  Qtiles.clear();

	try{
		b->move(tileNum);
	}
	catch(int i){
		if(i == 4)
			errMsg->setPlainText("Improper tile click"); 
		else
			errMsg->setPlainText("Tile has moved"); 
	}
	
	int size = b->getSize();
	int *tiles = b->getTiles();
	
	// temporary tile for saving each tile
	GUITile *tile;
	
	int length = 0;
	int dim = static_cast<int>(sqrt(size));
	
	// board size 288 * 288
	if(size == 9){
		// if size is 9, size of each tile is 96
		length = (96*3)/2;
	}
	else if(size == 16){
		// if size is 16, then size of each tile is 72
		length = (72*3)/2;
	}

	// display board
	for(int i=0;i<size;i++){
		QString Qnumber;
		Qnumber.setNum(tiles[i]);
		// don't need to dynamically allocate it.??? yes, lets save these into temp list and delete 
		tile = new GUITile(length*(i%dim),length*(i/dim),length,length,tiles[i], Qnumber); // creating tiles
		
		if(tiles[i] == 0){
			//tile->setBrush(blkBrush);
			tile->setBrush(whiteBrush);
			//tile->Qnumber.setBrush(blkBrush);
			tile->Qnumber.setBrush(whiteBrush);
		}
		else{
			tile->setBrush(blueBrush);
			tile->Qnumber.setBrush(whiteBrush);
		}
		
		scene->addItem(tile);
		scene->addItem(&tile->Qnumber);

		Qtiles.push_back(tile);
		
		if(b->solved() != true)
			connect(Qtiles[i],SIGNAL(myPressSignal(int)),this,SLOT(MoveTile(int)));
		else{
			errMsg->setPlainText("Puzzle is solved!");
		}
	}
}

void MainWindow::AnimateTile(int tileNum)
{
	// will use these variables in SlidingTile()
  direction = 0;
  timerCnt = 0;
  tempTileNum = tileNum;
  
  //cout << "clicking tile num: " << tileNum << endl;
  
	try{
		b->move(tileNum);
	}
	catch(int i){
		// direction number (0:N, 1:W, 2:S, 3:E)
		if(i==4){
			direction = 4;
			errMsg->setPlainText("Improper tile click"); 
			//cout << "direction: " << direction << endl;
		}
		else if(i != 4){

			// disconnect tiles for a while for prevent double click error
			for(int j=0;j<Qtiles.size();j++){
				Qtiles[j]->disconnect(Qtiles[j],0,0,0);	
			}

			if(i == 0)	direction = 0;
			else if(i == 1)	direction = 1;
			else if(i == 2)	direction = 2;
			else if(i == 3)	direction = 3;
			errMsg->setPlainText("Tile has moved"); 
			//cout << "direction: " << direction << endl;

			timer->setInterval(speed);
	    connect(timer,SIGNAL(timeout()),this,SLOT(SlidingTile()));
 	    timer->start();
		}
	}
}

void MainWindow::SlidingTile()
{
	//cout << "moving in SlidingTile" << endl;
	int loc=0;
	int blank=0;
	
	for(int i=0;i<Qtiles.size();i++){
		int temp = Qtiles[i]->getNumber();
		if(tempTileNum == temp){
			loc = i;
		}
		if(temp == 0){
			blank = i;
		}
	}

	// when timer stops, re-draw the tile
	if(timerCnt >= (Qtiles[loc]->getLength())*speed){
		timer->stop();

		// reconnect tile with signal when moving(sliding) is done
		for(int i=0;i<Qtiles.size();i++){
			connect(Qtiles[i],SIGNAL(myPressSignal(int)),this,SLOT(AnimateTile(int)));
		}		
	
		// reset the timer
		delete timer;
		timer = new QTimer(this);
		
		timerCnt = 0;
		Qtiles[loc]->cnt = 0;
		Qtiles[blank]->cnt = 0;
		
		if(b->solved() == true){
			errMsg->setPlainText("Puzzle is solved!");
			// disconnect all tiles when the puzzle is solved
			for(int i=0;i<Qtiles.size();i++){
				Qtiles[i]->disconnect(Qtiles[i],0,0,0);
			}
		}
	}
	else if(timerCnt < (Qtiles[loc]->getLength())*speed){
		// moving target tile
		Qtiles[loc]->move(direction);	
		// moving black tile
		Qtiles[blank]->move((direction+2)%4);

		timerCnt++;		
	}	
}
 
void MainWindow::Qcheat()
{
//	cout << Qtiles.size() << endl;
	ManhattanHeuristic Man_Heur;
	OutOfPlaceHeuristic Out_Heur;

	if(b == NULL){
		errMsg->setPlainText("Game has not started");
	}
	else if(b->solved() == true){
		errMsg->setPlainText("Puzzle is solved already");
		model->clear();
	}
	else if(man_heur->isChecked() || out_heur->isChecked()){
		PuzzleSolver cheat(*b);
	
		if(man_heur->isChecked()){
			errMsg->setPlainText("Manhattan heuristic is executed->calculating");
			cheat.run(&Man_Heur);
			errMsg->setPlainText("Manhattan heuristic is executed->finished!");
		}
		else if(out_heur->isChecked()){
			errMsg->setPlainText("Out-of-place heuristic is executed->calculating");
			cheat.run(&Out_Heur);
			errMsg->setPlainText("Out-of-place heuristic is executed->finished");
		}		
		
		// actual solution printing out codes 
		deque<int> solution = cheat.get_solution();
		int sol_size = solution.size();

		//QStandardItemModel for saving solution
		model = new QStandardItemModel(sol_size,0,this);

		// add items to model and will add this model to the QListView
		//cout << endl << "Try this sequence:";
		
		for(int i=0;i<sol_size;i++){
			QString temp;
			//cout << " " << solution.back();
			// converting solution integer to QString
			temp.setNum(solution.back());
			
			// put Qstring(temp) to StandardItem
			QStandardItem* itm = new QStandardItem(temp);
			// put item to model
			model->setItem(i,0,itm);
			solution.pop_back();
		}
		//cout << endl << "(Expansion = " << cheat.getNumExpansions() << ")" << endl << endl;

		// add model to QListView
		solList->setModel(model);
	}
	else{
		errMsg->setPlainText("You should check either Manhattan heuristic or Out-of-place heuristic");
	}		
}
 
void MainWindow::show() 
{
	window->show();
}

MainWindow::~MainWindow()
{
	delete startGame;
	delete quitGame;	
	delete aAlg;
	delete man_heur;
	delete out_heur;

	delete boardSizeLabel;
  delete startingMovesLabel;
	delete seedValueLabel;

	if(b != NULL)
		delete b;
	 
	for(QList<GUITile*>::iterator it=Qtiles.begin();it!=Qtiles.end();++it){
    	delete *it;
  }  
  Qtiles.clear();
	
	delete boardSize;
	delete startingMoves;
	delete seedValue;

	delete errMsg;
	
	delete scene;
	delete view;
	delete topLayout; // top input text board layout
	delete heurLayout; // heuristic radio buttons layout
	delete solList; // list for displaying solutions
	delete layout; // main layout    

	delete window;
}

