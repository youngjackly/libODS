/*
** ODScell.cpp
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

#include "ODScell.h"

#include "ODSprototypeXMLfamiliarData.h"
#include "ODSprototypeRepeatableData.h"
#include "ODScellData.h"

namespace ODSlib
{
ODScell::ODScell(QDomElement &element) :
	ODSprototypeXMLfamiliar( ODS_TAG_TEXT_P, element), // req due to virtual inheritance
	ODSprototypeRepeatable( ODS_TAG_TEXT_P, ODS_ATTR_TBL_CELL_REPEAT, element), // child: text; expecting repetitions for: cell
	m_pCellData( new ODScellData( element ) )
{

}

/*ODScell::ODScell(const ODScell &rhs) : pCellData(rhs.pCellData)
{

}

ODScell &ODScell::operator=(const ODScell &rhs)
{
	if (this != &rhs)
		pCellData.operator=(rhs.pCellData);
	return *this;
}*/

ODScell::~ODScell()
{
}

void ODScell::clear()
{
	m_pCellData->clear();
}

CellType::Type ODScell::type() const
{
	return m_pCellData->type();
}

float ODScell::value() const
{
	return m_pCellData->value();
}

bool ODScell::setValue(float value)
{
	// manage data
	bool bReturn1 = m_pCellData->setValue( value );
	bool bReturn2 = false;

	// manage XML
	switch ( m_pCellData->type() )
	{
	case CellType::number:
	case CellType::currency:
	case CellType::percentage:
		setAttribute( value, ODS_ATTR_OFFICE_VALUE );
		bReturn2 = true;
		break;

	case CellType::boolean:
		setAttribute( value, ODS_ATTR_OFFICE_BOOLVAL );
		bReturn2 = true;
		break;

	default:
		break;
	}

	refreshXMLText();
	return bReturn1 && bReturn2;
}

bool ODScell::hasText() const
{
	return m_pCellData->m_pText != NULL;
}

QString ODScell::text() const
{
	if ( hasText() )
		return *m_pCellData->m_pText;
	else
		return QString();
}

QString ODScell::contentString() const
{
	return m_pCellData->contentString();
}

bool ODScell::setContentString(const QString &value)
{
	// manage data
	bool bReturn1 = m_pCellData->setContentString(value);
	bool bReturn2 = false;

	// mange XML
	switch ( m_pCellData->type() )
	{
	case CellType::stringContent:
		// text node is updated by refreshXMLText();
		bReturn2 = true;
		break;

	case CellType::date:
		setAttribute( value, ODS_ATTR_OFFICE_DATEVAL );
		bReturn2 = true;
		break;

	case CellType::time:
		setAttribute( value, ODS_ATTR_OFFICE_TIMEVAL );
		bReturn2 = true;
		break;

	default:
		break;
	}

	refreshXMLText();
	return bReturn1 && bReturn2;
}

void ODScell::parse()
{
	m_pCellData->parse();
	m_pPXFData->m_bValid = true;
}

/*ODSprototypeRepeatable *ODScell::clone()
{
	// create a deep copy of this node
	QDomElement cloneElement = m_oAssociated.cloneNode( true ).toElement();
	m_oAssociated.parentNode().insertAfter( cloneElement, m_oAssociated );

	// and create a cell out of it
	ODScell *pCell = new ODScell( cloneElement );
	pCell->parse();
	return pCell;
}*/

void ODScell::setAttribute(float nAttr, QString sTag)
{
	QString sValue = QString();
	sValue.setNum( nAttr );
	setAttribute( sValue, sTag );
}

void ODScell::setAttribute(const QString &sAttr, QString sTag)
{
	// get the attribute node
	QDomAttr attribute = m_pPXFData->m_oAssociated.attributeNode( sTag );
	attribute.setValue( sAttr );
}

void ODScell::refreshXMLText()
{
	// remove all XML text nodes (there should be only one)
	QDomNodeList children = m_pPXFData->m_oAssociated.elementsByTagName( ODS_TAG_TEXT_P );
	for ( int i = 0; i < children.size(); ++i )
	{
		m_pPXFData->m_oAssociated.removeChild( children.at(i) );
	}

	// refresh XML text node
	if ( m_pCellData->m_pText )
	{
		QDomElement &associated = m_pPXFData->m_oAssociated;
		QDomElement textNode = associated.ownerDocument().createElement( ODS_TAG_TEXT_P );
		QDomNode text = associated.ownerDocument().createTextNode( *m_pCellData->m_pText );
		textNode.appendChild( text );
		associated.appendChild( textNode );
	}
}

} // namespace ODSlib
