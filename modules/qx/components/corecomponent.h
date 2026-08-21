#ifndef CORECOMPONENT_H
#define CORECOMPONENT_H

#include <rendering/canvas.h>
#include <core/metaobject.h>
#include <misc/callbacks.h>



namespace Qx::prv
{

class GraphicsItem;
class WindowItem;


class CoreComponent : public MetaObject
{
    friend class CoreItem;
    friend class GraphicsItem;
    friend class WindowItem;

    QX_META_OBJECT( CoreComponent, MetaItemType::NA, MetaItemType::NA )

public:
    CoreComponent(GraphicsItem *gItem);
    virtual ~CoreComponent();
    void remove();
    GraphicsItem *graphicsItem() const;

protected:
    void processComponent( x_real dlt );
    WindowItem *windowItem();

public:
    x_processCallback process;

protected:
    GraphicsItem *m_graphicsItem;

private:
    WindowItem   *m_windowItem;
};


}


#endif // CORECOMPONENT_H
