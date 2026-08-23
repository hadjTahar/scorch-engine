#ifndef ITEMTRANSFORM_H
#define ITEMTRANSFORM_H

#include "properties.h"



namespace Qx::prv
{

class GraphicsItem;


class ItemTransform
{


private:
    auto localMatrix()
    {
        update();
        return m_localMatrix;
    }
    auto worldMatrix()
    {
        update();
        return m_worldMatrix;
    }

    ItemTransform(){}
    ItemTransform(const ItemTransform&){}
    ItemTransform(const ItemTransform&&){}

public:
    ItemTransform(GraphicsItem *owner):
        m_item{ owner },
        m_localMatrix{ x_matrix4x4{1} },
        m_worldMatrix{ x_matrix4x4{1} },
        m_position{ 0 },
        m_scale{    1,1,1 },
        m_rotation{ 1,0,0,0},
        m_size{ 0,0,0 },
        m_dirtyLocal{ true },
        m_dirtyWorld{ true }
    {
        // setPosition( {} );
    }

    void setPosition( const x_vector3 &vec)
    {
        if( m_position == vec )
            return;
        m_position = vec;
        m_dirtyLocal = true;
        m_dirtyWorld = true;
        update();
    }

    void setScale( const x_vector3 &vec)
    {
        m_scale = vec;
        m_dirtyLocal = true;
        m_dirtyWorld = true;
        update();
    }

    void setRotation( const x_quat &quat)
    {
        m_rotation = quat;
        m_dirtyLocal = true;
        m_dirtyWorld = true;
        update();
    }



    auto position() const{return m_position;}
    auto scale()    const{return m_scale;}
    auto rotation() const{return m_rotation;}



    void setSize( const x_size &sz )
    {
        if(m_size == sz)
            return;
        m_size = sz;
        updateSize();
    }
    auto size() const
    {
        return m_size;
    }

    void setPivot( const x_pivot &pivot)
    {
        m_pivot = pivot;
    }
    auto pivot() const
    {
        return m_pivot;
    }

    auto physicsTransform()
    {
        /// ## TODO: Should I use the pivot for physics?
        /// ## Or retrun the ::worldMatrix directly?
        return worldMatrix();
    }

    auto layoutsTransform()
    {
        /// ## TODO: Layouts should not be concerned with the pivot???
        return worldMatrix();
    }

    auto pivotTransform()
    {
        /// m_graphicsModel->matrix  = mat1 * transform.worldMatrix() * mat0;
        if( m_pivot.type == PivotType::None)
            return worldMatrix();

        const auto transformOrigin = getPivot();
        const x_matrix4x4 imat = {1};
        const x_matrix4x4 mat0 = glm::translate(imat, -transformOrigin );
        const x_matrix4x4 mat1 = glm::translate(imat,  transformOrigin);
        return mat1 * worldMatrix() * mat0;
    }

    auto cameraTransform( const x_matrix4x4 &gvwMatrix,
                         const x_matrix4x4 &canvasMatrix,
                         bool ignoreCamera)
    {
        const auto pvtTransform = pivotTransform();
        if( ignoreCamera )
            /// ## Use the graphics view transform only
            return pvtTransform * gvwMatrix;
        else
            /// ## Use the camera transform
            return pvtTransform * canvasMatrix;
    }

private:


    void updateSize();
    void update();
    void updateLocal();
    void updateWorld();


    // Generates a translation matrix
    static x_matrix4x4 translationMat(const glm::vec3& offset)
    {
        return glm::translate(x_matrix4x4(1.0f), offset);
    }

    // Generates a scaling matrix
    static x_matrix4x4 scaleMat(const glm::vec3& factors)
    {
        return glm::scale(x_matrix4x4(1.0f), factors);
    }

    // Generates a rotation matrix from a quaternion
    static x_matrix4x4 rotationMat(const x_quat& rotationQuat)
    {
        return glm::mat4_cast(rotationQuat);
        // glm::mat4 rotationMatrix = glm::mat4_cast(myQuat);
        // return x_matrix4x4{1};
    }
    static constexpr auto axisValue = [](x_real min, x_real max, PivotAxis axis)
    {
        switch (axis)
        {
        case PivotAxis::Min: return min;
        case PivotAxis::Mid: return (min + max) * 0.5f;
        case PivotAxis::Max: return max;
        }

        return 0.0f;
    };
    x_vector3 getPivot()
    {



        if( m_pivot.type == PivotType::None )
            return {};
        else if( m_pivot.type == PivotType::Custom )
            return m_pivot.custom;


        const x_vector3 min{0,0,0};
        const x_vector3 max{ m_size.width, m_size.height, m_size.depth};
        const x_vector3 ret {
            axisValue(min.x, max.x, m_pivot.x),
            axisValue(min.y, max.y, m_pivot.y),
            axisValue(min.z, max.z, m_pivot.z)
        };
        return ret;
    }

private:
    // friend class  MetaObject;
    // friend class  CoreItem;
    friend class  GraphicsItem;
    GraphicsItem *m_item;
    /// ## Cached matrices
    x_matrix4x4 m_localMatrix;
    x_matrix4x4 m_worldMatrix;
    x_vector3   m_position;
    x_vector3   m_scale;
    x_quat      m_rotation;
    x_size      m_size;
    x_pivot     m_pivot;

    bool m_dirtyLocal;
    bool m_dirtyWorld;

};

}
#endif // ITEMTRANSFORM_H
