/*
** ODStable.cpp
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
#include "ODStable.h"

using namespace ODSlib;

ODStable::ODStable(QDomElement &element) :
	ODSprototypeXMLfamiliar( ODS_TAG_TABLE_ROW, element ), // req due to virtual inheritance
	ODSprototypeContentRepeatable( ODS_TAG_TABLE_ROW, ODS_ATTR_TBL_ROW_REPEAT, element ) // child: row; child repetitions for: row
{
}

ODStable::~ODStable()
{
}

void ODStable::parse()
{
	m_sName = m_oAssociated.attribute( ODS_ATTR_TBL_NAME );
	ODSprototypeXMLfamiliar::parse();
}

const QString &ODStable::name()
{
	return m_sName;
}

void ODStable::setName(const QString &name)
{
	m_oAssociated.setAttribute( ODS_ATTR_TBL_NAME, name );
	m_sName = name;
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

