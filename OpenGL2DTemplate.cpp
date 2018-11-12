#include <stdio.h>
#include <math.h>
#include <random>
#include <vector>
#include <string.h>
#include <glut.h>
#include <windows.h>

//-----------------

//  Methods Signatures

void background();
void print(int x, int y, char *string);
void drawRect(int x, int y, int w, int h);
void Key(unsigned char key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer2(int value);

void Timer(int value);
void Display();
void Anim();
void defenderfire();

//-----------------
class Fire
{
public:  int x;
public:  int y;
public:  int type;
		 //0 fire 1 +health 2+score

		 //Default Constructor
		 Fire(int xx, int yy, int zz)
		 {
			 x = xx;
			 y = yy;
			 type = zz;
		 }

public:  void update(int sign) {
	y = y + sign;
}
public: void draw() {
	if (type == 1) {
		//score
		glColor3f(1.0f, 1.0f, 1.0f);
		Circle(12, 14, x, y);
	}
	else if (type == 2) {
		//health
		glColor3f(0.0f, .0f, 1.0f);
		Circle(12, 14, x, y);
	}
	else if (type == 0) {
		glColor3f(1.0f, 0.0f, 0.0f);
		Circle(8, 8, x, y);
	}
	else {
		glColor3f(1.0f, 4.0f, 2.0f);
		Circle(8, 8, x, y);
	}
}

		void Circle(float radiusX, float radiusY, float x, float y)
		{
			const float DEG2RAD = 3.14159 / 180;

			glBegin(GL_POLYGON);
			for (int i = 0; 360<0 ? i >= 360 : i <= 360; 360<0 ? i-- : i++)
			{
				float degInRad = i*DEG2RAD;
				glVertex3f(cos(degInRad)*radiusX + x, sin(degInRad)*radiusY + y, 0);
			}


			glEnd();
		}

};
//  Global Variables
std::vector<Fire> fireenemy;
std::vector<Fire> fireplayer;
std::vector<Fire> defenderfires;
std::vector<Fire> pluss;


int z = 1;
int p1[2];
int res[2];
int p0[2];
int p2[2];
int p3[2];
int enemTranx;
int enemTrany;
float rotangle;
int xold = 0;
int yold = 0;
int *p;
float t = 0;
int player_x = 0;
int lastx = 0;
int lasty = 0;
int defx = -600;
// holds the Y translation value of bar 1
float angel = 0;
int player_health = 60;
int enemy_health = 40;
int score = 0;
int h = 1;
int level = 1;

//-----------------

void backgroundSound(int val) {
	PlaySound(TEXT("spaceinvaders1.wav"), NULL, SND_ASYNC | SND_FILENAME);
}


int main(int argc, char** argr) {
	glutInit(&argc, argr);

	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(150, 150);

	glutCreateWindow("Chicken Invaders");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Key);      // sets the Keyboard handler function; called when a key is pressed
	glutKeyboardUpFunc(KeyUp);  // sets the KeyboardUp handler function; called when a key is released
								// glutMouseFunc(Mouse);       // sets the Mouse handler function; called when a mouse button is clicked
	glutIdleFunc(Anim);
	glutTimerFunc(0, Timer, 0); // sets the Timer handler function; which runs every Threshold milliseconds (1st argument)
								// glutTimerFunc(0, Timer2, 0); // sets the Timer handler function; which runs every Threshold milliseconds (1st argument)
	glutTimerFunc(0, backgroundSound, 0);

	p0[0] = 0;
	p0[1] = 0;

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(1, 1, 1, 0);
	gluOrtho2D(0, 1000, 0, 1000);



	glutMainLoop();
	return 0;
}


const float DEG2RAD = 3.14159 / 180;

void Circle(float radiusX, float radiusY, float x, float y)
{
	glBegin(GL_POLYGON);
	for (int i = 0; 360<0 ? i >= 360 : i <= 360; 360<0 ? i-- : i++)
	{
		float degInRad = i*DEG2RAD;
		glVertex3f(cos(degInRad)*radiusX + x, sin(degInRad)*radiusY + y, 0);
	}

	glEnd();
}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{

	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}

void defenderfire() {
	defenderfires.push_back(Fire(defx + 160, 500, 0));

}

