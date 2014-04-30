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


#include <obstacles/obstacle.hpp>


/// Constructors and destructor
// Assign default values
Obstacle::Obstacle (const Rectangle& rectangle, const prg::Colour& colour)
   : m_kRectangle (rectangle), m_kColour (colour)
{
}



/// Functionality
void Obstacle::draw (prg::Canvas& canvas)
{
   /// Get parameters for the sake of efficiency
   const unsigned int x = getRectangle().getX();
   const unsigned int y = getRectangle().getY();
   const unsigned int width = getRectangle().getWidth();
   const unsigned int height = getRectangle().getHeight();

   // Bottom line
   canvas.drawLine (x,           y,
                    x + width,   y, m_kColour);

   // Top line
   canvas.drawLine (x,           y + height,
                    x + width,   y + height, m_kColour);

   // Left line
   canvas.drawLine (x,           y,
                    x,           y + height, m_kColour);

   // Right line
   canvas.drawLine (x + width,   y,
                    x + width,   y + height, m_kColour);

   // Left diagonal
   canvas.drawLine (x,           y,
                    x + width,   y + height, m_kColour);

   // Right diagonal
   canvas.drawLine (x + width,   y,
                    x,           y + height, m_kColour);
}

/*
                             __
                            |\/|
   Obstacles look like this |/\| The cross meets the corners
                             __
*/
