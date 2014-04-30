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


#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H


/// STL
#include <memory> // m_pSetup


/// Third Party
#include <prg/interactive/app_state.hpp>  // Parent
#include <prg/interactive/app.hpp>        // onEntry()


/// Personal
#include <setup/snakestatesetup.hpp>   // m_pSetup
#include <ui/button.hpp>               // m_easyButton


class MainMenuState final : public prg::IAppState, public prg::IKeyEvent, public prg::IMouseEvent
{
   public:
      /// Constructors and destructor
      MainMenuState();

      MainMenuState (const MainMenuState& copy) = default;
      MainMenuState (MainMenuState&& move) = default;
      MainMenuState& operator= (const MainMenuState& copy) = default;
      MainMenuState& operator= (MainMenuState&& move) = default;
      ~MainMenuState() = default;


      /// Functionality
      bool onCreate() override;
      bool onDestroy() override;
      void onEntry() override;
      void onExit() override;
      void onUpdate() override;
      void onRender (prg::Canvas& canvas) override;
      bool onKey (const KeyEvent& keyEvent) override;
      bool onMotion (const MouseEvent& mouseEvent) override;
      bool onButton (const MouseEvent& mouseEvent) override;


      /// Assignment functions
      void setSetup (const std::shared_ptr<SnakeStateSetup>& setup);

   protected:
   private:
      /// Core requirements
      void prepareButtons();
      void setupFont();

      /// Functionality
      void drawTitle (prg::Canvas& canvas);


      /// Members
      std::shared_ptr<SnakeStateSetup> m_pSetup;   /// The main setup class used through

      /// Font object used for rendering, there's a massive performance issue having to create one every time draw()
      /// is called
      prg::Font m_font;
      std::string m_title;    /// The title of the game

      Button m_easyButton;    /// Triggers easy mode
      Button m_normalButton;  /// Triggers normal mode
      Button m_hardButton;    /// Triggers hard mode
      Button m_optionsButton; /// Opens the options menu
};

#endif // MAINMENUSTATE_H
