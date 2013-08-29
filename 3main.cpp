

#include<unistd.h>
#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include<vector>
#include <cmath>
//#include "glm-0.3.1/glm/glm.h"
//#include "glm-0.3.1/glm/glmint.h"
//#include "glm-0.3.1/glm/glmimg.cpp"
//#include<freeglut.h>
#include "imageloader.h"
#include <GL/glut.h>
#include <GL/gl.h>

using namespace std;
#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)
typedef struct bloc{
	int tramp,up,down,prob,drop,coin;
	int fire;
	float y,xstart,xend,zstart,zend;
}block;
void updatex(int);
void updateout(int);
void updatey(int);
void checkpos();
void drawStrokeText(char *,int,int,int);
void drawrobo();
void blockups(int );
void initializer(int);
float zr=40.0f,xr=-40.0f,yr=15.5f;
float anglee=270,anglee2=90;
float pos_X,pos_Y,pos_Z;
int i,j,left1=1;
int interface=33;
int stage=3;
float variable=225;
int colflag=0,jmpflag=0,downflag=0;
int fpson=0,mflag=0;
int tcami=1,tcamj=1;
int cnt=0,ton=0,spotl=0,outgr=0;
float angle1=180;
float xx,yy,zz,xprev,zprev;
float xc,yc,zc,xla,yla,zla;
float old_x=0,diff_x,iold_y,old_y=0,diff_y=0;
float sp=2.5,oriyr;
int presbi,presbj,hon=0;
int inerflag=0;
float sau=105;
float anglo=0;
int flagchu=0;
int score=0;
void GetOGLPos(int,int);
block a[101][101];
//Called when a key is pressed

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId,_textureId2,_textureId3,_textureId4,_textureId5,_textureId6,_textureId7,_textureId8,_textureId9,_textureId10; //The id of the texture

static double yVal=1.0;
void earth(){

	if(anglee> 270)
	{
		glPushMatrix();
		glColor3f(1.0f,0.0f,0.0f);
		glRotatef(anglee, 1.0, 0.0, 0.0);
		//printf("%f\n",anglee);

		glTranslatef(0.0,70,0);
		glutSolidSphere(3,50,50);
		glPopMatrix();
	}

	if(anglee2 > 270)
	{
		glPushMatrix();
		//	printf("chuu%f\n",anglee);
		glColor3f(1.0f,1.0f,1.0f);
		glRotatef(anglee2, 1.0, 0.0f, 0.0f);
		glTranslatef(0.0,70,0);
		glutSolidSphere(3,50,50);
		glPopMatrix();
	}
	anglee+=0.05;
	anglee2+=0.05;
	if(anglee >=360)
	{
		anglee=0;
	}
	if(anglee2 >=360)
	{
		anglee2=0;
	}
}
void leftright(int key, int x, int y)
{
	if(key==GLUT_KEY_UP)
	{
		if(ton==1)
		{
			tcami++;
			if(tcami>10)
				tcami=10;
		}
	}
	else if(key==GLUT_KEY_DOWN)
	{
		
		if(ton==1)
		{
			tcami--;
			if(tcami<1)
				tcami=1;
		}

	}
	else if(key==GLUT_KEY_LEFT)
	{


		if(ton==1)
		{
			tcamj++;
			if(tcamj>10)
				tcamj=10;
		}

	}
	else if(key==GLUT_KEY_RIGHT)
	{
		if(ton==1)
		{
			tcamj--;
			if(tcamj<1)
				tcamj=1;
		}
	}



}
void handleKeypress(unsigned char key, int x, int y) {
	//if(outgr==1)
	//	return;
	 if(key=='n' && (interface==1 || interface==33))
	{
		interface=-1;
	}
		if(key==27)
			exit(0);
	
	if(flagchu==0 && interface==0)
	{
	if(key=='a')
	{
		angle1=angle1+90;
		if(angle1>360)
			angle1=0;
	}
	else if(key=='d')
	{
		angle1=angle1-90;
		if(angle1<0)
			angle1=angle1+360;
	}
	else if(key=='f')
	{
		if(fpson==1)
			fpson=2;
		else
			fpson=1;
	}
	else if(key=='h')
	{
		if(hon==1)
			hon=0;
		else
			hon=1;
	
	}
	else if(key=='l')
	{
		if(spotl==1)
			spotl=0;
		else
			spotl=1;
	}

	else if(key=='j')
	{
		jmpflag=1;
		oriyr=yr;
	}
	
	else if(key=='t')
	{
		if(ton==0)
			ton=1;
		else
			ton=0;
	}
	else if(key=='o')
	{
		fpson=0;
	}
	else if(key=='s')
	{
		sp=2.5;
		xprev=xr;zprev=zr;
		if(angle1>=0 && angle1 <=90)
		{
			zr-=(2.5*cos(DEG2RAD(angle1)));
			xr-=(2.5*sin(DEG2RAD(angle1)));
		}
		else if(angle1>90 && angle1 <=180)
		{
			zr+=(2.5*(-cos(DEG2RAD(angle1))));
			xr-=(2.5*sin(DEG2RAD(angle1)));
		}
		if(angle1>180 && angle1 <=270)
		{
			zr+=(2.5*(-cos(DEG2RAD(angle1))));
			xr+=(2.5*(-sin(DEG2RAD(angle1))));
		}
		if(angle1>270 && angle1 <=360)
		{
			zr-=(2.5*cos(DEG2RAD(angle1)));
			xr+=(2.5*(-sin(DEG2RAD(angle1))));
		}
		if(left1==1)
			left1=0;
		else
			left1=1;
	}

	else if(key=='w')
	{
			inerflag=1;
	//		if(inerflag==1)
			//printf("aaya on acceleration with %f\n",sp);
			if(sp<=5)
			{
				
			sp=sp+0.5;
			xprev=xr;zprev=zr;
			if(angle1>=0 && angle1 <=90)
			{
				zr+=(sp*cos(DEG2RAD(angle1)));
				xr+=(sp*sin(DEG2RAD(angle1)));
			}
			else if(angle1>90 && angle1 <=180)
			{
				zr-=(sp*(-cos(DEG2RAD(angle1))));
				xr+=(sp*sin(DEG2RAD(angle1)));
			}
			if(angle1>180 && angle1 <=270)
			{
				zr-=(sp*(-cos(DEG2RAD(angle1))));
				xr-=(sp*(-sin(DEG2RAD(angle1))));
			}
			if(angle1>270 && angle1 <=360)
			{
				zr+=(sp*cos(DEG2RAD(angle1)));
				xr-=(sp*(-sin(DEG2RAD(angle1))));
			}

			if(left1==1)
				left1=0;
			else
				left1=1;
			}
	
	}
	
}

}
void handleKeypressUp(unsigned char key, int x, int y) {
	if(key=='w')
	{
		inerflag=0;
		//sp=2.5;
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE); //Automatically normalize normals
	//	glShadeModel(GL_SMOOTH); //Enable smooth shading
	Image* image = loadBMP("water2.bmp");
	_textureId = loadTexture(image);
	delete image;
	Image* image2 = loadBMP("grass.bmp");
	_textureId2 = loadTexture(image2);
	delete image2;
	Image* image3 = loadBMP("dirt.bmp");
	_textureId3 = loadTexture(image3);
	delete image3;
	Image* image4 = loadBMP("skull.bmp");
	_textureId4 = loadTexture(image4);
	delete image4;
	Image* image5 = loadBMP("start.bmp");
	_textureId5 = loadTexture(image5);
	delete image5;
	Image* image6 = loadBMP("end.bmp");
	_textureId6 = loadTexture(image6);
	delete image6;
	Image* image7 = loadBMP("coinn.bmp");
	_textureId7 = loadTexture(image7);
	delete image7;
	Image* image8 = loadBMP("hii.bmp");
	_textureId8 = loadTexture(image8);
	delete image8;

Image* image9 = loadBMP("hii2.bmp");
	_textureId9 = loadTexture(image9);
	delete image9;

Image* image10 = loadBMP("fire.bmp");
	_textureId10 = loadTexture(image10);
	delete image10;

}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = -70.0f;

