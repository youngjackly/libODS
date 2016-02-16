/*
** ODSprototypeXMLfamiliar.h
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

#ifndef ODS_PROTOTYPE_XML_FAMILIAR_H
#define ODS_PROTOTYPE_XML_FAMILIAR_H

#include <QtXml>
#include <QExplicitlySharedDataPointer>

#include "ODSglobal.h"
#include "ODSconstants.h"

namespace ODSlib
{
class ODSelementFactory;
class ODSprototypeXMLfamiliarData;

/**
 * @brief The ODSprototypeXMLfamiliar class represents a logical node in a tree parallel to an XML
 * file tree structure.
 */
class ODSprototypeXMLfamiliar
{
	//friend class ODStable;
	//friend class ODSprototypeContentRepeatable;
	friend class ODSelementFactory;

public:
	typedef std::vector<ODSprototypeXMLfamiliar*> TContainer;

protected:
	/**
	 * @brief ODSprototypeXMLfamiliar
	 * @param sChildElementFilter The name of child elements to watch for/expect while parsing.
	 * @param associatedElement The XML element associated with this node.
	 */
	ODSprototypeXMLfamiliar(QString sChildElementFilter, QDomElement element);

public:
	//ODSprototypeXMLfamiliar(const ODSprototypeXMLfamiliar &);
	//ODSprototypeXMLfamiliar &operator=(const ODSprototypeXMLfamiliar &);
	virtual ~ODSprototypeXMLfamiliar();

	bool valid();
	//bool isNull();

	virtual std::vector<ODStable*> tables();

protected:
	virtual void parse();

	/**
	 * @brief doMagic is called once for every new child that is added to the current node.
	 * It allows Child classes to do fancy stuff based on the event that a new child is added.
	 * @param pNew
	 */
	virtual void doMagic(ODSprototypeXMLfamiliar *pNew);

	/**
	 * @brief child allows to access a child of this node by its index.
	 * @param pos
	 * @return
	 */
	ODSprototypeXMLfamiliar *child(ODSprototypeXMLfamiliar::TContainer::size_type pos);

	/**
	 * @brief item allows to access a child of this node by its logical index.
	 * This also counts repeated nodes where implemented.
	 * @param pos
	 * @return
	 */
	virtual ODSprototypeXMLfamiliar *item(ODSprototypeXMLfamiliar::TContainer::size_type pos);

protected:
	QExplicitlySharedDataPointer<ODSprototypeXMLfamiliarData> m_pPXFData;
};

typedef ODSprototypeXMLfamiliar::TContainer::size_type st;
}

#endif // ODS_PROTOTYPE_XML_FAMILIAR_H
