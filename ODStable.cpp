#include "ODStable.h"

ODStable::ODStable(QDomElement table) :
	m_oAssociatedDomElement( table )
{
	m_bValid = parse(table);
}

ODStable::~ODStable()
{

}

ODScell &ODStable::cell(ODStable::TRow y, ODStable::TCol x)
{
	ODScell bogus;
	return bogus;
}

bool ODStable::valid()
{
	return m_bValid;
}

bool ODStable::parse(QDomElement table)
{
	return false;
}

