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


#ifndef SNAKEMANAGER_H
#define SNAKEMANAGER_H


/// Third party
#include <prg/interactive/app_state.hpp>  // Parent
#include <prg/interactive/timer.hpp>      // m_timer


/// Personal
#include <controllers/dumbaicontroller.hpp>  // m_aiP
#include <controllers/playercontroller.hpp>  // m_playersP
#include <controllers/smartaicontroller.hpp> // m_aiP
#include <snakes/snake.hpp>                  // m_snakesP
#include <ui/snakeinterface.hpp>             // m_pUI


/// Forward declarations
class FoodManager;
class ObstacleManager;


/// SnakeManager is completely in charge of any and all interactions between Snakes and external sources. SnakeManager also
/// takes charge of Controller classes so that they are appropriately assigned to the correct Snakes.
/// SnakeManager is a leaf class.
class SnakeManager final : public prg::ITimerEvent
{
   public:
      /// Constructors and destructor
      SnakeManager (const InGameSetup& setup, const unsigned int timer_id, const unsigned int moveInterval,
                    const unsigned int humans, const unsigned int ai, const std::string& difficulty);

      SnakeManager (SnakeManager&& move) = default;
      ~SnakeManager();

      /// Explicitly disallow (Effective C++: Item 6)
      SnakeManager (SnakeManager& copy) = delete;
      SnakeManager& operator= (SnakeManager& copy) = delete;


      /// Core requirements
      /// Create and assign names to Snake objects
      void initialiseSnakes (const std::vector<std::string>& names, const std::shared_ptr<SnakeInterface>& ui);

      /// Create and assign correct Keymap objects to PlayerController classes
      void initialisePlayers (const std::vector<Keymap>& keymaps);

      /// Create and assign correct pointers to AIController classes
      void initialiseAI (const std::shared_ptr<SnakeManager>& snakeManager, const std::shared_ptr<FoodManager>& foodManager,
                         const std::shared_ptr<ObstacleManager>& obstacleManager);


      /// Testing functions
      bool isSnakeAlive (const unsigned int index) const;
      bool isSnakeHere (const Rectangle& rect) const;

      bool isGameOver() const { return m_livingSnakes == 0; }


      /// Functionality
      void resume(); /// Must be called when game is ready to start
      void pause();  /// Must be called on change of state
      void update();
      void onTimer (prg::Timer& timer) override;
      void drawSnakes(prg::Canvas& canvas);
      void extractFlakes (std::vector<std::unique_ptr<Rectangle>>& modify);   /// Obtain all flakes and move them to modify


      /// Assignment functions
      void killSnake (const unsigned int index);
      void alterSnakeSize (const unsigned int index, const int foodEffect);
      void incrementScore (const unsigned int index, const unsigned int toAdd);


      /// Getters
      unsigned int getWinnerIndex() const;
      const Rectangle& getSnakeHead (const unsigned int index) const;

      unsigned int getSnakeAmount() const { return m_snakesP.size(); }

   protected:

   private:
      /// Testing functions
      bool snakesCrossed (const unsigned int snake, const unsigned int other);   /// See .cpp for information

      /// Functionality
      void updateSelfCollisions();  /// Check if any living snakes collide with themselves
      void updateHeadCollisions();  /// Check if any snake heads collide with each other
      void updateBodyCollisions();  /// Check if any head-body collisions happen


      /// Members
      const InGameSetup m_kSetup;      /// Required to pass to Snake and Controller objects
      const unsigned int m_kHumans;    /// The total number of human players in the game
      const unsigned int m_kAI;        /// The total number of AI players in the game
      const std::string m_kDifficulty; /// What level of AI should be spawned

      std::vector<std::shared_ptr<Snake>> m_snakesP;  /// Contains every Snake in the game

      /// Separate the PlayerController objects from the AIController objects to ensure that each PlayerController removes
      /// its key listener from prg::application before changing state.
      std::vector<std::shared_ptr<PlayerController>> m_playersP;
      std::vector<std::shared_ptr<AIController>> m_aiP;

      unsigned int m_livingSnakes;           /// The number of living Snakes
      std::shared_ptr<SnakeInterface> m_pUI; /// All scores are updated to the UI
      prg::Timer m_timer;                    /// A timer used to move all Snakes at the set interval
};

#endif // SNAKEMANAGER_H
