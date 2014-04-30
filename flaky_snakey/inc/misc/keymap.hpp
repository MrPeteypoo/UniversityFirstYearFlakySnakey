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


#ifndef KEYMAP_H_INCLUDED
#define KEYMAP_H_INCLUDED


/// PlayerController requires a Keymap to check input against.
struct Keymap final
{
   int up {'w'};
   int left {'a'};
   int right {'d'};
   int down {'s'};

   Keymap() = default;
   Keymap (const Keymap& copy) = default;
   Keymap (Keymap&& move) = default;
   Keymap& operator= (const Keymap& copy) = default;
   ~Keymap() = default;
};

#endif // KEYMAP_H_INCLUDED
