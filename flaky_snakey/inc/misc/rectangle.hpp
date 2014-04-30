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


#ifndef RECTANGLE_H
#define RECTANGLE_H


/// STL
#include <limits> // Used in inc/decrementPosition()


/// Used for defining a rectangular object, useful for drawing an object onto the screen.
/// Rectangle is a leaf class.
class Rectangle final
{
   public:
      /// Constructors and destructor
      Rectangle (const unsigned int width, const unsigned int height,
                 const unsigned int x = 0 , const unsigned int y = 0);

      Rectangle (const Rectangle& copy) = default;
      Rectangle (Rectangle&& move) = default;
      Rectangle& operator= (const Rectangle& copy) = default;
      ~Rectangle() = default;


      /// Testing functions
      bool operator== (const Rectangle& rhs) const;
      bool operator!= (const Rectangle& rhs) const;
      bool intersects (const Rectangle& target) const; /// Tests if rectangles intersect


      /// Assignment functions
      // Returns const reference for daisy chaining with a getter
      const Rectangle& incrementPosition (const unsigned int x, const unsigned int y);
      const Rectangle& decrementPosition (const unsigned int x, const unsigned int y);

      void setPosition (const unsigned int x, const unsigned int y);
      void setDimensions (const unsigned int width, const unsigned int height);


      /// Getter functions
      unsigned int getX() const        { return m_x; }
      unsigned int getY() const        { return m_y; }
      unsigned int getWidth() const    { return m_width; }
      unsigned int getHeight() const   { return m_height; }

   protected:

   private:
      unsigned int m_x;       /// Represents the x co-ordinate of the Rectangle
      unsigned int m_y;       /// Represents the y co-ordinate of the Rectangle
      unsigned int m_width;   /// The width of the Rectangle in units (typically pixels)
      unsigned int m_height;  /// The height of the Rectangle in units (typically pixels)
};

#endif // RECTANGLE_H
