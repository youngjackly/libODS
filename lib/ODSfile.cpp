/*
** ODSfile.cpp
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

#include <QFileInfo>

#include "ODSfile.h"

using namespace ODSlib;

ODSfile::ODSfile(QString sFileName) :
	m_sFileName(        sFileName ),
	m_ioODScontainer(   sFileName ),
	m_pCurrentlyOpened( NULL )
{
	m_ioODScontainer.open(QuaZip::mdUnzip);
}

ODSfile::~ODSfile()
{
	if ( m_pCurrentlyOpened )
	{
		QIODevice* pDevice = m_pCurrentlyOpened;
		closeContainerElement( pDevice );
	}

	m_ioODScontainer.close();
}

QIODevice *ODSfile::accessContainerElement(QString sName)
{
	if ( m_pCurrentlyOpened )
	{
		qWarning("Error: Only one file can be accessed at the same time.");
		return NULL;
	}

	if ( m_ioODScontainer.setCurrentFile(sName) )
	{
		m_pCurrentlyOpened = new QuaZipFile(&m_ioODScontainer);
		m_pCurrentlyOpened->open(QIODevice::ReadOnly);
		return m_pCurrentlyOpened;
	}
	else
	{
		qWarning(QString("Error: Failed to set current file in ZIP archive. File name: ")
				 .append(sName)
				 .append(" ZIP Error code: ")
				 .append(m_ioODScontainer.getZipError())
				 .toLocal8Bit().constData());

		return NULL;
	}
}

bool ODSfile::closeContainerElement(QIODevice *&pElement)
{
	if ( pElement && m_pCurrentlyOpened && m_pCurrentlyOpened == pElement )
	{
		pElement->close();
		delete pElement;
		pElement = NULL;

		m_pCurrentlyOpened = NULL;
		return true;
	}
	else
	{
		qWarning( "Error: Tried to close wrong or NULL element file." );
		return false;
	}
}

QString ODSfile::path() const
{
	QFileInfo info( m_sFileName );
	if ( info.exists() )
	{
		return info.absolutePath();
	}
	return QString();
}

QString ODSfile::fileName() const
{
	QFileInfo info( m_sFileName );
	if ( info.exists() )
	{
		return info.fileName();
	}
	return QString();
}
