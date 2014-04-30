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


#ifndef SNAKE_UTILITIES_H
#define SNAKE_UTILITIES_H


/// STL
#include <iostream>  // Used in flushCin()
#include <limits>    // Used in flushCin()
#include <sstream>   // Used in intToString()


/// Personal
#include <misc/rectangle.hpp>    // moveCell
#include <setup/ingamesetup.hpp> // moveCell


/// Used to contain all convenience/global functionality required by the game
namespace utility
{
   /// Completely flushes the buffer from cin to prevent input errors
   void flushCin();

   /// Converts and int to a string
   std::string intToString (const int value);
   std::string intToString (const unsigned int value);

   /// A boundary aware function to move a Rectangle however many cells is specified
   Rectangle& moveCell (const InGameSetup& setup, Rectangle& modify, int moveX, int moveY);
}

#endif // SNAKE_UTILITIES_H
