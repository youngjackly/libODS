/*
** ODSprototypeRepeatable.cpp
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

#include "ODSprototypeRepeatable.h"

namespace ODSlib
{

class ODSprototypeRepeatableData : public QSharedData
{
public:
	size_t m_nMultiplicity;
	const QString m_sRepeatAttribute;

	ODSprototypeRepeatableData( const QString &sRepeatFilter, QDomElement &associatedElement );
};

ODSprototypeRepeatableData::
ODSprototypeRepeatableData( const QString &sRepeatFilter, QDomElement &associatedElement ) :
	m_nMultiplicity( associatedElement.attribute( sRepeatFilter, QString( "0" ) ).toUInt() ),
	m_sRepeatAttribute( sRepeatFilter )
{
}

ODSprototypeRepeatable::
ODSprototypeRepeatable( const QString &sChildElementFilter, const QString &sRepeatFilter,
                        QDomElement &associatedElement) :
	ODSprototypeXMLfamiliar( sChildElementFilter, associatedElement ),
	m_pPRData( new ODSprototypeRepeatableData( sRepeatFilter, associatedElement ) )
{
}

/*ODSprototypeRepeatable::ODSprototypeRepeatable(const ODSprototypeRepeatable &rhs) :
    pPRData(rhs.pPRData)
{
}

ODSprototypeRepeatable &ODSprototypeRepeatable::operator=(const ODSprototypeRepeatable &rhs)
{
	if (this != &rhs)
		pPRData.operator=(rhs.pPRData);
	return *this;
}*/

ODSprototypeRepeatable::~ODSprototypeRepeatable()
{
}

size_t ODSprototypeRepeatable::multiplicity() const
{
	return m_pPRData->m_nMultiplicity;
}

ODSprototypeRepeatable *ODSprototypeRepeatable::split(size_t afterN)
{
	ODSprototypeRepeatable *pSplit = NULL;

	if ( afterN > 0 && afterN < m_pPRData->m_nMultiplicity )
	{
		pSplit = clone();
		pSplit->setMultiplicity( m_pPRData->m_nMultiplicity - afterN );

		setMultiplicity( afterN );
	}

	return pSplit;
}

void ODSprototypeRepeatable::setMultiplicity(const size_t &multiplicity)
{
	m_pPXFData->m_oAssociated.setAttribute( m_pPRData->m_sRepeatAttribute, multiplicity );
	m_pPRData->m_nMultiplicity = multiplicity;
}

} // namespace ODSlib
