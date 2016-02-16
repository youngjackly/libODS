/*
** ODSspreadsheet.cpp
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

#include "ODStable.h"
#include "ODSspreadsheet.h"

namespace ODSlib
{

class ODSspreadsheetData : public QSharedData
{
public:
};

ODSspreadsheet::ODSspreadsheet(QDomElement &element) :
    ODSprototypeXMLfamiliar( ODS_TAG_TABLE, element )
    ,m_pSpreadsheetData(new ODSspreadsheetData)
{

}

/*ODSspreadsheet::ODSspreadsheet(const ODSspreadsheet &rhs) :
    pSData(rhs.pSSpreadsheetData)
{
}

ODSspreadsheet &ODSspreadsheet::operator=(const ODSspreadsheet &rhs)
{
	if (this != &rhs)
		pSData.operator=(rhs.pSSpreadsheetData);
	return *this;
}*/

ODSspreadsheet::~ODSspreadsheet()
{
}

std::vector<ODStable*> ODSspreadsheet::tables()
{
	// The container of this node contains a vector of tables.
	std::vector<ODStable*> vReturn;

	for ( st i = 0; i < m_vContainer.size(); ++i )
	{
		// Dynamic cast required because of virtual inheritance.
		// Note: GCC doesn't warn about this.
		ODSprototypeXMLfamiliar* pFamiliar = m_vContainer[i];
		ODStable* pTable = dynamic_cast< ODStable* >(pFamiliar);
		vReturn.push_back( pTable );
	}

	return vReturn;
}

} // namespace ODSlib

