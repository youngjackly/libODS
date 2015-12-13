/*
** ODSrow.cpp
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

#include "ODSrow.h"

ODSrow::ODSrow(QDomElement &element) :
	OSDprototypeXMLfamiliar(element)
{

}

ODSrow::~ODSrow()
{

}

bool ODSrow::parse()
{
	bool bReturn = false;

	// TODO: finish here
	QDomNodeList cells = m_oAssociated.childNodes();
	for ( int i = 0; i < cells.size(); ++i )
	{
		QDomElement cell = cells.at(i).toElement();

		// check for table elements
		if ( !cell.isNull() && !cell.tagName().compare("table:table-cell") )
		{
			 bReturn |= parseCellEntry(cell);
		}
	}

	return bReturn;
}

bool ODSrow::parseCellEntry(QDomElement cell)
{
	int nRepetitions = 1;

	if ( cell.hasAttribute("table:number-cells-repeated") )
	{
		bool bOK;
		nRepetitions = cell.attribute("table:number-cells-repeated").toInt(&bOK);

		// TODO: maybe catch some more errors
		if ( !bOK || nRepetitions < 1 )
		{
			return false;
		}
	}

	parseSingleCellEntry(cell);

	if ( nRepetitions > 1 )
	{
		cell.removeAttribute("table:number-cells-repeated");

		for ( int i = 1; i < nRepetitions; ++i )
		{
			QDomElement singleCell = cell.cloneNode(true).toElement();
			singleCell = cell.parentNode().insertAfter(singleCell, cell).toElement();
			parseSingleCellEntry(singleCell);
		}
	}

	return true;
}

bool ODSrow::parseSingleCellEntry(QDomElement cell)
{
	return false;
}
