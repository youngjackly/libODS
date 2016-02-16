#
# libods.pri
#
# Copyright © libODS Development Team, 2015.
# This file is part of libODS (https://github.com/nweyand/libODS/)
#
# libODS is free software; this file may be used under the terms of the GNU
# General Public License version 3.0 or later or later as published by the Free Software
# Foundation and appearing in the file LICENSE included in the
# packaging of this file.
#
# libODS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Please review the following information to ensure the GNU General Public
# License version 3.0 requirements will be met:
# http://www.gnu.org/copyleft/gpl.html.
#
# You should have received a copy of the GNU General Public License version
# 3.0 along with libODS; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

QT_VERSION = $$[QT_VERSION]
QT_VERSION = $$split(QT_VERSION, ".")

QT += core
QT += xml

# std::vector::shrink_to_fit is required.
CONFIG      += c++11

INCLUDEPATH += $$PWD

# Use zlib bundled with Qt to avoid external dependencies.
# In case this causes problems, just remove this line and include
# zlib externally.
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtZlib

# This needs to be defined when building QuaZip directly into a project.
DEFINES += QUAZIP_STATIC
include($$PWD/3rdparty/QuaZIP/quazip/quazip.pri)

# Headers
HEADERS += \
    $$PWD/ODSlib.h \                        # this is a convenience header not used internally
    $$[QT_INSTALL_HEADERS]/QtZlib/zlib.h \  # required for QuaZip compilation
    $$PWD/ODScell.h \
    $$PWD/ODScellData.h \
    $$PWD/ODSconstants.h \
    $$PWD/ODScontent.h \
    $$PWD/ODScontentData.h \
    $$PWD/ODSdocument.h \
    $$PWD/ODSelementFactory.h \
    $$PWD/ODSfile.h \
    $$PWD/ODSglobal.h \
    $$PWD/ODSprototypeContentRepeatable.h \
    $$PWD/ODSprototypeContentRepeatableData.h \
    $$PWD/ODSprototypeFactory.h \
    $$PWD/ODSprototypeRepeatable.h \
    $$PWD/ODSprototypeRepeatableData.h \
    $$PWD/ODSprototypeXMLfamiliar.h \
    $$PWD/ODSprototypeXMLfamiliarData.h \
    $$PWD/ODSrow.h \
    $$PWD/ODSspreadsheet.h \
    $$PWD/ODStable.h \
    $$PWD/ODStableData.h

# Sources
SOURCES += \
    $$PWD/ODScell.cpp \
    $$PWD/ODScellData.cpp \
    $$PWD/ODScontent.cpp \
    $$PWD/ODScontentData.cpp \
    $$PWD/ODSdocument.cpp \
    $$PWD/ODSelementFactory.cpp \
    $$PWD/ODSfile.cpp \
    $$PWD/ODSprototypeContentRepeatable.cpp \
    $$PWD/ODSprototypeContentRepeatableData.cpp \
    $$PWD/ODSprototypeFactory.cpp \
    $$PWD/ODSprototypeRepeatable.cpp \
    $$PWD/ODSprototypeRepeatableData.cpp \
    $$PWD/ODSprototypeXMLfamiliar.cpp \
    $$PWD/ODSprototypeXMLfamiliarData.cpp \
    $$PWD/ODSrow.cpp \
    $$PWD/ODSspreadsheet.cpp \
    $$PWD/ODStable.cpp \
    $$PWD/ODStableData.cpp
