#include "cullingvisitor.h"
#include "group.h"
#include "transform.h"
#include "polygon.h"
#include "circle.h"
#include <QDebug>

void CullingVisitor::cull(Node* root, const QRectF &viewport)
{
    m_visibleObjects.clear();
    setViewport(viewport);
    root->accept(*this);
}

void CullingVisitor::visit(Group &group)
{
    if(m_currTrans.mapRect(group.bounding()).intersects(m_viewport))
    {
        for (auto &child : group.children())
        {
            if(child->type() == NodeType::Transform)
            {
                auto tChild = static_cast<Transform*>(child.get());
                QRectF childBound = tChild->bounding();
                QTransform local;
                local.rotateRadians(tChild->rotationRadiant());
                local.translate(tChild->position().x(), tChild->position().y());
                if (m_currTrans.mapRect(local.mapRect(childBound)).intersects(m_viewport))
                {
                    child->accept(*this);
                }

            } else if (m_currTrans.mapRect(child->bounding()).intersects(m_viewport))
            {
                child->accept(*this);
            }
        }
    }
}

void CullingVisitor::visit(Transform &transform)
{
    QTransform prevTransformation = m_currTrans;

    m_currTrans.rotateRadians(transform.rotationRadiant());
    m_currTrans.translate(transform.position().x(), transform.position().y());

    CullingVisitor::visit(static_cast<Group &>(transform));

    m_currTrans = prevTransformation;
}

void CullingVisitor::visit(Circle &circle)
{
    m_visibleObjects.push_back({ &circle, m_currTrans });
}

void CullingVisitor::visit(Polygon &polygon)
{
    m_visibleObjects.push_back({ &polygon, m_currTrans });
}
