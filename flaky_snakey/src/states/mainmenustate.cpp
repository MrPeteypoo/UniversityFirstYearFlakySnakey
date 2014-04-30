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


#include <states/mainmenustate.hpp>


/// Constructors and destructor
MainMenuState::MainMenuState()
   :  m_pSetup (nullptr), m_font ("assets/fonts/instruction.ttf", 10), m_title ("Flaky Snakey!"),
      m_easyButton(), m_normalButton(), m_hardButton(), m_optionsButton()
{
}



/// Core requirements
void MainMenuState::prepareButtons()
{
   /// The bottom 66% of the screen will be a 2x2 grid of buttons
   const unsigned int resX = m_pSetup->getResX();
   const unsigned int resY = m_pSetup->getResY();

   Rectangle placement { resX / 3,              resY / 4,
                         resX / 4 - resX / 6,   resY / 4 - resY / 6 };


   /// Set up buttons
   m_optionsButton.setClickableArea (placement);
   m_optionsButton.setColour ({0, 0, 255});         // Blue
   m_optionsButton.setText ("Configuration");

   // Move up
   placement.incrementPosition (0, resY / 4);
   m_easyButton.setClickableArea (placement);
   m_easyButton.setColour ({0, 255, 0});           // Green
   m_easyButton.setText ("Easy mode");

   // Move right
   placement.incrementPosition (resX / 2, 0);
   m_normalButton.setClickableArea (placement);
   m_normalButton.setColour ({255, 165, 0});       // Orange
   m_normalButton.setText ("Normal mode");

   // Move down
   placement.decrementPosition (0, resY / 4);
   m_hardButton.setClickableArea (placement);
   m_hardButton.setColour ({255, 0, 0});           // Red
   m_hardButton.setText ("Hard mode");
}


void MainMenuState::setupFont()
{
   /// Get parameters for the sake of efficiency
   const unsigned int resX = m_pSetup->getResX();
   const unsigned int resY = m_pSetup->getResY();

   // Ensure text stays in boundaries
   unsigned int textSize;

   if (resX / m_title.length() < resY / 3)
   {
      textSize = resX / m_title.length();
   }
   else
   {
      textSize = resY / 3;
   }

   m_font = prg::Font ("assets/fonts/instruction.ttf", textSize);
   //prg::Font font ("assets/fonts/instruction.ttf", textSize);
}



/// Functionality
bool MainMenuState::onCreate()
{
   // Check valid pointers
   if (!m_pSetup)
   {
      throw std::runtime_error ("Attempt to start MainMenuState with invalid data.");
   }

   prepareButtons();
   setupFont();
   return true;
}


bool MainMenuState::onDestroy()
{
   return true;
}


void MainMenuState::onEntry()
{
   // Ensure MainSnakeState gets reset if gameplay starts again
   m_pSetup->setForceReset (true);
   prg::application.addKeyListener (*this);
   prg::application.addMouseListener (*this);
}


void MainMenuState::onExit()
{
   prg::application.removeKeyListener (*this);
   prg::application.removeMouseListener (*this);
}


void MainMenuState::onUpdate()
{
   // Nothing to be done
}


void MainMenuState::onRender (prg::Canvas& canvas)
{
   drawTitle (canvas);
   m_easyButton.draw (canvas);
   m_normalButton.draw (canvas);
   m_hardButton.draw (canvas);
   m_optionsButton.draw (canvas);
}


bool MainMenuState::onKey (const KeyEvent& keyEvent)
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


bool MainMenuState::onMotion (const MouseEvent& mouseEvent)
{
   /// Disable borders
   m_easyButton.setMouseOver (false);
   m_normalButton.setMouseOver (false);
   m_hardButton.setMouseOver (false);
   m_optionsButton.setMouseOver (false);

   const Rectangle position {0, 0, (unsigned) mouseEvent.pos_x, (unsigned) mouseEvent.pos_y};

   if (m_easyButton.intersects (position))
   {
      m_easyButton.setMouseOver (true);
      return false;
   }

   else if (m_normalButton.intersects (position))
   {
      m_normalButton.setMouseOver (true);
      return false;
   }

   else if (m_hardButton.intersects (position))
   {
      m_hardButton.setMouseOver (true);
      return false;
   }

   else if (m_optionsButton.intersects (position))
   {
      m_optionsButton.setMouseOver (true);
      return false;
   }

   return true;
}


bool MainMenuState::onButton (const MouseEvent& mouseEvent)
{
   if (mouseEvent.button_state == MouseEvent::MB_DOWN && mouseEvent.button == MouseEvent::LM_BTN)
   {
      const Rectangle position {0, 0, (unsigned) mouseEvent.pos_x, (unsigned) mouseEvent.pos_y};

      if (m_easyButton.intersects (position))
      {
         m_pSetup->setScoring (25);
         m_pSetup->setSnakeInterval (150);
         m_pSetup->setSnakeAI ("generic");
         prg::application.setState ("game");
         return false;
      }

      else if (m_normalButton.intersects (position))
      {
         m_pSetup->setScoring (50);
         m_pSetup->setSnakeInterval (110);
         m_pSetup->setSnakeAI ("dumb");
         prg::application.setState ("game");
         return false;
      }

      else if (m_hardButton.intersects (position))
      {
         m_pSetup->setScoring (100);
         m_pSetup->setSnakeInterval (70);
         m_pSetup->setSnakeAI ("smart");
         prg::application.setState ("game");
         return false;
      }

      else if (m_optionsButton.intersects (position))
      {
         prg::application.setState ("config");
         return false;
      }
   }

   return true;
}


void MainMenuState::drawTitle (prg::Canvas& canvas)
{
   unsigned int dimensions[2];
   m_font.computePrintDimensions (dimensions, m_title);

   /// Draw text, top half of the screen centred.
   m_font.print (canvas,   m_pSetup->getResX() / 2 - dimensions[0] / 2,
                           m_pSetup->getResY() * 0.80 - dimensions[1] / 2, {255, 0, 255}, m_title);
}



/// Assignment functions
void MainMenuState::setSetup (const std::shared_ptr<SnakeStateSetup>& setup)
{
   if (setup)
   {
      m_pSetup = setup;
   }
}
