/*
* Derekas Panagiwths 4014
* Thoma Athanasios 2979
*/

#include "GManager.h"



GManager::GManager() {

	score = 0;
	playerMovesLeft = 30;
	gameOn = false;


	// single pointer for loader
	TextureLoader* singletonLoader = new TextureLoader();

	board = new GCube*[15];
	for (int i=0; i<15; i++){
		board[i] = new GCube[15];
	}

}

void GManager::randomizeBoard(){

	int ran, small_ran;


	for (int i=0; i<15; i++){
		for (int j=0; j<15; j++){
			ran = rand()%5 + 1; // give random values 1-5
			small_ran = rand()%50 ;
			if (small_ran == 1){ //small chance for block to be a bomb
				ran = BOMB;
			}
			board[i][j].setValue(ran);
		}
	}
}

void GManager::drawText(GLfloat x, GLfloat y, char* s){

    char* p;

    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0f, glutGet(GLUT_WINDOW_WIDTH), 0.0f, glutGet(GLUT_WINDOW_HEIGHT), -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    // font color
    glColor3f(1.0f,0.0f,0.8f);
    glRasterPos2f(x, y);
    for(p = s ; *p != '\0'; p++) {
    	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
    }
     glPopMatrix();
     glMatrixMode(GL_PROJECTION);
     glPopMatrix();
     glMatrixMode(GL_MODELVIEW);

     glEnable(GL_LIGHTING);
}


void GManager::swapCubeValue(int i1, int j1, int i2, int j2){

	int temp;

	if (areNeighbors(i1, j1, i2, j2)){
		temp = board[i1][j1].getValue();
		board[i1][j1].setValue(board[i2][j2].getValue());
		board[i2][j2].setValue(temp);
	}
}

int GManager::areNeighbors(int i1, int j1, int i2, int j2){

	if (i1 == i2){
		if(j1 - j2 == 1){ // RIGHT or LEFT
			return DOWN;
		}else if (j1 - j2 == -1){
			return UP;
		}

	}else if (j1 == j2){ // UP or DOWN
		if(i1 - i2 == -1){
			return RIGHT;
		}else if (i1 - i2 == 1){
			return LEFT;
		}
	}

	return NOT_NEIGH;
}


bool GManager::gameIsFinished(){

	if(playerMovesLeft == 0){

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 0 0 0 black
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		// show end message
		char endMsg1[20];
		char endMsg2[30];
		sprintf(endMsg1,"Game Over!");
		drawText(glutGet(GLUT_WINDOW_WIDTH)/2 - 50, glutGet(GLUT_WINDOW_HEIGHT)/2,endMsg1);

		sprintf(endMsg2,"Your final score is: %d",score);
		drawText(glutGet(GLUT_WINDOW_WIDTH)/2 - 75, glutGet(GLUT_WINDOW_HEIGHT)/2 - 25,endMsg2);

		glutSwapBuffers();

		sleep(5);
		exit(0);
	} else{
		return false;
	}
}

void GManager::startGame(){

	gameOn = true;

	randomizeBoard();

}

bool isNotTheSameCube(int i1, int j1, int i2, int j2){
	if(i1==i2 && j1==j2){
		return false;
	}
	return true;
}

bool isInsideBoard(int i,int j){

	if(i>=0 && i<15 && j>=0 && j<15){
		return true;
	}

	return false;
}

void GManager::d1NeighborDestroy(int i,int j, int value){

	for(int v=i-1; v<i+2 ; v++){
		for(int u=j-1; u<j+2 ;u++){
			if(isInsideBoard(v,u)){
				switch(value){
						case ROCK:
							if(board[v][u].getValue() == SCISSORS){
								board[v][u].setValue(BLANK);
								score += 2;
							}
							break;
						case PAPER:
							if(board[v][u].getValue() == ROCK){
								board[v][u].setValue(BLANK);
								score += 2;
							}
							break;
						case SCISSORS:
							if(board[v][u].getValue() == PAPER){
								board[v][u].setValue(BLANK);
								score += 2;
							}
							break;
						default:
							break;
					}

			}
		}
	}
}


