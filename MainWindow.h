/** File:		MainWindow.h	
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

#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QtGui>
#include "MeshGLWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	MeshGLWidget *canvas;
	QMenu *fileMenu;
	QMenu *modeMenu;
	QMenu *shadeMenu;
	QMenu *colorMenu;
	QMenu *helpMenu;

	QAction *openAction;
	QAction *exitAction;
	QAction *aboutAction;

	QAction *modePointAction;
	QAction *modeLineAction;
	QAction *modeFillAction;
	QActionGroup *modeGroup;

	QAction *shadeSmoothAction;
	QAction *shadeFlatAction;
	QActionGroup *shadeGroup;

	QAction *redAction;
	QAction *greenAction;
	QAction *blueAction;
	QAction *yellowAction;
	QAction *purpleAction;
	QAction *whiteAction;
	QActionGroup *colorGroup;

	QSignalMapper* signalModeMapper; 
	QSignalMapper* signalShadeMapper;
	QSignalMapper* signalColorMapper;

public:
	MainWindow();

private:
	void createMenus();
	void createActions();

private slots:
	void openFile();
	void about();
	void setMeshMode(int mode);
	void setMeshShade(int shade);
	void setMeshColor(int color);
};

#endif
