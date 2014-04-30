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


#include <controllers/playercontroller.hpp>


/// Constructors and destructor
PlayerController::PlayerController (const Keymap& keys)
   :  Controller(), m_kKeys (keys)
{
}


PlayerController::~PlayerController()
{
   //prg::application.removeKeyListener (*this);
}



/// Functionality
bool PlayerController::onKey (const KeyEvent& keyEvent)
{
   /// Ensure a key has been pressed down
   if (keyEvent.key_state == KeyEvent::KB_DOWN)
   {
      /// Check if key matches any of the movement keys stored in the Keymap
      if (keyEvent.key == m_kKeys.up)
      {
         m_move = Movement::Up;
         return false; // Don't pass the event to other listeners
      }

      else if (keyEvent.key == m_kKeys.left)
      {
         m_move = Movement::Left;
         return false;
      }

      else if (keyEvent.key == m_kKeys.right)
      {
         m_move = Movement::Right;
         return false;
      }

      else if (keyEvent.key == m_kKeys.down)
      {
         m_move = Movement::Down;
         return false;
      }

      else
      {
         /// Allow KeyEvent to be sent to other listeners
         return true;
      }
   }

   return true;
   /// No error checking is done because the Snake should always check input as it doesn't know if it's trustworthy,
   /// error checking is beyond the scope of Controller classes.
}



/// Getters
Movement PlayerController::getMove()
{
   // Although m_lastMove isn't used by PlayerController, set it anyway for future functionality expansion
   m_lastMove = m_move;
   return m_move;
}
