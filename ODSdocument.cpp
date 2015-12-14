/*
** ODSdocument.cpp
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

#include "ODSdocument.h"

using namespace ODSlib;

ODSdocument::ODSdocument(QString sFileName) :
	m_ioFile(sFileName),
	m_oContent(m_ioFile)
{
}

ODSdocument::~ODSdocument()
{
}

ODStable *ODSdocument::getFirstTable()
{
	TTableVector vTables = getTables();

	if ( vTables.size() )
	{
		return vTables[0];
	}
	else
	{
		return NULL;
	}
}

ODStable *ODSdocument::getTable(const QString &sSheetName)
{
	// TODO: implement (requires parsing sheet names)
	return NULL;
}

TTableVector ODSdocument::getTables()
{
	return m_oContent.tables();
}

