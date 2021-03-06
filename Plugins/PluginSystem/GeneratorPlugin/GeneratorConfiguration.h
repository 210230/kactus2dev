//-----------------------------------------------------------------------------
// File: GeneratorConfiguration.h
//-----------------------------------------------------------------------------
// Project: Kactus2
// Author: Esko Pekkarinen
// Date: 23.02.2015
//
// Description:
// Container class for generator configuration.
//-----------------------------------------------------------------------------

#ifndef GENERATORCONFIGURATION_H
#define GENERATORCONFIGURATION_H

#include <QString>
#include <QMap>
#include <QSharedPointer>

#include "ViewSelection.h"
#include "FileOutput.h"
#include <Plugins/common/HDLParser/HDLComponentParser.h>
#include <Plugins/common/HDLParser/HDLDesignParser.h>

//-----------------------------------------------------------------------------
//! Container class for generator configuration.
//-----------------------------------------------------------------------------
class GeneratorConfiguration : public QObject
{
    Q_OBJECT

public:

	//! The constructor.
    GeneratorConfiguration(QSharedPointer<ViewSelection> viewSelection,
        HDLComponentParser* componentParser,
        HDLDesignParser* designParser);

	//! The destructor.
    ~GeneratorConfiguration();
    
    /*!
     *  Checks if the generation configuration is valid.
     *
     *      @param [out] warning   The stated reason for not accepting.
     */
    bool validSelections(QString &warning);
    
    /*!
     *  Parses the documents so that we know what will be generated.
     */
    void parseDocuments();
	
    /*!
     *  Gets the view selection data.
     */
	QSharedPointer<ViewSelection> getViewSelection() const;
	
    /*!
     *  Gets the file output data.
     */
	QSharedPointer<FileOuput> getFileOuput() const;

    /*!
     *  Sets true for generating, false for not generating.
     */
    void setInterfaceGeneration(bool shouldGenerate);

    /*!
     *  Returns true for generating, false for not generating.
     */
    bool getInterfaceGeneration() const;

    /*!
     *  Sets true for generating, false for not generating.
     */
    void setMemoryGeneration(bool shouldGenerate);

    /*!
     *  Returns true for generating, false for not generating.
     */
    bool getMemoryGeneration() const;

signals:
	
    /*!
     *  Emitted when output files have changed.
     */
	void outputFilesChanged() const;

private:

	// Disable copying.
	GeneratorConfiguration(GeneratorConfiguration const& rhs);
	GeneratorConfiguration& operator=(GeneratorConfiguration const& rhs);

    //! The view selection configuration.
    QSharedPointer<ViewSelection> viewSelection_;
    //! The file output configuration.
    QSharedPointer<FileOuput> fileOutput_;

    //! The parsers used to parse IP-XACT for data usable in generation.
    HDLComponentParser* componentParser_;
    HDLDesignParser* designParser_;

    //! If true, interfaces should be utilized in generation, else it is false.
    bool generateInterface_;
    //! If true, definitions for registers are generated as well, else it is false.
    bool generateMemory_;
};

#endif // GENERATORCONFIGURATION_H
