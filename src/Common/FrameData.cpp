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
#include <boost/algorithm/string/predicate.hpp>
#include <boost/serialization/vector.hpp>
#include "serialize.hpp"
#include <fstream>

extern "C" void draw_gears();

FrameData::FrameData(RenderAlgorithm* algorithm_stack) :
	renderer(0), algorithm_stack(algorithm_stack)
{
	init();
}

FrameData::FrameData(FrameData const& other) :
	renderer(0), algorithm_stack(other.algorithm_stack)
{
	init();
}

void FrameData::init()
{
}

class algo_setter
{
public:
	algo_setter(std::string const& name, RenderAlgorithm*& algorithm) :
		name(name), algorithm(algorithm)
	{
	}

	void operator()(RenderAlgorithm*& algo)
	{
		if (name == algo->name())
			algorithm = algo;
	}

private:
	std::string const& name;
	RenderAlgorithm*& algorithm;
};

void FrameData::set_render_algorithm(std::string const& name)
{
	for_each_algorithm(algo_setter(name, renderer));
	ralgo_name = name;
}

class count
{
public:
	count(std::size_t& value) :
		value(value)
	{
	}

	template<typename T>
	void operator()(T)
	{
		++value;
	}

private:
	std::size_t& value;
};

std::size_t FrameData::num_algorithms() const
{
	std::size_t num = 0;
	for_each_algorithm(count(num));
	return num;
}

void FrameData::draw() const
{
	if (renderer)
		renderer->render(this->myrank(), this->ranks());
	else
		draw_gears();
}

void FrameData::do_export_scene(boost::archive::xml_oarchive& archive)
{
	archive << boost::serialization::make_nvp("model", model_name);
	archive << boost::serialization::make_nvp("ralgo_name", ralgo_name);

	if (renderer)
		archive << boost::serialization::make_nvp("renderer", *renderer);
}

void FrameData::export_scene(const char* filename)
{
	std::ofstream file(filename);
	if (!file)
		return;

	boost::archive::xml_oarchive archive(file);

	do_export_scene(archive);
}

void FrameData::do_import_scene(boost::archive::xml_iarchive& archive)
{
	archive >> boost::serialization::make_nvp("renderer", ralgo_name);
	set_render_algorithm(ralgo_name);

	archive >> boost::serialization::make_nvp("algorithm", *renderer);
}

void FrameData::import_scene(const char* filename)
{
	std::ifstream file(filename);
	if (!file)
		return;

	boost::archive::xml_iarchive archive(file);
	do_import_scene(archive);
}
