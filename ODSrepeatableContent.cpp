/*
** ODSrepeatableContent.cpp
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

#include "ODSrepeatableContent.h"

using namespace ODSlib;

ODSrepeatableContent::ODSrepeatableContent(const QString &sElementFilter, const QString &sRepeatFilter, QDomElement &element) :
	ODSprototypeXMLfamiliar( sElementFilter, element ),
	m_sRepeatFilter( sRepeatFilter ),
	m_nParseCounter( 0 )
{

}

ODSrepeatableContent::~ODSrepeatableContent()
{

}

void ODSrepeatableContent::doMagic(ODSprototypeXMLfamiliar *pNew)
{
	// remember the current position for faster lookup
	m_mPositions[m_nParseCounter] = m_vContainer.size();

	// keep track of pos counter incrementation
	const QDomElement row = pNew->m_oAssociated;
	if ( row.hasAttribute( m_sRepeatFilter ) )
	{
		bool bOK;
		const unsigned int nRepetitions = row.attribute( m_sRepeatFilter ).toUInt(&bOK);

		if ( bOK )
		{
			m_nParseCounter += nRepetitions;
		}
		else // handle the cell as not repeated in case of error
		{
			++m_nParseCounter;
		}
	}
	else
	{
		++m_nParseCounter;
	}

	// make sure to call parent
	ODSprototypeXMLfamiliar::doMagic(pNew);
}

ODSprototypeXMLfamiliar *ODSrepeatableContent::item(ODSprototypeXMLfamiliar::TContainer::size_type pos)
{
	if ( m_mPositions.count(pos) )
	{
		ST nStoragePos = m_mPositions.at(pos);
		if ( nStoragePos < m_vContainer.size() )
		{
			return m_vContainer[nStoragePos];
		}
		else
		{
			// should never happen except if there is a bug in the counting code...
			throw(42);
			return NULL;
		}
	}
	else
	{
		// TODO: fix
		return NULL;
	}
}

