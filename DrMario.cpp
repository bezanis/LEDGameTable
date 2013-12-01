#include <DrMario.h>

DrMario::DrMario(NESController *controller, Adafruit_WS2801 *strip,LCD *lcdIn):Game(controller, strip, lcdIn){
	lcd->setLCD(2);
	/*highScore = ((unsigned long)EEPROM.read(0) << 24)+((unsigned long)EEPROM.read(1) << 16)+((unsigned long)EEPROM.read(2) << 8)+((unsigned long)EEPROM.read(3));
	highInitials[0] = EEPROM.read(4);
	highInitials[1] = EEPROM.read(5);
	highInitials[2] = EEPROM.read(6);
	curPiece=0;
	curRotation=0;
	lastDropTime=0;
	clearingRows=false;
	animateClearRowTimer=0;
	initials[0]='A';
	initials[1]='A';
	initials[2]='A';
	initialsPos=0;
	newGame();*/
	//Reset high score
	/*EEPROM.write(0,0);
	EEPROM.write(1,0);
	EEPROM.write(2,0);
	EEPROM.write(3,1);
	EEPROM.write(4,'A');
	EEPROM.write(5,'A');
	EEPROM.write(6,'A');*/
	initializeBoard();
}

DrMario::~DrMario(){
}

void DrMario::newGame(){
	randomSeed(analogRead(0));
	lcd->write(22);
	/*score=0;
	curLevel=0;
	lines=0;
	gameOver=0;
	gameOverAnimation=0;
	for (int i = 0; i < boardWidth; i++) {
		for (int j = 0; j < boardHeight; j++) {
			 board[i][j].setColor(0x0);
		}
	}
	setPiece();*/
}

void DrMario::run(){
	/*if(controller->buttonPressed(controller->BUTTON_SELECT) && !controller->buttonHandled(controller->BUTTON_SELECT)){
		controller->handleButton(controller->BUTTON_SELECT);
		newGame();
	}
	if(gameOver){
		if(gameOverAnimation<200){
			if(board[gameOverAnimation%boardWidth][gameOverAnimation/boardWidth].getColor()==0){
				board[gameOverAnimation%boardWidth][gameOverAnimation/boardWidth].setColor(random(0,255)*255*255+random(0,255)*255+random(0,255));
			}
			gameOverAnimation++;
		}
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
	}else if(clearingRows){
		if(millis()>animateClearRowTimer){
			int linesCleared = 0;
			for (int i = 0; i < boardHeight; i++) {
				bool clearingRow=true;
				for (int j = 0; j < boardWidth; j++) {
					if(board[j][i].getColor()==0){
						clearingRow=false;
					}
				}
				if(clearingRow){
					shiftPiecesDown(i);
					linesCleared++;
				}
			}
			lines+=linesCleared;
			if(lines>=10){
				curLevel++;
				lines=lines%10;
			}
			increaseScore(100L*linesCleared*linesCleared);
			clearingRows=false;
			setPiece();
		}
	}else{
		if(controller->buttonPressed(controller->BUTTON_LEFT) && !controller->buttonHandled(controller->BUTTON_LEFT)){
			controller->handleButton(controller->BUTTON_LEFT);
			moveLeft();
		}
		if(controller->buttonPressed(controller->BUTTON_RIGHT) && !controller->buttonHandled(controller->BUTTON_RIGHT)){
			controller->handleButton(controller->BUTTON_RIGHT);
			moveRight();
		}
		if(controller->buttonPressed(controller->BUTTON_DOWN)){
			controller->handleButton(controller->BUTTON_DOWN);
			increaseScore(1L+curLevel);
			moveDown();
		}
		if(controller->buttonPressed(controller->BUTTON_A) && !controller->buttonHandled(controller->BUTTON_A)){
			controller->handleButton(controller->BUTTON_A);
			spinClockwise();
		}
		if(controller->buttonPressed(controller->BUTTON_B) && !controller->buttonHandled(controller->BUTTON_B)){
			controller->handleButton(controller->BUTTON_B);
			spinCounterClockwise();
		}
	}
	if(!gameOver && millis() > ((unsigned long)(lastDropTime+levelDropTimes[curLevel]))){
		lastDropTime = millis();
		moveDown();
	}
	for (int i = 0; i < boardHeight; i++) {
		bool clearingRow=false;
		if(clearingRows){
			clearingRow=true;
			for (int k = 0; k < boardWidth; k++) {
				if(board[k][i].getColor()==0){
					clearingRow=false;
				}
			}
		}
		for (int j = 0; j < boardWidth; j++) {
			if(clearingRow && (millis()-animateClearRowTimer)%50>24){
					strip->setPixelColor(j,i,blinkColor);
			}else{
				strip->setPixelColor(j,i,board[j][i].getColor());
			}
		}
	}
	if(!clearingRows){
		for(int i=0;i<4;i++){
			int xpos = curPos.getX()+((i!=3)?pieces[curPiece][curRotation][i][0]:0);
			int ypos = curPos.getY()+((i!=3)?pieces[curPiece][curRotation][i][1]:0);
			strip->setPixelColor(xpos, ypos, pieceColors[curPiece]);
		}
	}*/

}


