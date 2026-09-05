#ifndef ROOTBASEITEM_H
#define ROOTBASEITEM_H

#include "coreitem.h"


/*
    std::vector<Physics2D>
    std::vector<Physics3D>
    std::vector<MouseInput>
    std::vector<KeyInput>
    std::vector<Signal<Type>>::changed
    std::vector<ProcessComponent> /// pointer callbaks don’t capture
    When a component is constructed/destructed, it adds/removes itself in root()
    Sort render, and mouse by z when added
    ::attach<Component>

*/

namespace Qx::prv
{

class RootBaseItem : public CoreItem
{
public:
    RootBaseItem();
    ~RootBaseItem();
    static void mustBeRootBased(){}

protected:
    void render(Canvas*)        override final{dbg_assert(false) << "RootBaseItem::render should never be called";}
    void updateModel( GraphicsMeshModel * ) override final{dbg_assert(false) << "RootBaseItem::render should never be called";}
};

}

#endif // ROOTBASEITEM_H
