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


#include <setup/ingamesetup.hpp>


/// Constructors and destructor
// For initialisation information see recalculateMembers() and correctAspectRatio()
InGameSetup::InGameSetup()
   :  m_resX (0), m_resY (0),
      m_workingX (0), m_workingY (0),
      m_marginX (0), m_marginY (0), m_marginUI (0),
      m_startX (0), m_endX (0), m_startY (0), m_endY (0),
      m_aspectCorrection (true),
      m_gridWidth (20), m_gridHeight (20),
      m_rectWidth (0), m_rectHeight (0)
{
   setResolution (640, 480);
}



/// Assignment functions
/// Allow daisy chaining of assignment functions
InGameSetup& InGameSetup::setResolution (const unsigned int width, const unsigned int height)
{
   //Pre-condition: Check valid resolution
   if (width >= 640 && height >= 480 &&
         width <= 2560 && height <= 1600)
   {
      m_resX = width;
      m_resY = height;
      recalculateMembers(); // Ensure other members reflect the change

      if (m_aspectCorrection)
      {
         correctAspectRatio();
      }
   }

   return *this; // Daisy chaining
}


InGameSetup& InGameSetup::setGrid (const unsigned int width, const unsigned int height)
{
   // Pre-condition: Guarantee at least a 8x8 grid and less than 40x40 grid
   if (width >= 8 && height >= 8 &&
         width <= 40 && height <= 40)
   {
      m_gridWidth = width;
      m_gridHeight = height;
      recalculateMembers(); // Ensure other members reflect the change

      if (m_aspectCorrection)
      {
         correctAspectRatio();
      }
   }

   return *this; // Daisy chaining
}


InGameSetup& InGameSetup::setAspectRatioCorrection (const bool correct)
{
   m_aspectCorrection = correct;

   if (correct)
   {
      correctAspectRatio();
   }
   else
   {
      recalculateMembers();
   }

   return *this;
}


/// Base calculations, result will be a stretched image on any grid where m_rectWidth != m_rectHeight
void InGameSetup::recalculateMembers()
{
   /// Calculate X values
   m_workingX = m_resX;

   // 25% goes to the UI, * 0.15 caused inaccuracies
   m_marginUI = m_workingX / 100.0 * 25 / 2.0;
   m_workingX -= m_workingX / 100.0 * 25;

   // Create a margin for even block dimensions, m_workingX -= m_marginX * 2 causes inaccuracies
   m_marginX = (m_workingX % m_gridWidth) / 2.0;
   m_workingX -= m_workingX % m_gridWidth;


   /// Calculate Y values
   m_workingY = m_resY;

   // Create a margin for even block dimensions, m_workingY -= m_marginY * 2 causes inaccuracies
   m_marginY = (m_workingY % m_gridHeight) / 2.0;
   m_workingY -= m_workingY % m_gridHeight;


   /// Create Rectangle dimensions
   m_rectWidth = m_workingX / m_gridWidth;
   m_rectHeight = m_workingY / m_gridHeight;


   /// Create rendering values
   m_startX = m_marginX + m_marginUI;
   m_startY = m_marginY;
   m_endX = m_startX + m_workingX;
   m_endY = m_startY + m_workingY;
}


/// Attempt to correct aspect ratio based on grid size, the aim is for game to use as much
/// of the resolution available whilst maintaining m_rectHeight == m_rectWidth
void InGameSetup::correctAspectRatio()
{
   /// Correct width
   if (m_rectWidth > m_rectHeight)
   {
      // Fix the margin, I was so happy when I came up with this formula :-)
      m_marginX += (m_rectWidth - m_rectHeight) * m_gridWidth / 2.0;
      m_workingX -= (m_rectWidth - m_rectHeight) * m_gridWidth;
   }


   /// Correct height
   else if (m_rectWidth < m_rectHeight)
   {
      // Fix the margin
      m_marginY += (m_rectHeight - m_rectWidth) * m_gridHeight / 2.0;
      m_workingY -= (m_rectHeight - m_rectWidth) * m_gridHeight;
   }


   /// Update Rectangle dimensions
   m_rectWidth = m_workingX / m_gridWidth;
   m_rectHeight = m_workingY / m_gridHeight;


   /// Update rendering values
   m_startX = m_marginX + m_marginUI;
   m_startY = m_marginY;
   m_endX = m_startX + m_workingX;
   m_endY = m_startY + m_workingY;
}
