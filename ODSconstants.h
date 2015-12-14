/*
** ODSconstants.h
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

#ifndef ODSCONSTANTS
#define ODSCONSTANTS

#define ODS_CONTAINER_ELEMENT_CONTENT       "content.xml"

#define ODS_TAG_OFFICE_BODY         "office:body"
#define ODS_TAG_OFFICE_SPREADSHEET  "office:spreadsheet"
#define ODS_TAG_TABLE               "table:table"
#define ODS_TAG_TABLE_ROW           "table:table-row"
#define ODS_TAG_TABLE_CELL          "table:table-cell"
#define ODS_TAG_TEXT                "text:p"

#define ODS_ATTR_TBL_ROW_REPEAT     "table:number-rows-repeated"
#define ODS_ATTR_TBL_CELL_REPEAT    "table:number-columns-repeated"

#define ODS_ATTR_TBL_FORMULA        "table:formula"

#define ODS_ATTR_OFFICE_VALUE       "office:value"
#define ODS_ATTR_OFFICE_BOOLVAL     "office:boolean-value"
#define ODS_ATTR_OFFICE_DATEVAL     "office:date-value"
#define ODS_ATTR_OFFICE_TIMEVAL     "office:time-value"

#define ODS_ATTR_OFFICE_VAL_T       "office:value-type"
#define ODS_ATTR_CALCEXT_VAL_T      "calcext:value-type"

#define ODS_ATTRVAL_OFFICE_VAL_T_FLOAT      "float"
#define ODS_ATTRVAL_OFFICE_VAL_T_PERCENTAGE "percentage"
#define ODS_ATTRVAL_OFFICE_VAL_T_CURRENCY   "currency"
#define ODS_ATTRVAL_OFFICE_VAL_T_DATE       "date"
#define ODS_ATTRVAL_OFFICE_VAL_T_TIME       "time"
#define ODS_ATTRVAL_OFFICE_VAL_T_STRING     "string"
#define ODS_ATTRVAL_OFFICE_VAL_T_BOOL       "boolean"

#endif // ODSCONSTANTS

