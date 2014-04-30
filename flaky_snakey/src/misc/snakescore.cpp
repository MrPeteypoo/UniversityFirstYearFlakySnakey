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


#include <misc/snakescore.hpp>


/// Constructors and destructor
SnakeScore::SnakeScore()
   :  m_name ("NULL"), m_playerNumber (999), m_score (0), m_alive (false)
{
}



/// Assignment functions
void SnakeScore::setName (const std::string& name)
{
   m_name = name;

   // Post-condition: length is 10 or less
   if (m_name.length() > 10)
   {
      m_name.resize (10);     // Maximum name length
      m_name.shrink_to_fit(); // Truncate extra characters
   }
}


/// Supports up to 10 for leaderboard functionality
void SnakeScore::setPlayerNumber (const unsigned int playerNumber)
{
   m_playerNumber = playerNumber;

   // Post-condition: m_playerNumber is less than or equal to 10.
   if (m_playerNumber > 10)
   {
      m_playerNumber = 10;
   }
}
