#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Signature.h"
#include <array>
#include <queue>

class EntityManager {
public:
	EntityManager();
	~EntityManager();

	Entity CreateEntity();
	void DestroyEntity(Entity entity);
	Signature GetSignature(Entity entity);
	void SetSignature(Entity entity, Signature signature);

private:
	std::queue<Entity> m_availableEntities{};

	std::array<Signature, MAX_ENTITIES> m_signatures{};

	uint32_t m_livingEntityCount{};
};

#endif