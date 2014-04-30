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


#ifndef GAMESTATESETUP_H
#define GAMESTATESETUP_H


/// STL
#include <string> // m_namesP
#include <vector> // m_keymapsP


/// Third party
#include <prg/interactive/app_state.hpp> // Constructor


/// Personal
#include <setup/ingamesetup.hpp> // Parent
#include <misc/keymap.hpp> // Given to PlayerController classes


/// This class is used to provide the extra data needed for SnakeState to function correctly and efficiently. Most is
/// required at creation, the rest is used constantly during runtime.
/// SnakeStateSetup is a leaf class.
class SnakeStateSetup final : public InGameSetup
{
   public:
      /// Constructors and destructor
      SnakeStateSetup();
      SnakeStateSetup (const SnakeStateSetup& copy) = default;
      SnakeStateSetup (SnakeStateSetup&& move) = default;
      SnakeStateSetup& operator= (const SnakeStateSetup& copy) = default;
      ~SnakeStateSetup() = default;


      /// Assignment functions
      // Allow daisy chaining of set functions
      SnakeStateSetup& addKeymap (const Keymap& toAdd);

      /// Handle players from 0-3 to reflect index values
      SnakeStateSetup& setGrid (const unsigned int width, const unsigned int height) override;
      SnakeStateSetup& setPlayerName (const unsigned int index, const std::string& name);
      SnakeStateSetup& setPlayers (const unsigned int humans, const unsigned int ai);
      SnakeStateSetup& setSnakeAI (const std::string& intelligence);
      SnakeStateSetup& setFoodLimits (const unsigned int foodMin, const unsigned int foodMax);
      SnakeStateSetup& setScoring (const unsigned int food);
      SnakeStateSetup& setSnakeInterval (const unsigned int msInterval);

      SnakeStateSetup& setForceReset (const bool reset) { m_forceReset = reset; return *this; }


      /// Getters
      bool getForceReset() const                   { return m_forceReset; }
      unsigned int getHumans() const               { return m_human; }
      unsigned int getAI() const                   { return m_ai; }
      unsigned int getFoodMin() const              { return m_foodMin; }
      unsigned int getFoodMax() const              { return m_foodMax; }
      unsigned int getScoreFood() const            { return m_scoreFood; }
      unsigned int getSnakeUpdateInterval() const  { return m_snakeUpdateInterval; }
      unsigned int getFoodRotInterval() const      { return m_foodRotInterval; }
      const std::string& getSnakeAI() const        { return m_snakeAI; }


      friend class SnakeState;      // Only SnakeState and derivatives can access the vectors
      friend class MainSnakeState;
      friend class DemoSnakeState;

   protected:

   private:
      std::vector<Keymap> m_keymaps;      /// Stores keymaps for PlayerController
      std::vector<std::string> m_names;   /// Store all player names

      bool m_forceReset;                  /// Should the main state force reset itself?
      unsigned int m_human;               /// The number of humans in the play session
      unsigned int m_ai;                  /// The number of AI in the play session
      unsigned int m_foodMin;             /// The required amount of food at any time
      unsigned int m_foodMax;             /// The potential amount of food at any time
      unsigned int m_scoreFood;           /// The score achieved by eating some food
      unsigned int m_snakeUpdateInterval; /// How often (in ms) the snakes are updated
      unsigned int m_foodRotInterval;     /// How quickly the ThinFood rot
      std::string m_snakeAI;              /// How smart the AI snakes are
};

#endif // GAMESTATESETUP_H
