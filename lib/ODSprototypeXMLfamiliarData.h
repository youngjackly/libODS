/*
** ODSprototypeXMLfamiliarData.h
**
** Copyright © libODS Development Team, 2016.
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

#ifndef ODSPROTOTYPEXMLFAMILIARDATA_H
#define ODSPROTOTYPEXMLFAMILIARDATA_H

#include "ODSprototypeXMLfamiliar.h"

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

	void parse(ODSprototypeXMLfamiliar* pParent);
};

} // namespace ODSlib

#endif // ODSPROTOTYPEXMLFAMILIARDATA_H