//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(0.439216f, 0.858824f, 0.576471f, 0.0f);
	//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
glColor3f(0,1,0);	
if(interface!=1 && interface!=33)
{
if(stage==0)
{
	drawStrokeText("Stage1",30,15,-70);
}
else if(stage==1)
{
	drawStrokeText("Stage2",30,15,-70);
}
else if(stage==2)
{
	drawStrokeText("Stage3",30,15,-70);
}
else if(stage==3)
{
	drawStrokeText("Stage4",30,15,-70);
}
}
char str3[100];
sprintf(str3,"%d",score);
drawStrokeText("Score:",-45,15,-70);
if(interface==1)
{
	glPushMatrix();
	glTranslatef(-10, 5, -25);
	//printf("///////herhe////\n");
	glRotatef(45,0.0f,1.0f,0.0f);		
	drawrobo();
	glPopMatrix();
	char str3[100];
	sprintf(str3,"%d",score);
	glColor3f(0,1,0);
	//glTranslatef(0, 0, -25);

	//	glRotatef(90,1.0f,0.0f,0.0f);		
	//glRotatef(90,1.0f,1.0f,0.0f);		

	drawStrokeText("Your Score is :",-25,15,-80);
	drawStrokeText(str3,10,15,-80);
	drawStrokeText("Press n for next level:",-25,5,-80);
}
else if(interface==22)
{
	glPushMatrix();
	glTranslatef(-10, 5, -25);
	//printf("///////herhe////\n");
	glRotatef(45,0.0f,1.0f,0.0f);		
	drawrobo();
	glPopMatrix();
	char str3[100];
	sprintf(str3,"%d",score);
	glColor3f(0,1,0);
	//glTranslatef(0, 0, -25);

	//	glRotatef(90,1.0f,0.0f,0.0f);		
	//glRotatef(90,1.0f,1.0f,0.0f);		
	drawStrokeText("GAME OVER",-25,15,-80);
	drawStrokeText("Your Score is :",-25,5,-80);
	drawStrokeText(str3,10,5,-80);
	drawStrokeText("Press ESC for exit:",-20,-5,-80);

}
else if(interface==33)
{
	glPushMatrix();
	glTranslatef(-10, 5, -25);
	//printf("///////herhe////\n");
	glRotatef(45,0.0f,1.0f,0.0f);		
	drawrobo();
	glPopMatrix();
	char str3[100];
	sprintf(str3,"%d",score);
	glColor3f(0,1,0);
	//glTranslatef(0, 0, -25);

	//	glRotatef(90,1.0f,0.0f,0.0f);		
	//glRotatef(90,1.0f,1.0f,0.0f);		
	drawStrokeText("WELCOME",-25,15,-80);
	//drawStrokeText("Your Score is :",-25,5,-80);
	drawStrokeText(str3,10,5,-80);
	drawStrokeText("Press n to start:",-20,-5,-80);


}
drawStrokeText(str3,-33,15,-70);
		//Camera Variables setting
	//glPushMatrix()

	//glRotatef(_angle, 0.0f, 1.0f, 0.0f);
	glColor3f(0.33f, 0.33f, 0.33f);
	if(fpson==1)
	{
		xc=xr;yc=yr+3.5f;zc=zr;
		xla=xc;yla=2;zla=zc+20.0f;
		if(angle1>=0 && angle1 <=90)
		{
			zla=zc+(20*cos(DEG2RAD(angle1)));
			xla=xc+(20*sin(DEG2RAD(angle1)));
		}
		else if(angle1>90 && angle1 <=180)
		{
			zla=zc-(20*(-cos(DEG2RAD(angle1))));
			xla=xr+(20*sin(DEG2RAD(angle1)));
		}
		if(angle1>180 && angle1 <=270)
		{
			zla=zc-(20*(-cos(DEG2RAD(angle1))));
			xla=xr-(20*(-sin(DEG2RAD(angle1))));
		}
		if(angle1>270 && angle1 <=360)
		{
			zla=zc+(20*cos(DEG2RAD(angle1)));
			xla=xr-(20*(-sin(DEG2RAD(angle1))));
		}

		//printf("YR:%f\n",yr);
	}
	else if(fpson==2)
	{	

		xc=xr;yc=yr+10.0f;zc=zr-25.0f;
		xla=xc;yla=5;zla=zc+20.0f;

		if(angle1>=0 && angle1 <=90)
		{
			zc=zr-(20*cos(DEG2RAD(angle1)));
			xc=xr-(20*sin(DEG2RAD(angle1)));
			zla=zc+(20*cos(DEG2RAD(angle1)));
			xla=xc+(20*sin(DEG2RAD(angle1)));
		}
		else if(angle1>90 && angle1 <=180)
		{
			zc=zr+(20*(-cos(DEG2RAD(angle1))));
			xc=xr-(20*sin(DEG2RAD(angle1)));
			zla=zc-(20*(-cos(DEG2RAD(angle1))));
			xla=xc+(20*sin(DEG2RAD(angle1)));
		}
		if(angle1>180 && angle1 <=270)
		{
			zc=zr+(20*(-cos(DEG2RAD(angle1))));
			xc=xr+(20*(-sin(DEG2RAD(angle1))));
			zla=zc-(20*(-cos(DEG2RAD(angle1))));
			xla=xc-(20*(-sin(DEG2RAD(angle1))));
		}
		if(angle1>270 && angle1 <=360)
		{
			zc=zr-(20*cos(DEG2RAD(angle1)));
			xc=xr+(20*(-sin(DEG2RAD(angle1))));
			zla=zc+(20*cos(DEG2RAD(angle1)));
			xla=xc-(20*(-sin(DEG2RAD(angle1))));
		}

	}
	else if(ton==1)
	{
		yc=(a[tcami][tcamj].y+6.0f);
		xc=(a[tcami][tcamj].xstart+a[tcami][tcamj].xend)/2;
		zc=(a[tcami][tcamj].zstart+a[tcami][tcamj].zend)/2;
		yla=yr;
		zla=zr;
		xla=xr;
		
	}
	else
	{
		xc=0;yc=60;
		//zc=105;
		if(interface==0)
			zc=105;
		else if(interface==33)
			zc=225;
		else
			zc=variable;
		if(hon==1)
		{
			//if(old_x<=15)
			//	xc=(2*old_x);
			//else
			//	xc=30-old_x;
			xc=(sau*sin(DEG2RAD(3*old_x)));
			zc=(sau*cos(DEG2RAD(3*old_x)));
			//printf("diff_y:%f\n",diff_y);
			yc=(60-old_y);
			//zc=(125-(old_x*3));yc=(60+pos_Y);
			xla=0;yla=15.5+diff_y;zla=0;
			
		}
		else
		{
			xla=0;yla=15.5;zla=40;
		}
	}

	gluLookAt(xc,yc,zc,xla,yla,zla,0,9,0);	
	//glTranslatef(0.0f, 0.0f, -20.0f);
	if(spotl==1)
	{
		
	GLfloat lightColor0[] = {0.8f,0.8f,0,1.0f};

	GLfloat lightPos0[] = {xr,yr+34.0f,zr,1.0f};

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0);

	GLfloat spot_direction[] = {0.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);

	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightColor0);

	glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);
	glDisable(GL_LIGHT1);
	}
	else{

	GLfloat lightColor1[] = {0.8f,0.8f,0,1.0f};

	GLfloat lightPos1[] = {xr,40.0f,zr,1.0f};
	GLfloat lightColor0[] = {0.8f,0.8f,0,1.0f};

	GLfloat lightPos0[] = {xr,yr+34.0f,zr,1.0f};

	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightColor0);

	glLightfv(GL_LIGHT0,GL_POSITION,lightPos0);

	
