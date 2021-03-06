//-----------------------------------------------------------------------------
// File: MemoryDesignerChildGraphicsItem.cpp
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Mikko Teuho
// Date: 19.09.2016
//
// Description:
// Parent item for visualizing memory child items i.e. address blocks and segments.
//-----------------------------------------------------------------------------

#include "MemoryDesignerChildGraphicsItem.h"

#include <QBrush>
#include <QFont>

//-----------------------------------------------------------------------------
// Function: MemoryDesignerChildGraphicsItem::MemoryDesignerChildGraphicsItem()
//-----------------------------------------------------------------------------
MemoryDesignerChildGraphicsItem::MemoryDesignerChildGraphicsItem(QString const& itemName,
    QString const& toolTipType, quint64 baseAddress, quint64 range, qreal blockWidth, QString const& instanceName,
    QGraphicsItem* parent):
MemoryDesignerGraphicsItem(itemName, instanceName, parent)
{
    if (range == 1)
    {
        getRangeStartLabel()->hide();
    }

    setGraphicsRectangle(blockWidth, range);

    quint64 rangeEnd = baseAddress + range - 1;
    if (toolTipType.compare(QStringLiteral("Field")) != 0)
    {
        setupLabels(baseAddress, rangeEnd);
        setupToolTip(toolTipType);
    }
}

//-----------------------------------------------------------------------------
// Function: MemoryDesignerChildGraphicsItem::~MemoryDesignerChildGraphicsItem()
//-----------------------------------------------------------------------------
MemoryDesignerChildGraphicsItem::~MemoryDesignerChildGraphicsItem()
{

}

//-----------------------------------------------------------------------------
// Function: MemoryDesignerChildGraphicsItem::setColors()
//-----------------------------------------------------------------------------
void MemoryDesignerChildGraphicsItem::setColors(QColor itemColor, bool itemIsEmpty)
{
    QBrush itemBrush(itemColor);

    if (itemIsEmpty)
    {
        itemBrush.setColor(QColor("whiteSmoke"));

        QColor emptyTextColor (180, 180, 180);
        getNameLabel()->setDefaultTextColor(emptyTextColor);
        setEmptyItemRangeColors(emptyTextColor);
    }
    setBrush(itemBrush);
}

//-----------------------------------------------------------------------------
// Function: MemoryDesignerChildGraphicsItem::setEmptyItemRangeColors()
//-----------------------------------------------------------------------------
void MemoryDesignerChildGraphicsItem::setEmptyItemRangeColors(QColor emptyItemRangeColour)
{
    getRangeStartLabel()->setDefaultTextColor(emptyItemRangeColour);
    getRangeEndLabel()->setDefaultTextColor(emptyItemRangeColour);
}

//-----------------------------------------------------------------------------
// Function: MemoryDesignerChildGraphicsItem::changeAddressRange()
//-----------------------------------------------------------------------------
void MemoryDesignerChildGraphicsItem::changeAddressRange(quint64 offset)
{
    quint64 newBaseAddress = getBaseAddress() + offset;
    quint64 newLastAddress = getLastAddress() + offset;

    setupLabels(newBaseAddress, newLastAddress);
}

//-----------------------------------------------------------------------------
// Function: MemoryDesignerChildGraphicsItem::fitNameLabel()
//-----------------------------------------------------------------------------
void MemoryDesignerChildGraphicsItem::fitNameLabel()
{
    fitLabel(getNameLabel());
}

//-----------------------------------------------------------------------------
// Function: MemoryDesignerChildGraphicsItem::getItemWidth()
//-----------------------------------------------------------------------------
qreal MemoryDesignerChildGraphicsItem::getItemWidth() const
{
    return boundingRect().width();
}
