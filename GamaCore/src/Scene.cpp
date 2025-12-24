#include "Scene.h"


Scene::Scene() {
}

Scene::~Scene() {
}


void Scene::addEntity(const Entity& entity) {
	m_entities.push_back(entity);
}

void Scene::removeEntity(size_t index) {
	if (index < m_entities.size()) {
		m_entities.erase(m_entities.begin() + index);
	}
}

Entity* Scene::getEntity(size_t index) {
	if (index < m_entities.size()) {
		return &m_entities[index];
	}
	return nullptr;
}

size_t Scene::getEntityCount() const {
	return m_entities.size();
}