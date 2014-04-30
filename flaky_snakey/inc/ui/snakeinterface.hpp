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


#ifndef SNAKEINTERFACE_H
#define SNAKEINTERFACE_H


/// STL
#include <stdexcept> // addPlayer()
#include <vector>    // m_scores


/// Third party
#include <prg/core/font.hpp>  // draw()
#include <prg/core/image.hpp> // draw()


/// Personal
#include <interfaces/idrawable.hpp> // Parent
#include <misc/snakescore.hpp>      // m_scores
#include <misc/snakeutilities.hpp>  // draw()
#include <setup/ingamesetup.hpp>    // m_kSetup


/// SnakeInterface is used to display the scoring and naming of each Snake player, whether CPU or human. It's designed to
/// be used with SnakeManager but could work with anything that can give it the information it needs
/// SnakeInterface is a leaf class.
class SnakeInterface final : public IDrawable
{
   public:
      /// Constructors and destructor
      SnakeInterface (const InGameSetup& setup);

      SnakeInterface (const SnakeInterface& copy) = default;
      SnakeInterface (SnakeInterface&& move) = default;
      SnakeInterface& operator= (const SnakeInterface& copy) = default;
      ~SnakeInterface() = default;


      /// Functionality
      void draw (prg::Canvas& canvas) override;


      /// Assignment functions
      void addPlayer (const unsigned int playerNumber, const std::string& name);
      void updateScore (const unsigned int playerNumber, const unsigned int score);
      void setAlive (const unsigned int playerNumber, const bool alive);


      /// Getters
      const std::string& getName (const unsigned int playerNumber) const;
      unsigned int getScore (const unsigned int playerNumber) const;

   protected:

   private:
      /// Functionality
      void fillColours (std::vector<prg::Colour>& modify);   /// Determines what colour each players text should be


      /// Members
      const InGameSetup m_kSetup;         /// Contains all necessary settings to draw to the screen
      std::vector<SnakeScore> m_scores;   /// Contains all snakes scores, names, numbers and living state

};

#endif // SNAKEINTERFACE_H
