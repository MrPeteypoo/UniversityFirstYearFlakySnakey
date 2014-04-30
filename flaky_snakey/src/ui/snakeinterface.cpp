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


#include <ui/snakeinterface.hpp>


/// Constructors and destructor
SnakeInterface::SnakeInterface (const InGameSetup& setup)
   :  m_kSetup (setup), m_scores (4)
{
}



/// Functionality
void SnakeInterface::draw (prg::Canvas& canvas)
{
   // Used to simplify drawing code
   std::vector<prg::Colour> colours (4);
   fillColours (colours);

   const unsigned int startX = m_kSetup.getMarginX();
   const unsigned int startY = m_kSetup.getMarginY();
   const unsigned int endX = m_kSetup.getEndX();
   const unsigned int endY = m_kSetup.getEndY();
   const unsigned int uiWidth = m_kSetup.getMarginUI();

   prg::Font font ("assets/fonts/instruction.ttf", uiWidth / 10); // 10 max characters

   /// NULL represents an unused player
   for (unsigned int i {0}; i < m_scores.size(); ++i)
   {
      if (m_scores[i].getName() != "NULL")
      {
         const std::string& score = utility::intToString (m_scores[i].getScore());
         const std::string& name = m_scores[i].getName();

         unsigned int nameX;
         unsigned int nameY;
         unsigned int scoreX;
         unsigned int scoreY;
         unsigned int dimensions[2];

         /// Compute individual player positions
         switch (i)
         {
            case 0: // Player 1 == 66% up on the left side
               font.computePrintDimensions (dimensions, name);
               nameX = startX + uiWidth / 2 - dimensions[0] / 2;
               nameY = startY + (endY - startY) * 0.66 + dimensions[1];


               font.computePrintDimensions (dimensions, score);
               scoreX = startX + uiWidth / 2 - dimensions[0] / 2;
               scoreY = startY + (endY - startY) * 0.66 - dimensions[1];
               break;


            case 1: // Player 2 == 66% up on the right side
               font.computePrintDimensions (dimensions, name);
               nameX = endX + uiWidth / 2 - dimensions[0] / 2;
               nameY = startY + (endY - startY) * 0.66 + dimensions[1];


               font.computePrintDimensions (dimensions, score);
               scoreX = endX + uiWidth / 2 - dimensions[0] / 2;
               scoreY = startY + (endY - startY) * 0.66 - dimensions[1];
               break;


            case 2: // Player 3 == 33% up on the left side
               font.computePrintDimensions (dimensions, name);
               nameX = startX + uiWidth / 2 - dimensions[0] / 2;
               nameY = startY + (endY - startY) * 0.33 + dimensions[1];


               font.computePrintDimensions (dimensions, score);
               scoreX = startX + uiWidth / 2 - dimensions[0] / 2;
               scoreY = startY + (endY - startY) * 0.33 - dimensions[1];
               break;


            case 3: // Player 4 == 33% up on the right side
               font.computePrintDimensions (dimensions, name);
               nameX = endX + uiWidth / 2 - dimensions[0] / 2;
               nameY = startY + (endY - startY) * 0.33 + dimensions[1];


               font.computePrintDimensions (dimensions, score);
               scoreX = endX + uiWidth / 2 - dimensions[0] / 2;
               scoreY = startY + (endY - startY) * 0.33 - dimensions[1];
               break;

         }

         font.print (canvas, nameX, nameY, colours[i], name);
         font.print (canvas, scoreX, scoreY, colours[i], score);
      }
   }
}


/// Determines what colour each players text should be
void SnakeInterface::fillColours (std::vector<prg::Colour>& modify)
{
   // End up with less code and more efficiency by doing it using a loop
   for (unsigned int i {0}; i < modify.size(); ++i)
   {
      if (!m_scores[i].isAlive())
      {
         // White means dead
         modify[i] = {255, 255, 255};
      }
      else
      {
         switch (i)
         {
            case 0: // Player 1 == Red
               modify[i] = {255, 0, 0};
               break;

            case 1: // Player 2 == Green
               modify[i] = {0, 255, 0};
               break;

            case 2: // Player 3 == Blue
               modify[i] = {0, 0, 255};
               break;

            case 3: // Player 4 == Yellow
               modify[i] = {255, 255, 0};
         }
      }
   }
}



/// Assignment Functions
void SnakeInterface::addPlayer (const unsigned int playerNumber, const std::string& name)
{
   if (playerNumber > 3)
   {
      throw std::runtime_error ("Invalid playerNumber given to SnakeInterface::addPlayer(), shoot the programmer.");
   }

   m_scores[playerNumber].setName (name);
}


void SnakeInterface::updateScore (const unsigned int playerNumber, const unsigned int score)
{
   if (playerNumber > 3)
   {
      throw std::runtime_error ("Invalid playerNumber given to SnakeInterface::updateScore(), shoot the programmer.");
   }

   m_scores[playerNumber].setScore (score);
}


void SnakeInterface::setAlive (const unsigned int playerNumber, const bool alive)
{
   if (playerNumber > 3)
   {
      throw std::runtime_error ("Invalid playerNumber given to SnakeInterface::setLiving(), shoot the programmer.");
   }

   m_scores[playerNumber].setAlive (alive);
}



/// Getters
const std::string& SnakeInterface::getName (const unsigned int playerNumber) const
{
   if (playerNumber > 3)
   {
      throw std::runtime_error ("Invalid playerNumber given to SnakeInterface::getName(), shoot the programmer.");
   }

   return m_scores[playerNumber].getName();
}


unsigned int SnakeInterface::getScore (const unsigned int playerNumber) const
{
   if (playerNumber > 3)
   {
      throw std::runtime_error ("Invalid playerNumber given to SnakeInterface::getScore(), shoot the programmer.");
   }

   return m_scores[playerNumber].getScore();
}
