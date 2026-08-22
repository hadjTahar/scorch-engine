#ifndef PROPERTIES_H
#define PROPERTIES_H


#include <core/metaobject.h>
#include <misc/flags.h>
#include <misc/vecs.h>
#include <array>

namespace Qx::prv
{

struct PropertySet
{
protected:
    explicit PropertySet(MetaObject &owner) : m_owner{owner} {}
    MetaObject &m_owner;
};
/// ## ---------------------------------------------------------

struct WindowProperties : PropertySet
{
    WindowProperties(MetaObject &owner):
        PropertySet{owner}
    {}

    void setSize   ( const x_size &sz )  {if(m_size == sz)return;m_size = sz;m_owner.propertyChanged( PropertyStates::Geometry );}
    void setPosition   ( const x_vector2 &pos )  {if(m_position == pos)return;m_position = pos;m_owner.propertyChanged( PropertyStates::Transfom );}


    auto size() const{ return m_size;}
    auto position() const{ return m_position;}

private:
    x_size    m_size;
    x_vector2 m_position;


};

/// ## ---------------------------------------------------------


struct ItemRendering : PropertySet
{
    ItemRendering(MetaObject &owner):
        PropertySet{owner}
    {}

    void setVisible      ( bool val ){if(m_visible == val)   return;m_visible = val;m_owner.propertyChanged( PropertyStates::Render );}
    void setClipping     ( bool val ){if(m_clipping == val)  return;m_clipping = val;m_owner.propertyChanged( PropertyStates::Render );}
    void setCulling      ( bool val ){if(m_culling == val)   return;m_culling = val;m_owner.propertyChanged( PropertyStates::Render );}
    void setAntilalias   ( bool val ){if(m_antilalias == val)return;m_antilalias = val;m_owner.propertyChanged( PropertyStates::Render );}
    void setLod          ( bool val ){if(m_lod == val)       return;m_lod = val;m_owner.propertyChanged( PropertyStates::Render );}
    void setIgnoreCamera ( bool val ){if(m_ignoreCamera == val)return;m_ignoreCamera = val;m_owner.propertyChanged( PropertyStates::Render );}

    auto visible()      const{ return m_visible;}
    auto clipping()     const{ return m_clipping;}
    auto culling()      const{ return m_culling;}
    auto antilalias()   const{ return m_antilalias;}
    auto lod()          const{ return m_lod;}
    auto ignoreCamera() const{ return m_ignoreCamera;}


private:

    bool m_visible{true};
    bool m_clipping{false};
    bool m_culling{true};
    bool m_antilalias{true};
    bool m_lod{false};
    bool m_ignoreCamera{false};
};






}
#endif // PROPERTIES_H
