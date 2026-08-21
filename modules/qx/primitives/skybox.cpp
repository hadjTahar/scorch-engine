#include "skybox.h"
#include <fstream>



namespace Qx {


SkyBox::SkyBox(CoreItem *parent):
    prv::GraphicsItem3D{ parent }
{
}

SkyBox::~SkyBox()
{
}

void SkyBox::updateModel()
{

    // skybox as an item
    //     // Set up view (Skybox & Camera)
    //     auto skybox = filament::Skybox::Builder().color({0., 0., 0., 1.0})
    //           .build(*filamentEngine);
    // filamentScene->setSkybox( skybox );
}


}
