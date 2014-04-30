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


#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H


/// Third party
#include <prg/interactive/app.hpp>  // Parent and needed to add/remove listeners


/// Personal
#include <controllers/controller.hpp>  // Parent
#include <misc/keymap.hpp>             // m_kKeys


/// PlayerController is the primary controller used for human interaction. It listens for key events which match the keys
/// in the member Keymap and sets the desired Movement accordingly.
/// PlayerController is a leaf class.
class PlayerController final : public Controller, public prg::IKeyEvent
{
   public:
      /// Constructors and destructor
      PlayerController (const Keymap& keys);
      ~PlayerController() override;

      PlayerController (PlayerController&& move) = default;
      PlayerController (const PlayerController& copy) = default;
      PlayerController& operator= (const PlayerController& copy) = default;


      /// Functionality
      bool onKey (const KeyEvent& keyEvent) override;

      void addListener() { prg::application.addKeyListener (*this); }
      void removeListener() { prg::application.removeKeyListener (*this); }


      /// Getters
      Movement getMove() override;  /// Can't guarantee that getMove() won't modify anything

   protected:

   private:
      const Keymap m_kKeys;   /// Contains all the keys for the onKey() event to listen out for
};

#endif // PLAYERCONTROLLER_H
