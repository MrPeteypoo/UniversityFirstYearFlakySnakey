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


#ifndef MAINSNAKESTATE_H
#define MAINSNAKESTATE_H


/// Personal
#include <states/snakestate.hpp> // Parent


/// MainSnakeState is the primary gameplay state used in the game. Most functionality is derived from SnakeState but it
/// it manages when to switch to the demo or game over states whilst managing gameplay.
/// MainSnakeState is a leaf class.
class MainSnakeState final : public SnakeState
{
   public:
      MainSnakeState();

      MainSnakeState (MainSnakeState&& move) = default;
      ~MainSnakeState() override = default;

      /// Explicitly disallow (Effective C++: Item 6)
      MainSnakeState (const MainSnakeState& copy) = delete;
      MainSnakeState& operator= (const MainSnakeState& copy) = delete;


      /// Functionality
      void onUpdate() override;
      void onRender (prg::Canvas& canvas) override;
      bool onKey (const KeyEvent& keyEvent) override;
      bool onMotion (const MouseEvent& mouseEvent) override;
      bool onButton (const MouseEvent& mouseEvent) override;

   protected:

   private:
      /// Core requirements
      void reset() override;
      void prepareButtons() override;


      /// Functionality
      void drawGameOver (prg::Canvas& canvas);


      /// Members
      unsigned int m_winnerIndex;
};

#endif // MAINSNAKESTATE_H
