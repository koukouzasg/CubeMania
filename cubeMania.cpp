//final

#include <GL/gl.h>		   // Open Graphics Library (OpenGL) header
#include <GL/glut.h>	   // The GL Utility Toolkit (GLUT) Header
#include <GL/glu.h>


#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <list>
#include <queue>
#include <unistd.h>

using namespace std;


/*--------------------Global Variables-----------------------*/
//PI
const double PI  =3.14159265358979323846;

//Initialize Life score 
int HP=3;
int playerScore=50;

//initialize N
int N;

//playerStock
int playerStock=0;
//Camera view;
int v=0;
//Lights Initialization
GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* Red diffuse light. */
GLfloat light_position1[] = {0.0, 0, 0.0, 0.0};  /* {0,0} Light location */
GLfloat light_position2[] = {0.0, 0, 0, 0.0};  /* {0,N} Light location */
GLfloat light_position3[] = {0, 0, 0.0, 0.0};  /* {N,0} Light location */
GLfloat light_position4[] = {0, 0, 0, 0.0};  /* {N,N} Light location */
GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat playerLight[] = {1.0f,0.8f,0.0f, 0.5f};
GLfloat light_player_pos[]={0,0,0,0};

//Grid flag
int flag = 0;

//Game over flag
int GOflag=0;

//Super Win flag
int SWflag=0;

//random colour
int randNum=1;

//Height and width of the window
int w,h;

//Cube Position

int indexX = 0;
int indexY = 0;
int indexZ = 0;

// angle of rotation for the camera direction in y axis
float angle=0.0;

// actual vector representing the camera's direction,line of sight
//------------Look at point = Line of sight + Camera position-------
float lx=0.0f,lz=1.0f;

// XZ position of the camera in the opengl world
float x=0,z=0,y=1.0f;

//int of x,y,z
int xx,yy,zz;

//Starting position of the player
int startingPos = 0;

//Defining the string for drawText
char str[50];


//-----------------------Cube class initialiazation-------------------

class cube{
private:
	int colour;
	int posX;
	int posY;
	int posZ;
	int active;
	int stock;

public:
	cube() { active=0; }
	void setColour() {colour = randNum;}
	void changeColour(int c) { colour = c;}
	int getColour() {return colour;}
	int getActive() {return active;}
	void setPos() { posX= indexX; posY= indexY; posZ= indexZ; }
	void changePos(int x,int y,int z) { posX=x; posY=y; posZ=z;}
	int getX() { return posX;}
	int getY() { return posY;}
	int getZ() { return posZ;}
	void setActive(int change) { active=change; }
	void colourDown(){colour--;}
	void setStockCube(){
		if (colour==0){
			stock = 0;
		}else if(colour==1){
			stock = 1;
		}else if (colour==2){
			stock = 2;		
		}else if (colour==3){
			stock = 3;
		}else{
			stock = 0;
		}
	}	
	
};
		
//grid array
cube *** ARRAY;


//------------------Initializing N and lights--------------

void init(){
	ARRAY = new cube**[N];
	for(int i=0; i<N; i++){
		ARRAY[i]=new cube*[N];
		for(int j=0; j<N; j++){
			ARRAY[i][j]= new cube[N];
		}
	}

	//Lights Initialization
	 light_position1[1] = N;  /* {0,0} Light location */
	 light_position2[1] = N;  /* {0,N} Light location */
	 light_position2[2]=N;
	 light_position3[0] = N;  /* {N,0} Light location */
	 light_position3[1] = N;
	 light_position4[0] = N;  /* {N,N} Light location */
	 light_position4[1]=N;
	 light_position4[2]=N;
	 x=round(N/2),z=round(N/2),y=1.0f;
	 startingPos = round(N/2);
	 //playerLight Pos
 	 light_player_pos[0]=x;
	 light_player_pos[1]=y;
	 light_player_pos[2]=z;	
}

void renderScene();

//------------------RESPONSIBLE FOR KEEPING THE WINDOW INTACT-----------------------
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}
	
