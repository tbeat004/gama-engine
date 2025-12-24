#pragma once

#include <vector>
#include "Entity.h"

class Scene {
public:
	Scene();
	~Scene();
	void addEntity(const Entity& entity);
	void removeEntity(size_t index);
	Entity* getEntity(size_t index);
	size_t getEntityCount() const;
private:
	std::vector<Entity> m_entities;
	
};

