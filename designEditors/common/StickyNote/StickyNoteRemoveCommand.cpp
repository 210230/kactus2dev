//-----------------------------------------------------------------------------
// File: FloatingItemRemoveCommand.h
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Esko Pekkarinen
// Date: 30.05.2014
//
// Description:
// Remove command for floating items.
//-----------------------------------------------------------------------------

#include "StickyNoteRemoveCommand.h"

#include <IPXACTmodels/VendorExtension.h>
#include <designEditors/common/DesignDiagram.h>
#include <designEditors/common/Association/AssociationRemoveCommand.h>

//-----------------------------------------------------------------------------
// Function: FloatingItemRemoveCommand()
//-----------------------------------------------------------------------------
StickyNoteRemoveCommand::StickyNoteRemoveCommand(StickyNote* noteItem, DesignDiagram* diagram, 
    QUndoCommand* parent) : 
    QUndoCommand(parent), note_(noteItem),
    diagram_(diagram), 
    del_(true)
{
    foreach(Association* association, noteItem->getAssociations())
    {
        new AssociationRemoveCommand(association, diagram, this);
    }
}

//-----------------------------------------------------------------------------
// Function: ~FloatingItemRemoveCommand()
//-----------------------------------------------------------------------------
StickyNoteRemoveCommand::~StickyNoteRemoveCommand()
{
    if (del_)
    {
        delete note_;
    }
}

//-----------------------------------------------------------------------------
// Function: undo()
//-----------------------------------------------------------------------------
void StickyNoteRemoveCommand::undo()
{
    diagram_->addItem(note_);
    del_ = false;

    emit addVendorExtension(note_->getVendorExtension());

    // Execute child commands.
    QUndoCommand::undo();
}

//-----------------------------------------------------------------------------
// Function: redo()
//-----------------------------------------------------------------------------
void StickyNoteRemoveCommand::redo()
{
    diagram_->removeItem(note_);
    del_ = true;

    emit removeVendorExtension(note_->getVendorExtension());

    QUndoCommand::redo();
}
