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


#include <states/demosnakestate.hpp>


/// Constructors and destructor
DemoSnakeState::DemoSnakeState()
   :  SnakeState(), m_continueButton ()
{
}



/// Core requirements
void DemoSnakeState::reset()
{
   /// Create InGameSetup
   InGameSetup setup;
   setup.setResolution (m_pSetup->m_resX, m_pSetup->m_resY);
   setup.setGrid (m_pSetup->m_gridWidth, m_pSetup->m_gridHeight);

   /// Prepare ObstacleManager
   m_pObstacleManager = std::make_shared<ObstacleManager> (setup);


   /// Prepare FoodManager
   m_pFoodManager = std::make_shared<FoodManager> (setup, m_pSetup->m_foodRotInterval, m_pSetup->m_foodMin, m_pSetup->m_foodMax, true);

   /// Prepare SnakeManager
   m_pSnakeManager = std::make_shared<SnakeManager> (setup, 1, m_pSetup->m_snakeUpdateInterval, 0, 1, "dumb");

   m_pUI = std::make_shared<SnakeInterface>(setup);
   m_pSnakeManager->initialiseSnakes (m_pSetup->m_names, m_pUI);
   m_pSnakeManager->initialiseAI (m_pSnakeManager, m_pFoodManager, m_pObstacleManager);
   m_pSnakeManager->resume();

   /// Prepare Button objects, do it here because workingX/Y can change mid-game
   prepareButtons();

   /// Ensure that switching back to the main state won't force a reset
   m_pSetup->setForceReset (false);
   m_needsReset = false;
}


void DemoSnakeState::prepareButtons()
{
   /// A button should appear at 25%, 50% and 75% of the height, centred
   const unsigned int workingX = m_pSetup->getWorkingX();
   const unsigned int workingY = m_pSetup->getWorkingY();

   // Try to maintain proportions
   unsigned int working;

   if (workingX > workingY) { working = workingY; }

   else { working = workingX; }

   Rectangle placement { working / 2, workingY / 5,
                         m_pSetup->getStartX() + workingX / 2 - working / 4,
                         m_pSetup->getStartY() + workingY / 4 - workingY / 10 };

   /// Set up buttons
   m_quitButton.setClickableArea (placement);
   m_quitButton.setColour ({255, 0, 0});           // Red
   m_quitButton.setText ("Exit to main menu");

   placement.incrementPosition (0, workingY / 4);
   m_resetButton.setClickableArea (placement);
   m_resetButton.setColour ({255, 165, 0});        // Orange
   m_resetButton.setText ("Restart game");

   placement.incrementPosition (0, workingY / 4);
   m_continueButton.setClickableArea (placement);
   m_continueButton.setColour ({0, 255, 0});       // Green
   m_continueButton.setText ("Continue game");
}



/// Functionality
void DemoSnakeState::onUpdate()
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

   if (m_pSnakeManager->isGameOver())
   {
      reset();
   }
}


void DemoSnakeState::onRender (prg::Canvas& canvas)
{
   drawBorder (canvas);
   m_pUI->draw (canvas);

   m_pObstacleManager->drawObstacles (canvas);
   m_pFoodManager->drawFood (canvas);
   m_pSnakeManager->drawSnakes (canvas);

   m_continueButton.draw (canvas);
   m_resetButton.draw (canvas);
   m_quitButton.draw (canvas);
}


bool DemoSnakeState::onKey (const KeyEvent& keyEvent)
{
   if (keyEvent.key_state == KeyEvent::KB_DOWN)
   {
      switch (keyEvent.key)
      {
         case KeyEvent::KB_ESC_KEY:
            prg::application.exit();
            return false;

         case 'p':
         case 'P':
            prg::application.setState ("game");
      }
   }
   return true;
}


bool DemoSnakeState::onMotion (const MouseEvent& mouseEvent)
{
   /// Disable borders
   m_continueButton.setMouseOver (false);
   m_resetButton.setMouseOver (false);
   m_quitButton.setMouseOver (false);

   const Rectangle position {0, 0, (unsigned) mouseEvent.pos_x, (unsigned) mouseEvent.pos_y};

   if (m_continueButton.intersects (position))
   {
      m_continueButton.setMouseOver (true);
      return false;
   }

   else if (m_resetButton.intersects (position))
   {
      m_resetButton.setMouseOver (true);
      return false;
   }

   else if (m_quitButton.intersects (position))
   {
      m_quitButton.setMouseOver (true);
      return false;
   }

   return true;
}


bool DemoSnakeState::onButton (const MouseEvent& mouseEvent)
{
   if (mouseEvent.button_state == MouseEvent::MB_DOWN && mouseEvent.button == MouseEvent::LM_BTN)
   {
      const Rectangle position {0, 0, (unsigned) mouseEvent.pos_x, (unsigned) mouseEvent.pos_y};

      if (m_continueButton.intersects (position))
      {
         prg::application.setState ("game");
         return false;
      }

      else if (m_resetButton.intersects (position))
      {
         m_pSetup->m_forceReset = true;
         prg::application.setState ("game");
         return false;
      }

      else if (m_quitButton.intersects (position))
      {
         prg::application.setState ("menu");
         return false;
      }
   }

   return true;
}
