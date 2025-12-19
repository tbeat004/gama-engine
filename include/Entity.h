#pragma once

class Entity {
public:
    Entity(float x = 0.0f, float y = 0.0f, float width = 50.0f, float height = 50.0f);
    ~Entity();

    // Moves this entity by a relative amount from its current position
    void move(float dx, float dy);
    // Sets the absolute position of this entity
    void setPosition(float x, float y);
    // Sets the size of this entity
    void setSize(float width, float height);
    // Sets the color of this entity
    void setColor(float r, float g, float b);

    // Getters
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getWidth() const { return m_width; }
    float getHeight() const { return m_height; }
    float getR() const { return m_r; }
    float getG() const { return m_g; }
    float getB() const { return m_b; }

private:
    float m_x, m_y;
    float m_width, m_height;
    float m_r, m_g, m_b;  // Color
};