void Anim()
{

	if (t >= 1) {



		p0[0] = p3[0];
		p0[1] = p3[1];

		p1[0] = p0[0] + z*(rand() % 300);
		p1[1] = (rand() % 150) + 10;

		p2[0] = p1[0] + z*(rand() % 200);
		p2[1] = (rand() % 100) + 10;

		p3[0] = p2[0] + z*(rand() % 200);
		p3[1] = (rand() % 220);




		if (p3[0]<-500) {
			p3[0] = -500;
		}
		if (p3[0]>350) {
			p3[0] = 350;
		}

		if (p2[0]<-500) {
			p2[0] = -500;
		}
		if (p2[0]>350) {
			p2[0] = 350;
		}

		if (p1[0]<-500) {
			p1[0] = -500;
		}
		if (p1[0]>350) {
			p1[0] = 350;
		}

		/////////////

		if (p3[1]<0) {
			p3[1] = 0;
		}
		if (p3[1]>350) {
			p3[1] = 350;
		}

		if (p2[1]<0) {
			p2[1] = 0;
		}
		if (p2[1]>350) {
			p2[1] = 350;
		}

		if (p1[1]<0) {
			p1[1] = 0;
		}
		if (p1[1]>350) {
			p1[1] = 350;
		}




		z = z*-1;

		//white room
		t = 0;
	}
	t += .0008;

	p = bezier(t, p0, p1, p2, p3);



	enemTranx = p[0];
	enemTrany = p[1];
	if (xold > enemTranx) {
		rotangle = 30;
	}
	if (xold < enemTranx) {
		rotangle = -30;
	}
	xold = enemTranx;
	yold = enemTrany;

	if (defx>1000) {
		defx = -650 + -1 * (rand() % 100);
		defenderfires.clear();

	}

	if (100 + defx >= 0 && defx % 300 == 0) {
		defenderfire();

	}

	if (100 + defx >= 0 && defx % 987 == 0 && (defx + rand()) % 7 == 0 && rand() % 2 == 0) {
		pluss.push_back(Fire(rand() % 1000, 1000 + rand() % 500, 1));

	}

	if (130 + defx >= 0 && defx % 577 == 0 && (defx + rand()) % 7 == 0 && 3 % 2 == 1) {
		pluss.push_back(Fire(rand() % 1000, 1000 + rand() % 300, 2));

	}


	if (defx % 200 == 0) {
		///darb  al wa74
		fireenemy.push_back(Fire(600 + enemTranx, 600 + enemTrany, 0));
	}
	glutPostRedisplay();

}



// Keyboard handler function
//   key: the key pressed on the keyboard
//   x  : the X coordinate of the mouse cursor at the moment of pressing the key
//   y  : the Y coordinate of the mouse cursor at the moment of pressing the key
void Key(unsigned char key, int x, int y) {



	if (key == 'd') {

		angel = -25;
		player_x += 10;


	}
	if (key == 'a') {
		angel = 25;
		player_x -= 10;



	}
	if (key == 'w') {
		//darb el 
		PlaySound(TEXT("shoot.wav"), NULL, SND_ASYNC | SND_FILENAME);
		glutTimerFunc(30, backgroundSound, 0);
		fireplayer.push_back(Fire(500 + player_x, 200, 4));

	}


	glutPostRedisplay();
}



// KeyboardUp handler function
//   similar to the Keyboard handler function except that it is called only when the key is released
void KeyUp(unsigned char key, int x, int y) {
	// reset the selectedBar value to 0 to unselect the selected bar
	angel = 0;
	// ask OpenGL to recall the display function to reflect the changes on the window
	glutPostRedisplay();
}



