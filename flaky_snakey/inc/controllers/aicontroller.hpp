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


#ifndef AICONTROLLER_H
#define AICONTROLLER_H


/// STL
#include <cstdlib>   // basicMove()
#include <vector>    // generatePossibleMoves()


/// Personal
#include <controllers/controller.hpp>     // Parent
#include <misc/snakeutilities.hpp>        // moveForward()


/// Forward declarations
class FoodManager;
class ObstacleManager;
class SnakeManager;


/// AIController is the base class of which DumbAIController and SmartAIController are derived from. It provides basic
/// functionality required for AI control of Snake objects for debugging purposes but should only be available on the
/// easiest of difficulties.
/// AIController is a branch class.
class AIController : public Controller
{
   public:
      /// Constructors and destructor
      AIController (const InGameSetup& setup);

      AIController (AIController&& move) = default;
      AIController (const AIController& copy) = default;
      AIController& operator= (const AIController& copy) = default;
      virtual ~AIController() = default;


      /// Assignment functions
      void setSnakeManager (const std::shared_ptr<SnakeManager>& snakeManager);
      void setFoodManager (const std::shared_ptr<FoodManager>& FoodManager);
      void setObstacleManager (const std::shared_ptr<ObstacleManager>& obstacleManager);


      /// Getters
      /// AIController will check for any safe movements and randomly choose one
      virtual Movement getMove() override;

   protected:
      /// Testing functions
      bool exists (const Movement test, const std::vector<Movement>& moves) const;


      /// Functionality
      /// Randomly generates a movement
      Movement basicMove() const;
      Movement safeMove();

      /// Moves a Rectangle one cell forward, taking into account the ability to spawn at the other side
      void moveForward (Rectangle& modify, const Movement move);

      /// Fills modify with possible moves based on m_lastMove
      void generatePossibleMoves (std::vector<Movement>& modify);
      void generateSafeMoves (std::vector<Movement>& modify);


      /// Members
      const InGameSetup m_kSetup;                        /// Used to test whether adjacent cells are available

      std::weak_ptr<const SnakeManager> m_pkSnakeManager;       /// Allows the ability to avoid Snake objects
      std::weak_ptr<const FoodManager> m_pkFoodManager;         /// Allows the ability to find the closest food
      std::weak_ptr<const ObstacleManager> m_pkObstacleManager; /// Allows the ability to avoid Obstacle objects

   private:
};

#endif // AICONTROLLER_H
