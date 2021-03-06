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

#include "FrameDataEq.hpp"
#include "Maoni/Enum.hpp"

class Serializer: public AlgorithmConfig
{
public:
	Serializer(co::DataOStream& os) :
		os(os)
	{
	}

	~Serializer()
	{
	}

private:
	void property(const char*, int& value)
	{
		os << value;
	}

	void property(const char*, bool& value)
	{
		os << value;
	}

	void property(const char*, float& value)
	{
		os << value;
	}

	void property(const char*, double& value)
	{
		os << value;
	}

	void property(const char*, Enum& value)
	{
		os << int(value);
	}

	void property(const char*, Path& value)
	{
		os << value.path();
	}

	void property(const char*, Color& value)
	{
		os << value.red() << value.green() << value.blue() << value.alpha();
	}

	void property(const char* name, ShaderProgram& value)
	{
	}

	void property(const char*, Vec2& value)
	{
		os << value.data[0] << value.data[1];
	}

	void property(const char*, Vec3& value)
	{
		os << value.data[0] << value.data[1] << value.data[2];
	}

	void property(const char*, Vec4& value)
	{
		os << value.data[0] << value.data[1] << value.data[2] << value.data[3];
	}

private:
	co::DataOStream& os;
};

void FrameDataEq::serialize(co::DataOStream& os, const uint64_t dirty)
{
	co::Serializable::serialize(os, dirty);

	if (dirty & DIRTY_RALGO)
		os << ralgo_name;

	if (dirty & DIRTY_RENDERER)
	{
		Serializer serializer(os);
		renderer->config(serializer);
	}
}

class Deserializer: public AlgorithmConfig
{
public:
	Deserializer(co::DataIStream& is) :
		is(is)
	{
	}

	~Deserializer()
	{
	}

private:
	void property(const char*, int& value)
	{
		is >> value;
	}

	void property(const char*, bool& value)
	{
		is >> value;
	}

	void property(const char*, float& value)
	{
		is >> value;
	}

	void property(const char*, double& value)
	{
		is >> value;
	}

	void property(const char*, Enum& value)
	{
		int temp;
		is >> temp;
		value = Enum(temp);
	}

	void property(const char*, Path& value)
	{
		std::string temp;
		is >> temp;
		value.path(temp);
	}

	void property(const char*, Color& value)
	{
		float temp[4];
		is >> temp[0] >> temp[1] >> temp[2] >> temp[3];
		value = Color(temp[0], temp[1], temp[2], temp[3]);
	}

	void property(const char* name, ShaderProgram& value)
	{
	}

	void property(const char*, Vec2& value)
	{
		is >> value.data[0] >> value.data[1];
	}

	void property(const char*, Vec3& value)
	{
		is >> value.data[0] >> value.data[1] >> value.data[2];
	}

	void property(const char*, Vec4& value)
	{
		is >> value.data[0] >> value.data[1] >> value.data[2] >> value.data[3];
	}

private:
	co::DataIStream& is;
};

void FrameDataEq::deserialize(co::DataIStream& is, const uint64_t dirty)
{
	co::Serializable::deserialize(is, dirty);

	if (dirty & DIRTY_RALGO)
	{
		is >> ralgo_name;
		FrameData::set_render_algorithm(ralgo_name);
	}

	if (dirty & DIRTY_RENDERER)
	{
		Deserializer deserializer(is);
		renderer->config(deserializer);
	}
}
