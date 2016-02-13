#
# UnitTests.pro
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

QT       += testlib

QT       -= gui

TARGET   = UnitTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# Copy test files to build folder
!equals(PWD, $$OUT_PWD){
	!build_pass:message("Configuring for shadow build")

	SRC_DIR = $$PWD/testData/*
	DST_DIR = $$OUT_PWD/testData/

	test_files.commands = $(COPY_DIR) $$shell_path($$SRC_DIR) $$shell_path($$DST_DIR)
	test_files.depends = FORCE

	QMAKE_EXTRA_TARGETS += test_files
	PRE_TARGETDEPS += test_files
}

include($$PWD/../lib/libods.pri)
include($$PWD/allUnits/allunits.pri)

SOURCES += main.cpp \
	ReadData.cpp \
	ModifySave.cpp

HEADERS += \
	ReadData.h \
	ModifySave.h
