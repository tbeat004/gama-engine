#include "Entity.h"
#include <iostream>
Entity::Entity(float x, float y, float width, float height, float speed)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_r(1.0f), m_g(1.0f), m_b(1.0f), m_speed(speed) {
}

Entity::~Entity() {
}

void Entity::move(float dx, float dy) {

    m_x += dx;
    m_y += dy;
}

void Entity::setPosition(float x, float y) {
    m_x = x;
    m_y = y;
}

void Entity::setSize(float width, float height) {
    m_width = width;
    m_height = height;
}

void Entity::setColor(float r, float g, float b) {
    m_r = r;
    m_g = g;
    m_b = b;
}

void Entity::setSpeed(float speed) {
    m_speed = speed;
}