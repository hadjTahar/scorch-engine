#ifndef PATHS_H
#define PATHS_H

#include <items/rectangle.h>


/// ## ------------------------------------------------------------

class RectanglePath : public Qx::Rectangle
{

public:
    RectanglePath(CoreItem *parent):Qx::Rectangle{ parent}{}
protected:
    void render( Qx::Canvas *canvas)override
    {
        const auto sz = transform.size();

        Qx::prv::CanvasPen pen;
        pen.setColor( style.borderColor() );
        pen.setWidth( style.border() );

        Qx::prv::SolidBrush brush;
        brush.setColor( Qx::red() );

        canvas->setAntialias( rendering.antilalias() );

        Qx::CanvasPath pth0;
        pth0.moveTo( {0,0} );
        pth0.lineTo( {200,200} );
        canvas->drawCanvasPath( pth0, pen, brush );



        Qx::CanvasPath pth1;
        // pth1.moveTo( {0,0} );
        // pth1.lineTo( {200,200} );


        pth1.moveTo({124, 108});
        pth1.lineTo({172, 24});
        // path.addCircle(50, 50, 30);
        pth1.moveTo({36, 148});
        pth1.quadTo({66, 188}, {120, 136});
        canvas->drawCanvasPath( pth1, pen, brush );
    }
};


#endif // PATHS_H
