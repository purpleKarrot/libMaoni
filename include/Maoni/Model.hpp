/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
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

#ifndef MAONI_MODEL_HPP
#define MAONI_MODEL_HPP

#include <Maoni/Vertex.hpp>
#include <vector>

class Model
{
public:
	Model()
	{
		reset();
	}

	//! clear the model
	void clear();

	//! reset the model to the Stanford Bunny
	void reset();

	//!
	bool empty() const;

	std::vector<Vertex> const& get_vertices() const
	{
		return vertices;
	}

	std::vector<std::size_t> const& get_indices() const
	{
		return indices;
	}

	//! draw the model
	void draw() const;

	void reserve_vertices(std::size_t number);

	void reserve_triangles(std::size_t number);

	void add_vertex(Vertex const& vertex);

	void add_triangle(std::size_t a, std::size_t b, std::size_t c);

	void fix_scale();

	//! Calculate the face or vertex normals of the current vertex data.
	void calculate_normals();

private:
	Model(Model const&);
	void operator=(Model const&);

	std::vector<Vertex> vertices;
	std::vector<std::size_t> indices;
};

#endif /* MAONI_MODEL_HPP */
