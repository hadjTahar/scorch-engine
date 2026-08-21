#include "glpetrinetcomponent.h"

namespace Qx{


GLPetriNetComponent::GLPetriNetComponent(GLGraphNode *prntNode):
    GLNodeComponent{ prntNode },
    m_petriEngine{}
{


}

void GLPetriNetComponent::doProcess(x_real delta)
{
    m_petriEngine.step( delta );

    if( !tokensChanged.isValid() )
        return;
    const auto changes = m_petriEngine.changeMarking();
    const auto sz      = changes.size();
    for (auto idx = 0; idx < sz; ++idx)
    {
        const auto tkns = changes[ idx ];
        if( tkns == 0)
            continue;
        const auto plc = m_petriEngine.place( idx );
        tokensChanged( plc, tkns );
    }
    m_petriEngine.displayMarking();
}

ptn::PetriEngine *GLPetriNetComponent::petriEngine()
{
    return &m_petriEngine;
}


}
