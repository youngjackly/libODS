/*
** ODScontent.cpp
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

#include "ODScontent.h"

namespace ODSlib
{

class ODScontentData : public QSharedData
{
public:
	QDomDocument m_oContentDocument;

	ODScontentData(QDomDocument doc);
};

ODScontentData::ODScontentData(QDomDocument doc) :
	m_oContentDocument( doc )
{
}

ODScontent::ODScontent(QDomDocument &doc) :
	ODSprototypeXMLfamiliar( ODS_TAG_OFFICE_SPREADSHEET, doc.documentElement() ),
	m_pContentData( new ODScontentData( doc ) )
{
}

/*ODScontent::ODScontent(const ODScontent &rhs) : pContentData(rhs.pContentData)
{
}

ODScontent &ODScontent::operator=(const ODScontent &rhs)
{
	if (this != &rhs)
		pContentData.operator=(rhs.pContentData);
	return *this;
}*/

ODScontent::~ODScontent()
{
}

QString ODScontent::toString()
{
	return m_pContentData->m_oContentDocument.toString(-1);
}

/*ODSspreadsheet *ODScontent::sheet(const QString &sName)
{
	for ( ST i = 0; i < m_vContainer.size(); ++i )
	{
		ODSspreadsheet *pSheet = dynamic_cast< ODSspreadsheet* >(m_vContainer[i]);
	}
}

ODSprototypeXMLfamiliar::TContainer ODScontent::sheets()
{
	return m_vContainer;
}*/

} // namespace ODSlib
