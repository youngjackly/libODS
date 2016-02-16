/*
** ODSprototypeXMLfamiliarData.cpp
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

#include "ODSprototypeXMLfamiliarData.h"
#include "ODSprototypeFactory.h"

namespace ODSlib
{

ODSprototypeXMLfamiliarData::ODSprototypeXMLfamiliarData(QString sFilter, QDomElement &element) :
	m_bValid( false ),
	//m_bNull( false ),
	m_oAssociated( element ),
	m_sChildElementName( sFilter )
{
}

ODSprototypeXMLfamiliarData::~ODSprototypeXMLfamiliarData()
{
	qDeleteAll(m_vContainer);
}

void ODSprototypeXMLfamiliarData::parse(ODSprototypeXMLfamiliar* pParent)
{
	bool bValid = false;

	QDomNodeList list = m_oAssociated.elementsByTagName( m_sChildElementName );
	const int nSize = list.size();
	m_vContainer.reserve(nSize);

	for ( int i = 0; i < nSize; ++i )
	{
		QDomElement element = list.at(i).toElement();
		if ( !element.isNull() )
		{
			ODSprototypeXMLfamiliar *pNew = ODSprototypeFactory::generate( element,
			                                                               m_sChildElementName );
			if ( pNew->valid() )
			{
				pParent->doMagic(pNew);
				m_vContainer.push_back(pNew);
				bValid = true;
			}
			else
			{
				delete pNew;
			}
		}
	}

	m_vContainer.shrink_to_fit();
	m_bValid = bValid;
}

} // namespace ODSlib

