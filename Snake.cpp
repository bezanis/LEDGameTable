#include <Snake.h>

Snake::Snake(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn):Game(controller, strip, lcdIn){
	segments = NULL;
	moveDirection = DOWN;
	score = 0;
	highScore=0;
	gameOver=false;
	initialsPos=0;
	lastMoveTime=0;
	growing=0;

	highScore = ((unsigned long)EEPROM.read(7) << 24)+((unsigned long)EEPROM.read(8) << 16)+((unsigned long)EEPROM.read(9) << 8)+((unsigned long)EEPROM.read(10));
	highInitials[0] = EEPROM.read(11);
	highInitials[1] = EEPROM.read(12);
	highInitials[2] = EEPROM.read(13);
	newGame();
	/*EEPROM.write(7,0);
	EEPROM.write(8,0);
	EEPROM.write(9,0);
	EEPROM.write(10,1);
	EEPROM.write(11,'A');
	EEPROM.write(12,'A');
	EEPROM.write(13,'A');*/
}

Snake::~Snake(){
	deleteSnake();
}

void Snake::newGame(){
	randomSeed(analogRead(0));
	lcd->write(22);
	score=0;
	gameOver=0;
	lastMoveTime = millis();
	moveDirection=RIGHT;
	deleteSnake();
	segments = new SnakeSegment(4,1,NULL);
	segments = new SnakeSegment(4,2,segments);
	segments = new SnakeSegment(4,3,segments);
	addFood();
	redrawBoard();
	updateDisplay();
}

void Snake::run(){
	if(controller->buttonPressed(controller->BUTTON_SELECT) && !controller->buttonHandled(controller->BUTTON_SELECT)){
		controller->handleButton(controller->BUTTON_SELECT);
		newGame();
	}
	if(gameOver){
		if(score>highScore){
			if(initialsPos>2){
				saveHighScore();
			}else{
				if(controller->buttonPressed(controller->BUTTON_DOWN) && !controller->buttonHandled(controller->BUTTON_DOWN)){
					controller->handleButton(controller->BUTTON_DOWN);
					if(initials[initialsPos]>'A'){
						initials[initialsPos]--;
					}else{
						initials[initialsPos]='Z';
					}
				}
				if(controller->buttonPressed(controller->BUTTON_UP) && !controller->buttonHandled(controller->BUTTON_UP)){
					controller->handleButton(controller->BUTTON_UP);
					if(initials[initialsPos]<'Z'){
						initials[initialsPos]++;
					}else{
						initials[initialsPos]='A';
					}
				}
				if(controller->buttonPressed(controller->BUTTON_A) && !controller->buttonHandled(controller->BUTTON_A)){
					controller->handleButton(controller->BUTTON_A);
					initialsPos++;
				}
				lcd->write(157+initialsPos);
				lcd->print(initials[initialsPos]);
				lcd->write(157+initialsPos);
			}
		}
	}else{
		if(controller->buttonPressed(controller->BUTTON_LEFT) && !controller->buttonHandled(controller->BUTTON_LEFT)){
			controller->handleButton(controller->BUTTON_LEFT);
			if(moveDirection==UP || moveDirection==DOWN){
				moveDirection=LEFT;
				moveSnake();
			}
		}
		if(controller->buttonPressed(controller->BUTTON_RIGHT) && !controller->buttonHandled(controller->BUTTON_RIGHT)){
			controller->handleButton(controller->BUTTON_RIGHT);
			if(moveDirection==UP || moveDirection==DOWN){
				moveDirection=RIGHT;
				moveSnake();
			}
		}
		if(controller->buttonPressed(controller->BUTTON_DOWN)){
			controller->handleButton(controller->BUTTON_DOWN);
			if(moveDirection==LEFT || moveDirection==RIGHT){
				moveDirection=DOWN;
				moveSnake();
			}
		}
		if(controller->buttonPressed(controller->BUTTON_UP) && !controller->buttonHandled(controller->BUTTON_UP)){
			controller->handleButton(controller->BUTTON_UP);
			if(moveDirection==LEFT || moveDirection==RIGHT){
				moveDirection=UP;
				moveSnake();
			}
		}
	}
	if(!gameOver && millis() > ((unsigned long)(lastMoveTime+180))){
		moveSnake();
	}
}

