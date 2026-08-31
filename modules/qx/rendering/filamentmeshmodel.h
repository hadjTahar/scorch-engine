#ifndef FILAMENTMESHMODEL_H
#define FILAMENTMESHMODEL_H

#include "graphicsmeshmodel.h"


namespace Qx {


class FilamentMeshModel : public GraphicsMeshModel
{
public:
    FilamentMeshModel();
    ~FilamentMeshModel();


protected:
    void clearBackendBuffers() override;
};


}

#endif // FILAMENTMESHMODEL_H
