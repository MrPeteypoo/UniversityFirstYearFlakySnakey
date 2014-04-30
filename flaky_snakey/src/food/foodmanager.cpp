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


#include <food/foodmanager.hpp>


/// Indicate the FoodManager is ready for food to be spawned
FoodManager::FoodManager (const InGameSetup& setup, const unsigned int rotInterval,
                          const unsigned int foodMin, const unsigned int foodMax, const bool demoMode)
   :  m_kSetup (setup), m_kFoodMin (foodMin), m_kFoodMax (foodMax), m_kRotInterval (rotInterval),
      m_foodP (0),
      m_timerID (2), m_timerCount (0), m_foodEffectMax (1),
      m_spawnRequired (false), m_demoMode (demoMode)
{
   // Pre-condition: Ensure min can't be > max
   if (foodMin > foodMax)
   {
      throw std::runtime_error ("foodMin > foodMax in FoodManager(), shoot the programmer.");
   }

   // Max food effect is 1% of total grid size
   m_foodEffectMax = m_kSetup.getGridWidth() * m_kSetup.getGridHeight() * 0.01;

   if (m_foodP.size() < m_kFoodMin)
   {
      m_spawnRequired = true;
   }
}


FoodManager::~FoodManager()
{
   pause();
}



/// Testing functions
bool FoodManager::isFoodHere (const Rectangle& rect) const
{
   /// Simply check the vector for intersecting rectangles
   for (const auto& food : m_foodP)
   {
      if (rect.intersects (food->getRectangle()))
      {
         return true;
      }
   }

   return false;
}



/// Functionality
// Basic game facilities
void FoodManager::pause()
{
   for (const auto& food : m_foodP)
   {
      food->pause();
   }
}


void FoodManager::resume()
{
   for (const auto& food : m_foodP)
   {
      food->resume();
   }
}


void FoodManager::update()
{
   /// Check if any food is rotten
   for (unsigned int i {0}; i < m_foodP.size(); ++i)
   {
      if (m_foodP[i]->isRotten())
      {
         m_foodP.erase (m_foodP.begin() + i--);
         --m_timerCount;
      }
   }

   /// Check if the minimum amount of food exists
   if (m_foodP.size() < m_kFoodMin)
   {
      m_spawnRequired = true;
   }

   /// Check if food can be spawned
   else if (m_foodP.size() < m_kFoodMax)
   {
      /// 1% chance per 64 cells (8x8) for food to spawn
      if (rand() % 1000 < (m_kSetup.getGridWidth() * m_kSetup.getGridHeight() / 64.0))
      {
         m_spawnRequired = true;
      }
   }
}


void FoodManager::drawFood (prg::Canvas& canvas)
{
   /// Simply call draw on all Food objects
   for (const auto& food : m_foodP)
   {
      food->draw (canvas);
   }
}


// AI facilities
const Rectangle FoodManager::findNearestFood (const Rectangle& rect, const bool fatFoodOnly) const
{
   // Pre-condition: Food is available
   if (m_foodP.empty()) { return rect; }

   /// Reduce function calls by obtaining constantly accessed data
   const unsigned int rectWidth = m_kSetup.getRectWidth();
   const unsigned int rectHeight = m_kSetup.getRectHeight();
   const unsigned int startX = m_kSetup.getStartX();
   const unsigned int startY = m_kSetup.getStartY();
   const unsigned int rectX = (rect.getX() - startX) / rectWidth;
   const unsigned int rectY = (rect.getY() - startY) / rectHeight;

   // Create some fail-safe defaults
   Rectangle closest = rect;
   unsigned int closestTotal = std::numeric_limits<unsigned int>::max();

   unsigned int tempX, tempY, diffX, diffY, diffTotal;
   for (const auto& food : m_foodP)
   {
      if (!fatFoodOnly || food->getFoodEffect() > 0)
      {
         /// Obtain food co-ordinates on the grid
         tempX = (food->getRectangle().getX() - startX) / rectWidth;
         tempY = (food->getRectangle().getY() - startY) / rectHeight;

         /// Determine difference, maintain positive numbers
         if (rectX > tempX) { diffX = rectX - tempX; }

         else { diffX = tempX - rectX; }

         if (rectY > tempY) { diffY = rectY - tempY; }

         else { diffY = tempY - rectY; }

         /// Compare values
         diffTotal = diffX + diffY;

         if (diffTotal < closestTotal)
         {
            closest = food->getRectangle();
            closestTotal = diffTotal;
         }
      }
   }

   return closest;
}



/// Assignment functions
/// Relies on being passed a rectangle containing a valid spawn location
void FoodManager::addFood (const Rectangle& rect)
{
   // FoodManager has no idea what other manager classes exist so it has to assume it's being passed a valid location
   // to spawn food. Therefore, it can only check against its own food locations.
   if (isFoodHere (rect))
   {
      throw std::runtime_error ("Attempt to spawn Food in occupied cell, shoot the programmer.");
   }

   std::unique_ptr<Food> food;
   const unsigned int rng = rand() % 100;

   /// 75% chance for spawning FatFood
   if (rng < 75 || m_timerCount == 6)
   {
      food.reset (new FatFood {rect});
   }

   /// 25% chance for spawning ThinFood
   else
   {
      if (!m_demoMode)
      {
         /// EXTENDED GAME RULE: ThinFood rot in 5 seconds
         food.reset (new ThinFood {m_timerID++, m_kRotInterval, rect});
         ++m_timerCount;

         // 0 and 1 are reserved for SnakeManager
         if (m_timerID < 2 || m_timerID == 255) { m_timerID = 2; }
      }
      else
      {
         food.reset (new ThinFood {rect});
      }
   }

   food->setFoodEffect (1, m_foodEffectMax);

   m_foodP.push_back (std::move (food));

   if (m_foodP.size() >= m_kFoodMin)
   {
      m_spawnRequired = false;
   }
}


void FoodManager::removeFood (const unsigned int index)
{
   // Pre-condition: index won't cause an out of bounds error
   if (index > m_foodP.size())
   {
      throw std::runtime_error ("Out of bounds error in FoodManager::removeFood(), shoot the programmer.");
   }

   if (m_foodP[index]->getTimerID() != 255)
   {
      --m_timerCount;
   }

   // unique_ptr takes care of deallocation
   m_foodP.erase (m_foodP.begin() + index);
}



/// Getters
/// Returns maximum unsigned int if invalid
unsigned int FoodManager::getFoodIndex (const Rectangle& position) const
{
   for (unsigned int i {0}; i < m_foodP.size(); ++i)
   {
      if (position == m_foodP[i]->getRectangle())
      {
         return i;
      }
   }

   return std::numeric_limits<unsigned int>::max();
}


int FoodManager::getFoodEffect (const unsigned int index) const
{
   // Pre-condition: index won't cause an out of bounds error
   if (index > m_foodP.size())
   {
      throw std::runtime_error ("Out of bounds error in FoodManager::getFoodEffect(), shoot the programmer.");
   }

   return m_foodP[index]->getFoodEffect();
}

const Rectangle& FoodManager::getFoodPosition (const unsigned int index) const
{
   // Pre-condition: index won't cause an out of bounds error
   if (index > m_foodP.size())
   {
      throw std::runtime_error ("Out of bounds error in FoodManager::getFoodPosition(), shoot the programmer.");
   }

   return m_foodP[index]->getRectangle();
}
