#pragma once

/**
 * @brief A 2D vector class representing a point or vector in integer coordinate space
 *
 * This class provides basic 2D vector operations with integer precision.
 * Suitable for grid-based games, pixel coordinates, or discrete mathematics applications.
 */
struct Vector2
{
  int x, y;

  /**
   * @brief Default constructor - initializes vector to origin (0, 0)
   */
  Vector2() : x(0), y(0) {};

  /**
   * @brief Parameterized constructor
   * 
   * @param x The x-coordinate
   * @param y The y-coordinate
   */
  Vector2(int x, int y) : x(x), y(y) {};

  /**
   * @brief Copy constructor
   * 
   * @param other The Vector2 to copy from
   */
  Vector2(const Vector2& other) : x(other.x), y(other.y) {};

  /**
   * @brief Assignment operator
   * 
   * @param other The Vector2 to assign from
   * @return Reference to this vector for chaining
   */
  Vector2& operator=(const Vector2& other)
  {
    if (this != &other) {
      x = other.x;
      y = other.y;
    }
    return *this;
  }

  /**
   * @brief Rotates this vector 90 degrees counterclockwise around a given origin point
   * 
   * @param origin The point to rotate around
   */
  void rotate_counterclockwise_90(const Vector2& origin)
  {
    // Translate to origin
    int dx = x - origin.x;
    int dy = y - origin.y;

    // Rotate 90° counterclockwise: (x,y) -> (-y,x)
    int rotated_x = -dy;
    int rotated_y = dx;

    // Translate back
    x = origin.x + rotated_x;
    y = origin.y + rotated_y;
  }

  /**
	 * @brief returns a new Vector2 that is one unit above this vector
   * 
	 * @return Vector2 The new vector above the current one
   */
	Vector2 getAbove() const { return Vector2(x, y - 1); }

  /**
	 * @brief returns a new Vector2 that is one unit below this vector
   * 
	 * @return Vector2 The new vector below the current one
   */
	Vector2 getBelow() const { return Vector2(x, y + 1); }
};
