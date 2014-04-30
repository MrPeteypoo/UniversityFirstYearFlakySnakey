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


#include <controllers/aicontroller.hpp>
#include <obstacles/obstaclemanager.hpp>
#include <snakes/snakemanager.hpp>


/// Constructors and destructor
AIController::AIController(const InGameSetup& setup)
   :  Controller(), m_kSetup (setup),
      m_pkSnakeManager (), m_pkFoodManager (), m_pkObstacleManager ()
{
}



/// Testing functions
bool AIController::exists (const Movement test, const std::vector<Movement>& moves) const
{
   for (const auto& move : moves)
   {
      if (move == test)
      {
         return true;
      }
   }

   return false;
}



/// Functionality
Movement AIController::basicMove() const
{
   return Movement (rand() % 4 + 1);
}


Movement AIController::safeMove()
{
   std::vector<Movement> moves;
   generateSafeMoves (moves);

   if (!moves.empty())
   {

      return moves[rand() % moves.size()];

   }

   else // Accept death
   {
      return m_lastMove;
   }
}

/// Moves a Rectangle one cell forward, taking into account the ability to spawn at the other side
void AIController::moveForward (Rectangle& modify, const Movement move)
{
   switch (move)
   {
      case Movement::Up:
         utility::moveCell (m_kSetup, modify, 0, 1);
         break;

      case Movement::Left:
         utility::moveCell (m_kSetup, modify, -1, 0);
         break;

      case Movement::Right:
         utility::moveCell (m_kSetup, modify, 1, 0);
         break;

      case Movement::Down:
         utility::moveCell (m_kSetup, modify, 0, -1);
         break;

      default: // Should never happen
         break;
   }
}


/// Fills modify with possible moves based on m_lastMove
void AIController::generatePossibleMoves (std::vector<Movement>& modify)
{
   switch (m_lastMove)
   {
      case Movement::Up:
         modify.push_back (Movement::Up);
         modify.push_back (Movement::Left);
         modify.push_back (Movement::Right);
         break;

      case Movement::Right:
         modify.push_back (Movement::Right);
         modify.push_back (Movement::Up);
         modify.push_back (Movement::Down);
         break;

      case Movement::Left:
         modify.push_back (Movement::Left);
         modify.push_back (Movement::Up);
         modify.push_back (Movement::Down);
         break;

      case Movement::Down:
         modify.push_back (Movement::Down);
         modify.push_back (Movement::Left);
         modify.push_back (Movement::Right);
         break;

      default: // Shouldn't be able to happen
         break;
   }
}


/// Calls generatePossibleMoves then checks if any don't contain collidable objects
void AIController::generateSafeMoves (std::vector<Movement>& modify)
{
   generatePossibleMoves (modify);

   const auto& obstacleManager = m_pkObstacleManager.lock();
   const auto& snakeManager = m_pkSnakeManager.lock();
   const auto& snake = m_pkSnake.lock();

   if (snake && obstacleManager && obstacleManager)
   {
      // Avoid ranged based loop for the ability to erase the move
      for (int i {0}; (unsigned int) i < modify.size(); ++i)
      {
         auto head = snake->getHead();
         moveForward (head, modify[i]);

         if (obstacleManager->isObstacleHere (head) || snakeManager->isSnakeHere (head))
         {
            modify.erase (modify.begin() + i--);
         }
         // Else the move is safe
      }
   }
   // Else just return possible moves
}


/// Assignment functions
void AIController::setSnakeManager (const std::shared_ptr<SnakeManager>& snakeManager)
{
   /// Ensure shared_ptr is valid
   if (snakeManager)
   {
      m_pkSnakeManager = snakeManager;
   }
}


void AIController::setFoodManager (const std::shared_ptr<FoodManager>& foodManager)
{
   /// Ensure shared_ptr is valid
   if (foodManager)
   {
      m_pkFoodManager = foodManager;
   }
}


void AIController::setObstacleManager (const std::shared_ptr<ObstacleManager>& obstacleManager)
{
   /// Ensure shared_ptr is valid
   if (obstacleManager)
   {
      m_pkObstacleManager = obstacleManager;
   }
}



/// Getters
/// AIController will check for any safe movements and randomly choose one
Movement AIController::getMove()
{
   /// Check validity of each necessary weak_ptr
   const auto& snake = m_pkSnake.lock();
   const auto& obstacleManager = m_pkObstacleManager.lock();
   const auto& snakeManager = m_pkSnakeManager.lock();
   if (snake && obstacleManager && snakeManager)
   {
      m_lastMove = snake->getLastMove();

      m_move = safeMove();
   }
   else
   {
      m_move = basicMove();
   }

   m_lastMove = m_move;
   return m_move;
}
