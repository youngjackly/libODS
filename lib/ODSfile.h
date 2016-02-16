/*
** ODSfile.h
**
** Copyright © libODS Development Team, 2015-2016.
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

#ifndef ODSFILE_H
#define ODSFILE_H

#include <QFile>

#include "3rdparty/QuaZIP/quazip/quazip/quazip.h"
#include "3rdparty/QuaZIP/quazip/quazip/quazipfile.h"

namespace ODSlib
{
/**
 * @brief The ODSfile class is used internally by ODSdocument.
 */
class ODSfile
{
public:
	ODSfile(QString sFileName);
	virtual ~ODSfile();

	/**
	 * @brief accessContainerElement allows to read from an element file of the ODS container.
	 * This is limited to one file at a time due to limitations of the underlying zip library.
	 * @param sName The file name + extension
	 * @return NULL if unsuccessfull
	 */
	QIODevice* accessContainerElement(QString sName);
	bool closeContainerElement(QIODevice *&pElement);

	QString path() const;
	QString fileName() const;

private:
	QString m_sFileName;
	QuaZip m_ioODScontainer;

	QuaZipFile* m_pCurrentlyOpened;
};
}

#endif // ODSFILE_H
