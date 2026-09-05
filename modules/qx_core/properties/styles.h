#ifndef STYLES_H
#define STYLES_H

#include "properties.h"

#include <misc/font.h>

namespace Qx::prv
{



/// ## ---------------------------------------------------------
///

struct RectangleStyle : PropertySet
{
    RectangleStyle(MetaObject &owner):
        PropertySet{owner}
    {}

    void setBorder  ( x_real brd )  {if(m_border == brd)  return;m_border = brd;m_owner.propertyChanged( PropertyStates::Material );}
    void setColor  ( const x_rgba &clr )    {if(m_color == clr) return;m_color = clr;m_owner.propertyChanged( PropertyStates::Material );}
    void setBorderColor  ( const x_rgba &clr )    {if(m_borderColor == clr) return;m_borderColor = clr;m_owner.propertyChanged( PropertyStates::Material );}

    auto  border()      const {return m_border; }
    auto  color()       const {return m_color; }
    auto  borderColor() const {return m_borderColor; }


private:

    x_real    m_border;
    x_rgba    m_color;
    x_rgba    m_borderColor;
};



/// ## ---------------------------------------------------------


struct RoundedRectangleStyle : PropertySet
{
    RoundedRectangleStyle(MetaObject &owner):
        PropertySet{owner}
    {}

    void setRadius   ( const x_radius &rad )  {if(m_radius == rad)   return;m_radius = rad;m_owner.propertyChanged(PropertyStates::Geometry );}
    void setBorder  ( x_real brd )  {if(m_border == brd)  return;m_border = brd;m_owner.propertyChanged( PropertyStates::Material );}
    void setColor  ( const x_rgba &clr )    {if(m_color == clr) return;m_color = clr;m_owner.propertyChanged( PropertyStates::Material );}
    void setBorderColor  ( const x_rgba &clr )    {if(m_borderColor == clr) return;m_borderColor = clr;m_owner.propertyChanged( PropertyStates::Material );}

    auto  radius()      const {return m_radius; }
    auto  border()      const {return m_border; }
    auto  color()       const {return m_color; }
    auto  borderColor() const {return m_borderColor; }



    x_radius   m_radius;
    x_real     m_border;
    x_rgba     m_color;
    x_rgba     m_borderColor;
};

/// ## ---------------------------------------------------------


struct ImageStyle : PropertySet
{
    ImageStyle(MetaObject &owner):PropertySet{owner}{}
    void setSource  ( const x_string &src )  {if(m_source == src) return;m_source = src;m_owner.propertyChanged( PropertyStates::Material );}
    auto  source()   const {return m_source; }

private:
    x_string m_source;
};
/// ## ---------------------------------------------------------


struct TextStyle : PropertySet
{
    TextStyle(MetaObject &owner):PropertySet{owner}{}


    void setText  ( const x_string &txt )  {if(m_text == txt)  return;m_text = txt;m_owner.propertyChanged( PropertyStates::Material );}
    void setColor ( const x_rgba &clr )    {if(m_color == clr) return;m_color = clr;m_owner.propertyChanged( PropertyStates::Material );}
    void setFont  ( const Font &fnt )      {if(m_font == fnt)  return;m_font = fnt;m_owner.propertyChanged( PropertyStates::Material );}
    void setHAlign( const TextHAlign &alg ){if(m_hAlign == alg)return;m_hAlign = alg;m_owner.propertyChanged( PropertyStates::Material );}
    void setVAlign( const TextVAlign &alg ){if(m_vAlign == alg)return;m_vAlign = alg;m_owner.propertyChanged( PropertyStates::Material );}



    auto  text()   const {return m_text; }
    auto  color()  const {return m_color; }
    auto  font()   const {return m_font; }
    auto  hAlign() const {return m_hAlign; }
    auto  vAlign() const {return m_vAlign; }

private:
    x_string    m_text;
    x_rgba      m_color;
    Font        m_font;
    TextHAlign  m_hAlign;
    TextVAlign  m_vAlign;
};



}

#endif // STYLES_H