void DrMario::resume(){
	lcd->setLCD(2);
	updateDisplay();
	initializeBoard();
}

void DrMario::initializeBoard(){
	for(int y=0;y<boardHeight;y++){
		for(int x=0;x<boardWidth;x++){
			strip->setPixelColor(x, y, 0x000000);
		}
	}
	for(int y=3;y<boardHeight;y++){
		strip->setPixelColor(0, y, 0xFFFFFF);
		strip->setPixelColor((boardWidth-1), y, 0xFFFFFF);
	}
	for(int x=1;x<boardWidth-1;x++){
		strip->setPixelColor(x, (boardHeight-1), 0xFFFFFF);
	}
	int framePixels[][2] = {{1,3},{2,3},{3,3},{6,3},{7,3},{8,3},
			{3,2},{6,2},{3,1},{6,1},{3,0},{6,0}};
	int frameSize = (sizeof framePixels / (sizeof framePixels[0]/2));
	for(int i=0;i<frameSize;i++){
		strip->setPixelColor(framePixels[i][0], framePixels[i][1], 0xFFFFFF);
	}
	strip->show();
}

void DrMario::updateDisplay(){
	/*lcd->write(12);
	lcd->print("High: "+String(highScore));
	lcd->write(141);
	lcd->print(String(highInitials[0])+String(highInitials[1])+String(highInitials[2]));
	lcd->write(148); // Move cursor to First column of second row
	lcd->print("Score:"+String(score));*/
}

