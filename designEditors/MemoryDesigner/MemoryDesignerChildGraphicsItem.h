//-----------------------------------------------------------------------------
// File: MemoryDesignerChildGraphicsItem.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Mikko Teuho
// Date: 19.09.2016
//
// Description:
// Parent item for visualizing memory child items i.e. address blocks and segments.
//-----------------------------------------------------------------------------

#ifndef MEMORYDESIGNERCHILDGRAPHICSITEM_H
#define MEMORYDESIGNERCHILDGRAPHICSITEM_H

#include <designEditors/MemoryDesigner/MemoryDesignerGraphicsItem.h>

#include <QSharedPointer>
#include <QGraphicsItem>

//-----------------------------------------------------------------------------
//! Parent item for visualizing memory child items i.e. address blocks and segments.
//-----------------------------------------------------------------------------
class MemoryDesignerChildGraphicsItem : public MemoryDesignerGraphicsItem
{

public:

    /*!
     *  The constructor.
     *
     *      @param [in] itemName        Name of the memory item.
     *      @param [in] toolTipType     The type of the memory item.
     *      @param [in] baseAddress     Base address of the memory item.
     *      @param [in] range           Range of the memory item.
     *      @param [in] blockWidth      Width of the memory item.
     *      @param [in] instanceName    Name of the containing component instance.
     *      @param [in] parent          The parent item.
     */
    MemoryDesignerChildGraphicsItem(QString const& itemName, QString const& toolTipType, quint64 baseAddress,
        quint64 range, qreal blockWidth, QString const& instanceName, QGraphicsItem* parent);

	/*!
     *  The destructor.
     */
    virtual ~MemoryDesignerChildGraphicsItem();

    /*!
     *  Get the type of the memory graphics item.
     */
    virtual int type() const  = 0;

    /*!
     *  Change the address range of the memory item.
     *
     *      @param [in] offset  The offset of the parent item.
     */
    virtual void changeAddressRange(quint64 offset);

    /*!
     *  Fit the name label to the available space.
     */
    void fitNameLabel();

protected:

    /*!
     *  Set the colors for the memory item.
     *
     *      @param [in] itemColor       The main color for the memory item.
     *      @param [in] itemIsEmpty     Boolean for determining empty memory item.
     */
    void setColors(QColor itemColor, bool itemIsEmpty);

private:
    // Disable copying.
    MemoryDesignerChildGraphicsItem(MemoryDesignerChildGraphicsItem const& rhs);
    MemoryDesignerChildGraphicsItem& operator=(MemoryDesignerChildGraphicsItem const& rhs);

    /*!
     *  Set colors for ranges in an empty sub graphics item.
     *
     *      @param [in] emptyItemRangeColour    The color for the empty sub graphics item ranges.
     */
    virtual void setEmptyItemRangeColors(QColor emptyItemRangeColour);

    /*!
     *  Get the width of the available area used by the memory sub item.
     *
     *      @return The width of the available area used by the memory sub item.
     */
    virtual qreal getItemWidth() const;
};

//-----------------------------------------------------------------------------

#endif // MEMORYDESIGNERCHILDGRAPHICSITEM_H
