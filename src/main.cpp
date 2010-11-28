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

#include <Maoni.hpp>
#include <boost/config.hpp>

BOOST_SYMBOL_IMPORT int maoni_main(int argc, char* argv[],
		RenderAlgorithm* algorithm_factory_stack,
		MeshLoader* mesh_loader_stack);

int main(int argc, char* argv[])
{
	return maoni_main(argc, argv, RenderAlgorithm::stack, MeshLoader::stack);
}
