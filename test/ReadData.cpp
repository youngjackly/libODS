/*
** ReadData.cpp
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

#include "ReadData.h"

ReadData::ReadData() :
	SingleDocumentTestCase( "./testData/ReadData.ods" )
{
}

void ReadData::checkDocumentValid()
{
	QVERIFY2( m_pDoc->valid(), "The specified document could not be verified as valid." );
	qDebug() << "\n   File: " << m_pDoc->fileName()
			 << "\n   Path: " << m_pDoc->path();
}

void ReadData::readLine0() // numbers
{
	ODSlib::ODStable* pTable = m_pDoc->getFirstTable();

	QVERIFY2(pTable, "No table could be obtained from the ODS document.");

	for ( uint x = 0; x < 8; ++x )
	{
		ODSlib::ODScell* pCell = pTable->cell( 0, x );
		QString sPos = QString("(y:").append("0").append(";x:").append(QString::number(x)).append(")");

		QVERIFY2( pCell->valid(), QString("Found invalid cell at ").append(sPos).toLatin1() );
		QVERIFY2( x == pCell->value(), QString("Expected different value at ").append(sPos).toLatin1() );
	}
}

void ReadData::readLine8() // letters
{

}

void ReadData::readLine30() // percentages
{

}

void ReadData::readCelly18x14() // random position read (string)
{

}

void ReadData::readCelly0x100() // read of repeated cell in standard row
{

}

void ReadData::readCelly100x20() // read of repeated cell in repeated row
{

}
