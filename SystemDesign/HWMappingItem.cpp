//-----------------------------------------------------------------------------
// File: HWMappingItem.cpp
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Joni-Matti M��tt�
// Date: 30.4.2012
//
// Description:
// Graphics item for visualizing the underlying HW in system designs.
//-----------------------------------------------------------------------------

#include "HWMappingItem.h"

#include "../EndpointDesign/SystemMoveCommands.h"

#include "SystemDesignDiagram.h"
#include "SWCompItem.h"
#include "SWPortItem.h"
#include "SWConnection.h"

#include <LibraryManager/libraryinterface.h>

#include <common/GenericEditProvider.h>
#include <common/layouts/VStackedLayout.h>

#include <models/component.h>

#include <QBrush>
#include <QUndoCommand>

//-----------------------------------------------------------------------------
// Function: HWMappingItem::HWMappingItem()
//-----------------------------------------------------------------------------
HWMappingItem::HWMappingItem(LibraryInterface* libInterface,
                             QSharedPointer<Component> component,
                             QString const& instanceName,
                             QString const& displayName,
                             QString const& description,
                             QMap<QString, QString> const& configurableElementValues,
                             unsigned int id)
    : SWComponentItem(QRectF(-WIDTH / 2, 0, WIDTH, 0), libInterface, component, instanceName,
                      displayName, description, configurableElementValues, 0),
      id_(id),
      oldStack_(0),
      swComponents_(),
      oldPos_()
{
    setFlag(ItemIsMovable);
    
    updateComponent();
    updateItemPositions();
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::~HWMappingItem()
//-----------------------------------------------------------------------------
HWMappingItem::~HWMappingItem()
{
    // Remove this item from the column where it resides.
    IComponentStack* column = dynamic_cast<IComponentStack*>(parentItem());

    if (column != 0)
    {
        column->removeItem(this);
    }
}

//-----------------------------------------------------------------------------
// Function: mousePressEvent()
//-----------------------------------------------------------------------------
void HWMappingItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ComponentItem::mousePressEvent(event);
    setZValue(1001.0);

    oldPos_ = scenePos();
    oldStack_ = dynamic_cast<IComponentStack*>(parentItem());

    // Begin the position update for the connections.
    foreach (QGraphicsItem* item, childItems())
    {
        if (item->type() == SWPortItem::Type)
        {
            SWPortItem* port = qgraphicsitem_cast<SWPortItem*>(item);

            foreach (SWConnection* conn, port->getConnections())
            {
                conn->beginUpdatePosition();
            }
        }
    }
}

//-----------------------------------------------------------------------------
// Function: mouseMoveEvent()
//-----------------------------------------------------------------------------
void HWMappingItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    // Discard mouse move if the diagram is protected.
    if (static_cast<DesignDiagram*>(scene())->isProtected())
    {
        return;
    }

    setConnectionUpdateDisabled(true);

    ComponentItem::mouseMoveEvent(event);

    if (oldStack_ != 0)
    {
        setPos(parentItem()->mapFromScene(oldStack_->mapStackToScene(pos())));

        IComponentStack* column = dynamic_cast<IComponentStack*>(parentItem());
        Q_ASSERT(column != 0);
        column->onMoveItem(this);
    }

    setConnectionUpdateDisabled(false);
}

