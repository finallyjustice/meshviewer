/** File:		MeshLoader.h
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


#ifndef __MESHLOADER_H__
#define __MESHLOADER_H__

#include <list>

typedef unsigned int uint;

class MeshLoader
{
private:
	bool mesh_status;

	char *file_name;
	int file_size;

	uint num_vert;
	uint num_face;
	uint num_norm;

	float *vert;
	float *vNorm;
	uint *face;
	float *norm;

public:
	MeshLoader();
	~MeshLoader();
	void setFileName(char *_file_name, int _file_size);
	void loadMesh();

	bool getMeshStatus();
	uint getNumVert();
	uint getNumFace();
	float* getVert();
	float* getNorm();
	uint* getFace();

private:
	void genMeshA();
	void genMeshB();

};

#endif
