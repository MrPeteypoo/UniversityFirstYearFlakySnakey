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


#include <obstacles/obstaclemanager.hpp>


/// Constructors and destructor
ObstacleManager::ObstacleManager (const InGameSetup& setup, const std::vector<Obstacle>& levelObs)
   :  m_kSetup (setup), m_levelObstacles (levelObs) //, m_flakes (0)
{
   // Pre-condition: levelObs doesn't contain more obstacles than the grid size
   // Pre-condition: levelObs isn't empty
   if (levelObs.size() > m_kSetup.getGridWidth() * m_kSetup.getGridHeight() ||
         m_levelObstacles.empty())
   {
      generateDefaultWalls();
   }
}



/// Testing functions
bool ObstacleManager::isObstacleHere (const Rectangle& rect) const
{
   if (!m_levelObstacles.empty())
   {
      for (const auto& ob : m_levelObstacles)
      {
         if (ob.getRectangle().intersects (rect))
         {
            return true;
         }
      }
   }

   return false;
}


/// Ensures that default snake spawn points are clear in the passed vector
bool ObstacleManager::isSpawnSafe (const std::vector<Obstacle>& levelObs)
{
   /// Create copies of common attributes for the sake of efficiency
   const unsigned int rectWidth = m_kSetup.getRectWidth();
   const unsigned int startX = m_kSetup.getStartX();
   const unsigned int endX = m_kSetup.getEndX();

   const unsigned int rectHeight = m_kSetup.getRectHeight();
   const unsigned int startY = m_kSetup.getStartY();
   const unsigned int endY = startY + m_kSetup.getWorkingY();

   /// Create spawn points for comparison purposes
   std::vector<Rectangle> spawnPoints
   {
      // Player 1 = (2, 2)
      {
         rectWidth, rectHeight,
         startX + 2 * rectWidth, startY + 2 * rectHeight
      },

      // Player 2 = (end-2, 2)
      {
         rectWidth, rectHeight,
         endX - 3 * rectWidth, startY + 2 * rectHeight
      },

      // Player 3 = (2, end-2)
      {
         rectWidth, rectHeight,
         startX + 2 * rectWidth, endY - 3 * rectHeight
      },

      // Player 4 = (end-2, end-2)
      {
         rectWidth, rectHeight,
         endX - 3 * rectWidth, endY - 3 * rectHeight
      }
   };

   /// Check for intersections
   for (const auto& ob : levelObs)
   {
      for (const auto& spawn : spawnPoints)
      {
         if (ob.getRectangle().intersects (spawn))
         {
            return false;
         }
      }
   }

   return true;
}


/// Functionality
void ObstacleManager::drawObstacles (prg::Canvas& canvas)
{
   if (!m_levelObstacles.empty())
   {
      for (auto& ob : m_levelObstacles)
      {
         ob.draw (canvas);
      }
   }
}

/*
                  //    //
                  /      /
                    8x8
           generateDefaultWalls()
              looks like this

                  /      /
                  //    //
*/
/// When constructed with no vector this is used to generate walls around the environment
void ObstacleManager::generateDefaultWalls()
{
   /// Create copies of common attributes for the sake of efficiency
   const unsigned int gridWidth = m_kSetup.getGridWidth();
   const unsigned int rectWidth = m_kSetup.getRectWidth();
   const unsigned int startX = m_kSetup.getStartX();
   const unsigned int endX = m_kSetup.getEndX();

   const unsigned int gridHeight = m_kSetup.getGridHeight();
   const unsigned int rectHeight = m_kSetup.getRectHeight();
   const unsigned int startY = m_kSetup.getStartY();
   const unsigned int endY = m_kSetup.getEndY();


   /// Create horizontal walls
   // 25% of the grid width is wall
   for (unsigned int  i = 0; i < gridWidth / 4; ++i)
   {

      // Bottom left
      m_levelObstacles.push_back ({{rectWidth,                    rectHeight,
                                    startX + i * rectWidth,       startY}});
      // Bottom right
      m_levelObstacles.push_back ({{rectWidth,                    rectHeight,
                                    endX - (i + 1) * rectWidth,   startY}});
      // Top left
      m_levelObstacles.push_back ({{rectWidth,                    rectHeight,
                                    startX + i * rectWidth,       endY - rectHeight}});
      // Top right
      m_levelObstacles.push_back ({{rectWidth,                    rectHeight,
                                    endX - (i + 1) * rectWidth,   endY - rectHeight}});
   }


   /// Create vertical walls
   // Ensure duplicates aren't created by starting at 1
   for (unsigned int i = 1; i < gridHeight / 4; ++i)
   {
      // Bottom left
      m_levelObstacles.push_back ({{rectWidth,           rectHeight,
                                    startX,              startY + i * rectHeight}});
      // Bottom right
      m_levelObstacles.push_back ({{rectWidth,           rectHeight,
                                    endX - rectWidth,    startY + i * rectHeight}});
      // Top left
      m_levelObstacles.push_back ({{rectWidth,           rectHeight,
                                    startX,              endY - (i + 1) * rectHeight}});
      // Top right
      m_levelObstacles.push_back ({{rectWidth,           rectHeight,
                                    endX - rectWidth,    endY - (i + 1) * rectHeight}});
   }
}



/// Assignment functions
void ObstacleManager::addObstacle (const Rectangle& rect)
{
   // Although there should never be a duplicate obstacle, addObstacle will check to see if adding would cause
   // duplication.
   if (!isObstacleHere (rect))
   {
      m_levelObstacles.push_back ({{rect}});
   }


}


/// Removes all obstacles, leaves the game with no walls
void ObstacleManager::clearObstacles()
{
   m_levelObstacles.clear();
}


/// Resets all level obstacles
void ObstacleManager::setObstacles (const std::vector<Obstacle>& levelObs)
{
   // Pre-condition: levelObs doesn't contain more obstacles than the grid size
   if (levelObs.size() < m_kSetup.getGridWidth() * m_kSetup.getGridHeight())
   {

      // Ensure snake spawn points are available
      if (isSpawnSafe (levelObs))
      {
         m_levelObstacles.clear();

         for (const auto& ob : levelObs)
         {
            m_levelObstacles.push_back (ob);
         }
      }
   }
}
