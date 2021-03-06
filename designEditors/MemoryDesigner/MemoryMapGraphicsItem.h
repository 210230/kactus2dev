//-----------------------------------------------------------------------------
// File: MemoryMapGraphicsItem.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Mikko Teuho
// Date: 09.08.2016
//
// Description:
// Graphics item for visualizing a memory map in the memory designer.
//-----------------------------------------------------------------------------

#ifndef MEMORYMAPGRAPHICSITEM_H
#define MEMORYMAPGRAPHICSITEM_H

#include <common/graphicsItems/GraphicsItemTypes.h>

#include <designEditors/MemoryDesigner/MainMemoryGraphicsItem.h>

class MemoryItem;
class ConnectivityComponent;
class AddressBlockGraphicsItem;

#include <QSharedPointer>

//-----------------------------------------------------------------------------
//! Graphics item for visualizing a memory map in the memory designer.
//-----------------------------------------------------------------------------
class MemoryMapGraphicsItem : public MainMemoryGraphicsItem
{

public:

    //! Type of the memory map graphics item.
    enum { Type = GFX_TYPE_MEMORY_ITEM };

    /*!
     *  The constructor.
     *
     *      @param [in] memoryItem              Memory item containing memory map data.
     *      @param [in] filterAddressBlocks     Value for filtering memory map address blocks.
     *      @param [in] filterRegisters         Value for filtering address block registers.
     *      @param [in] filterFields            Value for filtering register fields.
     *      @param [in] containingInstance      Instance containing the memory map.
     *      @param [in] parent                  The parent item.
     */
    MemoryMapGraphicsItem(QSharedPointer<MemoryItem> memoryItem, bool filterAddressBlocks, bool filterRegisters,
        bool filterFields, QSharedPointer<ConnectivityComponent> containingInstance, QGraphicsItem* parent = 0);

	/*!
     *  The destructor.
     */
    ~MemoryMapGraphicsItem();

    /*!
     *  Get the type of the memory item.
     */
    int type() const { return Type; }

    /*!
     *  Compress the item and the contained sub items.
     *
     *      @param [in] movedConnections    Connection items that have already been moved.
     */
    virtual void condenseItemAndChildItems(QSharedPointer<QVector<MemoryConnectionItem*> > movedConnections);

    /*!
     *  Compress the memory map item.
     *
     *      @param [in] movedConnections    Connection items that have already been moved.
     */
    void compressMapItem(QSharedPointer<QVector<MemoryConnectionItem*> > movedConnections);

    /*!
     *  Get the minimum required height of the memory map item to fit the selected memory connection.
     *
     *      @param [in] connectionBaseAddress   Base address of the selected memory connection.
     *      @param [in] connectionEndAddress    End address of the selected memory connection.
     *
     *      @return The minimum required height of the memory map item.
     */
    virtual qreal getMinimumRequiredHeight(quint64 connectionBaseAddress, quint64 connectionEndAddress) const;

    /*!
     *  Check if the memory map is connected to any of the selected address spaces.
     *
     *      @param [in] spaceItems  List of the selected address space graphics items.
     *
     *      @return True, if the memory map is connected to any of the selected address spaces.
     */
    bool isConnectedToSpaceItems(QVector<MainMemoryGraphicsItem*> spaceItems) const;

    /*!
     *  Change the width of this item and the contained register graphics items.
     *
     *      @param [in] widthChange     The change in width.
     */
    void changeWidth(qreal widthChange);

    /*!
     *  Get the maximum needed change in width to fully display the name labels of all the field items within the
     *  address block items.
     *
     *      @return The maximum needed change in width to display the name labels of all the field items.
     */
    qreal getMaximumNeededChangeInFieldWidth() const;

private:
    // Disable copying.
    MemoryMapGraphicsItem(MemoryMapGraphicsItem const& rhs);
    MemoryMapGraphicsItem& operator=(MemoryMapGraphicsItem const& rhs);

    /*!
     *  Get the ranges of the selected memory map.
     *
     *      @param [in] memoryItem  Memory item containing the selected memory map.
     *
     *      @return The memory range. First is base address, second is last address.
     */
    QPair<quint64, quint64> getMemoryRanges(QSharedPointer<MemoryItem> memoryItem) const;

    /*!
     *  Set the label positions.
     */
    virtual void setLabelPositions();

    /*!
     *  Create a new address block graphics item.
     *
     *      @param [in] subMemoryItem   Memory item containing address block data.
     *      @param [in] isEmpty         Boolean value for an empty address block.
     *
     *      @return The created address block graphics item.
     */
    virtual MemoryDesignerChildGraphicsItem* createNewSubItem(QSharedPointer<MemoryItem> subMemoryItem,
        bool isEmpty);

    /*!
     *  Create an empty address block graphics item.
     *
     *      @param [in] beginAddress    Base address of the empty address block graphics item.
     *      @param [in] rangeEnd        End address of the empty address block graphics item.
     *
     *      @return The created address block graphics item.
     */
    virtual MemoryDesignerChildGraphicsItem* createEmptySubItem(quint64 beginAddress, quint64 rangeEnd);

    /*!
     *  Get the minimum height for the memory map sub items.
     *
     *      @return The minimum height for the memory map sub items.
     */
    int getMinimumHeightForSubItems() const;

    /*!
     *  Setup sub items for the memory map.
     *
     *      @param [in] blockXPosition  X coordinate of the memory sub items.
     *      @param [in] memoryItem      The memory map memory item.
     */
    void setupSubItems(qreal blockXPosition, QSharedPointer<MemoryItem> memoryItem);

    /*!
     *  Get the width of the memory map sub items.
     *
     *      @return Width of the memory map sub items.
     */
    qreal getSubItemWidth() const;

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

    //! The address unit bits of a memory map.
    QString addressUnitBits_;

    //! Value for filtering address blocks.
    bool filterAddressBlocks_;

    //! Value for filtering address block registers.
    bool filterRegisters_;

    //! Value for filtering register fields.
    bool filterFields_;

    //! Width of the contained memory sub items.
    qreal subItemWidth_;
};

//-----------------------------------------------------------------------------

#endif // MEMORYMAPGRAPHICSITEM_H
