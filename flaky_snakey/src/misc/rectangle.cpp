/*
   Program: Flaky Snakey
   Created by Simon Peter Campbell

   The purpose of Flaky Snakey is simply to show understanding of OOP concepts for my C++ Programming
   module. Using the supplied PRG library I had the task of creating a Snake-like game.

   Copyright (C) 2014 Simon Peter Campbell
   This file is part of Flaky Snakey.

   Flaky Snakey is free software: you can redistribute it and/or modify it under
   the terms of the GNU General Public License as published by the Free Software Foundation,
   either version 3 of the License, or any later version. Flaky Snakey is distributed
   in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
   Public License for more details. You should have received a copy of the GNU General Public
   License along with Flaky Snakey. If not, see <http://www.gnu.org/licenses/>.
*/


#include <misc/rectangle.hpp>


/// Constructors and destructor
// Assign default values to members
// Subtract 1 due to the co-ordinate taking up a pixel
Rectangle::Rectangle (const unsigned int width, const unsigned int height,
                      const unsigned int x, const unsigned int y)
   : m_x (x), m_y (y), m_width (width), m_height (height)
{
   if (m_width != 0) { --m_width; }

   if (m_height != 0) { --m_height; }
}



/// Testing functions
bool Rectangle::operator== (const Rectangle& rhs) const
{
   // All values are equal
   return m_x == rhs.m_x &&
          m_y == rhs.m_y &&
          m_width == rhs.m_width &&
          m_height == rhs.m_height;
}


bool Rectangle::operator!= (const Rectangle& rhs) const
{
   // All values are equal
   return m_x != rhs.m_x ||
          m_y != rhs.m_y ||
          m_width != rhs.m_width ||
          m_height != rhs.m_height;
}


// Tests if rectangles intersect
bool Rectangle::intersects (const Rectangle& rect) const
{
   return m_x <= rect.m_x + rect.m_width  // A's left to B's right
          &&
          m_x + m_width >= rect.m_x       // A's right to B's left
          &&
          m_y <= rect.m_y + rect.m_height // A's top to B's bottom
          &&
          m_y + m_height >= rect.m_y;     // A's bottom to B's top
}



/// Assignment functions
// Increments the position, returns reference for daisy chaining with a getter
const Rectangle& Rectangle::incrementPosition (const unsigned int x, const unsigned int y)
{
   // Pre-condition: check for truncation because of numerical limits
   const unsigned int maxUInt = std::numeric_limits<unsigned int>::max();

   if (m_x + x < m_x || m_y + y < m_y) // Let the caller deal with the error
   {
      if (m_x + x < m_x) { m_x = maxUInt; }

      if (m_y + y < m_y) { m_y = maxUInt; }
   }

   else
   {
      m_x += x;
      m_y += y;
   }

   return *this;
}


// Decrements the position, returns reference for daisy chaining with a getter
const Rectangle& Rectangle::decrementPosition (const unsigned int x, const unsigned int y)
{
   // Pre-condition: check for truncation because of numerical limits
   if (m_x - x > m_x || m_y - y > m_y) // Let the caller deal with the error
   {
      if (m_x - x > m_x) { m_x = 0; }

      if (m_y - y > m_y) { m_y = 0; }
   }

   else
   {
      m_x -= x;
      m_y -= y;
   }

   return *this;
}


void Rectangle::setPosition (const unsigned int x, const unsigned int y)
{
   m_x = x;
   m_y = y;
}


void Rectangle::setDimensions (const unsigned int width, const unsigned int height)
{
   m_width = width;
   m_height = height;

   if (m_width != 0) { --m_width; }

   if (m_height != 0) { --m_height; }
}
