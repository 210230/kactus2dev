//-----------------------------------------------------------------------------
// File: ExpressionFormatter.h
//-----------------------------------------------------------------------------
// Project: Kactus 2
// Author: Mikko Teuho
// Date: 26.01.2015
//
// Description:
// Formatter for parameter expressions consisting of references.
//-----------------------------------------------------------------------------

#include "ExpressionFormatter.h"

#include <QStringList>
#include <QRegularExpression>

namespace
{
    const QRegularExpression NON_ALPHA_CHARACTERS("[^a-zA-Z0-9:_.]+");
}

//-----------------------------------------------------------------------------
// Function: ExpressionFormatter::ExpressionFormatter()
//-----------------------------------------------------------------------------
ExpressionFormatter::ExpressionFormatter(QSharedPointer<ParameterFinder> parameterFinder):
parameterFinder_(parameterFinder)
{

}

//-----------------------------------------------------------------------------
// Function: ExpressionFormatter::~ExpressionFormatter()
//-----------------------------------------------------------------------------
ExpressionFormatter::~ExpressionFormatter()
{

}

//-----------------------------------------------------------------------------
// Function: ExpressionFormatter::formatExpressionWithReference()
//-----------------------------------------------------------------------------
QString ExpressionFormatter::formatReferringExpression(QString const& expression) const
{
    QString formattedExpression = expression;

    foreach (QString const& valueID, expression.split(NON_ALPHA_CHARACTERS, QString::SkipEmptyParts))
    {
        if (parameterFinder_->hasId(valueID))
        {
            formattedExpression.replace(valueID, parameterFinder_->nameForId(valueID));
        }
    }

    return formattedExpression;
}
