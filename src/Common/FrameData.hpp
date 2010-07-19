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

#include "Light.hpp"
#include <Maoni/Model.hpp>
#include <Maoni/RenderAlgorithm.hpp>
#include <Maoni/MeshLoader.hpp>
#include "../Common/Logo.hpp"
#include <string>

class FrameData
{
public:
	FrameData(RenderAlgorithm* algorithm_factory_stack,
			MeshLoader* mesh_loader_stack);

	FrameData(FrameData const& other);

	virtual void load_model(std::string const& filename);

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

	std::size_t num_lights() const
	{
		return lights.size();
	}

	virtual Light& light(std::size_t i)
	{
		return lights[i];
	}

	virtual const Light& light(std::size_t i) const
	{
		return lights[i];
	}

	void draw() const;

	void enable_logo(bool render)
	{
		logo.set_render(render);
	}

	void set_logo_path(std::string path)
	{
		logo.set_path(path);
	}

	//! return if these settings belong to the master
	//! settings are broadcasted from the master to the slaves
	virtual bool master() const
	{
		return true;
	}

	virtual void animate()
	{
	}

	virtual void resize(int width, int height)
	{
		logo.calc_pos(width, height);
	}

	virtual int getMWidth() const
	{
	}

	virtual int getMHeight() const
	{
	}

	virtual void setLightChanged()
	{
	}

	virtual void setModelChanged()
	{
	}

	virtual void setRenderParamChanged()
	{
	}

	virtual void setRendererChanged()
	{
	}

	virtual void setTilesChanged()
	{
	}

	virtual bool getDoResize() const
	{
	}

	virtual void setDoResize(bool flag)
	{
	}

	virtual void calcDrawRange(unsigned int myrank, unsigned int ranks)
	{
		model_.calcDrawRange(myrank, ranks);
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

	template<typename Function>
	void for_each_loader(Function function) const
	{
		for_each(mesh_loader_stack, function);
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
	std::vector<Light> lights;

	std::string model_name;
	std::string ralgo_name;

	Logo logo;

	RenderAlgorithm* renderer;

private:
	RenderAlgorithm* algorithm_stack;
	MeshLoader* mesh_loader_stack;

	Model model_;
};

#endif /* FRAME_DATA_HPP */
