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


#include <food/food.hpp>


/// Constructors and destructor
// Assign default values
Food::Food (const Rectangle& rectangle, const prg::Colour& colour)
   :  Obstacle (rectangle, colour),
      m_timer (),
      m_rotten (false), m_foodEffect (0)
{
}


Food::Food (const unsigned short timerID, const unsigned int milliseconds,
            const Rectangle& rectangle, const prg::Colour& colour)
   :  Obstacle (rectangle, colour),
      m_timer (timerID, milliseconds, *this),
      m_rotten (false), m_foodEffect (0)
{
   m_timer.start();
}



/// Functionality
void Food::pause()
{
   m_timer.stop();
}


void Food::resume()
{
   /// 255 indicates that the Timer is invalid, prevent access violation errors by testing for it
   if (m_timer.getID() != 255)
   {
      m_timer.start();
   }
}


void Food::draw (prg::Canvas& canvas)
{
   /// Get parameters for the sake of efficiency
   const unsigned int x = getRectangle().getX();
   const unsigned int y = getRectangle().getY();
   const unsigned int width = getRectangle().getWidth();
   const unsigned int height = getRectangle().getHeight();

   /*                       ____
                           /    \
   Food looks like this:   |    |
                           \____/

   */
   /// ++ is used to correct integer rounding problems so lines are as straight as possible, only the upper left
   /// and lower right corners need fixing. Other fixes would cause the same issue
   unsigned int xWidth25p = x + width * 0.25;
   unsigned int yHeight25p = y + height * 0.25;

   /// Use + 1 to correct subtractions made by the Rectangle object
   if ((width + 1) % 2 == 0) { ++xWidth25p; }

   if ((height + 1) % 2 == 0) { ++yHeight25p; }


   // Top line
   canvas.drawLine (xWidth25p,         y + height,
                    x + width * 0.75,  y + height,          m_kColour);

   // Bottom line
   canvas.drawLine (x + width * 0.75,  y,
                    x + width * 0.25,  y,                   m_kColour);

   // Left line
   canvas.drawLine (x,                 y + height * 0.25,
                    x,                 y + height * 0.75,   m_kColour);

   // Right line
   canvas.drawLine (x + width,         y + height * 0.75,
                    x + width,         yHeight25p,          m_kColour);

   // Top left line
   canvas.drawLine (x,                 y + height * 0.75,
                    xWidth25p,         y + height,          m_kColour);

   // Top right line
   canvas.drawLine (x + width * 0.75,  y + height,
                    x + width,         y + height * 0.75,   m_kColour);

   // Bottom left line
   canvas.drawLine (x + width * 0.25,  y,
                    x,                 y + height * 0.25,   m_kColour);

   // Bottom Right line
   canvas.drawLine (x + width,         yHeight25p,
                    x + width * 0.75,  y,                   m_kColour);
}


void Food::onTimer (prg::Timer& timer)
{
   timer.stop();
   m_rotten = true;
}
