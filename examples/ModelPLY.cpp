/*
 * libMaoni - common viewing framework
 *
 * Copyright (C) 2011 Daniel Pfeifer
 * Visualization and Multimedia Lab, University of Zurich
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Maoni/glew.h>
#include "ModelPLY.hpp"
#include "ply_io.h"
#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <vector>

struct Vertex
{
	float x, y, z;
	float nx, ny, nz;
	unsigned char r, g, b;
};

void readVertices(PlyFile* file, std::size_t nVertices, GLuint buffer)
{
	PlyProperty vertexProps[] =
	{
		{ (char*) "x", Float32, Float32, offsetof(Vertex, x), 0, 0, 0, 0 },
		{ (char*) "y", Float32, Float32, offsetof(Vertex, y), 0, 0, 0, 0 },
		{ (char*) "z", Float32, Float32, offsetof(Vertex, z), 0, 0, 0, 0 },
		{ (char*) "red", Uint8, Uint8, offsetof(Vertex, r), 0, 0, 0, 0 },
		{ (char*) "green", Uint8, Uint8, offsetof(Vertex, g), 0, 0, 0, 0 },
		{ (char*) "blue", Uint8, Uint8, offsetof(Vertex, b), 0, 0, 0, 0 }
	};

	for (int i = 0; i < 3; ++i)
		setup_property_ply(file, &vertexProps[i]);

	std::vector<Vertex> vertices(nVertices);

	for (std::vector<Vertex>::iterator v = vertices.begin(); v != vertices.end(); ++v)
		get_element_ply(file, static_cast<void*> (&*v));

	for (std::vector<Vertex>::iterator v = vertices.begin(); v != vertices.end(); ++v)
		std::cout << v->x << " " << v->y << " " << v->z << std::endl;

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void readTriangles(PlyFile* file, std::size_t nFaces, GLuint buffer)
{
	struct Face
	{
		unsigned char size;
		unsigned int* vertices;
	} face;

	PlyProperty faceProps[] =
	{
		{ (char*) "vertex_indices", Uint32, Uint32, offsetof(Face, vertices), 1, Uint8, Uint8, offsetof(Face, size) }
	};

	ply_get_property(file, (char*) "face", &faceProps[0]);

	std::vector<unsigned int> faces(nFaces * 3);

	for (int i = 0, k = 0; i < nFaces; ++i)
	{
		ply_get_element(file, static_cast<void*> (&face));
		if(face.size != 3)
		{
			free(face.vertices);
			throw std::runtime_error("Encountered a face which does not have three vertices.");
		}

		faces[k++] = face.vertices[0];
		faces[k++] = face.vertices[1];
		faces[k++] = face.vertices[2];

		free(face.vertices);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * faces.size(), &faces[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ModelPLY::ModelPLY(const char* filename) :
		Path(filename), vbuffer(0), ibuffer(0)
{
}

ModelPLY::~ModelPLY()
{
}

void do_fclose(FILE* file)
{
	if (file)
		fclose(file);
}

void ModelPLY::read_file() const
{
	glGenBuffers(1, &vbuffer);
	glGenBuffers(1, &ibuffer);

	boost::shared_ptr<FILE> file(fopen(path().c_str(), "r"), do_fclose);
	if (!file)
		throw std::runtime_error("unabple to open " + path());

	boost::shared_ptr<PlyFile> ply(read_ply(file.get()), free_ply);
	if (!ply)
		throw std::runtime_error("unabple to load " + path());

	for (int i = 0; i < ply->num_elem_types; ++i)
	{
		int elem_count;
		char* elem_name = setup_element_read_ply(ply.get(), i, &elem_count);

	    if (equal_strings((char*) "vertex", elem_name))
		{
			readVertices(ply.get(), elem_count, vbuffer);
		}
		else if (equal_strings((char*) "face", elem_name))
		{
			faces = elem_count;
			readTriangles(ply.get(), elem_count, ibuffer);
		}
	}
}

void ModelPLY::draw(int myrank, int ranks) const
{
	if (!vbuffer)
		read_file();

	glColor3f(1.f, 0.5f, 0.5f);

	glBindBuffer(GL_ARRAY_BUFFER, vbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuffer);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, x));

//	glEnableClientState(GL_NORMAL_ARRAY);
//	glNormalPointer(GL_FLOAT, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, nx));
//
//	glEnableClientState(GL_COLOR_ARRAY);
//	glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(Vertex), (const GLvoid*) offsetof(Vertex, r));

	glDrawRangeElements(GL_TRIANGLES, 0, faces - 1, faces, GL_UNSIGNED_INT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
//	glDisableClientState(GL_NORMAL_ARRAY);
//	glDisableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ModelPLY::reset()
{
	glDeleteBuffers(1, &vbuffer);
	vbuffer = 0;

	glDeleteBuffers(1, &ibuffer);
	ibuffer = 0;
}

const char* const ModelPLY::filter() const
{
	return "PLY files (*.ply)";
}
