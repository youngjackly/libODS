/*
** ReadData.h
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

#ifndef READDATA_H
#define READDATA_H

#include <QString>
#include <QtTest>

#include "SingleDocumentTestCase.h"

class ReadData : public SingleDocumentTestCase
{
	Q_OBJECT
public:
	ReadData();

private:
	ODSlib::ODStable* m_pTable;

	void checkCellNameConversion(ODSlib::st y, ODSlib::st x, QString s);
	void checkCellNameConversionToString(ODSlib::st y, ODSlib::st x, QString s);
	void checkCellNameConversionToCoordinates(ODSlib::st y, ODSlib::st x, QString s);

private Q_SLOTS:
	void checkCellNameConversions();
	void checkDocument();
	void readLine0();       // numbers
	void readLine8();       // letters
	void readLine29();      // percentages
	void readCelly18x14();  // radom pos read / string
	void readCelly0x100();  // read repeated cell (normal row)
	void readCelly100x20(); // read repeated cell (repeated row)
};

#endif // READDATA_H
