#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "graphicscamera.h"

#include <misc/flags.h>
#include <vector>

namespace Qx::prv
{

class CoreItem;
class GraphicsItem;

class GraphicsView
{
public:
    GraphicsView( GraphicsScene *scene, const x_rect &rc, ViewType tp );
    ~GraphicsView();
    bool shouldRender(GraphicsItem *itm);


    GraphicsCamera *camera() const;
    x_matrix4x4 transform();

private:

    x_rect          m_rect;
    ViewType        m_type;
    std::unique_ptr<GraphicsCamera>  m_camera;


protected:
    x_matrix4x4 m_transform;
};

}
#endif // GRAPHICSVIEW_H
