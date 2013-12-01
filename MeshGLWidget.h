/** File:		MeshGLWidget.h
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


#ifndef __MESHGLWIDGET_H__
#define __MESHGLWIDGET_H__

#include <QtOpenGL/QGLWidget>
#include <GL\glut.h>
#include <QtGui>
#include "MeshGLEnv.h"
#include "MeshLoader.h"

#define NUM_BUFFERS 2
#define VERTEX 0
#define NORMAL 1

class MeshGLWidget : public QGLWidget
{
	Q_OBJECT

private:
	MeshGLEnv env;
	MeshLoader *loader;
	int mode;
	int shade;
	int color;

public:
	MeshGLWidget(QWidget *parent = 0);
	void reset();
	void drawMesh(char *fileName, int fileSize);
	void setMode(int _mode);
	void setShade(int _shade);
	void setColor(int _color);

protected:
	void initializeGL();
	void resizeGL(int width, int height);
	void paintGL();
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void wheelEvent(QWheelEvent *e);

private:
	void initEnv();
	void setupDraw();
};

#endif
