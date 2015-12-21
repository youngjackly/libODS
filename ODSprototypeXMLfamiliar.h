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

#ifndef OSDPROTOTYPEXMLFAMILIAR_H
#define OSDPROTOTYPEXMLFAMILIAR_H

#include <QtXml>

#include "ODSglobal.h"
#include "ODSconstants.h"

namespace ODSlib
{
class ODSelementFactory;
class ODSprototypeXMLfamiliar
{
public:
	typedef std::vector<ODSprototypeXMLfamiliar*> TContainer;

protected:
	//ODSprototypeXMLfamiliar();
	ODSprototypeXMLfamiliar(QString sElementFilter, QDomElement element);

public:
	virtual ~ODSprototypeXMLfamiliar();

	bool valid();
	//bool isNull();

	virtual TTableVector tables();

protected:
	bool m_bValid;
	//const bool m_bNull;
	QDomElement m_oAssociated;
	TContainer m_vContainer;

	virtual void parse();
	virtual void doMagic(ODSprototypeXMLfamiliar *pNew);

	/**
	 * @brief child allows to access a child of this node by its index.
	 * @param pos
	 * @return
	 */
	ODSprototypeXMLfamiliar *child(ODSprototypeXMLfamiliar::TContainer::size_type pos);

	/**
	 * @brief item allows to access a child of this node by its logical index. This also counts repeated nodes where implemented.
	 * @param pos
	 * @return
	 */
	virtual ODSprototypeXMLfamiliar *item(ODSprototypeXMLfamiliar::TContainer::size_type pos);

private:
	const QString m_sElementName;

	friend class ODStable;
	friend class ODSprototypeContentRepeatable;

	friend class ODSelementFactory;
};
typedef ODSprototypeXMLfamiliar::TContainer::size_type ST;
}

#endif // OSDPROTOTYPEXMLFAMILIAR_H
