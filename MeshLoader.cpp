/** File:		MeshLoader.cpp
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

#include <string.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include "MeshLoader.h"

#define MAX_FILE_PATH 255
#define DIM 3

using namespace std;

MeshLoader::MeshLoader()
{
	mesh_status=false;

	file_name = (char *)malloc(MAX_FILE_PATH * sizeof(char));
	file_size=0;

	num_vert=0;
	num_face=0;
	num_norm=0;

	vert  = NULL;
	vNorm = NULL;
	face  = NULL;
	norm  = NULL;
}

MeshLoader::~MeshLoader()
{
	if(num_vert != 0) free(vert);
	if(num_norm != 0) free(vNorm);
	if(num_face != 0) free(face);
	if(num_face != 0) free(norm);

	free(file_name);
}

void MeshLoader::setFileName(char *_file_name, int _file_size)
{
	file_size = _file_size;
	memset(file_name, '\0', MAX_FILE_PATH * sizeof(char));
	memcpy(file_name, _file_name, file_size*sizeof(char));
}

void MeshLoader::loadMesh()
{
	if(num_vert != 0) free(vert);
	if(num_norm != 0) free(vNorm);
	if(num_face != 0) free(face);
	if(num_face != 0) free(norm);

	vert = NULL;
	vNorm = NULL;
	face = NULL;
	norm = NULL;

	num_vert=0;
	num_face=0;
	num_norm=0;

	ifstream fline(file_name);

	string line_data;
	while(fline >> line_data)
	{
		switch(*line_data.c_str())
		{
		case 'v':
			{
				if(*(line_data.c_str()+1) == NULL)
				{
					num_vert++;
				}

				if(*(line_data.c_str()+1) == 'n')
				{
					num_norm++;
				}
			}
		break;
		case 'f':
			{
				num_face++;
			}
			break;
		}
	}

	fline.close();
	fline.clear();

	vert  = (float *)malloc(sizeof(float) * num_vert*DIM);
	vNorm = (float *)malloc(sizeof(float) * num_norm*DIM);
	face  = (uint *)malloc(sizeof(uint) * num_face*DIM);
	norm  = (float *)malloc(sizeof(float) * num_vert*DIM);

	if(num_norm == 0)
	{
		genMeshB();
	}
	else
	{
		genMeshA();
	}

	if(num_norm != 0)
	{
		free(vNorm);
	}

	num_norm=0;

	mesh_status = true;
}

//public getter
bool MeshLoader::getMeshStatus()
{
	return this->mesh_status;
}

//public getter
uint MeshLoader::getNumVert()
{
	return this->num_vert;
}


//public getter
uint MeshLoader::getNumFace()
{
	return this->num_face;
}

//public getter
float* MeshLoader::getVert()
{
	return this->vert;
}

//public getter
uint* MeshLoader::getFace()
{
	return this->face;
}

//public getter
float* MeshLoader::getNorm()
{
	return this->norm;
}

//private - obj with normal
void MeshLoader::genMeshA()
{
	ifstream file(file_name);
	string s;

	char c;
	float x, y, z;
	uint v1, v2, v3;
	uint n1, n2, n3;

	uint lenV=0;
	uint lenN=0;
	uint lenF=0;
	
	while(file >> s)
	{
		switch(*s.c_str())
		{
			case 'v':
			{
				if(*(s.c_str()+1) == NULL)
				{
					file >> x >> y >> z;

					vert[lenV]=x;
					lenV++;

					vert[lenV]=y;
					lenV++;

					vert[lenV]=z;
					lenV++;
				}

				if(*(s.c_str()+1) == 'n')
				{
					file >> x >> y >> z;

					vNorm[lenN]=x;
					lenN++;

					vNorm[lenN]=y;
					lenN++;

					vNorm[lenN]=z;
					lenN++;
				}
			}
			break;

			case 'f':
			{
				file >> v1;
				file >> c;
				file >> c;
				file >> n1;

				file >> v2;
				file >> c;
				file >> c;
				file >> n2;

				file >> v3;
				file >> c;
				file >> c;
				file >> n3;

				face[lenF]=v1-1;
				norm[(v1-1)*3+0]=vNorm[(n1-1)*3+0];
				norm[(v1-1)*3+1]=vNorm[(n1-1)*3+1];
				norm[(v1-1)*3+2]=vNorm[(n1-1)*3+2];
				lenF++;

				face[lenF]=v2-1;
				norm[(v2-1)*3+0]=vNorm[(n2-1)*3+0];
				norm[(v2-1)*3+1]=vNorm[(n2-1)*3+1];
				norm[(v2-1)*3+2]=vNorm[(n2-1)*3+2];
				lenF++;

				face[lenF]=v3-1;
				norm[(v3-1)*3+0]=vNorm[(n3-1)*3+0];
				norm[(v3-1)*3+1]=vNorm[(n3-1)*3+1];
				norm[(v3-1)*3+2]=vNorm[(n3-1)*3+2];
				lenF++;
			}
			break;
		}
	}

	file.close();
	file.clear();
}

//private mesh without normal row
void MeshLoader::genMeshB()
{
	ifstream file(file_name);
	string s;

	char c;
	float x, y, z;
	uint v1, v2, v3;
	uint n1, n2, n3;

	uint lenV=0;
	uint lenN=0;
	uint lenF=0;
	
	while(file >> s)
	{
		switch(*s.c_str())
		{
			case 'v':
			{
				if(*(s.c_str()+1) == NULL)
				{
					file >> x >> y >> z;

					vert[lenV]=x;
					lenV++;

					vert[lenV]=y;
					lenV++;

					vert[lenV]=z;
					lenV++;
				}
			}
			break;

			case 'f':
			{
				file >> v1 >> v2 >> v3;

				face[lenF]=v1-1;
				lenF++;

				face[lenF]=v2-1;
				lenF++;

				face[lenF]=v3-1;
				lenF++;
			}
			break;
		}
	}

	file.close();
	file.clear();

	float vec1[3];
	float vec2[3];
	float vec_norm[3];

	float *temp=(float *)malloc(sizeof(float)*num_vert);
	memset(temp, 0, sizeof(float)*num_vert);
	memset(norm, 0, sizeof(float)*num_vert*DIM);

	for(uint i=0; i<num_face; i++)
	{
		vec1[0]=vert[face[i*DIM+1]*DIM+0]-vert[face[i*DIM+0]*DIM+0]; 
		vec1[1]=vert[face[i*DIM+1]*DIM+1]-vert[face[i*DIM+0]*DIM+1];
		vec1[2]=vert[face[i*DIM+1]*DIM+2]-vert[face[i*DIM+0]*DIM+2];

		vec2[0]=vert[face[i*DIM+2]*DIM+0]-vert[face[i*DIM+0]*DIM+0];
		vec2[1]=vert[face[i*DIM+2]*DIM+1]-vert[face[i*DIM+0]*DIM+1];
		vec2[2]=vert[face[i*DIM+2]*DIM+2]-vert[face[i*DIM+0]*DIM+2];

		vec_norm[0]=vec1[1]*vec2[2]-vec1[2]*vec2[1];
		vec_norm[1]=vec1[2]*vec2[0]-vec1[0]*vec2[2];
		vec_norm[2]=vec1[0]*vec2[1]-vec1[1]*vec2[0];

		temp[face[i*DIM+0]]++;
		norm[face[i*DIM+0]*DIM+0] += vec_norm[0];
		norm[face[i*DIM+0]*DIM+1] += vec_norm[1];
		norm[face[i*DIM+0]*DIM+2] += vec_norm[2];

		temp[face[i*DIM+1]]++;
		norm[face[i*DIM+1]*DIM+0] += vec_norm[0];
		norm[face[i*DIM+1]*DIM+1] += vec_norm[1];
		norm[face[i*DIM+1]*DIM+2] += vec_norm[2];

		temp[face[i*DIM+2]]++;
		norm[face[i*DIM+2]*DIM+0] += vec_norm[0];
		norm[face[i*DIM+2]*DIM+1] += vec_norm[1];
		norm[face[i*DIM+2]*DIM+2] += vec_norm[2];
	}

	for(uint i=0; i<num_vert; i++)
	{
		norm[i*DIM+0] = norm[i*DIM+0] / temp[i];
		norm[i*DIM+1] = norm[i*DIM+1] / temp[i];
		norm[i*DIM+2] = norm[i*DIM+2] / temp[i];

		float d=sqrt(norm[i*DIM+0] * norm[i*DIM+0] 
					+norm[i*DIM+1] * norm[i*DIM+1] 
					+norm[i*DIM+2] * norm[i*DIM+2]);

		norm[i*DIM+0] = norm[i*DIM+0] / d;
		norm[i*DIM+1] = norm[i*DIM+1] / d;
		norm[i*DIM+2] = norm[i*DIM+2] / d;


	}

	free(temp);
}
