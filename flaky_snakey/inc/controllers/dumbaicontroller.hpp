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


#ifndef DUMBAICONTROLLER_H
#define DUMBAICONTROLLER_H


/// Personal
#include <controllers/aicontroller.hpp>   // Parent
#include <snakes/snake.hpp>               // getMove()


/// DumbAIController is a derivative of AIController, it only differs in the complexity of getMove() and any additional
/// functions it needs for getMove(). The aim of DumbAIController is to chase the nearest food whilst avoiding obstacles
/// as well as it can on a limited level.
/// DumbAIController is a leaf class.
class DumbAIController final : public AIController
{
   public:
      /// Constructors and destructor
      DumbAIController (const InGameSetup& setup);

      DumbAIController (DumbAIController&& move) = default;
      DumbAIController (const DumbAIController& copy) = default;
      DumbAIController& operator= (const DumbAIController& copy) = default;
      ~DumbAIController() override = default;


      /// Getters
      Movement getMove() override;

   protected:

   private:
      /// Functionality
      Movement chaseFood (const Rectangle& head, const Rectangle& food);
};

#endif // DUMBAICONTROLLER_H
