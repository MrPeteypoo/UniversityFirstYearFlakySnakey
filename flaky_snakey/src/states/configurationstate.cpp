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


#include <states/configurationstate.hpp>


/// Constructors and destructor
ConfigurationState::ConfigurationState()
   :  m_pSetup (nullptr), m_gridWidthButton(), m_gridHeightButton(), m_humanPlayersButton(), m_aiPlayersButton(),
      m_foodMinButton(), m_foodMaxButton(), m_returnButton()
{
}



/// Core requirements
void ConfigurationState::prepareButtons()
{
   /// The bottom 66% of the screen will be a 2x2 grid of buttons
   const unsigned int resX = m_pSetup->getResX();
   const unsigned int resY = m_pSetup->getResY();

   Rectangle placement { resX / 3,              resY / 5,
                         resX / 2 - resX / 6,   resY / 5 - resY / 10 };


   /// Set up buttons
   m_returnButton.setClickableArea (placement);
   m_returnButton.setColour ({255, 0, 255});       // Purple
   m_returnButton.setText ("Return to Main Menu");


   // Move up and left
   placement.setPosition (resX / 4 - resX / 6, placement.getY() + resY / 5);
   m_foodMinButton.setClickableArea (placement);
   m_foodMinButton.setColour ({0, 0, 255});        // Blue
   m_foodMinButton.setText ("FoodMin: " + utility::intToString (m_pSetup->getFoodMin()));


   // Move right
   placement.incrementPosition (resX / 2, 0);
   m_foodMaxButton.setClickableArea (placement);
   m_foodMaxButton.setColour ({0, 0, 255});        // Blue
   m_foodMaxButton.setText ("FoodMax: " + utility::intToString (m_pSetup->getFoodMax()));


   // Move up
   placement.incrementPosition (0, resY / 5);
   m_aiPlayersButton.setClickableArea (placement);
   m_aiPlayersButton.setColour ({0, 255, 0});      // Green
   m_aiPlayersButton.setText ("AI: " + utility::intToString (m_pSetup->getAI()));


   // Move left
   placement.decrementPosition (resX / 2, 0);
   m_humanPlayersButton.setClickableArea (placement);
   m_humanPlayersButton.setColour ({0, 255, 0});   // Green
   m_humanPlayersButton.setText ("Humans: " + utility::intToString (m_pSetup->getHumans()));


   // Move up
   placement.incrementPosition (0, resY / 5);
   m_gridWidthButton.setClickableArea (placement);
   m_gridWidthButton.setColour ({255, 0, 0});      // Red
   m_gridWidthButton.setText ("Grid Width: " + utility::intToString (m_pSetup->getGridWidth()));


   // Move right
   placement.incrementPosition (resX / 2, 0);
   m_gridHeightButton.setClickableArea (placement);
   m_gridHeightButton.setColour ({255, 0, 0});     // Red
   m_gridHeightButton.setText ("Grid Height: " + utility::intToString (m_pSetup->getGridHeight()));
}


/// Functionality
bool ConfigurationState::onCreate()
{
   if (!m_pSetup)
   {
      throw std::runtime_error ("Attempt to start ConfigurationState with invalid data.");
   }

   prepareButtons();
   return true;
}


bool ConfigurationState::onDestroy()
{
   return true;
}


void ConfigurationState::onEntry()
{
   prg::application.addKeyListener (*this);
   prg::application.addMouseListener (*this);
}


void ConfigurationState::onExit()
{
   prg::application.removeKeyListener (*this);
   prg::application.removeMouseListener (*this);
}


void ConfigurationState::onUpdate()
{
   // Nothing to be done
}


void ConfigurationState::onRender (prg::Canvas& canvas)
{
   m_gridWidthButton.draw (canvas);
   m_gridHeightButton.draw (canvas);
   m_humanPlayersButton.draw (canvas);
   m_aiPlayersButton.draw (canvas);
   m_foodMinButton.draw (canvas);
   m_foodMaxButton.draw (canvas);
   m_returnButton.draw (canvas);
}


