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

#ifndef FRAME_DATA_EQ_HPP
#define FRAME_DATA_EQ_HPP

#include "../Common/FrameData.hpp"
#include "EqInclude.hpp"

class FrameDataEq: public FrameData, public co::Serializable
{
public:
	FrameDataEq(RenderAlgorithm* algorithm_stack) :
		FrameData(algorithm_stack)
	{
	}

	FrameDataEq(FrameDataEq const& other) :
		FrameData(other)
	{
	}

	virtual void set_render_algorithm(std::string const& name)
	{
		setDirty(DIRTY_RALGO);
		FrameData::set_render_algorithm(name);
	}

	void serialize(co::DataOStream& os, const uint64_t dirty);

	void deserialize(co::DataIStream& is, const uint64_t dirty);

private:
	enum DirtyBits
	{
		DIRTY_RALGO = DIRTY_CUSTOM << 1,
		DIRTY_RENDERER = DIRTY_CUSTOM << 2
	};
};

#endif /* FRAME_DATA_EQ_HPP */
