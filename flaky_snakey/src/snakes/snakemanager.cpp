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


#include <snakes/snakemanager.hpp>


/// Constructors and destructor
SnakeManager::SnakeManager (const InGameSetup& setup, const unsigned int timer_id, const unsigned int moveInterval,
                            const unsigned int humans, const unsigned int ai, const std::string& difficulty)
   :  m_kSetup (setup), m_kHumans (humans), m_kAI (ai), m_kDifficulty (difficulty),
      m_snakesP (0), m_playersP (0), m_aiP (0), m_livingSnakes (0),
      m_pUI (nullptr), m_timer (timer_id, moveInterval, *this)
{
   // Pre-condition: Must not be 0 snakes in total
   if (m_kHumans + m_kAI == 0)
   {
      throw std::runtime_error ("Attempt to create SnakeManager that manages no snakes.");
   }
}


SnakeManager::~SnakeManager()
{
   /// Stop PlayerController objects from being listeners to prevent crashing
   pause();
}



/// Core requirements
/// Create and assign names to Snake objects
void SnakeManager::initialiseSnakes (const std::vector<std::string>& names, const std::shared_ptr<SnakeInterface>& ui)
{
   if (!ui)
   {
      throw std::runtime_error ("Attempt to incorrect set up UI at SnakeManager::initialisesnakes()");
   }

   m_pUI = ui;

   for (unsigned int i {0}; i < m_kHumans + m_kAI; ++i)
   {

      auto snake = std::make_shared<Snake> (m_kSetup, i);
      if (i < names.size())
      {
         snake->setName (names[i]);
      }

      ui->addPlayer (i, snake->getName());
      m_snakesP.push_back (std::move (snake));
   }

   m_livingSnakes = m_snakesP.size();
}


/// Create and assign correct Keymap objects to PlayerController classes
void SnakeManager::initialisePlayers (const std::vector<Keymap>& keymaps)
{
   // Pre-condition: Enough Keymap objects for everyone
   if (keymaps.size() < m_kHumans)
   {
      throw std::runtime_error ("Attempt to initialise SnakeManager with too few key maps.");
   }
   else
   {
      // Can't use range-based loop due to accessing multiple vectors
      for (unsigned int i {0}; i < m_kHumans; ++i)
      {
         auto player = std::make_shared<PlayerController> (keymaps[i]);
         player->setSnake (m_snakesP[i]);
         m_snakesP[i]->setController (player);

         m_playersP.push_back (std::move (player));
      }
   }
}


/// Create and assign correct pointers to AIController classes
void SnakeManager::initialiseAI (const std::shared_ptr<SnakeManager>& snakeManager,
                                 const std::shared_ptr<FoodManager>& foodManager,
                                 const std::shared_ptr<ObstacleManager>& obstacleManager)
{
   // AIController objects are always placed after PlayerController objects
   for (unsigned int i {m_kHumans}; i < m_kHumans + m_kAI; ++i)
   {
      std::shared_ptr<AIController> ai;

      if (m_kDifficulty == "dumb")
      {
         ai = std::make_shared<DumbAIController> (m_kSetup);
      }
      else if (m_kDifficulty == "smart")
      {
         ai = std::make_shared<SmartAIController> (m_kSetup);
      }
      else
      {
         ai = std::make_shared<AIController> (m_kSetup);
      }

      ai->setSnakeManager (snakeManager);
      ai->setFoodManager (foodManager);
      ai->setObstacleManager (obstacleManager);
      ai->setSnake (m_snakesP[i]);
      m_snakesP[i]->setController (ai);

      m_aiP.push_back (std::move (ai));
   }
}



/// Testing functions
bool SnakeManager::isSnakeAlive (const unsigned int index) const
{
   // Pre-condition: Index < m_snakesP.size()
   if (index > m_snakesP.size())
   {
      throw std::runtime_error ("Index too high in SnakeManager::isSnakeAlive().");
   }

   return m_snakesP[index]->isAlive();
}


bool SnakeManager::isSnakeHere (const Rectangle& rect) const
{
   for (const auto& snake : m_snakesP)
   {
      if (snake->intersects (rect))
      {
         return true;
      }
   }
   return false;
}


