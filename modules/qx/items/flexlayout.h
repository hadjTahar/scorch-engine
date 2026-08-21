#ifndef FLEXLAYOUT_H
#define FLEXLAYOUT_H

#include "rectangle.h"


namespace Qx {


class FlexLayout : public Rectangle
{
    QX_META_OBJECT( "FlexLayout",
                   prv::MetaItemType::GraphicsItem2D,
                   prv::MetaItemType::GraphicsItem2D )

public:
    FlexLayout(CoreItem *parent);

private:
    x_matrix4x4 m_prevMat;
    x_count     m_prevChildren;

};

}

#endif // FLEXLAYOUT_H
