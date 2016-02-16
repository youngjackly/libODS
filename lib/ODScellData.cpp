/*
** ODScellData.cpp
**
** Copyright © libODS Development Team, 2015.
** This file is part of libODS (https://github.com/nweyand/libODS/)
**
** libODS is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later or later as published by the Free Software
** Foundation and appearing in the file LICENSE included in the
** packaging of this file.
**
** libODS is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with libODS; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "ODScellData.h"

namespace ODSlib
{

ODScellData::ODScellData(QDomElement &element) :
	m_pFormula( NULL ),
	m_pText( NULL ),
	m_bHasCalcExtValueType( false ),
	m_oAssociated( element ),
	m_eType( CellType::unknown )
{
}

ODScellData::~ODScellData()
{
	if ( m_pFormula )
		delete m_pFormula;

	if ( m_pText )
		delete m_pText;
}

void ODScellData::clear()
{
	m_eType = CellType::unknown;

	if ( m_pFormula )
	{
		delete m_pFormula;
		m_pFormula = NULL;
	}

	if ( m_pText )
	{
		delete m_pText;
		m_pText = NULL;
	}

	m_bHasCalcExtValueType = false;

	m_nValue = 0;

	// remove all children and attributes while retaining the XML node type
	while ( m_oAssociated.hasChildNodes() )
	{
		m_oAssociated.removeChild( m_oAssociated.firstChild() );
	}
}

CellType::Type ODScellData::type() const
{
	return m_eType;
}

float ODScellData::value() const
{
	switch ( m_eType )
	{
	case CellType::boolean:
	case CellType::number:
	case CellType::percentage:
	case CellType::currency:
		return m_nValue;

	default:
		return 0.0f;
	}
}

bool ODScellData::setValue(float value)
{
	bool bReturn = false;

	switch ( m_eType )
	{
	case CellType::number:
	case CellType::currency:
	case CellType::percentage:
		m_nValue = value;
		bReturn = true;
		break;

	case CellType::boolean:
		m_nValue = value;
		bReturn = true;
		break;

	default:
		break;
	}

	refreshText();
	return bReturn;
}

QString ODScellData::contentString() const
{
	switch ( m_eType )
	{
	case CellType::stringContent:
		return m_sData;

	case CellType::date:
		return m_sData;

	case CellType::time:
		return m_sData;

	default:
		return QString();
	}
}

bool ODScellData::setContentString(const QString &value)
{
	bool bReturn = false;

	switch ( m_eType )
	{
	case CellType::stringContent:
		m_sData = value;
		bReturn = true;
		break;

	case CellType::date:
		m_sData = value;
		bReturn = true;
		break;

	case CellType::time:
		m_sData = value;
		bReturn = true;
		break;

	default:
		break;
	}

	refreshText();
	return bReturn;
}

void ODScellData::parse()
{
	// read the type
	if ( !parseType( ODS_ATTR_OFFICE_VAL_T ) )
	{
		// use the calcext extension as a backup in case there is no office value attribute
		parseType( ODS_ATTR_CALCEXT_VAL_T );
	}

	// Important to know when changing the type. We don't want to generate conflicts by missing one type attribute.
	m_bHasCalcExtValueType = m_oAssociated.hasAttribute( ODS_ATTR_CALCEXT_VAL_T );


	// extract the text section from cells that have it
	if ( m_pText )
	{
		delete m_pText;
		m_pText = NULL;
	}
	QDomNodeList children = m_oAssociated.elementsByTagName( ODS_TAG_TEXT_P );
	if ( children.size() )
	{
		QDomElement element = children.at(0).toElement();
		if ( !element.isNull() )
		{
			m_pText = new QString( element.text() );
		}
	}


	// extract the formula section from cells that have it
	if ( m_pFormula )
	{
		delete m_pFormula;
		m_pFormula = NULL;
	}
	if ( m_oAssociated.hasAttribute( ODS_ATTR_TBL_FORMULA ) )
	{
		m_pFormula = new QString( m_oAssociated.attribute( ODS_ATTR_TBL_FORMULA ) );
	}


	// now comes the data extraction (list sorted approx by number of occurrences)
	switch ( m_eType )
	{
	case CellType::number:
	case CellType::currency:
	case CellType::percentage:
	{
		QString value = m_oAssociated.attribute(ODS_ATTR_OFFICE_VALUE);

		bool bOK;
		m_nValue = value.toFloat(&bOK);

		if (!bOK)
		{
			m_eType = CellType::error;
		}
	}
		break;

	case CellType::stringContent:
	{
		if ( m_pText )
		{
			m_sData = *m_pText;
		}
		else
		{
			m_sData = QString();
		}
	}
		break;

	case CellType::none:
	case CellType::unknown:
	{
		m_sData = QString();
	}
		break;

	case CellType::boolean:
	{
		QString value = m_oAssociated.attribute(ODS_ATTR_OFFICE_BOOLVAL);

		bool bOK;
		m_nValue = value.toFloat(&bOK);

		if (!bOK)
		{
			m_eType = CellType::error;
		}
	}
		break;

	case CellType::date:
	{
		m_sData = m_oAssociated.attribute(ODS_ATTR_OFFICE_DATEVAL);
	}
		break;

	case CellType::time:
	{
		m_sData = m_oAssociated.attribute(ODS_ATTR_OFFICE_TIMEVAL);
	}
		break;

	default:
		break;
	}
}

bool ODScellData::parseType(const QString& sAttribute)
{
	// if there is no such attribute, an empty string is returned
	QString sType = m_oAssociated.attribute( sAttribute );
	bool bReturn = true;

	if ( sType.isEmpty() )
	{
		m_eType = CellType::none;
		bReturn = false;
	}
	else if ( !sType.compare( ODS_ATTRVAL_OFFICE_VAL_T_FLOAT ) )
	{
		m_eType = CellType::number;
	}
	else if ( !sType.compare( ODS_ATTRVAL_OFFICE_VAL_T_STRING ) )
	{
		m_eType = CellType::stringContent;
	}
	else if ( !sType.compare( ODS_ATTRVAL_OFFICE_VAL_T_CURRENCY ) )
	{
		m_eType = CellType::currency;
	}
	else if ( !sType.compare( ODS_ATTRVAL_OFFICE_VAL_T_PERCENTAGE ) )
	{
		m_eType = CellType::percentage;
	}
	else if ( !sType.compare( ODS_ATTRVAL_OFFICE_VAL_T_DATE ) )
	{
		m_eType = CellType::date;
	}
	else if ( !sType.compare( ODS_ATTRVAL_OFFICE_VAL_T_TIME ) )
	{
		m_eType = CellType::time;
	}
	else if ( !sType.compare( ODS_ATTRVAL_OFFICE_VAL_T_BOOL ) )
	{
		m_eType = CellType::boolean;
	}
	else
	{
		// there is a cell type but it is unknown
		m_eType = CellType::unknown;
	}

	return bReturn;
}

void ODScellData::refreshText()
{
	switch ( m_eType )
	{
	case CellType::number:
	case CellType::percentage:
	case CellType::stringContent:
	case CellType::date:
	case CellType::time:
		if ( !m_pText )
		{
			m_pText = new QString();
		}
		break;

	default:
		if ( m_pText )
		{
			delete m_pText;
			m_pText = NULL;
		}
		break;
	}

	switch ( m_eType )
	{
	case CellType::number:
		m_pText->setNum(m_nValue);
		break;
	case CellType::percentage:
		m_pText->setNum(100 * m_nValue, 'f', 2);
		m_pText->append(" %");
		break;

	case CellType::stringContent:
		m_pText->clear();
		m_pText->append( m_sData );
		break;

	case CellType::date:
		m_pText->clear();
		m_pText->append( m_sData );
		break;

	case CellType::time:
		m_pText->clear();
		m_pText->append( m_sData );
		break;

	default:
		break;
	}
}

} // namespace ODSlib