//-------------------------------GRID CODE----------------------

	
void basicGrid(){
	int number;
	srand(time(NULL));
	if (flag == 0){		//set for the first time
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				for(int z=0;z<N;z++){
					ARRAY[i][0][z].setActive(1);	//activate the floor
					number = rand() % 4;
					ARRAY[i][j][z].changeColour(number);
				}
			}
		}
		flag = 1;
		ARRAY[startingPos][0][startingPos].changeColour(4); 	//MAGENTA CUBE
		//ARRAY[N/2][5][12].setActive(1);voh8htiko kubaki gia eksetash
		//ARRAY[N/2][9][12].setActive(1);voh8htiko kubaki gia eksetash
		//ARRAY[N/2][2][13].setActive(1); gia eksetash
		//ARRAY[N/2][1][19].setActive(1); gia eksetash
		//ARRAY[N/2+2][1][19].setActive(1); gia eksetash
		//ARRAY[N/2][0][12].setActive(0);//voh8htiko kubaki pesimo gia eksetash
		//Check (ix)
		for(int i = 0; i < N; i++) {
			for(int j=0; j < N; j++) {
				if(i==j){
					ARRAY[i][j][0].setActive(1);
				}
			}
		}
	}
}

//Drawing the little avatar guy

void createAvatar(){
	//left foot
	glPushMatrix();
	glTranslatef(x+0.1f,y-0.5f,z);
	glColor3f(1.0f,1.0f,1.0f);
	glutSolidCube(0.1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(x+0.1f,y-0.4f,z);
	glColor3f(1.0f,1.0f,1.0f);	
	glutSolidCube(0.1);
	glPopMatrix();
	//right foot
	glPushMatrix();
	glTranslatef(x-0.1f,y-0.5f,z);
	glColor3f(1.0f,1.0f,1.0f);	
	glutSolidCube(0.1);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(x-0.1f,y-0.4f,z);
	glColor3f(1.0f,1.0f,1.0f);	
	glutSolidCube(0.1);
	glPopMatrix();
	//body
	glPushMatrix();
	glTranslatef(x,y-0.2f,z);
	glColor3f(0.44f,0.51f,0.57f);	
	glutSolidCube(0.3);
	glPopMatrix();
	//head
	glPushMatrix();
	glTranslatef(x,y,z);
	glColor3f(0.18f,0.31f,0.31f);	
	glutSolidCube(0.2);
	glPopMatrix();
}


void drawGrid() {
	int c=0;
	basicGrid();
	for(int i = 0; i < N; i++) {
		for(int j=0; j < N; j++) {
			for(int z=0;z < N ; z++){
				glPushMatrix();
				c=ARRAY[i][j][z].getColour();
				switch(c) {
				case 0:
					glColor3f( 0.0, 0.0, 1.0 );
					break;
				case 1:
					glColor3f( 1.0, 1.0, 0.0 );
					break;
				case 2:
					glColor3f( 1.0, 0.0, 0.0 );
					break;
				case 3:
					glColor3f( 0.0, 1.0, 0.0 );	
					break;
				case 4:		
					glColor3f(1.0f,0,1.0f);	
				default:
					break;
				}
				glTranslatef(i*1.0,j * 1.0f,z * 1.0);
				if(ARRAY[i][j][z].getActive()){
					glutSolidCube(1.0f);
					glColor3f(0,0,0);
					glutWireCube(1.0f);
				}
				glPopMatrix();
			}
		}
	}
	createAvatar();
}

//----------------GAME FUNCTIONS----------------------

void gameOver(){
	if(playerScore<=0){
		HP--;
		playerScore=50;
		//Respawn point for the player after losing one life
		if(ARRAY[startingPos][1][startingPos].getActive()==1){
			ARRAY[startingPos][1][startingPos].setActive(0);
		}
		x=round(N/2);
		y=1.0f;
		z=round(N/2);
		lx=0.0f;
		lz=1.0f;
	}
	
	if(HP<=0){
		GOflag=1;
		renderScene();
		printf("GAME OVER\n");
		sleep(5);
		exit(1);	
	}
}

void subtractLife(){
	HP--;
	gameOver();
	//Respawn point for the player after losing one life
	if(ARRAY[startingPos][1][startingPos].getActive()==1){
			ARRAY[startingPos][1][startingPos].setActive(0);
	}
	x=round(N/2);
	y=1.0f;
	z=round(N/2);
	lx=0.0f;
	lz=1.0f;
}

void computeScore(int count){
	playerScore -= count*5;
	if(playerScore<=0){
		gameOver();	
	}
}

//Reached Highest level of the grid?
void checkSuperWin(){
		if(y==N-1){
			HP++;
			playerScore+=100;
			printf("Upper level succeeded\n");
		}
}

//----------------HANDLING THE LIGHTS FUNCTION---------------

//Defining the Light types,their positions and are turned on
void lights(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	
	//LIGHTS
	
  	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position4);
	glLightfv(GL_LIGHT0,GL_SPECULAR, sourceLight);
	//playerLight
	glLightfv(GL_LIGHT0,GL_AMBIENT,playerLight);
	glLightfv(GL_LIGHT0,GL_POSITION, light_player_pos);

  	glEnable(GL_LIGHT0);
  	glEnable(GL_LIGHTING);
	
	
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	glShadeModel( GL_SMOOTH );
}

