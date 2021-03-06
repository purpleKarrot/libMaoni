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

#include "RenderWidget.hpp"
#include <boost/assert.hpp>
#include <IceTMPI.h>
#include <IceTGL.h>

RenderWidgetIceT* RenderWidgetIceT::singleton = 0;

RenderWidgetIceT::RenderWidgetIceT(FrameData& framedata) :
	RenderWidget(framedata), framedata_icet(
			dynamic_cast<FrameDataIceT&> (framedata))
{
	BOOST_ASSERT(!singleton && "Only one Instance of IceTWidget may exist");
	singleton = this;

	IceTCommunicator communicator = icetCreateMPICommunicator(MPI_COMM_WORLD);
	context = icetCreateContext(communicator);
	icetDestroyMPICommunicator(communicator);

	glClearColor(0.2f, 0.5f, 0.1f, 1.0f);
	icetGLDrawCallback(static_draw);

	// slaves should animate from the beginning
	if (!framedata_icet.master())
		startAnimation();
}

RenderWidgetIceT::~RenderWidgetIceT()
{
	icetDestroyContext(context);
}

void RenderWidgetIceT::static_draw()
{
	singleton->RenderWidget::draw();
}

void RenderWidgetIceT::paintGL()
{
	if (framedata_icet.getDoResize())
	{
		resizeWindow();
		framedata_icet.setDoResize(false);
	}

	framedata_icet.animate();

	// the projection matrix gets the correct aspect ratio by using
	// libqglviewer functionality
	camera()->setScreenWidthAndHeight(framedata_icet.getScreenWidth(),
			framedata_icet.getScreenHeight());

	preDraw();
	framedata_icet.setMatrices();
	icetGLDrawFrame();
	postDraw();
}

void RenderWidgetIceT::stopAnimation()
{
	// slaves should keep animating
	if (framedata_icet.master())
		QGLViewer::stopAnimation();
}

/*
 * Every RenderWidget, the master's as well as the slave ones, has to have
 * the same size as the biggest one (IceT User Guide).
 */
void RenderWidgetIceT::resizeWindow()
{
	if (framedata_icet.tiles[framedata_icet.myrank()].fullscreen)
	{
		setWindowState(Qt::WindowFullScreen);
	}
	else
	{
		setWindowState(Qt::WindowNoState);
	}
	// the window may not be smaller than the render context
	setMinimumSize(framedata_icet.getMWidth(), framedata_icet.getMHeight());
	framedata_icet.resize(framedata_icet.getMWidth(),
			framedata_icet.getMHeight());
}
