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


#ifndef FOOD_H
#define FOOD_H


/// Third party
#include <prg/interactive/app_state.hpp>  // Parent
#include <prg/interactive/timer.hpp>      // m_timer


/// Personal
#include <obstacles/obstacle.hpp> // Parent


/// Gets eaten by snakes and depending on the derived type, makes them grow or flake.
/// Food is abstract but should not be used as an interface.
class Food : public Obstacle, public prg::ITimerEvent
{
   public:
      /// Constructors and destructor
      // Food are red
      Food (const Rectangle& rectangle = {10, 10, 0, 0},
            const prg::Colour& colour = {255, 0, 0});

      Food (const unsigned short timerID, const unsigned int milliseconds,
            const Rectangle& rectangle = {10, 10, 0, 0},
            const prg::Colour& colour = {255, 0, 0});

      virtual ~Food() = default;


      /// Testing functions
      bool isRotten() const { return m_rotten; }


      /// Functionality
      void pause();
      void resume();
      void draw (prg::Canvas& canvas) override;
      void onTimer (prg::Timer& timer) override;


      /// Assignment functions
      void setDeterioration (const unsigned short timer_id, const unsigned int milliseconds);
      virtual void setFoodEffect (unsigned int effectMin, unsigned int effectMax) = 0;


      /// Getters
      int getFoodEffect() const           { return m_foodEffect; }
      unsigned short getTimerID() const   { return m_timer.getID(); }

   protected:
      prg::Timer m_timer;  /// Controls when the food becomes rotten
      bool m_rotten;       /// Used to determine if food is rotten
      int m_foodEffect;    /// Stores the amount a snake should grow or flake

   private:
};

#endif // FOOD_H
