#include "uidevice.h"
#include <misc/dbg/tools.h>


namespace Qx{



std::map<x_displayID,UIDevice> UIDevice::m_devices = {};
x_displayID UIDevice::m_currentDisplayID = 0;

UIDevice::UIDevice(x_displayID index)
{
    auto dispInfo = qx_getCurrentDisplayMode( index );
    qx_assert( dispInfo, "Invalid DisplayMode");

    m_width       = static_cast<x_real>( dispInfo->w );
    m_height      = static_cast<x_real>( dispInfo->h );
    m_pixelScale  = dispInfo->pixel_density;
    m_userScale   = 1;
    m_dpi         = computeDpi();

    qx_debug() << "DPI : " << m_dpi
               << " SC : " << m_pixelScale
               << " PX : " << px( 160 )
               << " DP : " << dp( 160 )
        ;
}

prv::x_px UIDevice::lp(x_real vpVal) const
{
    return prv::px( vpVal );
}

prv::x_px UIDevice::pt(x_real ptVal) const
{
    const auto ret = dp( ptVal / static_cast<x_real>( .75 ) );
    return prv::x_px( ret );
}

prv::x_px UIDevice::in(x_real inVal) const
{
    return prv::px(  160 * inVal );
}

prv::x_px UIDevice::mm(x_real mmVal) const
{
    const auto ret = in( mmVal ) * static_cast<x_real>( 25.4 );
    return prv::px( ret );
}

prv::x_px UIDevice::cm(x_real cmVal) const
{
    const auto ret = in( cmVal ) * static_cast<x_real>( 2.54 );
    return prv::px( ret );
}

prv::x_px UIDevice::hp(x_real hpVal) const
{
    return prv::px( hpVal );
}

prv::x_px UIDevice::vp(x_real vpVal) const
{
    return prv::px( vpVal );
}



// prv::x_px UIDevice::pc(x_real pcVal) const
// {
//     // pcVal * ??? Screen or window????
//     qx_assert( false, "DON'T USE, NOT supported yet" );
//     return pcVal;
// }

prv::x_px UIDevice::px(x_real pxVal) const
{
    qx_todo( "If ::px is not working, devide it by \"m_pixelScale\"." );
    qx_count();
    const auto ret = pxVal / m_pixelScale;
    return prv::px( ret );
}

prv::x_px UIDevice::dp(x_real dpVal) const
{
    const auto ret = dpVal * ( m_dpi / 160.f);
    return prv::px( ret );
}

prv::x_px UIDevice::sp(x_real spVal) const
{
    return prv::px( m_userScale * dp( spVal ) );
}

void UIDevice::setupScreens()
{
    int count_displays;
    x_displayID *displays = qx_getDisplays(&count_displays);
    for( auto idx = 0; idx < count_displays; idx++){
        const auto id = displays[idx];
        UIDevice scrn( id );
        m_devices[ id ] = scrn;
    }
    qx_free(displays);
}

UIDevice UIDevice::screen(x_window *sdlWindow)
{
    auto id = qx_getDisplayForWindow( sdlWindow );
    const auto chk = m_devices.contains( id );
    qx_assert( chk, "Window has no display" );
    return m_devices[ id ];
}

DeviceType UIDevice::defaultDeviceType()
{
    qx_todo( "Add rest of types " );
    return DeviceType::Desktop;
}

DeviceOS UIDevice::defaultDeviceOS()
{
    qx_todo( "Add rest of OS" );
    return DeviceOS::Windows;
}

prv::x_px UIDevice::width() const
{
    return prv::px( m_width );
}

prv::x_px UIDevice::height() const
{
    return prv::px( m_height );
}

x_real UIDevice::rpxToLogical(x_real px) const
{
    return px / m_pixelScale;
}

x_real UIDevice::rlpToPixel(x_real px) const
{
    return m_pixelScale * px;
}

void UIDevice::setCurrentDisplayID(x_displayID newCurrentDisplayID)
{
    m_currentDisplayID = newCurrentDisplayID;
}

UIDevice &UIDevice::currentDevice()
{
    qx_assert( UIDevice::m_currentDisplayID != 0,
              "\n"
              "Can't access a device with a null ID\n"
              "This is likely due to calling a screen related function\n"
              "like (px, dp, UIMainWindow::reisze)\n"
              "in the app class outside UIWindow or a node"
              );

    return m_devices[ m_currentDisplayID ];

}

x_real UIDevice::computeDpi() const
{
    x_real dpiBase = 96;
    switch ( defaultDeviceType() ) {
    case DeviceType::Mobile:
    case DeviceType::Tablet:
        dpiBase = 160;
        break;
    default:
        break;
    }

    return dpiBase * m_pixelScale;
}

x_real UIDevice::dpi() const
{
    return m_dpi;
}



}