/// If both Snake objects are only a head and they go straight towards each other they can pass through each other
/// because their heads technically never intersect, this function checks that possibility.
bool SnakeManager::snakesCrossed (const unsigned int snake, const unsigned int other)
{
   // Pre-condition: Both indexes are valid
   if (snake > m_snakesP.size() || other > m_snakesP.size() || snake == other)
   {
      throw std::runtime_error ("Invalid use of SnakeManager::snakesCrossed().");
   }

   // It can only happen if both snakes are just a head
   if (m_snakesP[snake]->getSize() == 1 && m_snakesP[other]->getSize() == 1)
   {
      /// Test if moves are opposite
      switch (m_snakesP[snake]->getLastMove())
      {
         case Movement::Up:
            if (m_snakesP[other]->getLastMove() == Movement::Down)
            {
               /// Test if the previous position of snake intersects with other
               auto head = m_snakesP[snake]->getHead();
               head.decrementPosition (0, m_kSetup.getRectHeight());

               if (head.intersects (m_snakesP[other]->getHead()))
               {
                  return true;
               }
            }
            return false;

         case Movement::Left:
            if (m_snakesP[other]->getLastMove() == Movement::Right)
            {
               auto head = m_snakesP[snake]->getHead();
               head.incrementPosition (m_kSetup.getRectWidth(), 0);

               if (head.intersects (m_snakesP[other]->getHead()))
               {
                  return true;
               }
            }
            return false;

         case Movement::Right:
            if (m_snakesP[other]->getLastMove() == Movement::Left)
            {
               auto head = m_snakesP[snake]->getHead();
               head.decrementPosition (m_kSetup.getRectWidth(), 0);

               if (head.intersects (m_snakesP[other]->getHead()))
               {
                  return true;
               }
            }
            return false;

         case Movement::Down:
            if (m_snakesP[other]->getLastMove() == Movement::Up)
            {
               auto head = m_snakesP[snake]->getHead();
               head.incrementPosition (0, m_kSetup.getRectHeight());

               if (head.intersects (m_snakesP[other]->getHead()))
               {
                  return true;
               }
            }
            return false;

         default: // This should never happen
            return false;
      }
   }
   return false;
}



/// Functionality
/// Must be called when game is ready to start
void SnakeManager::resume()
{
   m_timer.start();
   for (const auto& player : m_playersP)
   {
      player->addListener();
   }
}


/// Must be called on change of state
void SnakeManager::pause()
{
   m_timer.stop();
   for (const auto& player : m_playersP)
   {
      player->removeListener();
   }
}


void SnakeManager::update()
{
   // All that needs to be done is to determine how many snakes are still alive
   m_livingSnakes = 0;

   // Split the functions up for the sake of clarity
   updateSelfCollisions();
   updateHeadCollisions();
   updateBodyCollisions();

   for (unsigned int i {0}; i < m_snakesP.size(); ++i)
   {
      const auto& snake = m_snakesP[i];

      m_pUI->updateScore (i, snake->getScore());
      m_pUI->setAlive (i, snake->isAlive());
      if (snake->isAlive())
      {
         ++m_livingSnakes;
      }
   }
}


/// Check if any living snakes collide with themselves and kill them
void SnakeManager::updateSelfCollisions()
{
   for (const auto& snake : m_snakesP)
   {
      if (snake->isAlive())
      {
         snake->checkSelfCollision();
      }
   }
}


/// Check cross-snake collisions and kill them
void SnakeManager::updateHeadCollisions()
{
   /// Avoid range-based loop for maximum efficiency
   for (unsigned int i {0}; i < m_snakesP.size(); ++i)
   {
      const auto& snake = m_snakesP[i];
      const auto& head = snake->getHead();

      // Avoid checking against self or previous comparisons
      for (unsigned int j {i+1}; j < m_snakesP.size(); ++j)
      {
         auto& other = m_snakesP[j];

         if (head.intersects (other->getHead()) || snakesCrossed (i, j))
         {
            if (other->isAlive())
            {
               if (snake->getSize() > other->getSize())
               {
                  // Prevent snake from dying from future comparisons with other until it moves again
                  // This gives one chance to turn away from the competing snake.
                  snake->setPassThrough (true);
                  other->killSnake();
               }
               else if (snake->getSize() < other->getSize())
               {
                  snake->killSnake();
                  other->setPassThrough (true);
               }
               else // sizes are equal
               {
                  snake->killSnake();
                  other->killSnake();
               }
            }

            else if (!snake->canPassThrough())
            {
               snake->killSnake();
            }
            /// If snake->canPassThrough && !other->isAlive(dd) then allow snake to live
         }
      }
   }
}


