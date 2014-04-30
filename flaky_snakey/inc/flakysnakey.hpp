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


#ifndef FLAKYSNAKEY_H
#define FLAKYSNAKEY_H


/// STL
#include <stdexcept> // run()


/// Third party
#include <prg/core/log.hpp> // run()


/// Personal
#include <states/mainmenustate.hpp>       // initialise()
#include <states/configurationstate.hpp>  // initialise()
#include <states/mainsnakestate.hpp>      // initialise()
#include <states/demosnakestate.hpp>      // initialise()


/// FlakySnakey is a simple encapsulation of the entire game initialisation, running and shutdown. It provides an easy
/// interface for the main() function.
/// FlakySnake is a leaf class.
class FlakySnakey final
{
   public:
      /// Constructors and destructor
      FlakySnakey();

      ~FlakySnakey() = default;

      /// Explicitly disallow (Effective C++: Item 6)
      FlakySnakey (FlakySnakey&& move) = delete;
      FlakySnakey (FlakySnakey& copy) = delete;
      FlakySnakey& operator= (FlakySnakey& copy) = delete;


      /// Functionality
      /// Runs the game and returns error codes
      int run();

   protected:

   private:
      /// Functionality
      bool initialise();   /// Run through the set up and prepare the game
      void close();        /// Perform shutdown process

      /// Logs an error, type = 0 for info and 1 for error
      void log (const unsigned int type, const std::string& error);


      /// Members
      std::shared_ptr<SnakeStateSetup> m_pSetup;      /// Contains shared set up information
      std::unique_ptr<MainMenuState> m_pMainMenu;     /// The main menu
      std::unique_ptr<ConfigurationState> m_pConfig;  /// The configurations menu
      std::unique_ptr<MainSnakeState> m_pMainGame;    /// The main game state
      std::unique_ptr<DemoSnakeState> m_pPauseDemo;   /// The pause game state
};

#endif // FLAKYSNAKEY_H