/*void DrMario::shiftPiecesDown(int row){
	for(int i=row-1;i>=0;i--){
		for (int j=0; j<boardWidth; j++) {
			board[j][i+1].setColor(board[j][i].getColor());
			if(i==0){
				board[j][0].setColor(0);
			}
		}
	}
}

bool DrMario::clearRows(){
	if(clearingRows){
		return true;
	}
	bool fullRows = false;
	for (int i = 0; i < boardHeight; i++) {
		bool fullRow = true;
		for (int j = 0; j < boardWidth; j++) {
			 if(board[j][i].getColor()==0){
				 fullRow = false;
			 }
		}
		if(fullRow){
			fullRows=true;
		}
	}

	if(fullRows){
		lcd->write(209); // 1/32 note
		lcd->write(216); // 4th scale
		lcd->write(220); // A note
		lcd->write(223); // C note
		lcd->write(230); // G note
		clearingRows=true;
		animateClearRowTimer=millis()+800;
		return true;
	}
	return false;
}

void DrMario::spinClockwise(){
	int nextRotation=(curRotation+1)%4;
	bool collision = false;
	for(int i=0; i<4; i++){
		int pixelX = curPos.getX() + ((i==3)?0:pieces[curPiece][nextRotation][i][0]);
		int pixelY = curPos.getY() + ((i==3)?0:pieces[curPiece][nextRotation][i][1]);
		if((pixelY>=boardHeight) || pixelX<0 || pixelX>=boardWidth ||   (pixelY>=0 && board[pixelX][pixelY].getColor()!=0) ){
			collision=true;
		}
	}
	if(!collision){
		curRotation=nextRotation;
		lcd->write(209); // 1/32 note
		lcd->write(215); // 3rd scale
		lcd->write(221); // A# note
	}
}

void DrMario::spinCounterClockwise(){
	int nextRotation=curRotation-1;
	if(nextRotation<0){
		nextRotation=3;
	}
	bool collision = false;
	for(int i=0; i<4; i++){
		int pixelX = curPos.getX() + ((i==3)?0:pieces[curPiece][nextRotation][i][0]);
		int pixelY = curPos.getY() + ((i==3)?0:pieces[curPiece][nextRotation][i][1]);
		if((pixelY>=boardHeight) || pixelX<0 || pixelX>=boardWidth ||   (pixelY>=0 && board[pixelX][pixelY].getColor()!=0) ){
			collision=true;
		}
	}
	if(!collision){
		curRotation=nextRotation;
		lcd->write(209); // 1/32 note
		lcd->write(215); // 3rd scale
		lcd->write(221); // A# note
	}
}

void DrMario::moveLeft(){
	bool collision = false;
	for(int i=0; i<4; i++){
		int pixelX = curPos.getX() + ((i==3)?0:pieces[curPiece][curRotation][i][0]);
		int pixelY = curPos.getY() + ((i==3)?0:pieces[curPiece][curRotation][i][1]);
		if((pixelY<0 && pixelX<=0) || ((pixelY>=0)&& (pixelX<=0 || board[pixelX-1][pixelY].getColor()!=0))){
			collision=true;
		}
	}
	if(!collision){
		curPos.setX(curPos.getX()-1);
		lcd->write(209); // 1/32 note
		lcd->write(215); // 3rd scale
		lcd->write(225); // D note
	}
}

void DrMario::moveRight(){
	bool collision = false;
	for(int i=0; i<4; i++){
		int pixelX = curPos.getX() + ((i==3)?0:pieces[curPiece][curRotation][i][0]);
		int pixelY = curPos.getY() + ((i==3)?0:pieces[curPiece][curRotation][i][1]);
		if((pixelY<0 && pixelX>=(boardWidth-1)) || ((pixelY>=0)&& (pixelX>=(boardWidth-1) || board[pixelX+1][pixelY].getColor()!=0))){
			collision=true;
		}
	}
	if(!collision){
		curPos.setX(curPos.getX()+1);
		lcd->write(209); // 1/32 note
		lcd->write(215); // 3rd scale
		lcd->write(225); // D note
	}
}

void DrMario::moveDown(){
	bool hitBottom=false;
	for(int i=0; i<4; i++){
		int pixelX = curPos.getX() + ((i==3)?0:pieces[curPiece][curRotation][i][0]);
		int pixelY = curPos.getY() + ((i==3)?0:pieces[curPiece][curRotation][i][1]);
		if(pixelY>=boardHeight-1 || board[pixelX][pixelY+1].getColor()!=0){
			hitBottom=true;
		}
	}
	if(!hitBottom){
		curPos.setY(curPos.getY()+1);
	}else{
		for(int i=0; i<4; i++){
			int pixelX = curPos.getX() + ((i==3)?0:pieces[curPiece][curRotation][i][0]);
			int pixelY = curPos.getY() + ((i==3)?0:pieces[curPiece][curRotation][i][1]);
			if(pixelY>=0){
				if(!gameOver && board[pixelX][pixelY].getColor()!=0 && curPos.getY()==0){
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
					}
					initialsPos=0;
					initials[0] = 'A';
					initials[1] = 'A';
					initials[2] = 'A';
					lcd->write(211); // 1/8 note
					lcd->write(216); // 3rd scale
					lcd->write(227);
					lcd->write(226);
					lcd->write(221);
					lcd->write(227);
					lcd->write(226);
					lcd->write(221);
				}
				board[pixelX][pixelY].setColor(pieceColors[curPiece]);
			}
		}
		if(!clearRows()){
			setPiece();
			lcd->write(208); // 1/8 note
			lcd->write(215); // 3rd scale
			lcd->write(220);
		}
	}
}

void DrMario::setPiece(){
	if(!gameOver){
		curPos.setPosition(4,0);
		lastDropTime = millis();
		random(7);
		curPiece=random(7);
		curRotation=0;
		updateDisplay();
	}
}

void DrMario::increaseScore(unsigned long amount){
	score+=amount;
	updateDisplay();
}

void DrMario::saveHighScore(){
	highScore = score;
	EEPROM.write(0,(byte)(score>>24));
	EEPROM.write(1,(byte)(score>>16));
	EEPROM.write(2,(byte)(score>>8));
	EEPROM.write(3,(byte) score);
	EEPROM.write(4,(byte) initials[0]);
	EEPROM.write(5,(byte) initials[1]);
	EEPROM.write(6,(byte) initials[2]);
	highInitials[0] = initials[0];
	highInitials[1] = initials[1];
	highInitials[2] = initials[2];
	lcd->write(22);
	newGame();
}

//Piece,rotation,pixel,position
const int DrMario::pieces[7][4][3][2] = {
	{{{-1,0},{1,0},{2,0}}, {{0,-1},{0,1},{0,2}}, {{-1,0},{1,0},{2,0}}, {{0,-1},{0,1},{0,2}}},
	{{{-1,0},{1,0},{0,1}}, {{-1,0},{0,-1},{0,1}}, {{-1,0},{0,-1},{1,0}}, {{0,-1},{1,0},{0,1}}},
	{{{-1,0},{-1,1},{0,1}}, {{-1,0},{-1,1},{0,1}}, {{-1,0},{-1,1},{0,1}}, {{-1,0},{-1,1},{0,1}}},
	{{{1,0},{-1,1},{0,1}}, {{0,-1},{1,0},{1,1}}, {{1,0},{-1,1},{0,1}}, {{0,-1},{1,0},{1,1}}},
	{{{-1,0},{0,1},{1,1}}, {{1,-1},{1,0},{0,1}}, {{-1,0},{0,1},{1,1}}, {{1,-1},{1,0},{0,1}}},
	{{{-1,0},{1,0},{-1,1}}, {{-1,-1},{0,-1},{0,1}}, {{-1,0},{1,0},{1,-1}}, {{0,-1},{0,1},{1,1}}},
	{{{-1,0},{1,0},{1,1}}, {{-1,1},{0,1},{0,-1}}, {{-1,-1},{-1,0},{1,0}}, {{0,1},{0,-1},{1,-1}}}
};
const uint32_t DrMario::pieceColors[7] = {0xFF0000,0x00FF00,0x0000FF,0xFFFF00,0x00FFFF,0xFF00FF,0xFF7800};
const int DrMario::levelDropTimes[24] = {2000,1700,1400,1150,900,750,600,450,300,200,140,100,75,63,50,40,30,20,10,5,1,1,1,1};
const uint32_t DrMario::blinkColor = 0xFFFFFF;
*/
