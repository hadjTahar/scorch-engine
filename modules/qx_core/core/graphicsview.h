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
    GraphicsView(GraphicsScene *scene);
    ~GraphicsView();
    bool shouldRender(GraphicsItem *itm);

    GraphicsCamera *camera() const;

    /// ## Used for Canvas
    x_matrix4x4 logicalTransform( const x_size &windSz ) const;

    /// ## Used for Filament
    x_vector2   logicalScale( const x_size &windSz ) const;

    x_rect viewport() const;
    void setViewport(const x_rect &newViewport);
    x_rect effectiveViwport(const x_size &windSz) const;

    x_size logicalSize() const;
    void setLogicalSize(x_size newLogicalSize);

    ViewType type() const;
    void setType(ViewType newType);

    ViewMode mode() const;
    void setMode(ViewMode newMode);


private:

    x_rect   m_viewport;
    x_size   m_logicalSize;
    ViewType m_type;
    ViewMode m_mode;

    std::unique_ptr<GraphicsCamera>  m_camera;


};

}
#endif // GRAPHICSVIEW_H