/// Check if any head-body collisions happen
void SnakeManager::updateBodyCollisions()
{
   // Avoid self-collision detection by avoiding range-based loops
   for (unsigned int i {0}; i < m_snakesP.size(); ++i)
   {
      const auto& snake = m_snakesP[i];
      if (snake->isAlive())
      {
         for (unsigned int j {0}; j < m_snakesP.size(); ++j)
         {
            if (i != j && m_snakesP[j]->intersectsBody (snake->getHead()))
            {
               snake->killSnake();
               // Ensure that rolling back snake won't kill the other Snake
               if (m_snakesP[j]->isAlive())
               {
                  m_snakesP[j]->setPassThrough (true);
               }
            }
         }
      }
   }
}


void SnakeManager::onTimer (prg::Timer& timer)
{
   /// Move all living snakes
   for (const auto& snake : m_snakesP)
   {
      if (snake->isAlive())
      {
         snake->moveSnake();
      }
   }
}


void SnakeManager::drawSnakes(prg::Canvas& canvas)
{
   /// Draw dead snakes first so head-on collisions make it look like the small snake got crushed
   for (const auto& snake : m_snakesP)
   {
      if (!snake->isAlive())
      {
         snake->draw (canvas);
      }
   }

   for (const auto& snake : m_snakesP)
   {
      if (snake->isAlive())
      {
         snake->draw (canvas);
      }
   }
}


/// Obtain all flakes and move them to modify
void SnakeManager::extractFlakes (std::vector<std::unique_ptr<Rectangle>>& modify)
{
   // Have all Snake objects flake into modify
   for (const auto& snake : m_snakesP)
   {
      snake->extractFlakes (modify);
   }
}



/// Assignment functions
void SnakeManager::killSnake (const unsigned int index)
{
   // Pre-condition: Index < m_snakesP.size()
   if (index > m_snakesP.size())
   {
      throw std::runtime_error ("Index too high in SnakeManager::killSnake().");
   }
   m_snakesP[index]->killSnake();
   --m_livingSnakes;
}


void SnakeManager::alterSnakeSize (const unsigned int index, const int foodEffect)
{
   // Pre-condition: Index < m_snakesP.size()
   if (index > m_snakesP.size())
   {
      throw std::runtime_error ("Index too high in SnakeManager::alterSnakeSize().");
   }
   m_snakesP[index]->alterSnakeSize (foodEffect);
}


void SnakeManager::incrementScore (const unsigned int index, const unsigned int toAdd)
{
   // Pre-condition: Index < m_snakesP.size()
   if (index > m_snakesP.size())
   {
      throw std::runtime_error ("Index too high in SnakeManager::incrementScore().");
   }
   m_snakesP[index]->incrementScore (toAdd);
}



/// Getters
unsigned int SnakeManager::getWinnerIndex() const
{
   // Pre-condition: !empty()
   if (m_snakesP.empty())
   {
      return std::numeric_limits<unsigned int>::max();
   }

   unsigned int winnerIndex = 0;
   unsigned int winnerScore = 0;
   unsigned int winnerSize = 0;

   for (unsigned int i {0}; i < m_snakesP.size(); ++i)
   {
      const auto& snake = m_snakesP[i];

      if ((snake->getScore() > winnerScore) ||
          (snake->getScore() == winnerScore && snake->getSize() > winnerSize))
      {
         winnerIndex = i;
         winnerScore = snake->getScore();
         winnerSize = snake->getSize();
      }

      else if (snake->getScore() == winnerScore && snake->getSize() == winnerSize)
      {
         // max() - 1 indicates a draw
         winnerIndex = std::numeric_limits<unsigned int>::max() - 1;
      }

   }

   return winnerIndex;
}


const Rectangle& SnakeManager::getSnakeHead (const unsigned int index) const
{
   // Pre-condition: Index < m_snakesP.size()
   if (index > m_snakesP.size())
   {
      throw std::runtime_error ("Index too high in SnakeManager::getSnakeHead().");
   }
   return m_snakesP[index]->getHead();
}

