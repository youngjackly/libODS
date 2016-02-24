/*
** ReadData.cpp
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

#include "ReadData.h"

ReadData::ReadData() :
	SingleDocumentTestCase( "./testData/ReadData.ods" )
{
}

void ReadData::checkCellNameConversion(ODSlib::st y, ODSlib::st x, QString s)
{
	checkCellNameConversionToString(      y, x, s );
	checkCellNameConversionToCoordinates( y, x, s );
}

void ReadData::checkCellNameConversionToString(ODSlib::st y, ODSlib::st x, QString s)
{
	const QString sInput = QString("(y:").append(QString::number(y)).append(";x:").append(QString::number(x)).append(")");
	const QString sConvert = ODSlib::ODStable::coordinatesToString( y, x );
	QVERIFY2( sConvert == s, QString( "Invalid to string conversion for cell position "
	                                  ).append(sInput).append( " Expected: " ).append(s
	                                  ).append( " Got: " ).append( sConvert ).toLatin1() );
}

void ReadData::checkCellNameConversionToCoordinates(ODSlib::st y, ODSlib::st x, QString s)
{
	const QString sExpected = QString("(y:").append(QString::number(y)).append(";x:").append(QString::number(x)).append(")");

	ODSlib::st ny, nx;
	ODSlib::ODStable::stringToCoordinates( s, ny, nx );

	const QString sConvert = QString("(y:").append(QString::number(ny)).append(";x:").append(QString::number(nx)).append(")");
	QVERIFY2( x == nx && y == ny, QString( "Invalid conversion for cell "
	                                       ).append(s).append( " Expected: " ).append(sExpected
	                                       ).append( " Got: " ).append( sConvert ).toLatin1() );
}

void ReadData::checkCellNameConversions()
{
	checkCellNameConversion( 0,  0,   "A1"   );
	checkCellNameConversion( 0,  1,   "B1"   );
	checkCellNameConversion( 1,  0,   "A2"   );
	checkCellNameConversion( 1,  1,   "B2"   );
	checkCellNameConversion( 0,  25,  "Z1"   );
	checkCellNameConversion( 1,  25,  "Z2"   );
	checkCellNameConversion( 0,  26,  "AA1"  );
	checkCellNameConversion( 0,  27,  "AB1"  );
	checkCellNameConversion( 1,  26,  "AA2"  );
	checkCellNameConversion( 1,  27,  "AB2"  );
	checkCellNameConversion( 0,  51,  "AZ1"  );
	checkCellNameConversion( 0,  52,  "BA1"  );
	checkCellNameConversion( 0,  53,  "BB1"  );
	checkCellNameConversion( 1,  52,  "BA2"  );
	checkCellNameConversion( 1,  53,  "BB2"  );
	checkCellNameConversion( 0,  701, "ZZ1"  );
	checkCellNameConversion( 0,  702, "AAA1" );
	checkCellNameConversion( 0,  703, "AAB1" );

	checkCellNameConversion( 8,  0,   "A9"   );
	checkCellNameConversion( 9,  0,   "A10"  );
	checkCellNameConversion( 10, 0,   "A11"  );
	checkCellNameConversion( 19, 0,   "A20"  );
	checkCellNameConversion( 99, 0,   "A100" );
}

void ReadData::checkDocument()
{
	QVERIFY2( m_pDoc->valid(), "The specified document could not be verified as valid." );
	qDebug() << "\n   File: " << m_pDoc->fileName()
			 << "\n   Path: " << m_pDoc->path();

	m_pTable = m_pDoc->getFirstTable();
	QVERIFY2( m_pTable, "No table could be obtained from the ODS document." );
}

void ReadData::readLine0() // numbers
{
	for ( uint x = 0; x < 8; ++x )
	{
		QString sPos = ODSlib::ODStable::coordinatesToString(0, x);

		ODSlib::ODScell* pCell = m_pTable->cell( 0, x );
		QVERIFY2( pCell, QString( "Got NULL when querying cell " ).append(sPos).toLatin1() );

		QVERIFY2( pCell->valid(), QString( "Found invalid cell at " ).append(sPos).toLatin1() );
		QVERIFY2( pCell->type() == ODSlib::CellType::number, "Caught cell with unexpected type." );
		QVERIFY2( x == pCell->value(), QString( "Expected different value at " ).append(sPos).toLatin1() );
	}
}

void ReadData::readLine8() // letters
{
	for ( uint x = 0; x < 8; ++x )
	{
		QString sPos = ODSlib::ODStable::coordinatesToString(8, x);

		ODSlib::ODScell* pCell = m_pTable->cell( 8, x );
		QVERIFY2( pCell, QString( "Got NULL when querying cell " ).append(sPos).toLatin1() );

		QVERIFY2( pCell->valid(), QString( "Found invalid cell at " ).append(sPos).toLatin1() );
		QVERIFY2( pCell->type() == ODSlib::CellType::stringContent, "Caught cell with unexpected type." );
		QVERIFY2( pCell->hasText(), "Expected cell to have text." );
		const uchar c = 97 + x;
		QVERIFY2( pCell->text() == QString().append( QChar(c) ), QString( "Expected different value at " ).append(sPos).toLatin1() );
	}
}

void ReadData::readLine29() // percentages
{
	for ( uint x = 0; x < 8; ++x )
	{
		QString sPos = ODSlib::ODStable::coordinatesToString(29, x);

		ODSlib::ODScell* pCell = m_pTable->cell( 29, x );
		QVERIFY2( pCell, QString( "Got NULL when querying cell " ).append(sPos).toLatin1() );

		QVERIFY2( pCell->valid(), QString( "Found invalid cell at " ).append(sPos).toLatin1() );
		QVERIFY2( pCell->type() == ODSlib::CellType::percentage, "Caught cell with unexpected type." );

		const float nExpected = (float)x / 100.0f;
		const float nValue = pCell->value();
		QString sError = sPos.append( " Got: " ).append( QString::number(nValue) ).append( " Epected: " ).append( QString::number(nExpected) );
		QVERIFY2( nExpected == nValue, QString( "Expected different value at " ).append(sError).toLatin1() );
	}
}

void ReadData::readCellO19() // random position read (string)
{
	ODSlib::ODScell* pCell = m_pTable->cell( "O19" );
	QVERIFY2( pCell, "Got NULL when querying cell O19." );

	QVERIFY2( pCell->valid(), "Cell O19 invalid." );
	QVERIFY2( pCell->type() == ODSlib::CellType::stringContent, "Caught cell with unexpected type." );

	QVERIFY2( pCell->contentString() == QString( "test" ), "Expected different value!" );
}

void ReadData::readCelly0x100() // read of repeated cell in standard row
{
}

void ReadData::readCelly100x20() // read of repeated cell in repeated row
{
}