bool GManager::threeSame(int i1, int j1, int i2, int j2, int i3, int j3){
	if(isInsideBoard(i1,j1) && isInsideBoard(i2,j2) && isInsideBoard(i3,j3)){
		if(board[i1][j1].getValue() == board[i2][j2].getValue() ){
			if(board[i1][j1].getValue() == board[i3][j3].getValue()){
				return true;
			}
		}
	}
	return false;
}
void GManager::findAndDestroyNeighborsD2_3(int i1, int j1, int i2, int j2, int i3, int j3,int value, int lineOrCol){
	if(lineOrCol == LINE){
		int x = i1;
		int y = j1;
		for(int u = y-3 ; u < y+4 ; u++){
			for(int v=x-3 ; v < x+6 ; v++){
				if(isInsideBoard(v,u)){
					switch(value){
						case ROCK:
							if(board[v][u].getValue() == SCISSORS){
								board[v][u].setValue(BLANK);
								score += 3;
							}
							break;
						case PAPER:
							if(board[v][u].getValue() == ROCK){
								board[v][u].setValue(BLANK);
								score += 3;
							}
							break;
						case SCISSORS:
							if(board[v][u].getValue() == PAPER){
								board[v][u].setValue(BLANK);
								score += 3;
							}
							break;
						default:
							break;
					}
				}

			}
		}

	}else if(lineOrCol == COLUMN){
		int x = i1;
		int y = j1;
		for(int v = x-3; v<x+4; v++){
			for(int u= y+3; u>y-6; u--){
				if(isInsideBoard(v,u)){
					switch(value){
						case ROCK:
							if(board[v][u].getValue() == SCISSORS){
								board[v][u].setValue(BLANK);
								score += 3;
							}
							break;
						case PAPER:
							if(board[v][u].getValue() == ROCK){
								board[v][u].setValue(BLANK);
								score += 3;
							}
							break;
						case SCISSORS:
							if(board[v][u].getValue() == PAPER){
								board[v][u].setValue(BLANK);
								score += 3;
							}
							break;
						default:
							break;
					}
				}
			}
		}
	}
}


void GManager::findAndDestroyNeighborsD1(int i1, int j1, int i2, int j2, int i3, int j3,int value, int lineOrCol){

	if(lineOrCol == LINE){
		int x = i1;
		int y = j1;
		for(int u = y-1 ; u < y+2 ; u++){
			for(int v=x-1 ; v < x+4 ; v++){
				if(isInsideBoard(v,u)){
					switch(value){
						case ROCK:
							if(board[v][u].getValue() != PAPER && board[v][u].getValue() != BLANK){
								board[v][u].setValue(BLANK);
								score +=2;
							}else if(board[v][u].getValue() == BOMB){
								board[v][u].setValue(BLANK);
								score -= 30;
							}else{
								score --;
							}
							findAndDestroyNeighborsD2_3(i1,j1,i2,j2,i3,j3,value,lineOrCol);
							break;
						case PAPER:
							if(board[v][u].getValue() != SCISSORS && board[v][u].getValue() != BLANK){
								board[v][u].setValue(BLANK);
								score +=2;
							}else if(board[v][u].getValue() == BOMB){
								board[v][u].setValue(BLANK);
								score -= 30;
							}else{
								score --;
							}
							findAndDestroyNeighborsD2_3(i1,j1,i2,j2,i3,j3,value,lineOrCol);
							break;
						case SCISSORS:
							if(board[v][u].getValue() != ROCK && board[v][u].getValue() != BLANK){
								board[v][u].setValue(BLANK);
								score +=2;
							}else if(board[v][u].getValue() == BOMB){
								board[v][u].setValue(BLANK);
								score -= 30;
							}else{
								score --;
							}
							findAndDestroyNeighborsD2_3(i1,j1,i2,j2,i3,j3,value,lineOrCol);
							break;
						default:
							break;
					}
				}
			}
		}


	} else if (lineOrCol == COLUMN){
		int x = i1;
		int y = j1;
		for(int v=x-1 ; v < x+2 ; v++){
			for(int u = y+1 ; u > y-4 ; u--){
				if(isInsideBoard(v,u)){
					switch(value){
						case ROCK:
							if(board[v][u].getValue() != PAPER && board[v][u].getValue() != BLANK ){
								board[v][u].setValue(BLANK);
								score +=2;
							}else if(board[v][u].getValue() == BOMB){
								board[v][u].setValue(BLANK);
								score -= 30;
							}else{
								score --;
							}
							findAndDestroyNeighborsD2_3(i1,j1,i2,j2,i3,j3,value,lineOrCol);
							break;
						case PAPER:
							if(board[v][u].getValue() != SCISSORS && board[v][u].getValue() != BLANK){
								board[v][u].setValue(BLANK);
								score +=2;
							}else if(board[v][u].getValue() == BOMB){
								board[v][u].setValue(BLANK);
								score -= 30;
							}else{
								score --;
							}
							findAndDestroyNeighborsD2_3(i1,j1,i2,j2,i3,j3,value,lineOrCol);
							break;
						case SCISSORS:
							if(board[v][u].getValue() != ROCK && board[v][u].getValue() != BLANK){
								board[v][u].setValue(BLANK);
								score +=2;
							}else if(board[v][u].getValue() == BOMB){
								board[v][u].setValue(BLANK);
								score -= 30;
							}else{
								score --;
							}
							findAndDestroyNeighborsD2_3(i1,j1,i2,j2,i3,j3,value,lineOrCol);
							break;
						default:
							break;
					}
				}
			}
		}

	}

}