bool ConfigurationState::onKey (const KeyEvent& keyEvent)
{
   if (keyEvent.key_state == KeyEvent::KB_DOWN)
   {
      switch (keyEvent.key)
      {
         case KeyEvent::KB_ESC_KEY:
            prg::application.exit();
            return false;
      }
   }
   return true;
}


bool ConfigurationState::onMotion (const MouseEvent& mouseEvent)
{
   /// Disable borders
   m_gridWidthButton.setMouseOver (false);
   m_gridHeightButton.setMouseOver (false);
   m_humanPlayersButton.setMouseOver (false);
   m_aiPlayersButton.setMouseOver (false);
   m_foodMinButton.setMouseOver (false);
   m_foodMaxButton.setMouseOver (false);
   m_returnButton.setMouseOver (false);

   const Rectangle position {0, 0, (unsigned) mouseEvent.pos_x, (unsigned) mouseEvent.pos_y};

   if (m_gridWidthButton.intersects (position))
   {
      m_gridWidthButton.setMouseOver (true);
      return false;
   }

   else if (m_gridHeightButton.intersects (position))
   {
      m_gridHeightButton.setMouseOver (true);
      return false;
   }

   else if (m_humanPlayersButton.intersects (position))
   {
      m_humanPlayersButton.setMouseOver (true);
      return false;
   }

   else if (m_aiPlayersButton.intersects (position))
   {
      m_aiPlayersButton.setMouseOver (true);
      return false;
   }

   else if (m_foodMinButton.intersects (position))
   {
      m_foodMinButton.setMouseOver (true);
      return false;
   }

   else if (m_foodMaxButton.intersects (position))
   {
      m_foodMaxButton.setMouseOver (true);
      return false;
   }

   else if (m_returnButton.intersects (position))
   {
      m_returnButton.setMouseOver (true);
      return false;
   }

   return true;
}


bool ConfigurationState::onButton (const MouseEvent& mouseEvent)
{
   if (mouseEvent.button_state == MouseEvent::MB_DOWN &&
      (mouseEvent.button == MouseEvent::LM_BTN || mouseEvent.button == MouseEvent::RM_BTN))
   {
      const Rectangle position {0, 0, (unsigned) mouseEvent.pos_x, (unsigned) mouseEvent.pos_y};


      /// Determine correct function to run
      if (m_gridWidthButton.intersects (position))
      {
         onClickGridWidth (mouseEvent);
         return false;
      }

      else if (m_gridHeightButton.intersects (position))
      {
         onClickGridHeight (mouseEvent);
         return false;
      }

      else if (m_humanPlayersButton.intersects (position))
      {
         onClickHumanPlayers (mouseEvent);
         return false;
      }

      else if (m_aiPlayersButton.intersects (position))
      {
         onClickAIPlayers (mouseEvent);
         return false;
      }

      else if (m_foodMinButton.intersects (position))
      {
         onClickFoodMin (mouseEvent);
         return false;
      }

      else if (m_foodMaxButton.intersects (position))
      {
         onClickFoodMax (mouseEvent);
         return false;
      }

      else if (m_returnButton.intersects (position))
      {
         prg::application.setState ("menu");
         return false;
      }
   }


   return true;
}


void ConfigurationState::onClickGridWidth (const MouseEvent& mouseEvent)
{
   unsigned int gridWidth = m_pSetup->getGridWidth();

   // Increase gridWidth
   if (mouseEvent.button == MouseEvent::LM_BTN)
   {
      if (gridWidth != 40)
      {
         ++gridWidth;
      }
   }
   // Decrease gridWidth
   else
   {
      if (gridWidth != 8)
      {
         --gridWidth;
      }
   }

   m_pSetup->setGrid (gridWidth, m_pSetup->getGridHeight());

   // Confirm correct data by retrieving from m_pSetup
   m_gridWidthButton.setText ("Grid Width: " + utility::intToString (m_pSetup->getGridWidth()));
}


