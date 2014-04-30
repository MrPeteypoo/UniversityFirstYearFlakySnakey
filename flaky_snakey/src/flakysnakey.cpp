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


#include <flakysnakey.hpp>


/// Constructors and destructor
FlakySnakey::FlakySnakey()
   :  m_pSetup (std::make_shared<SnakeStateSetup>()),
      m_pMainMenu (new MainMenuState()), m_pConfig (new ConfigurationState()),
      m_pMainGame (new MainSnakeState()), m_pPauseDemo (new DemoSnakeState())
{
}



/// Functionality
int FlakySnakey::run()
{
   try
   {
      if (initialise())
      {
         prg::application.setClearColour ({0,0,0});
         prg::application.run (m_pSetup->getResX(), m_pSetup->getResY(), "Simon Peter Campbell", "n3053620");
      }
      close();

      return 0;
   }

   catch (std::exception& error)
   {
      log (1, error.what());
      return 1;
   }

   catch (...)
   {
      log (1, "An unknown error occurred.");
      return -1;
   }
}


/// Run through the set up and prepare the game, returns whether to run or close the game
bool FlakySnakey::initialise()
{
   /// Obtain game resolution required to start the game
   bool successful = false;
   while (!successful)
   {
      try
      {
         std::cout << "Welcome to Flaky Snakey. Please input the resolution to play the game at:\n"
                   << "e.g. 1280 720, 1920 1080, 640 480. 0 0 to exit.\n\n";

         unsigned int resX, resY;
         if (std::cin >> resX >> resY)
         {
            // Exit the game
            if (resX == 0 || resY == 0)
            {
               return false;
            }

            m_pSetup->setResolution (resX, resY);

            // Check for invalid resolution
            if (m_pSetup->getResX() != resX || m_pSetup->getResY() != resY)
            {
               throw std::runtime_error ("Invalid resolution, min is 640x480 and max is 2560x1440.");
            }

            else
            {
               successful = true;
            }
         }

         else
         {
            throw std::runtime_error ("Unable to determine resolution.");
         }
      }

      catch (std::exception& e)
      {
         std::cerr << "An error occurred: " << e.what() << "\n\n";
         utility::flushCin();
      }
   }


   /// Output controls
   std::cout << "\nControls:\n"
             << "Exit:\t \tESCAPE\n"
             << "Pause:\t \tP\n\n"
             << "P1 Up:\t \tW\n"
             << "P1 Left: \tA\n"
             << "P1 Right: \tD\n"
             << "P1 Down: \tS\n"
             << "P2 Up:\t \tUp Arrow\n"
             << "P2 Left: \tLeft Arrow\n"
             << "P2 Right: \tRight Arrow\n"
             << "P2 Down: \tDown Arrow\n"
             << "P3 Up:\t \tI\n"
             << "P3 Left: \tJ\n"
             << "P3 Right: \tL\n"
             << "P3 Down: \tK\n"
             << "P4 Up:\t \t8\n"
             << "P4 Left: \t4\n"
             << "P4 Right: \t6\n"
             << "P4 Down: \t2\n";


   /// Default settings
   m_pSetup->setGrid (20, 20);
   m_pSetup->setPlayers (1, 0);


   /// Set up states
   m_pMainMenu->setSetup (m_pSetup);
   m_pConfig->setSetup (m_pSetup);
   m_pMainGame->setSetup (m_pSetup);
   m_pPauseDemo->setSetup (m_pSetup);

   prg::application.addState ("menu", *m_pMainMenu);
   prg::application.addState ("config", *m_pConfig);
   prg::application.addState ("game", *m_pMainGame);
   prg::application.addState ("pause", *m_pPauseDemo);

   prg::application.setState ("menu");

   return true;
}


/// Perform shutdown process
void FlakySnakey::close()
{
   log (0, "Flaky Snakey closed successfully.");
}


/// Logs an error, type = 0 for info and 1 for error
void FlakySnakey::log (const unsigned int type, const std::string& error)
{
   switch (type)
   {
      case 0: // Clean exit
      {
         prg::Log::Message infoMessage (prg::Log::Message::LT_Info);
         infoMessage << error << '\n';
         prg::logger.add (infoMessage);
         break;
      }
      case 1: // Dirty exit
      {
         prg::Log::Message errorMessage (prg::Log::Message::LT_Error);
         errorMessage << "Flaky Snakey terminated for the following reason: " << error << '\n';
         prg::logger.add (errorMessage);
      }
      default:
         break;
   }
}
