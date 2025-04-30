#ifndef SCENERENDERER_H
#define SCENERENDERER_H

#include <QPainter>
#include "node.h"
#include "cullingvisitor.h"
#include "boundingboxdrawvisitor.h"

class SceneRenderer
{
public:
    void renderScene(QPainter &, Node *root, const QTransform &viewTransform, const QRectF &screenRect, Node *selected);

private:
    BoundingBoxDrawVisitor  m_bbdVisitor;
    CullingVisitor          m_cullVisitor;
};

#endif // SCENERENDERER_H
