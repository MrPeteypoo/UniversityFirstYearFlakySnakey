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


#include <ui/button.hpp>


/// Constructors and destructor
Button::Button (const Rectangle& clickableArea, const prg::Colour& colour)
   :  m_font ("assets/fonts/instruction.ttf", 10), m_area (clickableArea), m_colour (colour),
      m_text ("NULL"), m_mouseOver (false)
{
}



/// Core requirements
void Button::setupFont()
{
   // Ensure text stays in boundaries
   unsigned int textSize;
   if (m_area.getWidth() / m_text.length() < m_area.getHeight() * 0.8)
   {
      textSize = m_area.getWidth() / m_text.length();
   }
   else
   {
      textSize = m_area.getHeight() * 0.8;
   }

   /// Draw text
   m_font = prg::Font ("assets/fonts/instruction.ttf", textSize);
}


/// Testing functions
bool Button::intersects (const unsigned int x, const unsigned int y) const
{
   const Rectangle position {0, 0, x, y};

   return position.intersects (m_area);
}



/// Functionality
void Button::draw (prg::Canvas& canvas)
{
   /// Get parameters for the sake of efficiency
   const unsigned int x = m_area.getX();
   const unsigned int y = m_area.getY();
   const unsigned int width = m_area.getWidth();
   const unsigned int height = m_area.getHeight();


   unsigned int dimensions[2];
   m_font.computePrintDimensions (dimensions, m_text);

   m_font.print (canvas,  x + width / 2 - dimensions[0] / 2,
                        y + height / 2 - dimensions[1] / 2, m_colour, m_text);

   /// Draw borders
   if (m_mouseOver)
   {
      // Bottom line
      canvas.drawLine (x,           y,
                       x + width,   y,          m_colour);

      // Top line
      canvas.drawLine (x,           y + height,
                       x + width,   y + height, m_colour);

      // Left line
      canvas.drawLine (x,           y,
                       x,           y + height, m_colour);

      // Right line
      canvas.drawLine (x + width,   y,
                       x + width,   y + height, m_colour);
   }
}



/// Assignment functions
void Button::setText (const std::string& text)
{
   m_text = text;
   setupFont();
}


void Button::setText (const int value)
{
   m_text = utility::intToString (value);
   setupFont();
}


void Button::setText (const unsigned int value)
{
   m_text = utility::intToString (value);
   setupFont();
}
