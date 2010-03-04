#include <GL/glew.h>
#include "RenderWidget.hpp"

void RenderWidget::init()
{
	glewInit();
}

void RenderWidget::draw()
{
	frame_data.draw();
}

QString RenderWidget::helpString() const
{
	return "<h2>S i m p l e V i e w e r</h2>"
		"Use the mouse to move the camera around the object. "
		"You can respectively revolve around, zoom and translate with the three mouse buttons. "
		"Left and middle buttons pressed together rotate around the camera view direction axis<br><br>"
		"Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. "
		"Simply press the function key again to restore it. Several keyFrames define a "
		"camera path. Paths are saved when you quit the application and restored at next start.<br><br>"
		"Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, "
		"<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. "
		"See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>"
		"Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). "
		"A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>"
		"A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. "
		"See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>"
		"Press <b>Escape</b> to exit the viewer.";
}
