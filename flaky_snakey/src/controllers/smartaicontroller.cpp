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


#include <controllers/smartaicontroller.hpp>
#include <food/foodmanager.hpp>



/// Constructors and destructor
SmartAIController::SmartAIController(const InGameSetup& setup)
   :  AIController (setup)
{
}


// TODO: Make smarter, currently only avoids ThinFood that can kill and never switches preferred/secondary, need bigger difference than DumbAIController
/// Functionality
Movement SmartAIController::chaseFood (const Rectangle& head, const Rectangle& food)
{
   /// Improve efficiency by getting parameters
   const unsigned int startX = m_kSetup.getStartX();
   const unsigned int startY = m_kSetup.getStartY();
   const unsigned int rectWidth = m_kSetup.getRectWidth();
   const unsigned int rectHeight = m_kSetup.getRectHeight();

   unsigned int headX = (head.getX() - startX) / rectWidth;
   unsigned int headY = (head.getY() - startY) / rectHeight;
   unsigned int foodX = (food.getX() - startX) / rectWidth;
   unsigned int foodY = (food.getY() - startY) / rectHeight;

   int diffX = foodX - headX;
   int diffY = foodY - headY;
   Movement preferred, secondary;


   // Discover preferred and secondary directions, taking into account diffX/diffY == 0
   if       (diffX < 0) { preferred = Movement::Left; }
   else if  (diffX > 0) { preferred = Movement::Right; }
   else if  (diffY > 0) { preferred = Movement::Up; }
   else                 { preferred = Movement::Down; }

   if       (diffY > 0) { secondary = Movement::Up; }
   else if  (diffY < 0) { secondary = Movement::Down; }
   else if  (diffX < 0) { secondary = Movement::Left; }
   else                 { secondary = Movement::Right; }


   std::vector<Movement> moves;
   generateSafeMoves (moves);

   if (!moves.empty())
   {
      if (exists (preferred, moves))
      {
         return preferred;
      }

      else if (exists (secondary, moves))
      {
         return secondary;
      }

      else
      {
         return moves[rand() % moves.size()];
      }
   }

   // Accept death
   else
   {
      return m_lastMove;
   }
}


#include <iostream>
/// Getters
Movement SmartAIController::getMove()
{
   const auto& snake = m_pkSnake.lock();
   const auto& foodManager = m_pkFoodManager.lock();
   const auto& obstacleManager = m_pkObstacleManager.lock();
   const auto& snakeManager = m_pkSnakeManager.lock();

   if (snake && foodManager && obstacleManager && snakeManager)
   {
      m_lastMove = snake->getLastMove();
      const auto head = snake->getHead();
      Rectangle food = head;

      const unsigned int avoid = m_kSetup.getGridWidth() * m_kSetup.getGridHeight() * 0.01;
      if (snake->getSize() <= avoid)
      {
         // Only look for FatFood to prevent death
         food = foodManager->findNearestFood (head, true);
      }
      else
      {
         food = foodManager->findNearestFood (head, false);
      }

      if (head != food)
      {
         m_move = chaseFood (head, food);
      }

      // No edible food available
      else
      {
         m_move = safeMove();
      }
   }

   else // weak_ptrs are invalid
   {
      m_move = basicMove();
   }

   m_lastMove = m_move;
   return m_move;
}
