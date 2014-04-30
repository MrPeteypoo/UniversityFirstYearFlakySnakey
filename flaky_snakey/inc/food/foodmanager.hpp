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


#ifndef FOODMANAGER_H
#define FOODMANAGER_H


/// STL
#include <memory>    // std::unique_ptr
#include <vector>    // std::vector


/// Personal
#include <setup/ingamesetup.hpp> // InGameSetup
#include <food/fatfood.hpp>      // FatFood
#include <food/thinfood.hpp>     // ThinFood


/// FoodManager is a designated management class, it deals with all interactions between other classes and the available
/// food in the game, it manages FatFood and ThinFood objects.
/// FoodManager is a leaf class.
class FoodManager final
{
   public:
      /// Constructors and destructor
      FoodManager (const InGameSetup& setup, const unsigned int rotInterval,
                   const unsigned int foodMin, const unsigned int foodMax, const bool demoMode = false);
      ~FoodManager();

      FoodManager (FoodManager&& move) = default;

      /// Explicitly disallow (Effective C++: Item 6)
      FoodManager (const FoodManager& copy) = delete;
      FoodManager& operator= (const FoodManager& copy) = delete;


      /// Testing functions
      bool isFoodHere (const Rectangle& rect) const;

      bool isSpawnRequired() const { return m_spawnRequired; }


      /// Functionality
      // Basic game facilities
      void pause();
      void resume();
      void update();
      void drawFood (prg::Canvas& canvas);

      // AI facilities
      const Rectangle findNearestFood (const Rectangle& rect, const bool fatFoodOnly) const;
      const Rectangle findNearestFatFood (const Rectangle& rect) const;


      /// Assignment functions
      /// Relies on being passed a rectangle containing a valid spawn location
      void addFood (const Rectangle& rect);
      void removeFood (const unsigned int index);


      /// Getters
      /// Returns maximum unsigned int if invalid
      unsigned int getFoodIndex (const Rectangle& position) const;
      int getFoodEffect (const unsigned int index) const;
      const Rectangle& getFoodPosition (const unsigned int index) const;

      unsigned int getFoodAmount() const { return m_foodP.size(); }

   protected:

   private:
      const InGameSetup m_kSetup;         /// Contains all game settings necessary for FoodManager
      const unsigned int m_kFoodMin;      /// The minimum amount of food that can exist at any point
      const unsigned int m_kFoodMax;      /// The maximum amount of food that can exist at any point
      const unsigned int m_kRotInterval;  /// How quickly ThinFood rots

      /// Contains all FatFood and ThinFood objects that exist in the game
      std::vector<std::unique_ptr<Food>> m_foodP;

      /// Incremented each time a Timer is created to guarantee that a timer can be created, 0 and 1 are reserved for the
      /// SnakeManager timer(s).
      unsigned short m_timerID;
      unsigned int m_timerCount;    /// Used to check that the 6 timer limit hasn't been exceeded
      unsigned int m_foodEffectMax; /// The largest impact food can have on a Snake

      /// Indicates that the SnakeState needs to provide a spawn point so food can spawn
      bool m_spawnRequired;

      /// Avoid a bug with faulty timers due to conflicts with the demo mode by not allowing ThinFood to rot
      bool m_demoMode;

};

#endif // FOODMANAGER_H
