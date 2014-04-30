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


#ifndef OBSTACLE_H
#define OBSTACLE_H


/// Third party
#include <prg/core/image.hpp> // m_kColour


/// Personal
#include <interfaces/idrawable.hpp> // Parent
#include <misc/rectangle.hpp> // m_kRectangle


/// Used to represent obstacles for snakes to collide with such as a wall
class Obstacle : public IDrawable
{
   public:
      /// Constructors and destructor
      // Optional first is required by ObstacleManager, Obstacle is grey
      Obstacle (const Rectangle& rectangle = { 10, 10, 0, 0 }, const prg::Colour& colour = { 112, 138, 144 });

      Obstacle (const Obstacle& copy) = default;
      Obstacle& operator= (const Obstacle& copy) = default;
      virtual ~Obstacle() = default;


      /// Functionality
      virtual void draw (prg::Canvas& canvas) override;


      /// Getters
      const Rectangle& getRectangle() const  { return m_kRectangle; }
      const prg::Colour& getColour() const   { return m_kColour; }

   protected:
      const Rectangle m_kRectangle; /// Contains the location and size of Obstacle
      const prg::Colour m_kColour;  /// The colour used when drawing onto the screen

   private:

};

#endif // OBSTACLE_H
