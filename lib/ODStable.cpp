/*
** ODStable.cpp
**
** Copyright © libODS Development Team, 2015-2016.
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
#include "ODStable.h"

#include "ODSprototypeXMLfamiliarData.h"
#include "ODSprototypeContentRepeatableData.h"
#include "ODStableData.h"

namespace ODSlib
{

ODStable::ODStable(QDomElement &element) :
    ODSprototypeXMLfamiliar( ODS_TAG_TABLE_ROW, element ), // req due to virtual inheritance
    ODSprototypeContentRepeatable( ODS_TAG_TABLE_ROW, ODS_ATTR_TBL_ROW_REPEAT, element ), // child: row; child repetitions for: row
    m_pTableData( new ODStableData )
{
}

/*ODStable::ODStable(const ODStable &rhs) :
    m_pTableData(rhs.pTableData)
{
}

ODStable &ODStable::operator=(const ODStable &rhs)
{
	if (this != &rhs)
		m_pTableData.operator=(rhs.m_pTableData);
	return *this;
}*/

ODStable::~ODStable()
{
}

void ODStable::parse()
{
	m_pTableData->m_sName = m_pPXFData->m_oAssociated.attribute( ODS_ATTR_TBL_NAME );
	ODSprototypeXMLfamiliar::parse();
}

const QString &ODStable::name() const
{
	return m_pTableData->m_sName;
}

void ODStable::setName(const QString &name)
{
	m_pPXFData->m_oAssociated.setAttribute( ODS_ATTR_TBL_NAME, name );
	m_pTableData->m_sName = name;
}

QString ODStable::coordinatesToString(st y, st x)
{
	return coordinatesToString(x + 1).append( QString::number( y + 1 ) );
}

void ODStable::stringToCoordinates(QString s, st &y, st &x)
{
	x = 0;
	y = 0;

	QRegularExpression validator( "^([A-Z]+)(\\d+)$" );
	QRegularExpressionMatch match = validator.match( s );

	if ( match.hasMatch() )
	{
		// note: capturing group 0 matches the entire pattern
		QString sx = match.captured( 1 );
		QString sy = match.captured( 2 );

		st multiplicator = 1;
		for ( int i = 1; i <= sx.length(); ++i )
		{
			QChar c = sx.at( sx.length() - i );

			ushort nc = c.unicode() - QChar( 'A' ).unicode();
			++nc; // Correct value so that A causes multiplication by 1 and not 0.
			nc *= multiplicator;

			x += nc;

			multiplicator *= 26;
		}

		y = sy.toULong() - 1;
	}
	else
	{
		--y;
	}

	--x; // make sure to transpose 1 based counting back to 0 based counting
}

ODScell *ODStable::cell(st y, st x)
{
	ODSprototypeXMLfamiliar* pRow = item(y);

	if ( pRow )
	{
		// Dynamic cast required because of virtual inheritance.
		// I.e. this is wrong: return (ODScell *)(pRow->item(x));
		// Note: GCC doesn't warn about this.
		ODSprototypeXMLfamiliar* pFamiliar = pRow->item(x);
		ODScell *pCell = dynamic_cast< ODScell* >(pFamiliar);
		return pCell;
	}

	return NULL;
}

QString ODStable::coordinatesToString(st x, QString s)
{
	--x; // for the caller, x = 1 corresponds to A, but it's more easy to work with x = 0 => A
	QChar cNew = QChar( QChar( 'A' ).unicode() + ( x % 26 ) );
	QString sNew = QString( cNew ).append( s );

	x /= 26; // here we get a representation where x = 1 => A in the next step

	if ( x )
	{
		return coordinatesToString( x, sNew );
	}
	else
	{
		return sNew;
	}
}

} // namespace ODSlib
