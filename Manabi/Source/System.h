#ifndef SYSTEM_H
#define	SYSTEM_H

#include "Entity.h"
#include <set>

class System {
public:
	std::set<Entity> m_entities;
};


#endif // !SYSTEM_H