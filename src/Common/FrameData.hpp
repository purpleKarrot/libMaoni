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

#ifndef FRAME_DATA_HPP
#define FRAME_DATA_HPP

#include <Maoni/RenderAlgorithm.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <string>
#include <vector>

class FrameData
{
public:
	FrameData(RenderAlgorithm* algorithm_factory_stack);

	FrameData(FrameData const& other);

	virtual int myrank() const
	{
		return 0;
	}

	virtual int ranks() const
	{
		return 1;
	}

	virtual void set_render_algorithm(std::string const& name);

	void config_algorithm(AlgorithmConfig& manager)
	{
		if (renderer)
			renderer->config(manager);
	}

	//! get the amount of render algorithms
	std::size_t num_algorithms() const;

	//! get the amount of mesh loaders
	std::size_t num_loaders() const;

	void draw() const;

	virtual void resize(int width, int height)
	{
	}

	virtual void setRenderParamChanged()
	{
	}

	virtual std::string getRalgoName()
	{
		return ralgo_name;
	}

public:
	void export_scene(const char* filename);
	void import_scene(const char* filename);

public:
	template<typename Function>
	void for_each_algorithm(Function function) const
	{
		for_each(algorithm_stack, function);
	}

private:
	void init();

	template<typename T, typename Function>
	void for_each(T* stack, Function function) const
	{
		for (T* i = stack; i; i = i->next)
			function(i);
	}

protected:
	virtual void do_import_scene(boost::archive::xml_iarchive& archive);
	virtual void do_export_scene(boost::archive::xml_oarchive& archive);

protected:
	std::string model_name;
	std::string ralgo_name;

	RenderAlgorithm* renderer;

private:
	RenderAlgorithm* algorithm_stack;
};

#endif /* FRAME_DATA_HPP */
