#ifndef UIDEVICE_H
#define UIDEVICE_H

#include <misc/dbg/dbgtools.h>
#include <misc/types/list.h>
#include <misc/types/pixelunit.h>
#include <misc/utils/xdl.h>

#include <map>


namespace Qx{

#define QX_SET_CURRENT_DISP(sdlWin) DispSetter tmpSetter(sdlWin); qx_unused( tmpSetter );

/// ## ----------------------------------------------------------------------------
///


class UIDevice
{

protected:
    UIDevice( x_displayID index );

public:

    UIDevice(){}


    /// ## True pixel, no scaling, no scale factor, or pixel density
    prv::x_px px( x_real pxVal ) const;

    /// ## All of these functions return true pixels
    /// ## and will lead to the call of ::px

    /// ## Density independent pixels
    prv::x_px dp( x_real dpVal ) const;

    /// ## User scaled dp, m_userScale * dp
    prv::x_px sp( x_real spVal ) const;

    /// ## Virtual/Logical pixel, what Qt considers a pixel
    /// ## This will undo the effects of ::px()
    prv::x_px lp( x_real vpVal ) const;

    prv::x_px pt( x_real ptVal ) const;
    prv::x_px in( x_real inVal ) const;
    prv::x_px mm( x_real mmVal ) const;
    prv::x_px cm( x_real cmVal ) const;
    /// ## horizontal and vertical Percentages
    /// ## of the screen
    prv::x_px hp(x_real hpVal ) const;
    prv::x_px vp( x_real vpVal ) const;


    static void setupScreens();
    static UIDevice screen( x_window *sdlWindow );

    static QX_TRIVIAL DeviceType  defaultDeviceType();
    static QX_TRIVIAL DeviceOS defaultDeviceOS();

    prv::x_px width() const;
    prv::x_px height() const;

    /// ## Raw pixels <--> logical pixels,
    /// ## no sim involved used only in window for
    /// ## size and mouse events
    x_real rpxToLogical( x_real px ) const;
    x_real rlpToPixel( x_real px ) const;

    static void setCurrentDisplayID(x_displayID newCurrentDisplayID);
    static UIDevice &currentDevice() ;


    x_real dpi() const;

protected:
    x_real computeDpi() const;

protected:

    x_real m_width;
    x_real m_height;
    x_real m_pixelScale; /// ## pixel to logical pixels
    x_real m_userScale;
    x_real m_dpi;

    static std::map<x_displayID,UIDevice> m_devices;
    static x_displayID m_currentDisplayID;

};


/// ## ------------------------------------------------------------------------

struct DispSetter
{

    DispSetter( x_window *sdlWin )
    {
        UIDevice::setCurrentDisplayID( qx_getDisplayForWindow( sdlWin ) );
    }
    ~DispSetter()
    {
        UIDevice::setCurrentDisplayID( 0 );
    }
};


}

#endif // UIDEVICE_H
