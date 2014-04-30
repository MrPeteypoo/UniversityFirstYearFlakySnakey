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


#ifndef SNAKESTATE_H
#define SNAKESTATE_H


/// STL
#include <ctime>  // time(0)


/// Third party
#include <prg/interactive/app_state.hpp>  // Parent


/// Personal
#include <food/foodmanager.hpp>           // onEntry()
#include <obstacles/obstaclemanager.hpp>  // updateCollisions()
#include <setup/snakestatesetup.hpp>      // m_pSetup
#include <snakes/snakemanager.hpp>        // onEntry()
#include <ui/button.hpp>                  // m_resetButton


/// Forward declaration
class ObstacleManager;


/// SnakeState is the main gameplay state class. Every piece of gameplay is managed with this class. SnakeState is
/// designed to be a base class for more specific implementations, for example a pause state would inherit SnakeState as
/// it functions incredibly similarly but has slight differences which are handled in the derived class.
/// SnakeState manages all interactions between the manager classes.
/// SnakeState is a branch class.
class SnakeState : public prg::IAppState, public prg::IKeyEvent, public prg::IMouseEvent
{
   public:
      /// Constructors and destructor
      SnakeState();

      SnakeState (SnakeState&& move) = default;
      virtual ~SnakeState() = default;

      /// Explicitly disallow (Effective C++: Item 6)
      SnakeState (SnakeState& copy) = delete;
      SnakeState& operator= (SnakeState& copy) = delete;


      /// Core requirements
      void setSetup (const std::shared_ptr<SnakeStateSetup>& setup);


      /// Functionality
      /// Maintain virtual nature for derived classes
      bool onCreate() override;
      bool onDestroy() override;
      void onEntry() override;
      void onExit() override;
      virtual void onUpdate() override = 0;
      virtual void onRender (prg::Canvas& canvas) override = 0;
      virtual bool onKey (const KeyEvent& keyEvent) override = 0;
      virtual bool onMotion (const MouseEvent& mouseEvent) override = 0;
      virtual bool onButton (const MouseEvent& mouseEvent) override = 0;

   protected:
      /// Core requirements
      virtual void reset() = 0;           /// Starts the game again
      virtual void prepareButtons() = 0;  /// Prepares and places buttons

      /// Functionality
      void drawBorder (prg::Canvas& canvas); /// Draws a border around the play area
      void updateCollisions();               /// Check all cross-Manager collisions
      void processFlakes();                  /// Extract flakes and convert into Obstacle objects
      Rectangle findSpawnPoint();   /// Obtain a valid spawn point for FoodManager, return {10, 10, 0, 0} if impossible


      /// Members
      std::shared_ptr<SnakeStateSetup> m_pSetup;            /// Contains all information necessary for the game to work
      std::shared_ptr<FoodManager> m_pFoodManager;          /// Manages all Food objects
      std::shared_ptr<ObstacleManager> m_pObstacleManager;  /// Manages all Obstacle objects
      std::shared_ptr<SnakeManager> m_pSnakeManager;        /// Manages all Snake objects
      std::shared_ptr<SnakeInterface> m_pUI;                /// Contains information on current Snake scores


      Button m_resetButton;   /// Allows for restarting the game
      Button m_quitButton;    /// Allows for quitting of the game

      /// Is a spawn available for FoodManager? This is merely to avoid an infinite loop if all cells are occupied
      bool m_spawnAvailable;

      /// Is a reset needed due to in-game events? (e.g. isGameOver())
      bool m_needsReset;

   private:

};

#endif // SNAKESTATE_H
