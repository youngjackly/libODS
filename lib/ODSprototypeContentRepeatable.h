/*
** ODSrepeatableContent.h
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

#ifndef ODSPROTOTYPECONTENTREPEATABLE_H
#define ODSPROTOTYPECONTENTREPEATABLE_H

#include "ODSprototypeXMLfamiliar.h"

namespace ODSlib
{
/**
 * @brief The ODSprototypeContentRepeatable class manages accessing an underlying item container with repeatable items.
 */
class ODSprototypeContentRepeatable : virtual public ODSprototypeXMLfamiliar
{
protected:
	/**
	 * @brief ODSprototypeContentRepeatable
	 * @param sChildElementFilter The name of child elements to watch for/expect while parsing.
	 * @param sRepeatFilter The element tag associated with the number of repetitions of the element with the above name tag.
	 * @param associatedElement The XML element associated with this node.
	 */
	ODSprototypeContentRepeatable(const QString &sChildElementFilter, const QString &sRepeatFilter, QDomElement &associatedElement);
public:
	virtual ~ODSprototypeContentRepeatable();

protected:
	/**
	 * @brief doMagic is used to store the children's positions in the m_mPositions map.
	 * This allows for faster child lookup of in case of children containing repetitions.
	 * @param pNew
	 */
	void doMagic(ODSprototypeXMLfamiliar* pNew);

	virtual ODSprototypeXMLfamiliar *item(ODSprototypeXMLfamiliar::TContainer::size_type pos);

private:
	const QString m_sRepeatFilter;
	unsigned int m_nParseCounter;
	std::map<st,st> m_mPositions;
};
}

#endif // ODSPROTOTYPECONTENTREPEATABLE_H
