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


#include <misc/snakeutilities.hpp>


/// Completely flushes the buffer from cin to prevent input errors
void utility::flushCin()
{
   std::cin.clear();
   std::cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
}


/// Converts and int to a string
std::string utility::intToString (const int value)
{
   /// MingGW has a bug with header guards not allowing access to std::to_string, so this work around is used.
   std::ostringstream temp;
   temp << value;
   return temp.str();
}


std::string utility::intToString (const unsigned int value)
{
   /// MingGW has a bug with header guards not allowing access to std::to_string, so this work around is used.
   std::ostringstream temp;
   temp << value;
   return temp.str();
}


/// A boundary aware function to move a Rectangle however many cells is specified
Rectangle& utility::moveCell (const InGameSetup& setup, Rectangle& modify, int moveX, int moveY)
{
   if (moveX == 0 && moveY == 0)
   {
      return modify;
   }

   const unsigned int gridWidth = setup.getGridWidth();
   const unsigned int gridHeight = setup.getGridHeight();

   // Adjust moveX and moveY to the actual cells modify should be moved
   if (moveX > (int) gridWidth || moveX < (int) gridWidth * -1)
   {
      moveX %= gridWidth;
   }

   if (moveY > (int) gridHeight || moveY < (int) gridHeight * -1)
   {
      moveY %= gridHeight;
   }


   // Calculate targetX
   unsigned int currentX = (modify.getX() - setup.getStartX()) / setup.getRectWidth();

   int targetX = currentX + moveX;
   if (targetX >= (int) gridWidth)
   {
      targetX -= gridWidth;
   }

   else if (targetX < 0)
   {
       targetX += gridWidth;
   }


   // Calculate targetY
   unsigned int currentY = (modify.getY() - setup.getStartY()) / setup.getRectHeight();

   int targetY = currentY + moveY;
   if (targetY >= (int) gridHeight)
   {
      targetY -= gridHeight;
   }

   else if (targetY < 0)
   {
       targetY += gridHeight;
   }


   /// Move modify to the correct cell
   modify.setPosition (setup.getStartX() + targetX * setup.getRectWidth(),
                       setup.getStartY() + targetY * setup.getRectHeight());

   return modify;
}
