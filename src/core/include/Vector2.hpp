#pragma once

struct Vector2
{
    int m_xPos, m_yPos;

    Vector2() : m_xPos(0), m_yPos(0) {};
    Vector2(int x, int y) : m_xPos(x), m_yPos(y) {};
    Vector2(const Vector2 &other) : m_xPos(other.m_xPos), m_yPos(other.m_yPos) {};
    Vector2& operator=(const Vector2& other)
    {
        if (this != &other) {
            m_xPos = other.m_xPos;
            m_yPos = other.m_yPos;
        }
        return *this;
		}

    void rotate_counterclockwise_90(const Vector2& origin)
    {
      // Translate to origin
      int dx = m_xPos - origin.m_xPos;
      int dy = m_yPos - origin.m_yPos;

      // Rotate 90° counterclockwise
      int rotated_x = -dy;
      int rotated_y = dx;

      // Translate back
      m_xPos = origin.m_xPos + rotated_x;
      m_yPos = origin.m_yPos + rotated_y;
    }
};
