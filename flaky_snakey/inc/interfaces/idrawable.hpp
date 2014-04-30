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


#ifndef IDRAWABLE_H
#define IDRAWABLE_H


/// Forward declarations
namespace prg
{
   class Image;
   typedef Image Canvas;
}


/// Used to indicate drawable objects on the screen.
/// IDrawable is an interface.
class IDrawable
{
   public:
      /// Constructors and destructor
      virtual ~IDrawable() {} // See below


      /// Functionality
      /// Draw the object onto the screen
      virtual void draw (prg::Canvas& canvas) = 0;

   protected:

   private:
};

#endif // IDRAWABLE_H

/// My desired destructor code is "virtual ~IDrawable() = default;" but unfortunately that causes a "looser throw specifier"
/// error in child classes. This is due to a bug on the version of MinGW that ships with Code::Blocks 13.12.

/// Updating MinGW to the latest version causes linker errors such as "undefined reference to '___gxx_personality_sj0' in
/// the PRG library so unfortunately I've had to go with virtual ~IDrawable() {}.
