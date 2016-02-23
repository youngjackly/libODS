/*
** ODSdocument.cpp
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

#include "ODSdocument.h"

#include "ODStable.h"
#include "ODSelementFactory.h"

using namespace ODSlib;

ODSdocument::ODSdocument(QString sFileName) :
	m_ioFile(sFileName),
	m_pContent( ODSelementFactory::generateContentXML( m_ioFile ) )
{
}

ODSdocument::~ODSdocument()
{
	delete m_pContent;
}

ODStable *ODSdocument::getFirstTable()
{
	std::vector<ODStable*> vTables = getTables();

	if ( vTables.size() )
	{
		return vTables[0];
	}
	else
	{
		return NULL;
	}
}

ODStable *ODSdocument::getTable(const QString &sTableName)
{
	std::vector<ODStable*> vTables = getTables();

	for ( st i = 0; i < vTables.size(); ++i )
	{
		ODStable* pTable = vTables[i];
		if ( pTable->name().compare(sTableName) )
		{
			return pTable;
		}
	}
	return NULL;
}

std::vector<ODStable*> ODSdocument::getTables()
{
	return m_pContent->tables();
}

bool ODSdocument::valid() const
{
	// m_pContent is only non NULL if an zipped file was recognized and a content.xml
	// found therein (QuaZIP). Additionally, it is valid if the content.xml could be parsed.
	return m_pContent && m_pContent->valid();
}

QString ODSdocument::path() const
{
	return m_ioFile.path();
}

QString ODSdocument::fileName() const
{
	return m_ioFile.fileName();
}

bool ODSdocument::save()
{
	return true;
}