//	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);

//	GLfloat spot_direction1[] = {0.0, -1.0, 0.0 };

//	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glEnable(GL_LIGHT1);
	}

	//Add ambient light
/*	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	//Add positioned light
	GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
	GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	//Add directed light
	GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
	//Coming from the direction (-1, 0.5, 0.5)
	GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
//*/
			//printf("Lookfrom Y:%f\n",yc);
	
	
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1000.0f, -10.0f,-1000.0f);
	glTexCoord2f(100.0f, 0.0f);
	glVertex3f(1000.0f, -10.0f, -1000.0f);
	glTexCoord2f(100.0f, 100.0f);
	glVertex3f(1000.0f, -10.0f, 1000.0f);
	glTexCoord2f(0.0f, 100.0f);
	glVertex3f(-1000.0f, -10.0f, 1000.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);
/*
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId4);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1000.0f, 100.0f,-90.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(1000.0f, 100.0f, -90.0f);
	glTexCoord2f(2.0f, 2.0f);
	glVertex3f(1000.0f, -15.0f, -90.0f);
	glTexCoord2f(0.0f, 2.0f);
	glVertex3f(-1000.0f, -15.0f, -90.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);	
	glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId4);

	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-100.0f, 100.0f,-91.0f);
	glTexCoord2f(2.0f, 0.0f);
	glVertex3f(-100.0f, -15.0f, -91.0f);
	glTexCoord2f(2.0f, 2.0f);
	glVertex3f(-100.0f, -15.0f, 91.0f);
	glTexCoord2f(0.0f, 2.0f);
	glVertex3f(-100.0f, 100.0f, 91.0f);

	glEnd();
	glDisable(GL_TEXTURE_2D);	

*/


	
	//spot(xr,yr+10,zr,xr,yr,zr);
	a[1][1].drop=0;
	a[1][1].tramp=0;
	a[10][10].drop=0;
	a[10][10].tramp=0;
	a[3][3].drop=0;
	a[3][3].up=0;
	a[3][3].tramp=0;
	a[4][7].drop=0;
	a[4][7].tramp=0;
	a[4][7].up=0;
	a[5][5].drop=0;
	a[5][5].tramp=0;
	a[5][5].up=0;
	a[6][9].drop=0;
	a[6][9].up=0;
	a[6][9].tramp=0;
	zz=40;
	xx=-40;
	glColor3f(1.0f,1.0f,1.0f);
	//glTranslatef(xx,-10.0f,zz);
	//int r;
	for(i=1;i<=10;i++)
	{
		for(j=1;j<=10;j++)
		{
			///if(a[i][j].prob==1)
			//{
				
			
			glPushMatrix();
			if((i+j)%2==0)
				glColor3f(0.0f,0.0f,1.0f);
			else
				glColor3f(1.0f,1.0f,1.0f);
			glTranslatef(xx,0.0f,zz);
			//if(a[i][j].up==1)
			//{
			//	glPushMatrix();
				glTranslatef(0.0f,a[i][j].y,0.0f);
			//}
			if(a[i][j].drop==1)	
				glColor3f(0.80f, 0.498039f, 0.196078f);
				
			//glutSolidCube(10.0f);
			glColor3f(1.0f,1.0f,1.0f);
			glEnable(GL_TEXTURE_2D);
			if(a[i][j].drop==1)
				glBindTexture(GL_TEXTURE_2D, _textureId4);
			else if(a[i][j].fire==1)
				glBindTexture(GL_TEXTURE_2D,_textureId10);
			else if(a[i][j].tramp==1)
				glBindTexture(GL_TEXTURE_2D, _textureId7);
			else if(i==1 && j==1)
				glBindTexture(GL_TEXTURE_2D, _textureId5);
			else if((i==3 && j==3) || i==4 && j==7)
				glBindTexture(GL_TEXTURE_2D, _textureId8);
			else if((i==5 && j==5 || i==6 && j==9) && flagchu!=0 )
				glBindTexture(GL_TEXTURE_2D, _textureId9);
			else if(i==10 && j==10)	
				glBindTexture(GL_TEXTURE_2D, _textureId6);
			else
				glBindTexture(GL_TEXTURE_2D, _textureId2);

			//Bottom
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-5.0f, 5.1f,-5.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(5.0f, 5.1f, -5.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(5.0f, 5.1f, 5.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-5.0f, 5.1f, 5.0f);

			glEnd();
			glDisable(GL_TEXTURE_2D);	
			
			glColor3f(1.0f,1.0f,1.0f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId3);

			//Bottom
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-5.0f, 5.0f,5.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(5.0f, 5.0f, 5.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(5.0f, -5.0f, 5.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-5.0f, -5.0f, 5.0f);
			glEnd();


			glDisable(GL_TEXTURE_2D);	
			glColor3f(1.0f,1.0f,1.0f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId3);

			//Bottom
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-5.0f, 5.0f,-5.0f);
			glTexCoord2f(100.0f, 0.0f);
			glVertex3f(5.0f, 5.0f, -5.0f);
			glTexCoord2f(100.0f, 100.0f);
			glVertex3f(5.0f, -5.0f, -5.0f);
			glTexCoord2f(0.0f, 100.0f);
			glVertex3f(-5.0f, -5.0f, -5.0f);
			glEnd();


			glDisable(GL_TEXTURE_2D);	
			glColor3f(1.0f,1.0f,1.0f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId3);

			//Bottom
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-5.0f, 5.0f,-5.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-5.0f, 5.0f, 5.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-5.0f, -5.0f, 5.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-5.0f, -5.0f, -5.0f);
			glEnd();
			glColor3f(1.0f,1.0f,1.0f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId3);

			//Bottom
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


			glBegin(GL_QUADS);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(5.0f, 5.0f,-5.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(5.0f, 5.0f, 5.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(5.0f, -5.0f, 5.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(5.0f, -5.0f, -5.0f);
			glEnd();



			glDisable(GL_TEXTURE_2D);	
			
			//if(a[i][j].up==1)
			//	glPopMatrix();
			glTranslatef(0.0f,7.5f,0.0f);
			glRotatef(anglo,0,1,0);
			if(a[i][j].coin==1)
			{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, _textureId7);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			 gluQuadricTexture(gluNewQuadric(),1);
			gluDisk(gluNewQuadric(),0,2.0f,40,40);
			}
			glPopMatrix();
			//}
			
			
			a[i][j].xstart=xx-5;
			a[i][j].xend=xx+5;
			a[i][j].zstart=zz-5;
			a[i][j].zend=zz+5;
			xx=xx+10;
		}
		xx=-40;
		zz=zz-10;
	}

	glColor3f(0.33f, 0.33f, 0.33f);
	if(flagchu==1)
	{
		yr=yr-0.02;
		//printf("chu\n");

		glutTimerFunc(80, updatex, 0);
		//	exit(1);
	}
	//glRotatef(angle1,0.0f,1.0f,0.0f);
	earth();
	glTranslatef(xr, yr, zr);
	glRotatef(angle1,0.0f,1.0f,0.0f);		
	//glutStrokeString(GLUT_STROKE_ROMAN, "K.1");
	//glPushMatrix();
	//glTranslatef(0.0f, 0.0f, zr);
	checkpos();
	drawrobo();
	if(zr >=45.0f || xr <=-45.0f || xr >=55.0f || zr <=-55.0f)
	{
		glutTimerFunc(50, updateout, 0);
		//	exit(1);
	}
	//glPopMatrix();
	//glPushMatrix();
	glutSwapBuffers();
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(20, update, 0);
}
void changeflag(int value) {
	if(colflag==0)
	{
		colflag=1;
	}
	else if(colflag==1)
		colflag=0;
	glutTimerFunc(550, changeflag, 0);
}
void jump(int value) {
	checkpos();
	if(interface==-1)
		variable--;
	if(variable<=105 && interface==-1)
		interface=0;
			
	if(interface==11)
		variable++;
	if(variable>=225 && interface==11)
	{
		interface=1;
		if(stage==4)
			interface=22;
	}
	anglo=anglo-5;
	if(anglo<=-360)
		anglo=0;
	if(yr<=-15.0f)
	{
		printf("SUNKK\n");
		exit(1);
	}
	if(jmpflag==1 && downflag==0)
	{
		yr=yr+0.2f;
		cnt++;
		//if(yr>=a[presbi][presbj].y+15.5f+10.0f)
		//	downflag=1;
		if(cnt>=60)
		{
			downflag=1;
			cnt=0;
		}
	}
	else if(jmpflag==1 && downflag==1)
	{
		yr=yr-0.2f;
		if(yr<=a[presbi][presbj].y+15.5f)

		{
			
			//printf("present i:%d and j:%d\n",presbi,presbj);
			yr=a[presbi][presbj].y+15.5f;
			downflag=0;
			jmpflag=0;
			if(a[presbi][presbj].tramp==1)
			{
				printf("aaya\n");
				jmpflag=1;
				downflag=0;
			}
		}
	}
	/*if(outgr==1)
	{
		yr=yr-0.3f;
		if(yr<=-12.0f)
		{
			printf("Out of Grid\n");
			exit(0);
		}
	}*/
	glutTimerFunc(10,jump,0);
}
void blockups(int value) {
	for(i=1;i<11;i++)
	{
		for(j=1;j<11;j++)
		{
			if(a[i][j].up==1 && a[i][j].down==0)
			{
				a[i][j].y=a[i][j].y+0.2f;
				if(a[i][j].y>=20.0f)
				{
					a[i][j].down=1;
				}
			}
			else if(a[i][j].up==1 && a[i][j].down==1)
			{
				a[i][j].y=a[i][j].y-0.2f;
				if(a[i][j].y<=0.0f)
				{
					a[i][j].down=0;
					//.a[i][j].y=0.0f;
				}
			}
		}
	
	}
	float kk1=15.5f+a[presbi][presbj].y;
	//printf("kk1 is %f 0and yr is%f\n",kk1,yr);
	if(a[presbi][presbj].drop==1 && yr==kk1)
	{
		a[presbi][presbj].y-=0.2f;
		//printf("hhhhhhhherre\n");
	}
	else if(a[presbi][presbj].drop==1)
	{
		//printf("$$$$yr:: %f and $$$$a.y: %f and drop: %d\n",yr,15.5f+a[presbi][presbj].y,a[presbi][presbj].drop);
	
	}
	glutTimerFunc(30,blockups,0);
}
void updateout (int value)
{
	yr=yr-0.2f;
	if(yr <= 0.0f)	
	{
		exit(1);
	}
	glutTimerFunc(50, updateout, 0);
}
void inertia(int value)
{
	
	//printf("InerFlag:%d\n",inerflag);
		if(sp > 3.0 && inerflag==0)
		{
		sp=sp-0.5;

		//printf("aaya on deceleration with %f\n",sp);
		if(angle1>=0 && angle1 <=90)
		{
			zr+=(sp*cos(DEG2RAD(angle1)));
			xr+=(sp*sin(DEG2RAD(angle1)));
		}
		else if(angle1>90 && angle1 <=180)
		{
			zr-=(sp*(-cos(DEG2RAD(angle1))));
			xr+=(sp*sin(DEG2RAD(angle1)));
		}
		if(angle1>180 && angle1 <=270)
		{
			zr-=(sp*(-cos(DEG2RAD(angle1))));
			xr-=(sp*(-sin(DEG2RAD(angle1))));
		}
		if(angle1>270 && angle1 <=360)
		{
			zr+=(sp*cos(DEG2RAD(angle1)));
			xr-=(sp*(-sin(DEG2RAD(angle1))));
		}

		if(left1==1)
			left1=0;
		else
			left1=1;

		}
		else if(sp<=3.0 && inerflag==0)
		{
			sp=2.5;
			//printf("aaya in saadhi with %f\n",sp);
		}
		
	glutTimerFunc(80,inertia,0);
}
void checkpos()
{
	if(flagchu==0)
	{
		//		return;
		mflag=0;
		for(i=1;i<11;i++)
		{
			for(j=1;j<11;j++)
			{
				if(xr<=a[i][j].xend && xr>=a[i][j].xstart && zr<=a[i][j].zend && zr>=a[i][j].zstart)
				{
					//if(jmpflag==0)
					//{

					if(a[presbi][presbj].coin==1&& (xr<=a[presbi][presbj].xend-1.5 && xr>=a[presbi][presbj].xstart+1.5 && zr<=a[presbi][presbj].zend-1.5 && zr>=a[presbi][presbj].zstart+1.5 ))
					{
						score=score+10;
						a[presbi][presbj].coin=0;
					}
					if( presbi==i && presbj==j && jmpflag==0)
					{
						yr=a[i][j].y+15.5f;
						//printf("aaya\n");
					}
					else if( (yr-a[i][j].y<=12.0f)&&(a[i][j].up==1 || a[presbi][presbj].drop==1) && (presbi!=i || presbj!=j))
					{
						//	printf("presbi:%d i:%d presbj:%d j:%d\n",presbi,i,presbj,j);
						xr=xprev;
						zr=zprev;
					}
					else if(jmpflag==0){
						if(a[presbi][presbj].y==a[i][j].y)
							yr=a[i][j].y+15.5f;
						else
						{
							jmpflag=1;
							downflag=1;
						}
					}
					if(i==10 && j==10)
					{
						printf("WONN\n");
						stage++;
						interface=11;
						//if(stage==4)
						//	interface=22;
						//score=0;
						usleep(800000);
						if(stage!=4)
							initializer(stage);
						else
						{
							printf("Thanks For Playing.. Final Score : %d\n",score);
							//exit(1);
							zr=40.0f,xr=-40.0f,yr=15.5f;
							printf("//////came here/////\n");
						}
						return;
						//exit(0);
					}
					if((i==3 && j==3) || (i==4 && j==7))
					{
						flagchu=1;
					}
					if(a[i][j].fire==1)
					{
						if(yr<=15.5)
							exit(1);
					}

					//}
					presbi=i;
					presbj=j;
					//if(a[i][j].y>=12.0f)
					//printf("presbi:%d i:%d presbj:%d j:%d\n",presbi,i,presbj,j);
					//	exit(0);
					//printf("aaya for x:%d and z:%d\n",i,j);
					//	if(a[i][j].prob==0)
					//		exit(0);
					//	else
					//		return;
					return;
				}
			}
		}
	}
	if(mflag==0)
	{
		printf("Fell Down");
		outgr=1;
		//exit(0);
	}
}

void drawrobo() {
	//Head
	
	glColor3f(0.33f, 0.33f, 0.33f);
	glutSolidCube(2.0f);
	glPushMatrix();
	glTranslatef(-0.5f,0.5f,1.0f);
	if(colflag==0)
		glColor3f(0.0f,1.0f,0.0f);
	else	
		glColor3f(0.0f,0.0f,1.0f);
	glutSolidSphere(0.3f,100,100);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5f,0.5f,1.0f);
	if(colflag==0)
		glColor3f(0.0f,1.0f,0.0f);
	else
		glColor3f(0.0f,0.0f,1.0f);
	glutSolidSphere(0.3f,100,100);
	glPopMatrix();
	glTranslatef(0.0f,-1.0f,0.0f);	

	glColor3f(0.0f,1.0f,0.0f);
	//Neck
	glutSolidCube(1.0f);
	glTranslatef(0.0f,-0.5f,0.0f);
	glutSolidCube(1.0f);
	glTranslatef(0.0f,-2.25f,0.0f);	
	glColor3f(1.0f,0.0f,0.0f);

	//Torso
	glutSolidCube(3.5f);
	//Arms
	glPushMatrix();
	glTranslatef(-2.0f,1.0f,0.0f);
	glutSolidCube(1.0f);
	glPushMatrix();
	glTranslatef(-0.5f,0.0f,0.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(-0.4f,-0.5f,0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(left1==1)
		glRotatef(40.0f,1.0f,0.0f,0.0f);
	else
		glRotatef(-40.0f,1.0f,0.0f,0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	gluCylinder(gluNewQuadric(),0.35f,0.35f,2.5f,40,40);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.0f,1.0f,0.0f);
	glColor3f(1.0f,0.0f,0.0f);
	glutSolidCube(1.0f);
	glPushMatrix();
	glTranslatef(0.5f,0.0f,0.0f);
	glutSolidCube(1.0f);
	glPopMatrix();
	glTranslatef(0.4f,-0.5f,0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	if(left1==1)
		glRotatef(-40.0f,1.0f,0.0f,0.0f);
	else
		glRotatef(40.0f,1.0f,0.0f,0.0f);
	glColor3f(0.0f,1.0f,0.0f);
	gluCylinder(gluNewQuadric(),0.35f,0.35f,2.5f,40,40);
	glPopMatrix();
	glTranslatef(0.0f,-1.75f,0.0f);	
	glColor3f(0.33f, 0.33f, 0.33f);

	//Chaddi

	//glutSolidCube(3.0f);
	glPushMatrix();
	glTranslatef(-0.875f,0.0f,0.0f);
	if(left1==1)
	{
		glRotatef(50.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(gluNewQuadric(),0.875f,0.8f,2.5f,40,40);
		glTranslatef(0.0f,0.0f,2.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(gluNewQuadric(),0.5f,0.35f,3.0f,40,40);
	}
	else
	{
		glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(0.33f, 0.33f, 0.33f);
		gluCylinder(gluNewQuadric(),0.875f,0.8f,2.0f,40,40);
		glTranslatef(0.0f,0.0f,2.0f);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(gluNewQuadric(),0.5f,0.35f,3.0f,40,40);

	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.875f,0.0f,0.0f);
	if(left1==1)
	{
		glRotatef(100.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(0.33f, 0.33f, 0.33f);
		gluCylinder(gluNewQuadric(),0.875f,0.8f,2.0f,40,40);
		glTranslatef(0.0f,0.0f,2.0f);
		glColor3f(0.0f,1.0f,0.0f);
		gluCylinder(gluNewQuadric(),0.5f,0.35f,3.0f,40,40);
	}
	else
	{
		glRotatef(50.0f, 1.0f, 0.0f, 0.0f);
		glColor3f(0.33f, 0.33f, 0.33f);
		gluCylinder(gluNewQuadric(),0.875f,0.8f,2.5f,40,40);
		glTranslatef(0.0f,0.0f,2.0f);
		glColor3f(0.0f,1.0f,0.0f);
		glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(gluNewQuadric(),0.5f,0.35f,3.0f,40,40);
	}
	glPopMatrix();


	glColor3f(0.0f,1.0f,0.0f);
}
void mouse(int x,int y)
{
	//diff_x=old_x-((x-545)/10);
	old_x=(x-545)/10;
	old_y=(y-300)/10;
	//printf("aaya\n");
	//if(mflag==0)
		iold_y=old_y;
	//printf("iold:%f\n",iold_y);
	
}
void mwheel(int button,int state,int x,int y)
{
	if(hon==1)
	{
		if(button==3)
		{
		//	printf("In\n");
			sau=sau-2;
		}
		else if(button==4)
		{
			//printf("Out\n");
			sau=sau+2;
		}
	}
}

void GetOGLPos(int x, int y)
{
	/*GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
*/
	//printf("iold:%f\n",iold_y);
	//mflag=1;
	pos_X=(x-545)/10;
	pos_Y=(y-300)/10;
	diff_y=(iold_y-pos_Y);
	//iold_y=pos_Y;
	//printf("iold:%f\n",iold_y);
	//pos_Z=posZ/10;
	//printf("Mouse_X:%f Mouse_Y:%f\n",pos_X,pos_Y);
	
	//return CVector3(posX, posY, posZ);
}
int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	int w = glutGet(GLUT_SCREEN_WIDTH);
	int h = glutGet(GLUT_SCREEN_HEIGHT);
	srand(time(0));	
	initializer(stage);

	glutInitWindowSize((w*4)/5, (h*4)/5);

	//Create the window
	glutCreateWindow("Game");
	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(handleKeypressUp);
	glutSpecialFunc(leftright);
	glutReshapeFunc(handleResize);
	glutPassiveMotionFunc(mouse);
	glutMotionFunc(GetOGLPos);
	glutMouseFunc(mwheel);
	glutTimerFunc(20, update, 0); //Add a timer
	glutTimerFunc(250,changeflag, 0);	
	glutTimerFunc(20,jump, 0);	
	glutTimerFunc(20,blockups, 0);	
	glutTimerFunc(120,inertia,0);
	glutMainLoop();
	return 0;
}


void updatey(int value)
{
	if(flagchu==2)
	{
		yr=yr+0.5;
		//printf("hmm2\n");
		if(yr>=15.5)
		{
			yr=15.5;
			flagchu=0;
			//glutTimerFunc(80, updatey, 0);

			//exit(1);
		}

		glutTimerFunc(80, updatey, 0);
	}
}
void updatex(int value)
{
	if(flagchu==1)

	{yr=yr-0.05;
		printf("hmm1\n");
		if(yr <= 0)
		{
			flagchu=2;
			xr=xr+20.0;
			zr=zr-20.0;
			glutTimerFunc(80, updatey, 0);

			//exit(1);
		}

		glutTimerFunc(80, updatex, 0);
	}
}
void initializer(int stage)
{
	if(stage==0)
	{
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				a[i][j].y=0;
				if(rand()%3==0)
					a[i][j].prob=0;
				else
					a[i][j].prob=0;
			}
		}
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				if(rand()%5!=0)
				{
					a[i][j].prob=0;
					a[i][j].up=0;

					if(rand()%8!=0)
						a[i][j].drop=0;
					else
						a[i][j].drop=0;

				}
				else
				{
					a[i][j].prob=0;
					a[i][j].up=0;
					a[i][j].drop=0;
				}
			}
		}
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				if(rand()%4==0)
					a[i][j].coin=1;
				else
					a[i][j].coin=0;
				if(a[i][j].up==0 && a[i][j].drop==0)
				{
					if(rand()%8==0)
						a[i][j].tramp=1;
				//	else if(rand()%5==1)
				//		a[i][j].fire=1;

				}
			}
		}
	}
	if(stage==1)
	{

		printf("Ghusaaa\n");
		zr=40.0f,xr=-40.0f,yr=15.5f;
		
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				a[i][j].y=0;
				a[i][j].tramp=0;
				if(rand()%3==0)
					a[i][j].prob=1;
				else
					a[i][j].prob=0;
			}
		}
		//a[2][1].tramp=1;
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				if(rand()%5!=0)
				{
					a[i][j].prob=1;
					a[i][j].up=0;

					if(rand()%8!=0)
						a[i][j].drop=0;
					else
						a[i][j].drop=0;

				}
				else
				{
					a[i][j].prob=0;
					a[i][j].up=1;
					a[i][j].drop=0;
				}
			}
		}
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				if(rand()%8==0)
					a[i][j].coin=1;
				else
					a[i][j].coin=0;
				if(a[i][j].up==0 && a[i][j].drop==0)
				{
					if(rand()%8==0)
						a[i][j].tramp=1;
				//	else if(rand()%5==1)
				//		a[i][j].fire=1;

				}
			}
		}

	}	if(stage==2)
	{

		printf("Ghusaaa\n");
		zr=40.0f,xr=-40.0f,yr=15.5f;
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				a[i][j].y=0;
				if(rand()%3==0)
					a[i][j].prob=1;
				else
					a[i][j].prob=0;
			}
		}
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				if(rand()%5!=0)
				{
					a[i][j].prob=1;
					a[i][j].up=0;

					if(rand()%8!=0)
						a[i][j].drop=0;
					else
						a[i][j].drop=1;

				}
				else
				{
					a[i][j].prob=0;
					a[i][j].up=0;
					a[i][j].drop=0;
				}
			}
		}
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				if(rand()%6==0)
					a[i][j].coin=1;
				else
					a[i][j].coin=0;
				if(a[i][j].up==0 && a[i][j].drop==0)
				{
					if(rand()%8==0)
						a[i][j].tramp=1;
					else if(rand()%8==1)
						a[i][j].fire=1;

				}
			}
		}

	}
	if(stage==3)
	{

		printf("Ghusaaa\n");
		zr=40.0f,xr=-40.0f,yr=15.5f;
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				a[i][j].y=0;
				if(rand()%3==0)
					a[i][j].prob=1;
				else
					a[i][j].prob=0;
			}
		}
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				if(rand()%5!=0)
				{
					a[i][j].prob=1;
					a[i][j].up=0;

					if(rand()%8!=0)
						a[i][j].drop=0;
					else
						a[i][j].drop=1;

				}
				else
				{
					a[i][j].prob=0;
					a[i][j].up=1;
					a[i][j].drop=0;
				}
			}
		}
		for(i=1;i<=100;i++)
		{
			for(j=1;j<=100;j++)
			{
				if(rand()%8==0)
					a[i][j].coin=1;
				else
					a[i][j].coin=0;
				if(a[i][j].up==0 && a[i][j].drop==0)
				{
					if(rand()%8==0)
						a[i][j].tramp=1;
					else if(rand()%8==1)
						a[i][j].fire=1;

				}
			
			}
		}

	}

}

void drawStrokeText(char*string,int x12,int y12,int z12)
{
	char *c;
	glPushMatrix();
	glTranslatef(x12, y12+8,z12);
	glRotatef(180,1,0,0);
	glScalef(0.03f,-0.03f,z12);
	for (c=string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	}
	glPopMatrix();
}



