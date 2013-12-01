#include <ConnectFour.h>

ConnectFour::ConnectFour(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn):Game(controller, strip, lcdIn){
	newGame();
}

ConnectFour::~ConnectFour(){
}

void ConnectFour::newGame(){
	dropPos=3;
	curPlayer=1;
	winner=0;
	dropHeight=8;
	for(int x=0;x<7;x++){
		for(int y=0;y<6;y++){
			droppedPieces[x][y]=0;
		}
	}
	for(int i=0;i<9;i++){
		board[0][xOffset+i].setColor(0xFFFFFF);
		board[7][xOffset+i].setColor(0x222222);
		board[9][xOffset+i].setColor(0xFFFFFF);
	}
	for(int i=0;i<8;i++){
		board[1+i][xOffset].setColor(0xFFFFFF);
		board[1+i][xOffset+8].setColor(0xFFFFFF);
	}
	redrawBoard();
	updateDisplay();
}

void ConnectFour::run(){
	if(controller->buttonPressed(controller->BUTTON_SELECT) && !controller->buttonHandled(controller->BUTTON_SELECT)){
		controller->handleButton(controller->BUTTON_SELECT);
		newGame();
	}
	if(winner==0){
		if(dropHeight<8){
			//droppedPieces[dropPos][dropHeight-1]
			if(dropHeight>=2 && (dropHeight==7 || droppedPieces[dropPos][dropHeight-2]==0)){
				dropHeight--;
			}else{
				droppedPieces[dropPos][dropHeight-1] = curPlayer;
				dropHeight=8;
				//check winner

				for(int xPos=0;xPos<7;xPos++){
					for(int yPos=0;yPos<3;yPos++){
						if(droppedPieces[xPos][yPos]==curPlayer &&
								droppedPieces[xPos][yPos+1]==curPlayer &&
								droppedPieces[xPos][yPos+2]==curPlayer &&
								droppedPieces[xPos][yPos+3]==curPlayer){
							winner=curPlayer;
							winPos[0].setPosition(xPos,yPos);
							winPos[1].setPosition(xPos,yPos+1);
							winPos[2].setPosition(xPos,yPos+2);
							winPos[3].setPosition(xPos,yPos+3);
							winTime = millis();
						}
					}
				}
				for(int xPos=0;xPos<4;xPos++){
					for(int yPos=0;yPos<6;yPos++){
						if(droppedPieces[xPos][yPos]==curPlayer &&
								droppedPieces[xPos+1][yPos]==curPlayer &&
								droppedPieces[xPos+2][yPos]==curPlayer &&
								droppedPieces[xPos+3][yPos]==curPlayer){
							winner=curPlayer;
							winPos[0].setPosition(xPos,yPos);
							winPos[1].setPosition(xPos+1,yPos);
							winPos[2].setPosition(xPos+2,yPos);
							winPos[3].setPosition(xPos+3,yPos);
							winTime = millis();
						}
					}
				}
				for(int xPos=0;xPos<4;xPos++){
					for(int yPos=0;yPos<3;yPos++){
						if(droppedPieces[xPos][yPos]==curPlayer &&
								droppedPieces[xPos+1][yPos+1]==curPlayer &&
								droppedPieces[xPos+2][yPos+2]==curPlayer &&
								droppedPieces[xPos+3][yPos+3]==curPlayer){
							winner=curPlayer;
							winPos[0].setPosition(xPos,yPos);
							winPos[1].setPosition(xPos+1,yPos+1);
							winPos[2].setPosition(xPos+2,yPos+2);
							winPos[3].setPosition(xPos+3,yPos+3);
							winTime = millis();
						}
					}
				}
				for(int xPos=0;xPos<4;xPos++){
					for(int yPos=3;yPos<6;yPos++){
						if(droppedPieces[xPos][yPos]==curPlayer &&
								droppedPieces[xPos+1][yPos-1]==curPlayer &&
								droppedPieces[xPos+2][yPos-2]==curPlayer &&
								droppedPieces[xPos+3][yPos-3]==curPlayer){
							winner=curPlayer;
							winPos[0].setPosition(xPos,yPos);
							winPos[1].setPosition(xPos+1,yPos-1);
							winPos[2].setPosition(xPos+2,yPos-2);
							winPos[3].setPosition(xPos+3,yPos-3);
							winTime = millis();
						}
					}
				}
				curPlayer=(curPlayer)%2+1;
				updateDisplay();
			}
			redrawBoard();
		}else{
			if(controller->buttonPressed(controller->BUTTON_LEFT) && !controller->buttonHandled(controller->BUTTON_LEFT)){
				controller->handleButton(controller->BUTTON_LEFT);
				dropPos--;
				if(dropPos<0){
					dropPos=6;
				}
				redrawBoard();
			}
			if(controller->buttonPressed(controller->BUTTON_RIGHT) && !controller->buttonHandled(controller->BUTTON_RIGHT)){
				controller->handleButton(controller->BUTTON_RIGHT);
				dropPos=(dropPos+1)%7;
				redrawBoard();
			}
			if(controller->buttonPressed(controller->BUTTON_A) && !controller->buttonHandled(controller->BUTTON_A)){
				controller->handleButton(controller->BUTTON_A);
				if(dropHeight==8 && droppedPieces[dropPos][5]==0){
					dropHeight--;
					redrawBoard();
				}
			}
		}
	}else{
		redrawBoard();
	}
}

