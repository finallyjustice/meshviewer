/** File:		MainWindow.cpp
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


#include "MainWindow.h"

MainWindow::MainWindow()
{
	createActions();
	createMenus();

	canvas=new MeshGLWidget;
	canvas->setMinimumSize(600, 600);
	setCentralWidget(canvas);
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu("File");
	fileMenu->addAction(openAction);
	fileMenu->addAction(exitAction);

	modeMenu = menuBar()->addMenu("Mode");
	modeMenu->addAction(modePointAction);
	modeMenu->addAction(modeLineAction);
	modeMenu->addAction(modeFillAction);

	shadeMenu = menuBar()->addMenu("Shade");
	shadeMenu->addAction(shadeSmoothAction);
	shadeMenu->addAction(shadeFlatAction);

	colorMenu = menuBar()->addMenu("Color");
	colorMenu->addAction(redAction);
	colorMenu->addAction(greenAction);
	colorMenu->addAction(blueAction);
	colorMenu->addAction(yellowAction);
	colorMenu->addAction(purpleAction);
	colorMenu->addAction(whiteAction);

	helpMenu = menuBar()->addMenu("About");
	helpMenu->addAction(aboutAction);
}

void MainWindow::createActions()
{
	openAction = new QAction("Open", this);
	connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
	exitAction = new QAction("Exit", this);
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	signalModeMapper = new QSignalMapper(this);
	modePointAction = new QAction("Point", this);
	modeLineAction = new QAction("Line", this);
	modeFillAction = new QAction("Fill", this);
	modePointAction->setCheckable(true);
	modeLineAction->setCheckable(true);
	modeFillAction->setCheckable(true);
	connect(modePointAction, SIGNAL(triggered()), signalModeMapper, SLOT(map()));
	connect(modeLineAction, SIGNAL(triggered()), signalModeMapper, SLOT(map()));
	connect(modeFillAction, SIGNAL(triggered()), signalModeMapper, SLOT(map()));
	signalModeMapper->setMapping(modePointAction, 0);
	signalModeMapper->setMapping(modeLineAction, 1);
	signalModeMapper->setMapping(modeFillAction, 2);
	connect(signalModeMapper, SIGNAL(mapped(int)), this, SLOT(setMeshMode(int)));
	modeGroup = new QActionGroup(this);
	modeGroup->addAction(modePointAction);
	modeGroup->addAction(modeLineAction);
	modeGroup->addAction(modeFillAction);
	modeFillAction->setChecked(true);

	signalShadeMapper = new QSignalMapper(this);
	shadeSmoothAction = new QAction("Smooth", this);
	shadeFlatAction = new QAction("Flat", this);
	shadeSmoothAction->setCheckable(true);
	shadeFlatAction->setCheckable(true);
	connect(shadeSmoothAction, SIGNAL(triggered()), signalShadeMapper, SLOT(map()));
	connect(shadeFlatAction, SIGNAL(triggered()), signalShadeMapper, SLOT(map()));
	signalShadeMapper->setMapping(shadeSmoothAction, 0);
	signalShadeMapper->setMapping(shadeFlatAction, 1);
	connect(signalShadeMapper, SIGNAL(mapped(int)), this, SLOT(setMeshShade(int)));
	shadeGroup = new QActionGroup(this);
	shadeGroup->addAction(shadeSmoothAction);
	shadeGroup->addAction(shadeFlatAction);
	shadeSmoothAction->setChecked(true);

	signalColorMapper = new QSignalMapper(this);
	redAction = new QAction("Red", this);
	greenAction = new QAction("Green", this);
	blueAction = new QAction("Blue", this);
	yellowAction = new QAction("Yellow", this);
	purpleAction = new QAction("Purple", this);
	whiteAction = new QAction("White", this);
	redAction->setCheckable(true);
	greenAction->setCheckable(true);
	blueAction->setCheckable(true);
	yellowAction->setCheckable(true);
	purpleAction->setCheckable(true);
	whiteAction->setCheckable(true);
	connect(redAction, SIGNAL(triggered()), signalColorMapper, SLOT(map()));
	connect(greenAction, SIGNAL(triggered()), signalColorMapper, SLOT(map()));
	connect(blueAction, SIGNAL(triggered()), signalColorMapper, SLOT(map()));
	connect(yellowAction, SIGNAL(triggered()), signalColorMapper, SLOT(map()));
	connect(purpleAction, SIGNAL(triggered()), signalColorMapper, SLOT(map()));
	connect(whiteAction, SIGNAL(triggered()), signalColorMapper, SLOT(map()));
	signalColorMapper->setMapping(redAction, 0);
	signalColorMapper->setMapping(greenAction, 1);
	signalColorMapper->setMapping(blueAction, 2);
	signalColorMapper->setMapping(yellowAction, 3);
	signalColorMapper->setMapping(purpleAction, 4);
	signalColorMapper->setMapping(whiteAction, 5);
	connect(signalColorMapper, SIGNAL(mapped(int)), this, SLOT(setMeshColor(int)));
	colorGroup = new QActionGroup(this);
	colorGroup->addAction(redAction);
	colorGroup->addAction(greenAction);
	colorGroup->addAction(blueAction);
	colorGroup->addAction(yellowAction);
	colorGroup->addAction(purpleAction);
	colorGroup->addAction(whiteAction);
	greenAction->setChecked(true);

	aboutAction = new QAction("About", this);
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}

//SLOT
void MainWindow::openFile()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open Obj File", ".", "obj files (*.obj)");
	QByteArray filename_byte = filename.toLatin1();
	char *fileName = filename_byte.data();
	int fileSize=filename_byte.size();
	
	this->setWindowTitle(filename);

	canvas->drawMesh(fileName, fileSize);
}

//SLOT
void MainWindow::about()
{
	QMessageBox::about(this, "About Software", 
						"<h3>MeshViewer</h3>"
						"<p>The viewer supports obj file, with or without normal information (vn).</p>"
						"<p>Contact: Dongli ZHANG, <a href=\"mailto:dozhang@cs.sunysb.edu\">dozhang@cs.sunysb.edu</a></p>");
}

//SLOT
void MainWindow::setMeshMode(int mode)
{
	canvas->setMode(mode);
}

//SLOT
void MainWindow::setMeshShade(int shade)
{
	canvas->setShade(shade);
}

//SLOT
void MainWindow::setMeshColor(int color)
{
	canvas->setColor(color);
}
