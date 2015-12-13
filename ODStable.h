#ifndef ODSTABLE_H
#define ODSTABLE_H

#include <vector>

#include <QtXml>

#include "ODScell.h"

class ODStable
{
private:
	typedef std::vector<ODScell*> TODSrow;
	typedef std::vector<TODSrow*> TODStable;

public:
	typedef TODSrow::size_type   TCol;
	typedef TODStable::size_type TRow;

	ODStable(QDomElement table);
	~ODStable();

	ODScell &cell(TRow y, TCol x);
	bool valid();

private:
	bool m_bValid;
	QDomElement m_oAssociatedDomElement;

	TODStable m_vTable;

	bool parse(QDomElement table);
};

#endif // ODSTABLE_H
