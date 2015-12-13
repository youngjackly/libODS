/*
** ODStable.cpp
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

#include "ODStable.h"

using namespace ODSlib;

ODStable::ODStable(QDomElement &table) :
	m_oAssociatedDomElement( table )
{
	m_bValid = parse();
}

ODStable::~ODStable()
{
	for ( TRow y = 0; y < m_vvTable.size(); ++y )
	{
		TODSrow &vRow = *m_vvTable[y];
		for ( TCol x = 0; x < vRow.size(); ++x )
		{
			delete vRow[x];
		}
		vRow.clear();
		delete m_vvTable[y];
	}
	m_vvTable.clear();
}

ODScell &ODStable::cell(ODStable::TRow y, ODStable::TCol x)
{
	return *(*m_vvTable[y])[x];
}

bool ODStable::valid()
{
	return m_bValid;
}

bool ODStable::parse()
{
	bool bReturn = false;


	return bReturn;
}

