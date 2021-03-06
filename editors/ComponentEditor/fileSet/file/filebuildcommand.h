//-----------------------------------------------------------------------------
// File: filebuildcommand.h
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Antti Kamppi
// Date: 7.2.2011
//
// Description:
// FileBuildCommand is a group box for editing buildCommand of a file.
//-----------------------------------------------------------------------------

#ifndef FILEBUILDCOMMAND_H
#define FILEBUILDCOMMAND_H

#include <QCheckBox>
#include <QFileInfo>
#include <QGridLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QSharedPointer>

class LibraryInterface;
class BuildCommand;
class File;
class Component;
class ExpressionEditor;
class ParameterFinder;
class ExpressionParser;

//-----------------------------------------------------------------------------
//! FileBuildCommand is a group box for editing buildCommand of a file.
//-----------------------------------------------------------------------------
class FileBuildCommand : public QGroupBox
{
	Q_OBJECT

public:

	/*!
     *  The constructor.
	 *
	 *      @param [in] file                The file that is being edited.
     *      @param [in] componentPath       The path to the component containing the file.
     *      @param [in] parameterFinder     The used parameter finder.
     *      @param [in] expressionParser    Parser for calculating expressions.
     *      @param [in] parent              The owner of this widget.
	 */
    FileBuildCommand(QSharedPointer<File> file, QString const& componentPath,
        QSharedPointer<ParameterFinder> parameterFinder,
        QSharedPointer<ExpressionParser> expressionParser, QWidget *parent);

	//! The destructor.
	virtual ~FileBuildCommand();

	/*!
     *  Restore the changes from the model to the editor.
	 */
	void refresh();

signals:

	//! Emitted when contents of the widget change.
	void contentChanged();

    /*!
     *  Increase the number of references made to the selected parameter.
     *
     *      @param [in] id  ID of the selected parameter.
     */
    void increaseReferences(QString id);

    /*!
     *  Decrease the number of references made to the selected parameter.
     *
     *      @param [in] id  ID of the selected parameter.
     */
    void decreaseReferences(QString id);

private slots:

	//! Handler for command changes.
    void onCommandChanged();

    void updateFileBuildCommand();

    //! Handler for flag changes.
    void onFlagsChanged();

    //! Handler for target changes.
    void onTargetChanged();

    void onReplaceDefaultChanged();

    void onBrowseTarget();

private:

	//! No copying. No assignment.
	FileBuildCommand(const FileBuildCommand& other);
    void setupLayout();

    FileBuildCommand& operator=(const FileBuildCommand& other);

    /*!
     *  Get the formatted value for an expression.
     *
     *      @param [in] expression  The selected expression.
     *
     *      @return The formatted expression.
     */
    QString formattedValueFor(QString const& expression) const;

    //-----------------------------------------------------------------------------
    // Data.
    //-----------------------------------------------------------------------------

    //! The file whose build command to edit.
    QSharedPointer<File> file_;

	//! The file's buildCommand.
    QSharedPointer<BuildCommand> buildCommand_; 

    //! Path to the containing component.
    QString componentPath_;

	//! Editor to set file's build command.
	QLineEdit commandEditor_;

	//! Editor to set build command's flags.
	QLineEdit flagsEditor_;

	//! Expression editor to set build command's replaceDefaultFlags setting.
    ExpressionEditor* replaceDefaultEditor_;

	//! Editor to set build command's target file.
	QLineEdit targetEditor_;

    QPushButton browseTargetButton_;

    //! The used expression parser.
    QSharedPointer<ExpressionParser> expressionParser_;
};

#endif // FILEBUILDCOMMAND_H
