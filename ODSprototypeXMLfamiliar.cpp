/*
** ODSprototypeXMLfamiliar.cpp
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

#include "ODSprototypeFactory.h"
#include "ODSprototypeXMLfamiliar.h"

using namespace ODSlib;

ODSprototypeXMLfamiliar::ODSprototypeXMLfamiliar() :
	m_bValid( false ),
	m_bNull( true ),
	m_sElementName( "" )
{

}

ODSprototypeXMLfamiliar::ODSprototypeXMLfamiliar(const QString &sElementFilter) :
	m_bValid( false ),
	m_bNull( true ),
	m_sElementName( sElementFilter )
{
}

ODSprototypeXMLfamiliar::ODSprototypeXMLfamiliar(const QString &sElementFilter, QDomElement &element) :
	m_bValid( false ),
	m_bNull( true ),
	m_oAssociated( element ),
	m_sElementName( sElementFilter )
{
}

ODSprototypeXMLfamiliar::~ODSprototypeXMLfamiliar()
{
	qDeleteAll(m_vContainer);
}

bool ODSprototypeXMLfamiliar::valid()
{
	return m_bValid;
}

bool ODSprototypeXMLfamiliar::isNull()
{
	return m_bNull;
}

bool ODSprototypeXMLfamiliar::parse()
{
	bool bReturn = false;

	QDomNodeList list = m_oAssociated.elementsByTagName( m_sElementName );
	const int nSize = list.size();
	m_vContainer.reserve(nSize);

	for ( int i = 0; i < nSize; ++i )
	{
		QDomElement element = list.at(i).toElement();
		if ( !element.isNull() )
		{
			ODSprototypeXMLfamiliar *pNew = ODSprototypeFactory::generate( element, m_sElementName );
			if ( pNew->valid() )
			{
				doMagic(pNew);
				m_vContainer.push_back(pNew);
				bReturn = true;
			}
			else
			{
				delete pNew;
			}
		}
	}

	m_vContainer.shrink_to_fit();

	return bReturn;
}

void ODSprototypeXMLfamiliar::doMagic(ODSprototypeXMLfamiliar *pNew)
{
	Q_UNUSED(pNew);
}

ODSprototypeXMLfamiliar *ODSprototypeXMLfamiliar::child(ODSprototypeXMLfamiliar::TContainer::size_type pos)
{
	return m_vContainer.at(pos);
}

ODSprototypeXMLfamiliar *ODSprototypeXMLfamiliar::item(ODSprototypeXMLfamiliar::TContainer::size_type pos)
{
	return child(pos);
}

