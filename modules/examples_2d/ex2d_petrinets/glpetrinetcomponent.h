#ifndef GLPETRINETCOMPONENT_H
#define GLPETRINETCOMPONENT_H

#include "glnodecomponent.h"
#include <petriengine.h>

namespace Qx{

class GLPetriNetComponent : public GLNodeComponent
{
    QX_DEBUG_TYPE( GLPetriNetComponent )

public:
    GLPetriNetComponent(GLGraphNode *prntNode);
    ptn::PetriEngine *petriEngine();

protected:
    void doProcess( x_real delta) override;

public:
    x_petriTokensChangedFunction tokensChanged;

protected:
    ptn::PetriEngine m_petriEngine;


};

}
#endif // GLPETRINETCOMPONENT_H
