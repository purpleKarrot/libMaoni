#ifndef RENDER_WIDGET_HPP
#define RENDER_WIDGET_HPP

#include <qglviewer.h>
#include <boost/noncopyable.hpp>

#include <Maoni/RenderAlgorithm.hpp>

class FrameData;

class RenderWidget: public QGLViewer, private boost::noncopyable
{
Q_OBJECT

public:
	RenderWidget(FrameData& framedata);

	virtual ~RenderWidget();

private:
	QString helpString() const;

protected:
	void resizeGL(int width, int height);
	void draw();

protected:
	FrameData& framedata;
};

#endif /* RENDER_WIDGET_HPP */