void GManager::explosion(int i1, int j1, int i2, int j2, int i3, int j3, int lineOrCol){

	int value = board[i1][j1].getValue();
	switch(value){
	case ROCK:
		score += 10;
		findAndDestroyNeighborsD1(i1,j1,i2,j2,i3,j3,ROCK,lineOrCol);
		break;

	case PAPER:
		score += 10;
		findAndDestroyNeighborsD1(i1,j1,i2,j2,i3,j3,PAPER,lineOrCol);
		break;
	case SCISSORS:
		score += 10;
		findAndDestroyNeighborsD1(i1,j1,i2,j2,i3,j3,SCISSORS,lineOrCol);
		break;

	case BLUE:
		board[i1][j1].setValue(BLANK);
		board[i2][j2].setValue(BLANK);
		board[i3][j3].setValue(BLANK);
		score += 10;
		break;

	case RED:
		board[i1][j1].setValue(BLANK);
		board[i2][j2].setValue(BLANK);
		board[i3][j3].setValue(BLANK);
		score += 10;
		break;

	default:
		break;
	}

}

void GManager::handlePlayerMove(int i1, int j1, int i2, int j2){


	if(isInsideBoard(i1,j1) && isInsideBoard(i2,j2) && areNeighbors(i1,j1,i2,j2) && isNotTheSameCube(i1,j1,i2,j2)){ //check if its actually 2 cubes

		swapCubeValue(i1,j1,i2,j2);
		// player did a valid move
		playerMovesLeft -- ;

		// ---------- same column different line
		// check for 3 same with cube 1
		if(threeSame( i1,j1, i1,j1-1, i1,j1-2)){
			
			explosion(i1,j1, i1,j1-1, i1,j1-2,COLUMN);

		}else if(threeSame(i1,j1+2, i1,j1, i1,j1+1)){
			
			explosion(i1,j1+2, i1,j1, i1,j1+1,COLUMN);

		}else if(threeSame(i1,j1+1, i1,j1-1, i1,j1)){
			
			explosion(i1,j1+1, i1,j1-1, i1,j1,COLUMN);
		}
		// check for 3 same with cube 2
		if(threeSame(i2,j2, i2,j2-1,i2,j2-2)){
			
			explosion(i2,j2, i2,j2-1,i2,j2-2,COLUMN);

		}else if(threeSame(i2,j2+2, i2,j2, i2,j2+1)){
			
			explosion(i2,j2+2, i2,j2, i2,j2+1,COLUMN);

		}else if(threeSame(i2,j2+1, i2,j2-1, i2,j2)){
			
			explosion(i2,j2+1, i2,j2-1, i2,j2,COLUMN);
		}

		// ---------- same line different column
		// check for 3 same with cube 1
		if(threeSame(i1-2,j1, i1,j1, i1-1,j1)){
			
			explosion(i1-2,j1, i1,j1, i1-1,j1,LINE);

		}else if(threeSame(i1,j1, i1+1,j1, i1+2,j1)){
			
			explosion(i1,j1, i1+1,j1, i1+2,j1,LINE);

		}else if(threeSame( i1-1,j1, i1,j1, i1+1,j1)){
			
			explosion(i1-1,j1, i1,j1, i1+1,j1,LINE);
		}

		// check for 3 same with cube 1
		if(threeSame( i2-2,j2, i2,j2, i2-1,j2)){
			
			explosion( i2-2,j2, i2,j2, i2-1,j2,LINE);

		}else if(threeSame(i2,j2, i2+1,j2, i2+2,j2)){
			
			explosion(i2,j2, i2+1,j2, i2+2,j2,LINE);

		}else if(threeSame(i2-1,j2, i2,j2, i2+1,j2)){
			
			explosion(i2-1,j2, i2,j2, i2+1,j2,LINE);
		}

		// if not explosion, or small explosion (BLUE/RED)
		// check neighbors of swapped cubes
		d1NeighborDestroy(i1,j1,board[i1][j1].getValue());
		d1NeighborDestroy(i2,j2,board[i2][j2].getValue());

		gameIsFinished();
	}
}



GCube** GManager::getBoard(){

	return board;
}

int GManager::getScore(){

	return score;
}

int GManager::getPlayerMoves(){

	return playerMovesLeft;
}

bool GManager::gameIsOn(){
	return gameOn;
}
