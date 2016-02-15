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

#include "ODSprototypeXMLfamiliar.h"
#include "ODSprototypeFactory.h"

namespace ODSlib
{

class ODSprototypeXMLfamiliarData : public QSharedData
{
public:
	bool m_bValid;
	//const bool m_bNull;
	QDomElement m_oAssociated;
	ODSprototypeXMLfamiliar::TContainer m_vContainer;

	const QString m_sChildElementName;

	ODSprototypeXMLfamiliarData(QString sFilter, QDomElement &element);
	~ODSprototypeXMLfamiliarData();
};

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

ODSprototypeXMLfamiliar::ODSprototypeXMLfamiliar(QString sChildElementFilter, QDomElement element) :
	m_pPXFData( new ODSprototypeXMLfamiliarData( sChildElementFilter, element ) )
{
}

/*ODSprototypeXMLfamiliar::ODSprototypeXMLfamiliar(const ODSprototypeXMLfamiliar &rhs) : pPXFData(rhs.pPXFData)
{

}

ODSprototypeXMLfamiliar &ODSprototypeXMLfamiliar::operator=(const ODSprototypeXMLfamiliar &rhs)
{
	if (this != &rhs)
		pPXFData.operator=(rhs.pPXFData);
	return *this;
}*/

ODSprototypeXMLfamiliar::~ODSprototypeXMLfamiliar()
{
}

bool ODSprototypeXMLfamiliar::valid()
{
	return m_bValid;
}

/*bool ODSprototypeXMLfamiliar::isNull()
{
	return m_bNull;
}*/

std::vector<ODStable*> ODSprototypeXMLfamiliar::tables()
{
	std::vector<ODStable*> vTables;
	std::vector<ODSprototypeXMLfamiliar*> &vContainer = m_pPXFData->m_vContainer;

	// for all children of this node
	const st nContainerSize = vContainer.size();
	for (st i = 0; i < nContainerSize; ++i)
	{
		std::vector<ODStable*> vChildTables = vContainer[i]->tables();

		// copy all tables of all children
		vTables.insert( vTables.end(), vChildTables.begin(), vChildTables.end() );
	}

	return vTables;
}

void ODSprototypeXMLfamiliar::parse()
{
	bool bValid = false;
	std::vector<ODSprototypeXMLfamiliar*> &vContainer = m_pPXFData->m_vContainer;

	QDomNodeList list = m_pPXFData->m_oAssociated.elementsByTagName( m_pPXFData->m_sChildElementName );
	const int nSize = list.size();
	vContainer.reserve(nSize);

	for ( int i = 0; i < nSize; ++i )
	{
		QDomElement element = list.at(i).toElement();
		if ( !element.isNull() )
		{
			ODSprototypeXMLfamiliar *pNew = ODSprototypeFactory::generate( element, m_pPXFData->m_sChildElementName );
			if ( pNew->valid() )
			{
				doMagic(pNew);
				vContainer.push_back(pNew);
				bValid = true;
			}
			else
			{
				delete pNew;
			}
		}
	}

	vContainer.shrink_to_fit();
	m_pPXFData->m_bValid = bValid;
}

void ODSprototypeXMLfamiliar::doMagic(ODSprototypeXMLfamiliar *pNew)
{
	Q_UNUSED(pNew);
}

ODSprototypeXMLfamiliar *ODSprototypeXMLfamiliar::child(st pos)
{
	return m_pPXFData->vContainer.at(pos);
}

ODSprototypeXMLfamiliar *ODSprototypeXMLfamiliar::item(st pos)
{
	return child(pos);
}

} //namespace ODSlib