void Timer(int value) {
	defx += 1;

	for (int i = 0; i<defenderfires.size(); i++) {



		defenderfires.at(i).update(-1);
		int x = 500 + player_x;
		int y = 175;
		if (abs(defenderfires.at(i).x - x)<40 && abs(defenderfires.at(i).y - y)<50) {
			defenderfires.erase(defenderfires.begin() + i);
			player_health -= .0000001;

		}
		else if (defenderfires.at(i).x - y <0) {
			defenderfires.erase(defenderfires.begin() + i);

		}

	}

	for (int i = 0; i<fireenemy.size(); i++) {



		fireenemy.at(i).update(-1);
		int x = 500 + player_x;
		int y = 175;
		if (fireenemy.at(i).x<-5) {
			fireenemy.erase(fireenemy.begin() + i);
		}

		else  if (abs(fireenemy.at(i).x - x)<40 && abs(fireenemy.at(i).y - y)<50) {
			fireenemy.erase(fireenemy.begin() + i);
			player_health -= .0000001;

			//sound

		}


	}

	for (int i = 0; i<fireplayer.size(); i++) {


		int x = 160 + defx;
		int y = 500;
		fireplayer.at(i).update(1);
		if (fireplayer.at(i).y>1000) {
			fireplayer.erase(fireplayer.begin() + i);
		}
		else if (abs(fireplayer.at(i).x - x)<100 && abs(fireplayer.at(i).y - y)<5) {


			fireplayer.erase(fireplayer.begin() + i);
			//sound

		}
		else  if (abs(fireplayer.at(i).x - (600 + enemTranx))<50 && abs(fireplayer.at(i).y - (600 + enemTrany))<60) {
			fireplayer.erase(fireplayer.begin() + i);
			enemy_health -= 5;
			score += 1;
			//sound // decrease health

		}


	}

	for (int i = 0; i<pluss.size(); i++) {



		pluss.at(i).update(-1);
		int x = 500 + player_x;
		int y = 175;
		if (pluss.at(i).x<-5) {
			pluss.erase(pluss.begin() + i);
		}

		else  if (abs(pluss.at(i).x - x)<40 && abs(pluss.at(i).y - y)<50) {
			if (pluss.at(i).type == 1)
				score += 10;

			else  if (pluss.at(i).type == 2)
				player_health += 5;
			pluss.erase(pluss.begin() + i);




			//sound

		}


	}

	if (enemy_health <= 0) {
		h++;
		enemy_health = h * 40;
		score += 10 * (h - 1);
		level++;
	}

	if (player_health <= 0) {
		print(500, 500, "Game Over ! Press r to replay");

	}








	// ask OpenGL to recall the display function to reflect the changes on the window
	//  glutPostRedisplay();

	// recall the Timer function after 20 seconds (20,000 milliseconds)
	glutTimerFunc(8, Timer, 0);
}


