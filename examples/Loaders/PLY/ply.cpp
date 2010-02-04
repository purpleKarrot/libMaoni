/*
 * ply.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: dpfeifer
 */

#include <VMMView/MeshLoader.hpp>
#include "plyfile.h"
#include <stdint.h>

typedef vmml::vector<3, std::size_t> Triangle;
static bool _invertFaces = false;

//static void useInvertedFaces() {
//	_invertFaces = true;
//}

/*  Read the vertex and (if available/wanted) color data from the open file.  */
static void readVertices(PlyFile* file, const int nVertices, Model &mesh) {
	// temporary vertex structure for ply loading
	struct _Vertex {
		float x;
		float y;
		float z;
		unsigned char r;
		unsigned char g;
		unsigned char b;
	} vertex;

	PlyProperty
			vertexProps[] = { { "x", PLY_FLOAT, PLY_FLOAT,
					offsetof( _Vertex, x ), 0, 0, 0, 0 }, { "y", PLY_FLOAT,
					PLY_FLOAT, offsetof( _Vertex, y ), 0, 0, 0, 0 }, { "z",
					PLY_FLOAT, PLY_FLOAT, offsetof( _Vertex, z ), 0, 0, 0, 0 },
					{ "red", PLY_UCHAR, PLY_UCHAR, offsetof( _Vertex, r ), 0,
							0, 0, 0 }, { "green", PLY_UCHAR, PLY_UCHAR,
							offsetof( _Vertex, g ), 0, 0, 0, 0 }, { "blue",
							PLY_UCHAR, PLY_UCHAR, offsetof( _Vertex, b ), 0, 0,
							0, 0 } };

	// use all 6 properties when reading colors, only the first 3 otherwise
	for (int i = 0; i < 6; ++i)
		ply_get_property(file, "vertex", &vertexProps[i]);

	mesh.vertices.clear();
	mesh.vertices.reserve(nVertices);

	// read in the vertices
	for (int i = 0; i < nVertices; ++i) {
		ply_get_element(file, static_cast<void*> (&vertex));
		mesh.vertices.push_back(Vertex(Vector3(vertex.x, vertex.y, vertex.z),
				Vector3(0.f), Vector4(vertex.r / 255.f, vertex.g / 255.f,
						vertex.b / 255.f, 0), Vector2(0.f)));
	}
}

/*  Read the index data from the open file.  */
static void readTriangles(PlyFile* file, const int nFaces, Model &mesh) {
	// temporary face structure for ply loading
	struct _Face {
		unsigned char nVertices;
		int* vertices;
	} face;

	PlyProperty faceProps[] = { { "vertex_indices", PLY_INT, PLY_INT,
			offsetof( _Face, vertices ), 1, PLY_UCHAR, PLY_UCHAR,
			offsetof( _Face, nVertices ) } };

	ply_get_property(file, "face", &faceProps[0]);

	mesh.triangles.clear();
	mesh.triangles.reserve(nFaces);

	// read in the faces, asserting that they are only triangles
	uint8_t ind1 = _invertFaces ? 2 : 0;
	uint8_t ind3 = _invertFaces ? 0 : 2;
	for (int i = 0; i < nFaces; ++i) {
		ply_get_element(file, static_cast<void*> (&face));
		BOOST_ASSERT(face.vertices != 0);
		if (face.nVertices != 3) {
			free(face.vertices);
			throw std::runtime_error("Error reading PLY file. Encountered a "
				"face which does not have three vertices.");
		}
		mesh.triangles.push_back(Triangle(face.vertices[ind1],
				face.vertices[1], face.vertices[ind3]));

		// free the memory that was allocated by ply_get_element
		free(face.vertices);
	}
}

MESH_LOADER(ply, Stanford Triangle Format)
{
	model.vertices.clear();
	model.triangles.clear();

	int nPlyElems;
	char** elemNames;
	int fileType;
	float version;
	bool result = false;

	PlyFile* file = ply_open_for_reading(const_cast<char*> (filename),
			&nPlyElems, &elemNames, &fileType, &version);
	if (!file) {
		std::cerr << "Unable to open PLY file " << filename << " for reading."
				<< std::endl;
		return false;
	}
	BOOST_ASSERT( elemNames != 0 );

#ifndef NDEBUG
	std::clog << filename << ": " << nPlyElems << " elements, file type = "
			<< fileType << ", version = " << version << std::endl;
#endif

	for (int i = 0; i < nPlyElems; ++i) {
		int nElems;
		int nProps;

		PlyProperty** props = ply_get_element_description(file, elemNames[i],
				&nElems, &nProps);
		BOOST_ASSERT( props != 0 );

#ifndef NDEBUG
		std::clog << "element " << i << ": name = " << elemNames[i] << ", "
				<< nProps << " properties, " << nElems << " elements"
				<< std::endl;
		for (int j = 0; j < nProps; ++j) {
			std::clog << "element " << i << ", property " << j << ": "
					<< "name = " << props[j]->name << std::endl;
		}
#endif

		if (equal_strings(elemNames[i], "vertex")) {
			bool hasColors = false;
			// determine if the file stores vertex colors
			for (int j = 0; j < nProps; ++j)
				if (equal_strings(props[j]->name, "red"))
					hasColors = true;

			readVertices(file, nElems, model);
			BOOST_ASSERT( model.vertices.size() == static_cast< size_t >( nElems ) );
		} else if (equal_strings(elemNames[i], "face"))
			try {
				readTriangles(file, nElems, model);
				BOOST_ASSERT( model.triangles.size() == static_cast< size_t >( nElems ) );
				result = true;
			} catch (std::exception& e) {
				std::cerr << "Unable to read PLY file, an exception occured:  "
						<< e.what() << std::endl;
				// stop for loop by setting the loop variable to break condition
				// this way resources still get released even on error cases
				i = nPlyElems;
			}

		// free the memory that was allocated by ply_get_element_description
		for (int j = 0; j < nProps; ++j)
			free(props[j]);
		free(props);
	}

	ply_close(file);

	// free the memory that was allocated by ply_open_for_reading
	for (int i = 0; i < nPlyElems; ++i)
		free(elemNames[i]);
	free(elemNames);

	model.calculateNormals();
	model.scale(2.0);

	return true;
}
