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


#include <food/fatfood.hpp>


/// Constructors and destructor
// Assign default values
FatFood::FatFood (const Rectangle& rectangle, const prg::Colour& colour)
   :  Food (rectangle, colour)
{
   m_foodEffect = 1;
}


FatFood::FatFood (const unsigned short timerID, const unsigned int milliseconds,
                  const Rectangle& rectangle, const prg::Colour& colour)
   :  Food (timerID, milliseconds, rectangle, colour)
{
   m_foodEffect = 1;
}



/// Assignment functions
// Trust is placed in the programmer not to abuse effectMax
void FatFood::setFoodEffect (unsigned int effectMin, unsigned int effectMax)
{
   // Pre-condition: Guarantee parameters won't cause truncation issues
   unsigned int intMax = std::numeric_limits<int>::max();

   if (effectMin > intMax) { effectMin = intMax; }

   if (effectMax > intMax) { effectMax = intMax; }


   // Pre-condition: Ensure effectMin & effectMax are valid
   if (effectMin == 0) { effectMin = 1; }

   if (effectMax == 0) { effectMax = 1; }


   // Calculate food effect
   if (effectMin < effectMax)
   {
      m_foodEffect = rand() % (effectMax - effectMin) + effectMin;
   }

   else if (effectMin == effectMax)
   {
      m_foodEffect = effectMax;
   }

   else // If effectMin > effectMax, handle error by swapping values
   {
      m_foodEffect = rand() % (effectMin - effectMax) + effectMax;
   }
}