void Snake::moveSnake(){
	lastMoveTime = millis();
	int headX=0;
	int headY=0;

	//Allows looping across the board
	/*if(moveDirection==UP){
		headX = (segments->getX()+1)%boardWidth;
		headY = segments->getY();
		//segments->setX((segments->getX()+1)%boardWidth);
	}
	if(moveDirection==DOWN){
		headX = (segments->getX()==0)?(boardWidth-1):(segments->getX()-1);
		headY = segments->getY();
		//segments->setX((segments->getX()==0)?(boardWidth-1):(segments->getX()-1));
	}
	if(moveDirection==LEFT){
		headX = segments->getX();
		headY = (segments->getY()==0)?(boardHeight-1):(segments->getY()-1);
		//segments->setY((segments->getY()==0)?(boardHeight-1):(segments->getY()-1));
	}
	if(moveDirection==RIGHT){
		headX = segments->getX();
		headY = (segments->getY()+1)%boardHeight;
		//segments->setY((segments->getY()+1)%boardHeight);
	}*/

	if(moveDirection==UP){
		if(segments->getX()>=boardWidth-1){
			setGameOver();
			return;
		}else{
			headX = segments->getX()+1;
			headY = segments->getY();
		}
	}
	if(moveDirection==DOWN){
		if(segments->getX()==0){
			setGameOver();
			return;
		}else{
			headX = segments->getX()-1;
			headY = segments->getY();
		}
	}
	if(moveDirection==LEFT){
		if(segments->getY()==0){
			setGameOver();
			return;
		}else{
			headX = segments->getX();
			headY = segments->getY()-1;
		}
	}
	if(moveDirection==RIGHT){
		if(segments->getY()>=boardHeight-1){
			setGameOver();
			return;
		}else{
			headX = segments->getX();
			headY = segments->getY()+1;
		}
	}

	SnakeSegment * eachSegment = segments;
	while(eachSegment!=NULL){
		if(eachSegment->getNextSegment()!=NULL && eachSegment->getNextSegment()->getNextSegment()==NULL){
			int tailX=0;
			int tailY=0;
			if(growing>0){
				tailX = eachSegment->getNextSegment()->getX();
				tailY = eachSegment->getNextSegment()->getY();
			}
			eachSegment->getNextSegment()->setNextSegment(segments);
			segments = eachSegment->getNextSegment();
			segments->setPosition(headX,headY);
			if(growing>0){
				growing--;
				SnakeSegment * newTail = new SnakeSegment(tailX,tailY,NULL);
				eachSegment->setNextSegment(newTail);
			}else{
				eachSegment->setNextSegment(NULL);
			}
		}
		eachSegment = eachSegment->getNextSegment();
	}

	eachSegment = segments;
	while(eachSegment!=NULL){
		if(eachSegment!=segments && segments->getX()==eachSegment->getX() && segments->getY()==eachSegment->getY()){
			setGameOver();
		}
		eachSegment = eachSegment->getNextSegment();
	}

	if(segments->getX()==foodPosition.getX() && segments->getY()==foodPosition.getY()){
		growing++;
		increaseScore(1);
		addFood();
		lcd->write(209); // 1/32 note
		lcd->write(215); // 3rd scale
		lcd->write(230); // A# note
	}

	redrawBoard();
}

void Snake::setGameOver(){
	gameOver=true;
	if(score<=highScore){
		lcd->write(12); // Clear
		lcd->print("Game Over!");
		lcd->write(148); // Move cursor to First column of second row
		lcd->print("Score:");
		lcd->print(score);
	}else{
		lcd->write(12); // Clear
		lcd->print("Record! ");
		lcd->print(score);
		lcd->write(148); // Move cursor to First column of second row
		lcd->print("Initials:");
		lcd->write(23); //Start blinking cursor
		initialsPos=0;
		initials[0] = 'A';
		initials[1] = 'A';
		initials[2] = 'A';
	}
	lcd->write(211); // 1/8 note
	lcd->write(216); // 3rd scale
	lcd->write(227);
	lcd->write(226);
	lcd->write(221);
	lcd->write(227);
	lcd->write(226);
	lcd->write(221);
}

void Snake::addFood(){
	int randX;
	int randY;
	bool positionTaken;
	do{
		randX = random(10);
		randY = random(20);
		positionTaken = false;
		SnakeSegment * eachSegment = segments;
		while(eachSegment!=NULL){
			if(eachSegment->getX()==randX && eachSegment->getY()==randY){
				positionTaken=true;
			}
			eachSegment = eachSegment->getNextSegment();
		}
	}while(positionTaken);
	foodPosition.setPosition(randX,randY);
}

void Snake::redrawBoard(){
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
				strip->setPixelColor(j,i,0x0);
		}
	}
	strip->setPixelColor(foodPosition.getX(),foodPosition.getY(),0xFF0000);
	SnakeSegment * eachSegment = segments;
	while(eachSegment!=NULL){
		strip->setPixelColor(eachSegment->getX(),eachSegment->getY(),0xFFFFFF);
		eachSegment = eachSegment->getNextSegment();
	}
	strip->show();
}

void Snake::increaseScore(unsigned long amount){
	score+=amount;
	updateDisplay();
}

void Snake::resume(){
	redrawBoard();
	updateDisplay();
}

void Snake::updateDisplay(){
	lcd->write(12); // Clear
	lcd->print("High: ");
	lcd->print(highScore);
	lcd->write(141);
	lcd->print(highInitials[0]);
	lcd->print(highInitials[1]);
	lcd->print(highInitials[2]);
	lcd->write(148); // Move cursor to First column of second row
	lcd->print("Score:");
	lcd->print(score);
}

void Snake::saveHighScore(){
	highScore = score;
	EEPROM.write(7,(byte)(score>>24));
	EEPROM.write(8,(byte)(score>>16));
	EEPROM.write(9,(byte)(score>>8));
	EEPROM.write(10,(byte) score);
	EEPROM.write(11,(byte) initials[0]);
	EEPROM.write(12,(byte) initials[1]);
	EEPROM.write(13,(byte) initials[2]);
	highInitials[0] = initials[0];
	highInitials[1] = initials[1];
	highInitials[2] = initials[2];
	lcd->write(22);
	newGame();
}

void Snake::deleteSnake(){
	while(segments!=NULL){
		SnakeSegment * nextSegment = segments->getNextSegment();
		delete segments;
		segments = nextSegment;
	}
}
