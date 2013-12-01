/** File:		MeshGLWidget.cpp
 ** Author:		Dongli Zhang
 ** Contact:	dongli.zhang0129@gmail.com
 **
 ** Copyright (C) Dongli Zhang 2013
 **
 ** This program is free software;  you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY;  without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 ** the GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program;  if not, write to the Free Software 
 ** Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "MeshGLWidget.h"

//constructor
MeshGLWidget::MeshGLWidget(QWidget *parent)
	: QGLWidget(parent)
{
	initEnv();
	setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
	setFocusPolicy(Qt::StrongFocus);

	loader = new MeshLoader();
	mode = 2;
	shade = 0;
	color = 1;
}

//public
void MeshGLWidget::reset()
{
	initEnv();
	setupDraw();
	updateGL();
}

//public
void MeshGLWidget::drawMesh(char *fileName, int fileSize)
{
	loader->setFileName(fileName, fileSize);
	loader->loadMesh();
	initEnv();

	if(loader->getMeshStatus() == true)
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);

		float *vertex=loader->getVert();
		float *normal=loader->getNorm();

		glNormalPointer(GL_FLOAT, 0, normal);
		glVertexPointer(3, GL_FLOAT, 0, vertex);
	}

	setupDraw();
	updateGL();
}

//public
void MeshGLWidget::setMode(int _mode)
{
	this->mode = _mode;
	setupDraw();
	updateGL();
}

//public 
void MeshGLWidget::setShade(int _shade)
{
	this->shade = _shade;
	setupDraw();
	updateGL();
}

//public
void MeshGLWidget::setColor(int _color)
{
	this->color = _color;
	setupDraw();
	updateGL();
}

//protected
void MeshGLWidget::initializeGL()
{
	initEnv();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

//protected
void MeshGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (float)width/height, 0.001, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);

	//set lighting param
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, env.ambientLight);

    glLightfv(GL_LIGHT0,GL_DIFFUSE, env.ambientLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR, env.specular);
    glLightfv(GL_LIGHT0,GL_POSITION, env.lightPos);
	
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
}

//protected
void MeshGLWidget::paintGL()
{
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

    glPushMatrix();

	if(env.buttonState == 1)
	{
		env.xRot += (env.xRotLength-env.xRot)*0.1f;
		env.yRot += (env.yRotLength-env.yRot)*0.1f;
	}

	glTranslatef(env.xTrans, env.yTrans, env.zTrans);
    glRotatef(env.xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(env.yRot, 0.0f, 1.0f, 0.0f);

	glPointSize(2.0f);

	if(loader->getMeshStatus() == true)
	{
		uint* face = (uint *)(loader->getFace());
		glDrawElements(GL_TRIANGLES, loader->getNumFace()*3, GL_UNSIGNED_INT, face);
	}

	glPopMatrix();
}

//protected
void MeshGLWidget::mousePressEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
	{
		int x = e->x();
		int y = e->y();

		env.buttonState = 1;

		env.ox = x; 
		env.oy = y;
	}
}

//protected
void MeshGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
	if(e->button() == Qt::LeftButton)
	{
		int x = e->x();
		int y = e->y();

		env.buttonState = 0;

		env.ox = x; 
		env.oy = y;
	}
}

//protected
void MeshGLWidget::mouseMoveEvent(QMouseEvent *e)
{
	if(e->buttons() & Qt::LeftButton)
	{
		int x = e->x();
		int y = e->y();

		float dx, dy;
		dx = (float)(x - env.ox);
		dy = (float)(y - env.oy);

		if (env.buttonState == 1) 
		{
			env.xRotLength += dy / 5.0f;
			env.yRotLength += dx / 5.0f;
		}

		env.ox = x; 
		env.oy = y;

		updateGL();
	}
}

//protexted
void MeshGLWidget::wheelEvent(QWheelEvent *e)
{
	int numDegrees = e->delta() / 8;
	int numSteps = numDegrees / 15;

	env.zTrans += 2.0f * numSteps;

	updateGL();

}

//protected
void MeshGLWidget::keyPressEvent(QKeyEvent *e)
{
	switch(e->key())
	{
	case Qt::Key_A:
		env.xTrans -= 2.0f;
		break;

	case Qt::Key_D:
		env.xTrans += 2.0f;
		break;

	case Qt::Key_S:
		env.yTrans -= 2.0f;
		break;

	case Qt::Key_W:
		env.yTrans += 2.0f;
		break;

	case Qt::Key_Up:
		env.zTrans += 2.0f;
		break;

	case Qt::Key_Down:
		env.zTrans -= 2.0f;
		break;
	}

	updateGL();
}

//private
void MeshGLWidget::initEnv()
{
	env.xRot = 0.0f;
	env.yRot = 0.0f;
	env.xTrans = 0.0f;
	env.yTrans = 0.0f;
	env.zTrans = -32.0;
	env.xRotLength = 0.0f;
	env.yRotLength = 0.0f;

	env.lightPos[0]=0.0f;
	env.lightPos[1]=0.0f;
	env.lightPos[2]=20.0f;
	env.lightPos[3]=0.0f;

	env.specular[0]=1.0f;
	env.specular[1]=1.0f;
	env.specular[2]=1.0f;
	env.specular[3]=1.0f;
	
	env.specref[0]=1.0f;
	env.specref[1]=1.0f;
	env.specref[2]=1.0f;
	env.specref[3]=1.0f;

	env.ambientLight[0]=0.5f;
	env.ambientLight[1]=0.5f;
	env.ambientLight[2]=0.5f;
	env.ambientLight[3]=1.0f;

	env.spotDir[0]=0.0f;
	env.spotDir[1]=0.0f;
	env.spotDir[2]=-1.0f;
	env.spotDir[3]=0.0f;
}

void MeshGLWidget::setupDraw()
{
	if(color == 0)	glColor3f(0.9f, 0.1f, 0.1f);
	if(color == 1)	glColor3f(0.1f, 0.9f, 0.1f);
	if(color == 2)	glColor3f(0.1f, 0.1f, 0.9f);
	if(color == 3)	glColor3f(0.9f, 0.9f, 0.1f);
	if(color == 4)	glColor3f(0.9f, 0.1f, 0.9f);
	if(color == 5)	glColor3f(0.8f, 0.8f, 0.8f);

	if(shade == 0)	glShadeModel(GL_SMOOTH);
	if(shade == 1)	glShadeModel(GL_FLAT);

	if(mode == 0)	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	if(mode == 1)	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if(mode == 2)	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