void ConfigurationState::onClickGridHeight (const MouseEvent& mouseEvent)
{
   unsigned int gridHeight = m_pSetup->getGridHeight();

   // Increase gridHeight
   if (mouseEvent.button == MouseEvent::LM_BTN)
   {
      if (gridHeight != 40)
      {
         ++gridHeight;
      }
   }
   // Decrease gridHeight
   else
   {
      if (gridHeight != 8)
      {
         --gridHeight;
      }
   }

   m_pSetup->setGrid (m_pSetup->getGridWidth(), gridHeight);

   // Confirm correct data by retrieving from m_pSetup
   m_gridHeightButton.setText ("Grid Height: " + utility::intToString (m_pSetup->getGridHeight()));
}


void ConfigurationState::onClickHumanPlayers (const MouseEvent& mouseEvent)
{
   unsigned int humans = m_pSetup->getHumans();

   // Increase humans
   if (mouseEvent.button == MouseEvent::LM_BTN)
   {
      if (humans != 4)
      {
         ++humans;
      }
   }
   // Decrease humans
   else
   {
      if (humans != 0)
      {
         --humans;
      }
   }

   m_pSetup->setPlayers (humans, m_pSetup->getAI());

   // Ensure minimum value is reflected by updating AI too
   m_humanPlayersButton.setText ("Humans: " + utility::intToString (m_pSetup->getHumans()));
   m_aiPlayersButton.setText ("AI: " + utility::intToString (m_pSetup->getAI()));
}


void ConfigurationState::onClickAIPlayers (const MouseEvent& mouseEvent)
{
   unsigned int ai = m_pSetup->getAI();

   // Increase ai
   if (mouseEvent.button == MouseEvent::LM_BTN)
   {
      if (ai != 4)
      {
         ++ai;
      }
   }
   // Decrease ai
   else
   {
      if (ai != 0)
      {
         --ai;
      }
   }

   m_pSetup->setPlayers (m_pSetup->getHumans(), ai);

   // Ensure minimum value is reflected by updating humans too
   m_humanPlayersButton.setText ("Humans: " + utility::intToString (m_pSetup->getHumans()));
   m_aiPlayersButton.setText ("AI: " + utility::intToString (m_pSetup->getAI()));
}


void ConfigurationState::onClickFoodMin (const MouseEvent& mouseEvent)
{
   unsigned int foodMin = m_pSetup->getFoodMin();

   // Increase foodMin
   if (mouseEvent.button == MouseEvent::LM_BTN)
   {
      if (foodMin != m_pSetup->getGridWidth() * m_pSetup->getGridHeight() / 2)
      {
         ++foodMin;
      }
   }
   // Decrease foodMin
   else
   {
      if (foodMin != 0)
      {
         --foodMin;
      }
   }

   m_pSetup->setFoodLimits (foodMin, m_pSetup->getFoodMax());

   // Ensure minimum value is reflected by updating foodMax too
   m_foodMinButton.setText ("FoodMin: " + utility::intToString (m_pSetup->getFoodMin()));
   m_foodMaxButton.setText ("FoodMax: " + utility::intToString (m_pSetup->getFoodMax()));
}


void ConfigurationState::onClickFoodMax (const MouseEvent& mouseEvent)
{
   unsigned int foodMax = m_pSetup->getFoodMax();

   // Increase foodMax
   if (mouseEvent.button == MouseEvent::LM_BTN)
   {
      if (foodMax != m_pSetup->getGridWidth() * m_pSetup->getGridHeight() / 2)
      {
         ++foodMax;
      }
   }
   // Decrease foodMax
   else
   {
      if (foodMax != 0)
      {
         --foodMax;
      }
   }

   m_pSetup->setFoodLimits (m_pSetup->getFoodMin(), foodMax);

   // Ensure minimum value is reflected by updating foodMin too
   m_foodMinButton.setText ("FoodMin: " + utility::intToString (m_pSetup->getFoodMin()));
   m_foodMaxButton.setText ("FoodMax: " + utility::intToString (m_pSetup->getFoodMax()));
}



/// Assignment functions
void ConfigurationState::setSetup (const std::shared_ptr<SnakeStateSetup>& setup)
{
   if (setup)
   {
      m_pSetup = setup;
   }
}