void playershape() {
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS); // GL_QUAD_STRIP
	glVertex3f((500.0 + (35 / 2.0) + 5), 350 / 2.0, 0.0f);
	glVertex3f((500.0 + (35 / 2.0) - 5), 350 / 2.0, 0.0f);

	glVertex3f(500.0 + (35 / 2.0) - 5, 350 / 2.0 + 50, 0.0f);
	glVertex3f(500.0 + (35 / 2.0) + 5, 350 / 2.0 + 50, 0.0f);

	/////////////
	glVertex3f((500.0 - (35 / 2.0) + 5), 350 / 2.0, 0.0f);
	glVertex3f((500.0 - (35 / 2.0) - 5), 350 / 2.0, 0.0f);

	glVertex3f(500.0 - (35 / 2.0) - 5, 350 / 2.0 + 50, 0.0f);
	glVertex3f(500.0 - (35 / 2.0) + 5, 350 / 2.0 + 50, 0.0f);


	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(570, 140, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(500, 210, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(500, 180, 0.0f);
	glEnd();
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(430, 140, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(500, 210, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(500, 180, 0.0f);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	Circle(13, 13, 465, 350 / 2.0 - 15);
	Circle(13, 13, 535, 350 / 2.0 - 15);



	// glBegin(GL_QUADS); // GL_QUAD_STRIP
	// glVertex3f(100.0f  , 50.0f, 0.0f);
	// glVertex3f(100.0f , 150.0f, 0.0f);
	// glVertex3f(200.0f , 150.0f, 0.0f);
	// glVertex3f(200.0f , 50.0f, 0.0f);
	// glEnd();
}




void player() {
	glPushMatrix();

	glTranslatef(player_x, 0, 0);
	glTranslatef(500.0, 175.0, 0);
	glRotated(angel, 0, 0, 1); // fan rotation
	glTranslatef(-500.0, -175.0, 0);

	playershape();

	glPopMatrix();


}

void enemyshape() {
	// glBegin(GL_TRIANGLES); // GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
	// glVertex3f(100.0f, 600.0f, 0.0f);
	// glVertex3f(150.0f, 600.0f, 0.0f);
	// glVertex3f(125.0f, 650.0f, 0.0f);
	//
	// glEnd();
	//main circle

	glColor3f(0.5, 0.5, 0.5);
	Circle(50, 60, 600, 600);

	//black around eye
	glColor3f(0, 0, 0);
	Circle(13, 16, 625, 630);
	//black
	glColor3f(0, 0, 0);
	Circle(13, 16, 600 - 25, 630);

	//eye
	glColor3f(0, 0.5, 0.5);
	Circle(10 - 5, 12.5 - 5, 600 - 25, 630);

	glColor3f(0, 0.5, 0.5);
	Circle(10 - 5, 12.5 - 5, 600 + 25, 630);

	glBegin(GL_LINES);
	glVertex3f(650.0f, 600.0f, 0.0f);
	//glVertex3f(20.0f, 20.0f, 0.0f);
	//glVertex3f(30.0f, 30.0f, 0.0f);
	glVertex3f(650 + 20.0f, 540.0f, 0.0f);

	////
	glVertex3f(550.0f, 600.0f, 0.0f);
	//glVertex3f(20.0f, 20.0f, 0.0f);
	//glVertex3f(30.0f, 30.0f, 0.0f);
	glVertex3f(550 - 20.0f, 540.0f, 0.0f);


	glEnd();

	glBegin(GL_QUADS); // GL_QUAD_STRIP
	glVertex3f(600 - 15 - 5.0f, 600 - 15 + 10.0f, 0.0f);
	glVertex3f(600 + 15 + 5.0f, 600 - 15 + 10.0f, 0.0f);
	glVertex3f(600 + 15 + 5.0f, 600 + 15 - 5.0f, 0.0f);
	glVertex3f(600 - 15 - 5.0f, 600 + 15 - 5.0f, 0.0f);


	glEnd();

	glBegin(GL_LINES);
	glVertex3f(650.0f, 540.0f, 0.0f);
	//glVertex3f(20.0f, 20.0f, 0.0f);
	//glVertex3f(30.0f, 30.0f, 0.0f);
	glVertex3f(650 + 20.0f, 500.0f, 0.0f);

	////
	glVertex3f(550.0f, 540.0f, 0.0f);
	//glVertex3f(20.0f, 20.0f, 0.0f);
	//glVertex3f(30.0f, 30.0f, 0.0f);
	glVertex3f(550 - 20.0f, 500.0f, 0.0f);


	glEnd();
	//Circle(10,12.5,80,625 ,false,180);


}

void enemy() {

	glPushMatrix();
	glTranslatef(enemTranx, enemTrany, 0);
	glTranslatef(600, 600, 0);

	glRotated(rotangle, 0, 0, 1);

	glTranslatef(-600, -600, 0);

	//printf("%f\n",rotangle );


	enemyshape();

	glPopMatrix();

}

void fire() {

}

void background() {
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS); // GL_QUAD_STRIP

	for (int l = 10; l<100; l++) {
		int x = rand() % 1000;
		int y = rand() % 1000;
		int i = x;
		int j = y;
		glVertex3f(i - 1, j - 1, 0.0f);
		glVertex3f(i + 1, j - 1.0f, 0.0f);
		glVertex3f(i + 1, j + 1, 0.0f);
		glVertex3f(i - 1, j + 1.0f, 0.0f);

	}
	glEnd();


}

void defender() {
	glBegin(GL_QUADS); // GL_QUAD_STRIP
	glColor3f(1.0, 3.0, 0.0);
	glVertex3f(100.0 + defx, 500.0f, 0.0f);
	glVertex3f(220.0 + defx, 500.0f, 0.0f);
	glVertex3f(220.0 + defx, 540.0f, 0.0f);
	glVertex3f(100.0 + defx, 540.0f, 0.0f);


	glEnd();

}
void fireshape() {
	for (int i = 0; i<defenderfires.size(); i++) {
		defenderfires.at(i).draw();
	}
	for (int i = 0; i<fireenemy.size(); i++) {
		fireenemy.at(i).draw();
	}

	for (int i = 0; i<fireplayer.size(); i++) {
		fireplayer.at(i).draw();
	}

	for (int i = 0; i<pluss.size(); i++) {
		pluss.at(i).draw();
	}

}
void health() {
	int c = enemy_health / 5;
	glColor3f(0, 0, 1);
	for (int i = 1; i <= c; i++) {
		Circle(10, 10, 200 + i * 20, 960);
	}
	int cc = player_health / 5;
	glColor3f(0, 0, 1);
	for (int i = 1; i <= cc; i++) {
		Circle(10, 10, 200 + i * 20, 100);
	}

}

void print(int x, int y, char *string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void info() {
	char* ps[20];
	sprintf((char *)ps, "Level %d", level);
	print(800, 950, (char*)ps);

	sprintf((char *)ps, "PLayer Score %d", score);
	print(800, 900, (char*)ps);

	print(20, 950, "Enemy Health");
	print(20, 100, "PLayer Health");

	// std::char *s = std::to_char(score);
	//
	//
	//   char *lev = "Your Level Is ";




}

void plus() {

}
void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);

	background();
	defender();
	player();
	enemy();
	fireshape();
	health();
	plus();
	info();

	glFlush();
}
