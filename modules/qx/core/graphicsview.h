#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "graphicscamera.h"

#include <filament/Camera.h>
#include <filament/View.h>
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
    // std::vector<GraphicsItem*> renderables( const std::vector<GraphicsItem*> lst) const;

    void applyFilamentCamera();

    GraphicsCamera *camera() const;
    x_matrix4x4 transform();
    filament::View *filamentView() const;

private:
    filament::Camera *m_filamentCamera;
    filament::View   *m_filamentView;

    x_rect          m_rect;
    ViewType        m_type;
    std::unique_ptr<GraphicsCamera>  m_camera;


protected:
    x_matrix4x4 m_transform;
};

}
#endif // GRAPHICSVIEW_H
