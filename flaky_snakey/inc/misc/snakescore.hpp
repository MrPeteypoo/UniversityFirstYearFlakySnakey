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


#ifndef SNAKESCORE_H
#define SNAKESCORE_H


/// STL
#include <string>


/// SnakeScore is primarily a data class which is used to represent a player in the games score on the user interface.
/// Although the primary use case is SnakeInterface, future leaderboard functionality would make use of SnakeScore.
/// SnakeScore is a leaf class.
class SnakeScore final
{
   public:
      /// Constructors and destructor
      SnakeScore();
      SnakeScore (const SnakeScore& copy) = default;
      SnakeScore (SnakeScore&& move) = default;
      SnakeScore& operator= (const SnakeScore& copy) = default;
      ~SnakeScore() = default;


      /// Testing functions
      bool isAlive() const { return m_alive; }


      /// Assignment functions
      void setName (const std::string& name);
      void setPlayerNumber (const unsigned int playerNumber);

      void setAlive (const bool alive)          { m_alive = alive; }
      void setScore (const unsigned int score)  { m_score = score; }


      /// Getters
      const std::string& getName() const     { return m_name; }
      unsigned int getPlayerNumber() const   { return m_playerNumber; }
      unsigned int getScore() const          { return m_score; }

   protected:
   private:
      std::string m_name;           /// The name of the Snake
      unsigned int m_playerNumber;  /// The corresponding player number of the Snake
      unsigned int m_score;         /// The score of the Snake
      bool m_alive;                 /// Whether the Snake is alive or not
};

#endif // SNAKESCORE_H
