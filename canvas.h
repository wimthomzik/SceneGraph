#ifndef CANVAS_H
#define CANVAS_H

#include "vec2.h"
#include "node.h"
#include "transform.h"
#include <QWidget>
#include <memory>
#include "cullingvisitor.h"
#include "boundingboxdrawvisitor.h"
#include "pickingvisitor.h"
#include <QMenu>
#include "scenerenderer.h"
#include "sceneeditor.h"

using Vec2 = wtm::Vec2T<double>;

// Helper functions to convert points to vectors and vice versa
inline Vec2     p2v(const QPointF &p){ return {p.x(), p.y()}; }
inline QPointF  v2p(const Vec2 &v){ return {v.x(), v.y()}; }

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void setRoot(TransformUPtr newRoot);
    Node* root() { return m_root.get(); }
    void resetRoot() { m_root.reset(); }
    Node* pickedNode() { return m_pickVisitor.pickedNode(); }

private:
    Vec2                    m_offset;
    Vec2                    m_prevPosition;
    Vec2                    m_scale {1, -1};
    TransformUPtr           m_root;
    PickingVisitor          m_pickVisitor;
    SceneRenderer           m_sceneRenderer;
    SceneEditor             m_sceneEditor;

    QTransform viewTransform() const;
    QPointF mapToScene(const QPointF &mousePos);
    void setPenSettings(QPainter *p) const;
    QRectF adjustScreenRect();
};

#endif // CANVAS_H
