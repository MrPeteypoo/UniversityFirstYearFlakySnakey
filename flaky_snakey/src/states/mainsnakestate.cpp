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


#include <states/mainsnakestate.hpp>


/// Constructors and destructor
MainSnakeState::MainSnakeState()
   :  SnakeState(), m_winnerIndex (0)
{
}



/// Core requirements
void MainSnakeState::reset()
{
   /// Create InGameSetup
   InGameSetup setup;
   setup.setResolution (m_pSetup->m_resX, m_pSetup->m_resY);
   setup.setGrid (m_pSetup->m_gridWidth, m_pSetup->m_gridHeight);

   /// Prepare FoodManager
   m_pFoodManager = std::make_shared<FoodManager> (setup, m_pSetup->m_foodRotInterval, m_pSetup->m_foodMin, m_pSetup->m_foodMax);


   /// Prepare ObstacleManager
   m_pObstacleManager = std::make_shared<ObstacleManager> (setup);


   /// Prepare SnakeManager
   m_pSnakeManager = std::make_shared<SnakeManager> (setup, 0, m_pSetup->m_snakeUpdateInterval, m_pSetup->m_human, m_pSetup->m_ai, m_pSetup->m_snakeAI);

   m_pUI = std::make_shared<SnakeInterface>(setup);
   m_pSnakeManager->initialiseSnakes (m_pSetup->m_names, m_pUI);
   m_pSnakeManager->initialisePlayers (m_pSetup->m_keymaps);
   m_pSnakeManager->initialiseAI (m_pSnakeManager, m_pFoodManager, m_pObstacleManager);
   m_pSnakeManager->resume();


   /// Prepare Button objects, do it here because workingX/Y can change mid-game
   prepareButtons();

   m_needsReset = false;
}


void MainSnakeState::prepareButtons()
{
   /// Two buttons should appear at 33% Y next to each other
   const unsigned int workingX = m_pSetup->getWorkingX();
   const unsigned int workingY = m_pSetup->getWorkingY();

   Rectangle placement { workingX / 3, workingY / 4,
                         m_pSetup->getStartX() + workingX / 4 - workingX / 6,
                         m_pSetup->getStartY() + workingY / 4 - workingY / 8 };

   /// Set up buttons
   m_resetButton.setClickableArea (placement);
   m_resetButton.setColour ({255, 165, 0});        // Orange
   m_resetButton.setText ("Restart game");

   placement.incrementPosition (workingX / 2, 0);
   m_quitButton.setClickableArea (placement);
   m_quitButton.setColour ({255, 0, 0});           // Red
   m_quitButton.setText ("Exit to main menu");
}



/// Functionality
void MainSnakeState::onUpdate()
{
   if (!m_pSnakeManager->isGameOver())
   {
      /// Update the food
      m_pFoodManager->update();
      if (m_pFoodManager->isSpawnRequired() && m_spawnAvailable)
      {
         const auto& spawn = findSpawnPoint();
         if (spawn == Rectangle {10, 10, 0, 0})
         {
            m_spawnAvailable = false;
         }

         else
         {
            m_pFoodManager->addFood (spawn);
         }
      }

      /// Update the snakes
      m_pSnakeManager->update();
      updateCollisions();
      processFlakes();
   }

   else
   {
      m_winnerIndex = m_pSnakeManager->getWinnerIndex();
   }
}


void MainSnakeState::onRender (prg::Canvas& canvas)
{
   drawBorder (canvas);
   m_pUI->draw (canvas);
   m_pObstacleManager->drawObstacles (canvas);
   m_pFoodManager->drawFood (canvas);
   m_pSnakeManager->drawSnakes (canvas);

   if (m_pSnakeManager->isGameOver())
   {
      drawGameOver (canvas);
      m_resetButton.draw (canvas);
      m_quitButton.draw (canvas);
   }
}


bool MainSnakeState::onKey (const KeyEvent& keyEvent)
{
   if (keyEvent.key_state == KeyEvent::KB_DOWN)
   {
      switch (keyEvent.key)
      {
         case KeyEvent::KB_ESC_KEY:
            prg::application.exit();
            return false;

         case 'r':
         case 'R':
            if (m_pSnakeManager->isGameOver())
            {
               reset();
               return false;
            }
            break;

         case 'p':
         case 'P':
            prg::application.setState ("pause");
      }
   }
   return true;
}


bool MainSnakeState::onMotion (const MouseEvent& mouseEvent)
{
   if (m_pSnakeManager->isGameOver())
   {
      /// Disable borders
      m_resetButton.setMouseOver (false);
      m_quitButton.setMouseOver (false);

      const Rectangle position {0, 0, (unsigned) mouseEvent.pos_x, (unsigned) mouseEvent.pos_y};

      if (m_resetButton.intersects (position))
      {
         m_resetButton.setMouseOver (true);
         return false;
      }

      else if (m_quitButton.intersects (position))
      {
         m_quitButton.setMouseOver (true);
         return false;
      }
   }

   return true;
}


bool MainSnakeState::onButton (const MouseEvent& mouseEvent)
{
   if (m_pSnakeManager->isGameOver())
   {
      if (mouseEvent.button_state == MouseEvent::MB_DOWN && mouseEvent.button == MouseEvent::LM_BTN)
      {
         const Rectangle position {0, 0, (unsigned) mouseEvent.pos_x, (unsigned) mouseEvent.pos_y};

         if (m_resetButton.intersects (position))
         {
            reset();
            return false;
         }

         else if (m_quitButton.intersects (position))
         {
            prg::application.setState ("menu");
            return false;
         }
      }
   }

   return true;
}


void MainSnakeState::drawGameOver (prg::Canvas& canvas)
{
   /// Get parameters for the sake of efficiency
   const unsigned int workingX = m_pSetup->getWorkingX();
   const unsigned int workingY = m_pSetup->getWorkingY();

   std::string winnerMessage;

   if (m_winnerIndex == std::numeric_limits<unsigned int>::max() - 1)
   {
      winnerMessage = "The game was a draw";
   }

   else // max() should never happen if this point has been reached
   {
      winnerMessage = "The winner is: " + m_pUI->getName (m_winnerIndex) + " with ";

      winnerMessage += utility::intToString (m_pUI->getScore (m_winnerIndex)) + " points";
   }


   // Ensure text stays in boundaries
   unsigned int textSize;

   if (workingX / winnerMessage.length() < workingY * 0.4)
   {
      textSize = workingX / winnerMessage.length();
   }
   else
   {
      textSize = workingY * 0.4;
   }

   /// Draw text, top half of the screen centred. Massive performance issue here which can't be avoided due to the
   /// support for many different resolutions, font has to be created each draw call.
   prg::Font font ("assets/fonts/instruction.ttf", textSize);

   unsigned int dimensions[2];
   font.computePrintDimensions (dimensions, winnerMessage);

   font.print (canvas,  m_pSetup->getStartX() + workingX / 2 - dimensions[0] / 2,
                        m_pSetup->getStartY() + workingY * 0.75 - dimensions[1] / 2,
                        {255, 0, 255}, winnerMessage);
}
