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


#include <states/snakestate.hpp>


/// Constructors and destructor
SnakeState::SnakeState()
   :  m_pSetup (nullptr), m_pFoodManager (nullptr), m_pObstacleManager (nullptr), m_pSnakeManager (nullptr),
      m_pUI (nullptr), m_resetButton (), m_quitButton(), m_spawnAvailable (true), m_needsReset (true)
{
}



/// Core Requirements
void SnakeState::setSetup (const std::shared_ptr<SnakeStateSetup>& setup)
{
   /// Ensure valid pointer
   if (setup)
   {
      m_pSetup = setup;
   }

   /// Call reset to prepare the game
   reset();
}



/// Functionality
bool SnakeState::onCreate()
{
   return true;
}


bool SnakeState::onDestroy()
{
   return true;
}


void SnakeState::onEntry()
{
   // Pre-condition: Check pointers
   if (m_pSetup && m_pFoodManager && m_pObstacleManager && m_pSnakeManager && m_pUI)
   {
      if (m_needsReset || m_pSetup->getForceReset())
      {
         reset ();
      }

      /// Reseed RNG
      srand (time (0));
      m_pSnakeManager->resume();
      m_pFoodManager->resume();
      prg::application.addKeyListener (*this);
      prg::application.addMouseListener (*this);
   }

   else
   {
      throw std::runtime_error ("Attempt to enter SnakeState without valid data.");
   }

}


void SnakeState::onExit()
{
   m_pSnakeManager->pause();
   m_pFoodManager->pause();
   prg::application.removeKeyListener (*this);
   prg::application.removeMouseListener (*this);
}


/// Check cross-Manager collisions
void SnakeState::updateCollisions()
{
   for (unsigned int i {0}; i < m_pSnakeManager->getSnakeAmount(); ++i)
   {
      if (m_pSnakeManager->isSnakeAlive (i))
      {
         /// Check Obstacle collision
         const auto& head = m_pSnakeManager->getSnakeHead (i);

         if (m_pObstacleManager->isObstacleHere (head))
         {
            m_pSnakeManager->killSnake (i);
         }

         /// Check Food collision manually for the sake of efficiency
         else
         {
            for (unsigned int j {0}; j < m_pFoodManager->getFoodAmount(); ++j)
            {
               if (head.intersects (m_pFoodManager->getFoodPosition (j)))
               {
                  /// Get food effect
                  m_pSnakeManager->alterSnakeSize (i, m_pFoodManager->getFoodEffect (j));
                  m_pSnakeManager->incrementScore (i, m_pSetup->getScoreFood());
                  m_pFoodManager->removeFood (j);
               }
            }
         }
      } // Do nothing if Snake is dead
   }
}


/// Extract flakes and convert into Obstacle objects
void SnakeState::processFlakes()
{
   // The vector will sink upon completion of processFlakes
   std::vector<std::unique_ptr<Rectangle>> flakes;
   m_pSnakeManager->extractFlakes (flakes);

   for (const auto& flake : flakes)
   {
      m_pObstacleManager->addObstacle (*flake);
   }
}


/// Obtain a valid spawn point for FoodManager, return {10, 10, 0, 0} if impossible
Rectangle SnakeState::findSpawnPoint()
{
   /// Increase efficiency by obtaining parameters early
   const unsigned int gridWidth = m_pSetup->getGridWidth();
   const unsigned int gridHeight = m_pSetup->getGridHeight();
   const unsigned int gridSize = gridWidth * gridHeight;
   const unsigned int rectWidth = m_pSetup->getRectWidth();
   const unsigned int rectHeight = m_pSetup->getRectHeight();
   const unsigned int startX = m_pSetup->getStartX();
   const unsigned int startY = m_pSetup->getStartY();

   /// Stores previous attempts, stops infinite looping if all spaces are full
   std::vector<Rectangle> attempted;

   while (attempted.size() != gridSize)
   {
      // Generate attempt
      Rectangle attempt {rectWidth,                                     rectHeight,
                         startX + (rectWidth * (rand() % gridWidth)),   startY + (rectHeight * (rand() % gridHeight))};

      /// Check if it's been tried before
      bool tried = false;
      for (const auto& previous : attempted)
      {
         if (attempt.intersects (previous))
         {
            tried = true;
            break;
         }
      }

      /// If it hasn't been tried then test if the position is empty
      if (!tried)
      {
         if (m_pSnakeManager->isSnakeHere (attempt) ||
             m_pObstacleManager->isObstacleHere (attempt) ||
             m_pFoodManager->isFoodHere (attempt))
         {
            attempted.push_back (attempt);
         }

         /// Found a valid spawn point!
         else
         {
            return attempt;
         }
      }
   }

   return Rectangle {10, 10, 0, 0};
}


void SnakeState::drawBorder (prg::Canvas& canvas)
{
   // A simple rectangle around the playable area
   const unsigned int startX = m_pSetup->getStartX();
   const unsigned int startY = m_pSetup->getStartY();
   const unsigned int endX = m_pSetup->getEndX();
   const unsigned int endY = m_pSetup->getEndY();

   // Don't draw unnecessary lines, the border is purple
   if (startY != 0)
   {
      // Bottom horizontal
      canvas.drawLine (startX - 1, startY - 1, endX, startY -1, {102, 0, 102});

      // Top horizontal
      canvas.drawLine (startX - 1, endY, endX, endY, {102, 0, 102});
   }

   // startX can never == 0
   // Left vertical
   canvas.drawLine (startX - 1, startY - 1, startX - 1, endY, {102, 0, 102});

   // Right vertical
   canvas.drawLine (endX, startY - 1, endX, endY, {102, 0, 102});
}
