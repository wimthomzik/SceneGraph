#include "sceneeditor.h"
#include "circle.h"
#include "polygon.h"
#include <QDebug>
#include <QInputDialog>
#include "canvas.h"

SceneEditor::SceneEditor(Canvas* canvas) : m_canvas(canvas)
{

}

void SceneEditor::handleRightClick(Node *selectedNode, const QPointF &scenePos, const QPoint &screenPos)
{
    QMenu menu;

    buildContextMenu(menu, selectedNode);
    QAction* action = menu.exec(screenPos);
    if(action)
    {
        handleMenuAction(action->text(), selectedNode, scenePos);
    }
}

void SceneEditor::buildContextMenu(QMenu &menu, Node* selectedNode)
{

    if(!selectedNode)
    {
        QMenu* secondMenu = menu.addMenu("Add Geode");
        secondMenu->addAction("Circle");
        secondMenu->addAction("Polygon");
    }
    else
    {

        switch (selectedNode->type())
        {
        case NodeType::Circle:
            menu.addAction("Change Radius");
            [[clang::fallthrough]];
        case NodeType::Polygon:
            menu.addAction("Change Position");
            menu.addAction("Delete");
            break;
        case NodeType::Group:
        case NodeType::Transform:
        {
            QMenu* secondMenu = menu.addMenu("Add Geode");
            secondMenu->addAction("Circle");
            secondMenu->addAction("Polygon");
            menu.addAction("Change Position");
            menu.addAction("Delete");
            break;
        }
        default:
            break;
        }
    }
}

void SceneEditor::handleMenuAction(const QString &action, Node* node, const QPointF &clickScenePos)
{
    Node* changedNode = nullptr;

    if(action == "Delete")
    {
        changedNode = node ? node->parent() : nullptr;
        deleteNode();
    }
    else if (action == "Change Radius" and node and node->type() == NodeType::Circle)
    {
        changedNode = node;
        changeRadius();
    }
    else if (action == "Change Position" and node)
    {
        changedNode = node;
        changePosition();
    }
    else if (action == "Circle")
    {
        changedNode = addGeode(node ? node : m_canvas->root(), clickScenePos, NodeType::Circle);
    }
    else if (action == "Polygon")
    {
        changedNode = addGeode(node ? node : m_canvas->root(), clickScenePos, NodeType::Polygon);
    }
    else
    {
        qDebug() << "Unhandled Action: " << action;
    }

    propagateChangeUp(changedNode);

//    m_canvas->update();
}

void SceneEditor::deleteNode()
{
    if (m_canvas->pickedNode()->parent())
    {
        m_canvas->pickedNode()->parent()->removeChild(m_canvas->pickedNode());
    }
    else
    {
        m_canvas->resetRoot();
    }
}

Node* SceneEditor::addGeode(Node* node, const QPointF& sceneMousePos, NodeType type)
{
    QPointF localPosition = node != nullptr ? computeWorldTransform(node).inverted().map(sceneMousePos) : sceneMousePos;

    auto transform = std::make_unique<Transform>();
    transform->setPosition(localPosition);

    Node* toReturn;
    if (type == NodeType::Circle)
    {
         auto newCircle = std::make_unique<Circle>();
         newCircle->setRadius(50);
         toReturn = newCircle.get();
         transform->addChild(std::move(newCircle));
    }
    else
    {
         auto newPolygon = std::make_unique<Polygon>();
         // Todo: Default Polygon
         newPolygon->setPolygon(QPolygonF());
         toReturn = newPolygon.get();
         transform->addChild(std::move(newPolygon));
    }
    if (node and node->isGroup())
    {
        node->asGroup()->addChild(std::move(transform));
        return toReturn;
    }
    else
    {
        m_canvas->setRoot(std::move(transform));
        return nullptr;
    }
}

QTransform SceneEditor::computeWorldTransform(Node *node)
{
    QTransform resultTransform;
    Node *current = node;
    std::vector<QTransform> stack;

    while (current)
    {
        if (current->type() == NodeType::Transform)
        {
            auto *transformNode = static_cast<Transform*>(current);
            QTransform local;
            local.rotateRadians(transformNode->rotationRadiant());
            local.translate(transformNode->position().x(), transformNode->position().y());
            stack.push_back(local);
        }
        current = current->parent();
    }

    for (auto it = stack.rbegin(); it != stack.rend(); it++)
    {
        resultTransform *= *it;
    }
    return resultTransform;
}

void SceneEditor::propagateChangeUp(Node *node)
{
    if(!node) return;

    Node* curr = node;
    while (curr)
    {
        curr->setDirty();
        curr = curr->parent();
    }
}

void SceneEditor::changeRadius()
{
    Circle *circle = static_cast<Circle*>(m_canvas->pickedNode());
    bool ok;
    double value = QInputDialog::getDouble(m_canvas, "Set Radius", "Radius", circle->radius(), 10, 2147483647, 1, &ok);

    if (ok)
    {
        circle->setRadius(value);
    }
}

void SceneEditor::changePosition()
{
    if (!m_canvas->pickedNode()) return;

   Group *parent = m_canvas->pickedNode()->parent();
   // Get current worldPosition
   QPointF worldPosition = computeWorldTransform(m_canvas->pickedNode()).map(QPointF(0,0));

   // Prompt user for new worldPosition
   bool okX;
   bool okY;
   double valueX = QInputDialog::getDouble(m_canvas, "Set x", "x-coordinate", worldPosition.x(), -2147483647, 2147483647, 1, &okX);
   double valueY = QInputDialog::getDouble(m_canvas, "Set y", "y-coordinate", worldPosition.y(), -2147483647, 2147483647, 1, &okY);

   if (!okX or !okY) return;

   if(m_canvas->pickedNode()->type() == NodeType::Transform)
   {
        auto transform = static_cast<Transform*>(m_canvas->pickedNode());
        transform->setPosition({valueX, valueY});
        return;
   }

   // Calculate and set offset for new transform node
   worldPosition = QPointF(valueX - worldPosition.x(), -(valueY - worldPosition.y()));
   auto transform = std::make_unique<Transform>();
   transform->setPosition(worldPosition);

   if (m_canvas->pickedNode()->type() == NodeType::Circle)
   {
        auto circle = static_cast<Circle*>(m_canvas->pickedNode());
        auto newCircle = std::make_unique<Circle>();
        newCircle->setRadius(circle->radius());
        transform->addChild(std::move(newCircle));
   }
   else
   {
        auto polygon = static_cast<Polygon*>(m_canvas->pickedNode());
        auto newPolygon = std::make_unique<Polygon>();
        newPolygon->setPolygon(polygon->polygon());
        transform->addChild(std::move(newPolygon));
   }

   if (!parent)
   {
       m_canvas->setRoot(std::move(transform));
   }
   else
   {
       parent->removeChild(m_canvas->pickedNode());
       parent->addChild(std::move(transform));
   }
}
