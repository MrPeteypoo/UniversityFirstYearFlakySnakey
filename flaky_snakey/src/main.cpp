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


/*
   Flaky Snakey, by Simon Peter Campbell.

   This collection of code is a game based upon the classic Snake game. Key features include single player, multiplayer,
   vector graphics, and many configurable game options.

   Common code conventions used in this game:

   Headers:
   /// STL           Indicates that the header comes from the STL
   /// Third party   The header comes from a third party library such as FMOD or PRG
   /// Personal      The header includes classes or functions specifically written by me for the game

   Classes and Functions:
   ClassName                     Classes all start with a capital and use camel case
   parameterName                 Represents local scope variables such as parameters or function variables
   functionName()                All functions follow the previous case example
   isFunction() & canFunction()  Read-only testing functions which return booleans
   setFunction()                 Sets the value of a variable indicated in the name
   getFunction()                 Typically read-only which returns the value of a member variable

   Members:
   m_member          All member variables are prefixed with m_
   m_members         Represents the use of a container (plural)
   m_initialism      Initialism will be lower case if it's the first word (m_aiP)
   m_bobINITIALISM   Initialism will be upper case if it's not the first word (m_snakeAI)
   m_kMember         Member is const
   m_pMember         Member is a pointer
   m_pkMember        Member is a pointer to const
   m_membersP        Member is a container of pointers

   Comments:
   ///         Used for headings and important comments
   //          Less important, just for clarity

   Code statistics (minus license comments):
   Code only            3857 lines  (59%)
   Code and comments    336 lines   (5%)
   Comments             843 lines   (13%)
   Empty                1525 lines  (23%)

*/


/// Personal
#include <flakysnakey.hpp> // Game class


int main()
{
   FlakySnakey game;
   int code = game.run();
   return code;
}
