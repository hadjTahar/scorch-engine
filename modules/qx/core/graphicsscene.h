#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H


#include "graphicsitem.h"
#include "graphicsview.h"
#include "graphicswindow.h"



namespace Qx::prv
{


class GraphicsScene : public prv::GraphicsItem
{
public:
    friend class GraphicsItem;
    friend class EventComponent;

    GraphicsScene(CoreItem *parent);
    virtual ~GraphicsScene();
    GraphicsView *addView();

    virtual BackendResult initCanvas(GraphicsWindow *winItm) = 0;
    virtual void renderViews( GraphicsWindow *winItm ) = 0;
    std::vector<GraphicsItem *> items() const;


protected:
    void render(Canvas *) override final{}
    void updateModel( GraphicsMeshModel *) override final{}

    void registerItem(GraphicsItem *itm);
    void unregisterItem(GraphicsItem *itm);
    const auto &views() const{return m_views;}


protected:
    virtual void itemRegistered(GraphicsItem *itm){}

private:

    /// ## When accessing GraphicsScene::transform
    /// ## It's causing an assert fail at:
    /// ## ItemTransform::updateWorld, because
    /// ## it's reaching GraphicsWindow
    using prv::GraphicsItem::transform;

protected:
    std::vector<std::unique_ptr<GraphicsView>> m_views;
    std::vector<GraphicsItem*>   m_items;

};

}

#endif // GRAPHICSSCENE_H