//-----------------------------------------------------------------------------
// Function: mouseReleaseEvent()
//-----------------------------------------------------------------------------
void HWMappingItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    ComponentItem::mouseReleaseEvent(event);
    setZValue(0.0);

    if (oldStack_ != 0)
    {
        IComponentStack* column = dynamic_cast<IComponentStack*>(parentItem());
        Q_ASSERT(column != 0);
        column->onReleaseItem(this);

        QSharedPointer<QUndoCommand> cmd;

        if (scenePos() != oldPos_)
        {
            cmd = QSharedPointer<QUndoCommand>(new SystemItemMoveCommand(this, oldPos_, oldStack_));
        }
        else
        {
            cmd = QSharedPointer<QUndoCommand>(new QUndoCommand());
        }

        // End the position update for the connections and clear the list.
        foreach (QGraphicsItem* item, childItems())
        {
            if (item->type() == SWPortItem::Type)
            {
                SWPortItem* port = qgraphicsitem_cast<SWPortItem*>(item);

                foreach (SWConnection* conn, port->getConnections())
                {
                    conn->endUpdatePosition(cmd.data());
                }
            }
        }
        
        // Add the undo command to the edit stack only if it has at least some real changes.
        if (cmd->childCount() > 0 || scenePos() != oldPos_)
        {
            static_cast<SystemDesignDiagram*>(scene())->getEditProvider().addCommand(cmd, false);
        }

        oldStack_ = 0;
    }
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::getHeight()
//-----------------------------------------------------------------------------
qreal HWMappingItem::getHeight() const
{
    // Calculate the minimum height based on the stack contents.
    qreal stackHeight = getComponentStackHeight();

    // Determine the largest one from the stack height, minimum height (empty) and the height
    // calculated by the base class.
    return std::max<qreal>(std::max<qreal>(stackHeight, MIN_HEIGHT), SWComponentItem::getHeight());
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::addItem()
//-----------------------------------------------------------------------------
void HWMappingItem::addItem(ComponentItem* item, bool load)
{
    item->setParentItem(this);
    item->setFlag(ItemStacksBehindParent, false);

    swComponents_.append(item);
    VStackedLayout::updateItemMove(swComponents_, item, TOP_MARGIN, SPACING);
    VStackedLayout::setItemPos(swComponents_, item, 0.0, TOP_MARGIN, SPACING);
    updateItemPositions();

    emit contentChanged();
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::removeItem()
//-----------------------------------------------------------------------------
void HWMappingItem::removeItem(ComponentItem* item)
{
    swComponents_.removeAll(item);
    item->setParentItem(0);
    updateItemPositions();

    emit contentChanged();
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::onMoveItem()
//-----------------------------------------------------------------------------
void HWMappingItem::onMoveItem(ComponentItem* item)
{
    VStackedLayout::updateItemMove(swComponents_, item, TOP_MARGIN, SPACING);
    offsetPortPositions(getComponentStackHeight() + SPACING);
    updateSize();

    // Check if the item is not overlapping the HW mapping item enough.
    QRectF intersection = sceneBoundingRect().intersected(item->sceneBoundingRect());

    if (item->rect().height() - intersection.height() >= 3 * GridSize)
    {
        swComponents_.removeAll(item);

        // Let the parent component stack handle the mouse move.
        SystemColumn* parentStack = static_cast<SystemColumn*>(parentItem());
        Q_ASSERT(parentStack != 0);
        
        QPointF newPos = parentStack->mapStackFromScene(item->scenePos());
        item->setParentItem(parentStack);
        item->setPos(newPos);
        item->setFlag(ItemStacksBehindParent);

        updateItemPositions();
        setZValue(0.0);

        parentStack->onMoveItem(item);
        return;
    }

    setZValue(1001.0);
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::onReleaseItem()
//-----------------------------------------------------------------------------
void HWMappingItem::onReleaseItem(ComponentItem* item)
{
    setZValue(0.0);
    VStackedLayout::setItemPos(swComponents_, item, 0.0, TOP_MARGIN, SPACING);
    offsetPortPositions(getComponentStackHeight() + SPACING);
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::updateItemPositions()
//-----------------------------------------------------------------------------
void HWMappingItem::updateItemPositions()
{
    // Just update the item positions.
    VStackedLayout::updateItemPositions(swComponents_, 0.0, TOP_MARGIN, SPACING);
    offsetPortPositions(getComponentStackHeight() + SPACING);
    updateSize();
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::mapStackToScene()
//-----------------------------------------------------------------------------
QPointF HWMappingItem::mapStackToScene(QPointF const& pos) const
{
    return mapToScene(pos);
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::mapStackFromScene()
//-----------------------------------------------------------------------------
QPointF HWMappingItem::mapStackFromScene(QPointF const& pos) const
{
    return mapFromScene(pos);
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::isItemAllowed()
//-----------------------------------------------------------------------------
bool HWMappingItem::isItemAllowed(ComponentItem* item) const
{
    return (item->type() == SWCompItem::Type);
}

//-----------------------------------------------------------------------------
// Function: HWMappingItem::getComponentStackHeight()
//-----------------------------------------------------------------------------
qreal HWMappingItem::getComponentStackHeight() const
{
    qreal stackHeight = TOP_MARGIN + BOTTOM_MARGIN;

    if (!swComponents_.isEmpty())
    {
        foreach (ComponentItem* item, swComponents_)
        {
            stackHeight += item->boundingRect().height();
        }

        stackHeight += (swComponents_.size() - 1) * SPACING;
    }

    return stackHeight;
}

void HWMappingItem::updateComponent()
{
    ComponentItem::updateComponent();

    VLNV* vlnv = componentModel()->getVlnv();

    // Check whether the component is packaged (valid vlnv) or not.
    if (vlnv->isValid())
    {
        if (!getLibraryInterface()->contains(*vlnv))
        {
            setBrush(QBrush(QColor(0xe8, 0xc5, 0xc5)));
        }
        else
        {
            setBrush(QBrush(QColor(0xa5,0xc3,0xef)));
        }
    }
    else
    {
        setBrush(QBrush(QColor(217, 217, 217)));
    }
}