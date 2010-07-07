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

#include "FrameData.hpp"
#include <boost/mpi/collectives.hpp>
#include "../Common/serialize.hpp"
#include <GL/ice-t_mpi.h>
#include <GL/gl.h>

FrameDataIceT::FrameDataIceT(RenderAlgorithm* algorithm_stack,
		MeshLoader* mesh_loader_stack) :
	FrameData(algorithm_stack, mesh_loader_stack), //
			world(), tiles(world.size())
{
	mwidth = 640;
	mheight = 640;

	change = 0;
	change ^= TILES_CHANGED;

	int rows = sqrt(tiles.size());
	for (std::size_t i = 0; i < tiles.size(); ++i)
	{
		int col = i / rows;
		int row = i % rows;

		tiles[i].visible = true; //i == 0;

		tiles[i].x = col * 640;
		tiles[i].y = row * 480;
	}
}

FrameDataIceT::~FrameDataIceT()
{
}

void FrameDataIceT::animate()
{
	double matrix[16];

	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	broadcast(world, matrix, 0);
	glMatrixMode( GL_PROJECTION);
	glLoadMatrixd(matrix);

	glGetDoublev(GL_MODELVIEW_MATRIX, matrix);
	broadcast(world, matrix, 0);
	glMatrixMode( GL_MODELVIEW);
	glLoadMatrixd(matrix);

	if ((change & TILES_CHANGED) == TILES_CHANGED)
	{
		broadcast(world, tiles, 0);

		icetResetTiles();
		for (std::size_t i = 0; i < tiles.size(); ++i)
		{
			Tile& tile = tiles[i];

			//if (tile.visible)
			//{
			broadcast(world, tile.sx, i);
			broadcast(world, tile.sy, i);
			icetAddTile(tile.x, tile.y, tile.sx, tile.sy, i);
			//}

			if (i == world.rank())
			{
				icetBoundingBoxf( //
						tile.min.data[0], tile.max.data[0], //
						tile.min.data[1], tile.max.data[1], //
						tile.min.data[2], tile.max.data[2]);
			}
		}

		icetGetIntegerv(ICET_TILE_MAX_WIDTH, &mwidth);
		icetGetIntegerv(ICET_TILE_MAX_HEIGHT, &mheight);
	}

	//TODO: if (model_changed)
	//	{
	//		broadcast(world, model_name, 0);
	//		if (!master())
	//			load_model(model_name);
	//	}

	if ((change & RALGO_CHANGED) == RALGO_CHANGED)
	{
		broadcast(world, ralgo_name, 0);
		if (!master())
			set_render_algorithm(ralgo_name);
	}

	if ((change & RENDERER_CHANGED) == RENDERER_CHANGED)
	{
		if (renderer)
			broadcast(world, *renderer, 0);
	}
}

void FrameDataIceT::resize(int w, int h)
{
	FrameData::resize(w, h);
}
