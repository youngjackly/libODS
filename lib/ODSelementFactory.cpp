/*
** ODSelementFactory.cpp
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

#include "ODSelementFactory.h"

#include "ODSfile.h"
#include "ODScontent.h"
#include "ODSspreadsheet.h"
#include "ODStable.h"
#include "ODSrow.h"
#include "ODScell.h"

using namespace ODSlib;

ODSelementFactory::ODSelementFactory()
{
}

ODSelementFactory::~ODSelementFactory()
{
}

ODScontent *ODSelementFactory::generateContentXML(ODSfile& ioFile)
{
	ODScontent *pNew = NULL;
	QDomDocument oContentFile = QDomDocument();
	int errorLine, errorCol;
	QString sError;

	QIODevice* pDevice = ioFile.accessContainerElement( ODS_CONTAINER_ELEMENT_CONTENT );

	if ( pDevice )
	{
		if ( oContentFile.setContent(pDevice, &sError, &errorLine, &errorCol) )
		{
			pNew = new ODScontent(oContentFile);
			pNew->parse();
			pNew->valid();
		}
		else
		{
			// TODO: improve warning with error string from above
			qWarning("ODScontent::parse - Failed to parse file.");
		}

		ioFile.closeContainerElement(pDevice);
	}
	else
	{
		qWarning( "ODScontent::parse - Could not obtain content.xml from the specified ODS file. Wrong file name / path?" );
	}

	return pNew;
}

ODSspreadsheet *ODSelementFactory::generateSpreadsheet(QDomElement &element)
{
	ODSspreadsheet *pNew = new ODSspreadsheet(element);
	pNew->parse();
	return pNew;
}

ODStable *ODSelementFactory::generateTable(QDomElement &element)
{
	ODStable *pNew = new ODStable(element);
	pNew->parse();
	return pNew;
}

ODSrow *ODSelementFactory::generateRow(QDomElement &element)
{
	ODSrow *pNew = new ODSrow(element);
	pNew->parse();
	return pNew;
}

ODScell *ODSelementFactory::generateCell(QDomElement &element)
{
	ODScell *pNew = new ODScell(element);
	pNew->parse();
	return pNew;
}