//----------------------PROJECTING AT THE WINDOW FUNCTION--------------

void drawText(const char *str,int x,int y) 
{  
	if(GOflag==1){
		glColor3f(1.0f,0.0f,0.0f); //red color.this is the game over case
		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D( 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0 );

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glRasterPos2i( x, y );  // The position of the text on the screen
		const char *c;
		for (c=str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		glMatrixMode( GL_MODELVIEW );
	}else{
		glColor3f(1.0f,0.8f,0.0f); //gold color
		glMatrixMode( GL_PROJECTION );
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D( 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0 );

		glMatrixMode( GL_MODELVIEW );
		glPushMatrix();
		glLoadIdentity();
		glDisable(GL_LIGHTING);
		glRasterPos2i( x, y );  // The position of the text on the screen
		const char *c;
		for (c=str; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
		glEnable(GL_LIGHTING);
		glPopMatrix();

		glMatrixMode( GL_PROJECTION );
		glPopMatrix();
		glMatrixMode( GL_MODELVIEW );
	}
}

//----------------BASIC AND MOST IMPORTANT FUNCTION FOR THE MAIN LOOP---------------

void renderScene(void) {

	//Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Reset transformations
	glLoadIdentity();

	//Enabling lights
	lights();
	
	// Set the camera
	if (v==0){
	gluLookAt(	x, y, z,
			x+lx, y,  z+lz,
			0.0f, 1.0f,  0.0f);
	}
	if (v==1){
	gluLookAt(	x + (-lx*3),y+0.5,z+ (-lz*3) ,
			x, y,  z,
			0.0f, 1.0f,  0.0f);
	}

	//Draw the grid every frame
	drawGrid();
	
	//Diplaying info
	if(GOflag==1){
		sprintf(str,"GAME OVER.Thank you for playing with me!!! ^_^\n");
		drawText(str,420,300);
	}else{
		sprintf(str,"Health Points: %d\n",HP);
		drawText(str,5,30);
		sprintf(str,"Score: %d\n",playerScore);
		drawText(str,5,60);
		sprintf(str,"Available Cubes: %d\n",playerStock);
		drawText(str,5,90);
	}
	
	glutSwapBuffers();
}

//-------------------KEYBOARD FUNCTION---------------------

void processNormalKeys(unsigned char key, int xx, int yy) {

	float frame =0.1f;//frame for better camera movement
	float beginningAngle=0.0f;
	float targetAngle=0.0f; 
	int nextX,nextZ,nextY;
	int countLevels=-1; //sum the descending levels.Starts at -1 for easier computing
	int numberColour;
	int eFlag,rFlag,flagScore,headFlag=0;
	int colourCube;
	int currentX=x;
	int currentY=y;
	int currentZ=z;

	if (key == 27)	exit(0);
		
	//SPACEBAR
	if (key ==32) {     
		xx=x;//metatroph se int
		yy=y;
		zz=z;	
		numberColour=ARRAY[xx][yy-1][zz].getColour();//check lower level
		if (numberColour==1||numberColour==2||numberColour==3){
			playerStock++;
			playerScore-=5;
			gameOver();
			ARRAY[xx][yy-1][zz].colourDown();
			ARRAY[xx][yy-1][zz].setStockCube();
		}
	}		
	switch (key) {
		case 'A' :	
		case 'a' :
			beginningAngle=angle;
			targetAngle=beginningAngle+PI/2;
			while(angle<=targetAngle){
				angle=angle+frame;
				lx = sin(angle);
				lz = cos(angle);
				renderScene();
			}
			angle=targetAngle;
			lx = sin(angle);
			lz = cos(angle);
			break;
		case 'D' :	
		case 'd' :
			beginningAngle=angle;
			targetAngle=beginningAngle-PI/2; 
			while(angle>=targetAngle){
				angle=angle-frame;
				lx = sin(angle);
				lz = cos(angle);
				renderScene();
			}
			angle=targetAngle;
			lx = sin(angle);
			lz = cos(angle);
			break;
		case 'W' :	
		case 'w' :
			nextX=x+round(lx);
			nextZ=z+round(lz);
			nextY=y;
			if((x+round(lx)>N-1)||(x+round(lx)<0)||(z+round(lz)>N-1)||(z+round(lz)<0)){ //Out of bounds condition
				
				break;
			}else if(ARRAY[nextX][nextY][nextZ].getActive()==1 && y==N-1){ //Out of on Y AXIS
				break;	
			}else if(ARRAY[nextX][nextY][nextZ].getActive()==1 && ARRAY[nextX][nextY+1][nextZ].getActive()==0 && nextY<=N-1){   //check front for ascending the cube
				y+=1;
				x += round(lx) ;
				z += round(lz) ;
				//light follows the player
				light_player_pos[0]=x;	
				light_player_pos[1]=y;
				light_player_pos[2]=z;
				playerScore+=5;
				if(y==N-1){
					SWflag==1; //super win flag
					checkSuperWin();
				}
			}else if(ARRAY[nextX][nextY][nextZ].getActive()==1 && ARRAY[nextX][nextY+1][nextZ].getActive()==1){ //Dont climb on two cubes
				break;
			}
			else{
				x += round(lx) ;
				z += round(lz) ;
				while(ARRAY[nextX][nextY-1][nextZ].getActive()==0){
					printf("x=%f y=%f z=%f\n",x,y,z);
					if(y-1 <=0){
						subtractLife();
						break;
					}
					nextY-=1;
					y-=1;
					SWflag=0;   //super win flag
					countLevels++;
					computeScore(countLevels);
					
				}
				//light follows the player
				light_player_pos[0]=x;	
				light_player_pos[1]=y;
				light_player_pos[2]=z;
			}
			break;
		case 'S' :	
		case 's' :
			beginningAngle=angle;
			targetAngle=beginningAngle-PI;
			while(angle>=targetAngle){
				angle=angle-frame;
				lx = sin(angle);
				lz = cos(angle);
				renderScene();
			}
			angle=targetAngle;
			lx = sin(angle);
			lz = cos(angle);
			break;
		case 'Q' :	
		case 'q' :
			nextX=x+round(lx);// int conversion
			nextY=y;
			nextZ=z+round(lz);
			if(ARRAY[nextX][nextY][nextZ].getActive()==1){
				ARRAY[nextX][nextY][nextZ].setActive(0);
			}
			break;
		case 'E' :	
		case 'e' :
			nextX=x+round(lx);//Conversion at point of view
			nextY=0;
			nextZ=z+round(lz);
			eFlag=0;
			for(int i=0;i<N;i++){
				if (ARRAY[nextX][i][nextZ].getActive()){
					eFlag=1;// at least one cube active
				}
			}
			while ((nextY<N)&&(eFlag==1)){
				ARRAY[nextX][nextY][nextZ].setActive(0);
				nextY++;
			}
			if (eFlag==1){
				HP++;
				playerScore-=20;
				gameOver();
			}
			ARRAY[startingPos][0][startingPos].setActive(1);//magenta always on
			break;
		case 'R' :	
		case 'r' :
			xx=x;
			yy=y;
			zz=z;
			//check all the cubes for active ones
			for(int i = 0; i < N; i++) {
				for(int j=0; j < N; j++) {
					for(int z=0;z < N ; z++){
						if (ARRAY[i][j][z].getActive()){			
							for(int a=0;a<N ;a++){	
								//check for something above
								if(ARRAY[currentX][a][currentZ].getActive()==1 && a>0){
									headFlag=1;
								}
							}
							if (headFlag==0){
								colourCube=ARRAY[i][j][z].getColour();	
								if (ARRAY[i][0][z].getActive()==0) { rFlag=1;} 		//check zero level
								while((j>0)&&(ARRAY[i][j-1][z].getActive()==0)){	
									ARRAY[i][j][z].setActive(0);
									ARRAY[i][j-1][z].setActive(1);
									ARRAY[i][j-1][z].changeColour(colourCube);
									j--;
									renderScene();
									sleep(1);
									flagScore=1;
								
								}
								if(rFlag){	
									ARRAY[i][0][z].setActive(0);
								}
							}
							headFlag=0;
						}
					
					rFlag=0;
					}
				
				}
			}
			if (flagScore==1){
				playerScore+=10;
			}
			break;
		case 'V' :	
		case 'v' :
			v=1;
			break;
		case 'C' :	
		case 'c' :
			v=0;
			break;
	}
}

//---------------------MOUSE FUNCTION-------------------------

void mouseButton(int button,int state,int xx,int yy){
	int nextX,nextZ,nextY;
	nextX=x+round(lx);
	nextY=y;
	nextZ=z+round(lz);
	int prevX= round(lx);
	int prevZ= round(lz);
	int currentX=x;
	int currentZ=z;
	int colourCube;
	int counterCubes=0;
	int tempX,tempZ;
	//LEFT CLICK EVENT
	if(button==GLUT_LEFT_BUTTON){
		if(state==GLUT_UP){
			if((x+round(lx)<=N-1)&&(x+round(lx)>=0)&&(z+round(lz)<=N-1)&&(z+round(lz)>=0)){  //Dont let the player build outside the grid
				if(playerStock>0){
					if(ARRAY[nextX][nextY][nextZ].getActive()==0){                
						ARRAY[nextX][nextY][nextZ].setActive(1);
						playerStock--;
						playerScore+=5;
					}else{
						while(ARRAY[nextX][nextY][nextZ].getActive()==1){
							nextY++;
							if(nextY>=N){ //dont let the player build over the Y AXIS
								break;
							}
						}
						if(nextY>=N){

						}else{
							ARRAY[nextX][nextY][nextZ].setActive(1);
							playerStock--;
							playerScore+=5;
						}
					}
				}
			}
		}
	}
	
	//RIGHT CLICK EVENT
	cube QUEUE[N];
	if(button==GLUT_RIGHT_BUTTON){
		if(state==GLUT_UP){
			if(ARRAY[nextX][nextY][nextZ].getActive()==1){
				colourCube=ARRAY[nextX][nextY][nextZ].getColour();
				while((nextX<=N-1)&&(nextX>=0)&&(nextZ<=N-1)&&(nextZ>=0)){ //check the number of cubes
					if(ARRAY[nextX][nextY][nextZ].getActive()){
						indexX=nextX;indexY=nextY;indexZ=nextZ;
						QUEUE[counterCubes].changeColour(ARRAY[nextX][nextY][nextZ].getColour());
						QUEUE[counterCubes].setPos();
						counterCubes++;
					}
				nextX+= round(lx);
				nextZ+= round(lz);
				}
				for(int i=counterCubes;i>=0;i--){		//Iterate the queue
					currentX=(QUEUE[i].getX());
					currentZ=QUEUE[i].getZ();
					colourCube=QUEUE[i].getColour();
					while((currentX<=N-1)&&(currentX>=0)&&(currentZ<=N-1)&&(currentZ>=0)){	
						ARRAY[currentX][nextY][currentZ].setActive(0);
						if((currentX==0 || currentX==N-1 ||currentZ==0 || currentZ==N-1)){
							ARRAY[currentX][nextY][currentZ].changeColour(QUEUE[i].getColour());
							ARRAY[currentX][nextY][currentZ].setActive(1);
							break;
						}else{												
							tempX= currentX+round(lx);
							tempZ= currentZ+round(lz);
							if(ARRAY[tempX][nextY][tempZ].getActive()){
								ARRAY[currentX][nextY][currentZ].changeColour(QUEUE[i].getColour());
								ARRAY[currentX][nextY][currentZ].setActive(1);
							}
							currentX+= round(lx);
							currentZ+= round(lz);
						}
					
					}
					renderScene();
					sleep(0.9);
				}
			}
		}
	}
}

//-------------MAIN------------------------------

int main (int argc, char **argv) {

	cout << "Welcome to Cube-Mania.A place where you can cube everything!" << endl;
	cout << "Happy Cubing!" << endl;
	cout << "Enter dimensions in range of 10 to 20" << endl;
	do{
	cin	 >> N;
	cout << "Please enter the right dimensions" << endl;
	}while(N<10 || N>20);
	//responsible for allocating N	
	init();

	//init Glut and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("CubeMania");

	//register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	//Keyboard functions
	glutKeyboardFunc(processNormalKeys);
	//glutSpecialFunc(processSpecialKeys);

	//Mouse Functions
	glutMouseFunc(mouseButton);
	
	
	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	//enter Glut event processing cyclei
	glutMainLoop();

	return 1;
}
