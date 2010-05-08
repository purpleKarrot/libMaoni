/*
 * stl.cpp
 *
 *  Created on: Jul 30, 2009
 *      Author: aishutter
 */

#include <Maoni/MeshLoader.hpp>
#include <stdexcept>
#include <iostream>

#include "stla_io.h"

MESH_LOADER(stl, StereoLithography)
{
	model.clear();

	// check if correct ascii stl file
	if (stla_check(filename)) {
		std::cout << "  The file \"" << filename
				<< "\" seems to be a legal ASCII STL file." << std::endl;
	} else {
		throw std::runtime_error("The file does NOT seem to be a legal ASCII STL file.");
	}

	// print file stats
	int face_num;
	int node_num;
	int solid_num;
	int text_num;

	stla_size(filename, &solid_num, &node_num, &face_num, &text_num);
	stla_size_print(filename, solid_num, node_num, face_num, text_num);

	// read file into mesh
	bool error;
	int *face_node;
	double *face_normal;
	//int ierror;
	double *node_xyz;

	face_node = new int[3 * face_num];
	face_normal = new double[3 * face_num];
	node_xyz = new double[3 * node_num];

	error = stla_read(filename, node_num, face_num, node_xyz, face_node,
			face_normal);

	if (error)
		throw std::runtime_error("An error occured while reading stl file.");

	// copy vertices
	for (int i = 0; i < node_num; i++)
	{
		model.add_vertex(Vertex(Vector3(node_xyz[i * 3], node_xyz[i * 3 + 1],
				node_xyz[i * 3 + 2]), Vector3(face_normal[i * 3], face_normal[i
				* 3 + 1], face_normal[i * 3 + 2]), Color(), Vector2()));
	}

	// copy nodes to triangles
	for (int i = 0; i < face_num; i++)
	{
		model.add_triangle(face_node[i * 3], face_node[i * 3 + 1], face_node[i
				* 3 + 2]);
	}

//	stla_face_node_print(face_num, face_node);
//	stla_face_normal_print(face_num, face_normal);
//	stla_node_xyz_print ( node_num, node_xyz );

	delete[] face_node;
	delete[] face_normal;
	delete[] node_xyz;

	model.calculate_normals();
	model.fix_scale();
}