void ConnectFour::redrawBoard(){
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			strip->setPixelColor(j,i,board[j][i].getColor());
		}
	}
	strip->setPixelColor(dropHeight,xOffset+1+dropPos,((curPlayer==1)?0xFF0000:0x0000FF));
	for(int x=0;x<7;x++){
		for(int y=0;y<6;y++){
			if(droppedPieces[x][y]==1){
				strip->setPixelColor(1+y,xOffset+1+x,0xFF0000);
			}else if(droppedPieces[x][y]==2){
				strip->setPixelColor(1+y,xOffset+1+x,0x0000FF);
			}
		}
	}
	if(winner!=0){
		if((millis()+winTime)%200<100){
			for(int i=0;i<4;i++){
				strip->setPixelColor(1+winPos[i].getY(),xOffset+1+winPos[i].getX(),0xFFFFFF);
			}
		}
		for(int y=0;y<10;y++){
			if(winner==1){
				if((millis()-winTime)%600>100){
					strip->setPixelColor(y,xOffset-1,0xFF0000);
					strip->setPixelColor(y,xOffset+9,0xFF0000);
				}
				if((millis()-winTime)%600>200){
					strip->setPixelColor(y,xOffset-2,0xFF0000);
					strip->setPixelColor(y,xOffset+10,0xFF0000);
				}
				if((millis()-winTime)%600>300){
					strip->setPixelColor(y,xOffset-3,0xFF0000);
					strip->setPixelColor(y,xOffset+11,0xFF0000);
				}
				if((millis()-winTime)%600>400){
					strip->setPixelColor(y,xOffset-4,0xFF0000);
					strip->setPixelColor(y,xOffset+12,0xFF0000);
				}
				if((millis()-winTime)%600>500){
					strip->setPixelColor(y,xOffset-5,0xFF0000);
					strip->setPixelColor(y,xOffset+13,0xFF0000);
				}
			}else if(winner==2){
				if((millis()-winTime)%600>100){
					strip->setPixelColor(y,xOffset-1,0x0000FF);
					strip->setPixelColor(y,xOffset+9,0x0000FF);
				}
				if((millis()-winTime)%600>200){
					strip->setPixelColor(y,xOffset-2,0x0000FF);
					strip->setPixelColor(y,xOffset+10,0x0000FF);
				}
				if((millis()-winTime)%600>300){
					strip->setPixelColor(y,xOffset-3,0x0000FF);
					strip->setPixelColor(y,xOffset+11,0x0000FF);
				}
				if((millis()-winTime)%600>400){
					strip->setPixelColor(y,xOffset-4,0x0000FF);
					strip->setPixelColor(y,xOffset+12,0x0000FF);
				}
				if((millis()-winTime)%600>500){
					strip->setPixelColor(y,xOffset-5,0x0000FF);
					strip->setPixelColor(y,xOffset+13,0x0000FF);
				}
			}
		}
	}
	strip->show();
}

void ConnectFour::resume(){
	redrawBoard();
	updateDisplay();
}

void ConnectFour::updateDisplay(){
	lcd->write(12); // Clear
	if(winner!=0){
		lcd->print((winner==1)?"Red":"Blue");
		lcd->print(" Wins");
	}else if(curPlayer==1){
		lcd->print("Red's Turn");
	}else{
		lcd->print("Blue's Turn");
	}
}

const int ConnectFour::xOffset = 6;
