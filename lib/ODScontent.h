/*
** ODScontent.h
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

#ifndef ODSCONTENT_H
#define ODSCONTENT_H

#include <QExplicitlySharedDataPointer>

#include "ODSprototypeXMLfamiliar.h"

namespace ODSlib
{
class ODSelementFactory;
class ODScontentData;

class ODScontent : public ODSprototypeXMLfamiliar
{
	friend class ODSelementFactory;

private:
	/**
	 * @brief ODScontent represents the content.xml file within the ODS container.
	 * Note that it is only considered to be valid in our case if it contains at least one valid
	 * <office:spreadsheet> element.
	 * @param ioFile
	 */
	ODScontent(QDomDocument &doc);
public:
	//ODScontent(const ODScontent &);
	//ODScontent &operator=(const ODScontent &);
	virtual ~ODScontent();

	QString toString();

	/*ODSspreadsheet* sheet(const QString& sName);
	TContainer sheets();*/

private:
	QExplicitlySharedDataPointer<ODScontentData> m_pContentData;
};

} // namespace ODSlib

#endif // ODSCONTENT_H
