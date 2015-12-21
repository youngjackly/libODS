/*
** ODScell.h
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

#ifndef ODSCELL_H
#define ODSCELL_H

#include "ODSprototypeRepeatable.h"

namespace ODSlib
{

namespace CellType
{
enum Type
{
	unknown,        // unknown or unsupported cell type
	error,          // indicates a parsing error
	none,           // empty cell; no type specified
	boolean,
	number,
	percentage,
	currency,
	stringContent,
	date,
	time
};
}

class ODSelementFactory;

class ODScell : public ODSprototypeRepeatable
{
private:
	class CellContent
	{
		CellContent(QDomElement &element);
		virtual ~CellContent();

		void            clear();
		CellType::Type  type() const;

		float       value() const;
		bool        setValue(float value);

		QString     contentString() const;
		bool        setContentString(const QString &value);

		QString*    m_pFormula;
		QString*    m_pText;
		bool        m_bHasCalcExtValueType;

		void        parse();

	private:
		bool        parseType(const QString &sAttribute);
		void        refreshText();

		QDomElement     m_oAssociated;
		CellType::Type  m_eType;
		float           m_nValue;
		QString         m_sData;

		friend class ODScell;
	};

private:
	ODScell(QDomElement &element);

public:
	~ODScell();

	void            clear();

	CellType::Type  type() const;

	float           value() const;
	bool            setValue(float value);

	/**
	 * @brief hasText
	 * @return
	 */
	bool        hasText() const;

	/**
	 * @brief text
	 * @return The cell text if it exists. A string cell always has one; other cells might or might not.
	 */
	QString text() const;

	/**
	 * @brief string allows to access the content of string, date and time cells.
	 * @return A string if the cell is of the above types; an empty string otherwise.
	 */
	QString     contentString() const;
	bool setContentString(const QString &value);

protected:
	virtual void parse();

private:
	CellContent m_oContent;

	void        setAttribute(float nAttr, QString sTag);
	void        setAttribute(const QString &sAttr, QString sTag);
	void        refreshXMLText();

	friend class ODSelementFactory;
};
}

#endif // ODSCELL_H
