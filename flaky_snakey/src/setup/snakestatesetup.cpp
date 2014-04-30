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


#include <setup/snakestatesetup.hpp>


/// Constructors and destructor
SnakeStateSetup::SnakeStateSetup()
   :  InGameSetup(),
      m_keymaps (0), m_names (0),
      m_forceReset (true),
      m_human (1), m_ai (0),
      m_foodMin (1), m_foodMax (5),
      m_scoreFood (25),
      m_snakeUpdateInterval (100), m_foodRotInterval (5000), m_snakeAI ("generic")
{
   /// Future functionality: allow custom keys for the player
   for (unsigned int i {0}; i < 4; ++i)
   {
      Keymap keys;

      switch (i)
      {
         // Allow default keys for case 0
         case 1:
            keys.up = prg::IKeyEvent::KeyEvent::KB_UP_KEY;
            keys.left = prg::IKeyEvent::KeyEvent::KB_LEFT_KEY;
            keys.right = prg::IKeyEvent::KeyEvent::KB_RIGHT_KEY;
            keys.down = prg::IKeyEvent::KeyEvent::KB_DOWN_KEY;
            break;

         case 2:
            keys.up = 'i';
            keys.left = 'j';
            keys.right = 'l';
            keys.down = 'k';
            break;

         case 3:
            keys.up = '8';
            keys.left = '4';
            keys.right = '6';
            keys.down = '2';
            break;

         default:
            break;
      }

      m_keymaps.push_back (keys);
   }
}



/// Assignment functions
// Allow daisy chaining of set functions
SnakeStateSetup& SnakeStateSetup::setGrid (const unsigned int width, const unsigned int height)
{
   // Pre-condition: Guarantee at least a 8x8 grid and less than 40x40 grid
   if (width >= 8 && height >= 8 &&
         width <= 40 && height <= 40)
   {
      m_gridWidth = width;
      m_gridHeight = height;
      recalculateMembers(); // Ensure other members reflect the change

      if (m_aspectCorrection)
      {
         correctAspectRatio();
      }

      // Force recalculation of m_foodRotInterval
      setSnakeInterval (m_snakeUpdateInterval);
   }

   return *this; // Daisy chaining
}


SnakeStateSetup& SnakeStateSetup::addKeymap (const Keymap& toAdd)
{
   // Pre-condition: Maximum of four Keymaps for a maximum of four players
   if (m_keymaps.size() == 4)
   {
      m_keymaps.erase (m_keymaps.begin());
   }


   /// Add Keymap
   m_keymaps.push_back (toAdd);


   // Post-condition: Human players can't outnumber the available Keymap objects.
   if (m_human > m_keymaps.size()) { m_human = m_keymaps.size(); }

   return *this;
}


/// Handle players from 0-3 to reflect index values
SnakeStateSetup& SnakeStateSetup::setPlayerName (const unsigned int index, const std::string& name)
{
   // Pre-condition: Index > 3
   if (index < 4)
   {
      m_names[index] = name;

      if (name.size() > 10)
      {
         m_names[index].resize (10); // Maximum name length
         m_names[index].shrink_to_fit(); // Truncate extra characters
      }
   }

   return *this;
}


SnakeStateSetup& SnakeStateSetup::setPlayers (const unsigned int humans, const unsigned int ai)
{
   /// Assign values
   m_human = humans;
   m_ai = ai;


   // Post-condition: Humans can't outnumber available Keymaps
   if (m_human > m_keymaps.size())
   {
      m_human = m_keymaps.size();
   }

   // Post-condition: AI can't be > 4
   if (m_ai > 4) { m_ai = 4; }

   // Post-conditions: Humans + AI can't > 4
   if (m_human + m_ai > 4)
   {
      m_ai = 4 - m_human;
   }

   // Post-condition: Humans + AI can't == 0
   if (m_human + m_ai == 0) { ++m_ai; }

   return *this;
}


SnakeStateSetup& SnakeStateSetup::setSnakeAI (const std::string& intelligence)
{
   if (intelligence == "generic" ||
       intelligence == "dumb" ||
       intelligence == "smart")
   {
      m_snakeAI = intelligence;
   }

   return *this;
}


SnakeStateSetup& SnakeStateSetup::setFoodLimits (const unsigned int foodMin, const unsigned int foodMax)
{
   // Pre-condition: Ensure Min < Max
   if (foodMin > foodMax)
   {
      m_foodMin = foodMax;
      m_foodMax = foodMin;
   }
   else
   {
      m_foodMin = foodMin;
      m_foodMax = foodMax;
   }

   // Post-condition: Values can't == 0
   if (m_foodMin == 0) { ++m_foodMin; }

   if (m_foodMax == 0) { m_foodMax = 5; }

   // Post-condition: m_foodMax can't be > total grid cells
   if (m_foodMax > m_gridWidth * m_gridWidth)
   {
      m_foodMax = m_gridWidth * m_gridHeight;
   }

   return *this;
}


SnakeStateSetup& SnakeStateSetup::setScoring (const unsigned int food)
{
   if (food == 0)
   {
      m_scoreFood = 20;
   }

   else
   {
      m_scoreFood = food;
   }

   return *this;
}


SnakeStateSetup& SnakeStateSetup::setSnakeInterval (const unsigned int msInterval)
{
   // Set minimum value to just under 60FPS
   if (msInterval < 17)
   {
      m_snakeUpdateInterval = 17;
   }
   else
   {
      m_snakeUpdateInterval = msInterval;
   }

   // Allow the player to traverse the full height and full width once to get rotting food
   m_foodRotInterval = m_snakeUpdateInterval * (m_gridWidth + m_gridHeight);

   return *this;
}
