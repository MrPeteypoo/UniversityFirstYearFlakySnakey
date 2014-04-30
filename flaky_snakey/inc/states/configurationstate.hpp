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


#ifndef CONFIGURATIONSTATE_H
#define CONFIGURATIONSTATE_H


/// STL
#include <memory> // m_pSetup


/// Third party
#include <prg/interactive/app.hpp>        // onEntry()
#include <prg/interactive/app_state.hpp>  // Parent


/// Personal
#include <setup/snakestatesetup.hpp>   // m_pSetup
#include <ui/button.hpp>               // m_gridWidthButton



/// ConfigurationState is where all in-game graphical configuration is done by the player. The player can modify most game
/// settings using this state to play the way they want to.
/// ConfigurationState is a leaf class.
class ConfigurationState final : public prg::IAppState, public prg::IKeyEvent, public prg::IMouseEvent
{
   public:
      /// Constructors and destructor
      ConfigurationState();

      ConfigurationState (const ConfigurationState& copy) = default;
      ConfigurationState (ConfigurationState&& move) = default;
      ConfigurationState& operator= (const ConfigurationState& copy) = default;
      ConfigurationState& operator= (ConfigurationState&& move) = default;
      ~ConfigurationState() = default;


      /// Functionality
      bool onCreate() override;
      bool onDestroy() override;
      void onEntry() override;
      void onExit() override;
      void onUpdate() override;
      void onRender(prg::Canvas& canvas) override;
      bool onKey (const KeyEvent& keyEvent) override;
      bool onMotion (const MouseEvent& mouseEvent) override;
      bool onButton (const MouseEvent& mouseEvent) override;


      /// Assignment functions
      void setSetup (const std::shared_ptr<SnakeStateSetup>& setup);

   protected:

   private:
      /// Core requirements
      void prepareButtons();


      /// Functionality
      void onClickGridWidth (const MouseEvent& mouseEvent);
      void onClickGridHeight (const MouseEvent& mouseEvent);
      void onClickHumanPlayers (const MouseEvent& mouseEvent);
      void onClickAIPlayers (const MouseEvent& mouseEvent);
      void onClickFoodMin (const MouseEvent& mouseEvent);
      void onClickFoodMax (const MouseEvent& mouseEvent);


      /// Members
      std::shared_ptr<SnakeStateSetup> m_pSetup;   /// Contains all set up information

      Button m_gridWidthButton;        /// How many cells wide the grid is
      Button m_gridHeightButton;       /// How many cells high the grid is
      Button m_humanPlayersButton;    /// How many human players are in the game
      Button m_aiPlayersButton;        /// How many AI are in the game
      Button m_foodMinButton;          /// The minimum food
      Button m_foodMaxButton;          /// The maximum food
      Button m_returnButton;           /// Indicates to go back to the main menu
};

#endif // CONFIGURATIONSTATE_H
