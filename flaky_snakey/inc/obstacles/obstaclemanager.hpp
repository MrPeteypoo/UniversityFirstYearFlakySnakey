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


#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H


/// STL
#include <vector>    // m_levelObstacles


/// Personal
#include <setup/ingamesetup.hpp> // m_setup
#include <obstacles/obstacle.hpp> // m_levelObstacles


/// ObstacleManager is responsible for the storage and usage of all objects in the Obstacle base class, it manages
/// no derivatives such as Food.
/// ObstacleManager is a leaf class.
class ObstacleManager final
{
   public:
      /// Constructors and destructor
      // levelObs would allow for level editor functionality
      ObstacleManager (const InGameSetup& setup, const std::vector<Obstacle>& levelObs = {});

      ObstacleManager (ObstacleManager&& move) = default;
      ~ObstacleManager() = default;

      /// Explicitly disallow (Effective C++: Item 6)
      ObstacleManager (const ObstacleManager& copy) = delete;
      ObstacleManager& operator= (const ObstacleManager& copy) = delete;


      /// Testing functions
      bool isObstacleHere (const Rectangle& rect) const;


      /// Functionality
      void drawObstacles (prg::Canvas& canvas);


      /// Assignment functions
      void addObstacle (const Rectangle& rect);                   /// Adds an Obstacle to the vector
      void clearObstacles();                                      /// Completely clears the vector
      void setObstacles (const std::vector<Obstacle>& levelObs);  /// Resets obstacles to levelObs

   protected:

   private:
      /// Core requirements
      /// When constructed with no vector this is used to generate walls around the environment
      void generateDefaultWalls();


      /// Testing functions
      /// Ensures that default snake spawn points are clear in the passed vector
      bool isSpawnSafe (const std::vector<Obstacle>& levelObs);


      /// Members
      const InGameSetup m_kSetup;               /// Contains all information required for rendering
      std::vector<Obstacle> m_levelObstacles;   /// Stores all default obstacles
};

#endif // OBSTACLEMANAGER_H
