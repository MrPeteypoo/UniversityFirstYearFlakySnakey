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


#include <snakes/snake.hpp>
#include <controllers/controller.hpp>


/// Constructors and destructor
Snake::Snake (const InGameSetup& setup, const unsigned int playerNumber, const std::string& name)
   :  m_partsP (0), m_flakesP (0), m_lastEnd (nullptr), m_pController (),
      m_kSetup (setup), m_kPlayerNumber (playerNumber), m_name (name), m_colour (0, 0, 0),
      m_alive (true), m_passThrough (false) , m_score (0), m_lastMove (Movement::Null)
{
   /// Generate starting values for Snake, handle playerNumber 0-3
   switch (m_kPlayerNumber)
   {
      case 0: // Red
         if (m_name == "")
         {
            m_name = "Player 1";
         }

         m_colour.setR (255).setG (0).setB (0);
         m_lastMove = Movement::Right;
         generateSpawn();
         break;

      case 1: // Green
         if (m_name == "")
         {
            m_name = "Player 2";
         }

         m_colour.setR (0).setG (255).setB (0);
         m_lastMove = Movement::Down;
         generateSpawn();
         break;

      case 2: // Blue
         if (m_name == "")
         {
            m_name = "Player 3";
         }

         m_colour.setR (0).setG (0).setB (255);
         m_lastMove = Movement::Up;
         generateSpawn();
         break;

      case 3: // Yellow
         if (m_name == "")
         {
            m_name = "Player 4";
         }

         m_colour.setR (255).setG (255).setB (0);
         m_lastMove = Movement::Left;
         generateSpawn();
         break;

      default:
         throw std::runtime_error ("Attempt to assign an invalid player number to Snake().");
         break;
   }
}



/// Core requirements
/// Generate spawn point based on m_playerNumber
void Snake::generateSpawn()
{
   switch (m_kPlayerNumber)
   {
      case 0:
      {
         m_partsP.push_front
         (std::unique_ptr<Rectangle>
            (
               new Rectangle // Player 1 = (2, end-2)
               (
                  m_kSetup.getRectWidth(), m_kSetup.getRectHeight(),
                  m_kSetup.getStartX() + 2 * m_kSetup.getRectWidth(),
                  m_kSetup.getEndY() - 3 * m_kSetup.getRectHeight()
               )
            )
         );

         break;
      }

      case 1:
      {
         m_partsP.push_front
         (std::unique_ptr<Rectangle>
            (
               new Rectangle // Player 2 = (end-2, end-2)
               (
                  m_kSetup.getRectWidth(), m_kSetup.getRectHeight(),
                  m_kSetup.getEndX() - 3 * m_kSetup.getRectWidth(),
                  m_kSetup.getEndY() - 3 * m_kSetup.getRectHeight()
               )
            )
         );

         break;
      }

      case 2:
      {
         m_partsP.push_front
         (std::unique_ptr<Rectangle>
            (new Rectangle // Player 3 = (2, 2)
               (
                  m_kSetup.getRectWidth(), m_kSetup.getRectHeight(),
                  m_kSetup.getStartX() + 2 * m_kSetup.getRectWidth(),
                  m_kSetup.getStartY() + 2 * m_kSetup.getRectHeight()
               )
            )
         );

         break;
      }

      case 3:
      {
         m_partsP.push_front
         (std::unique_ptr<Rectangle>
            (new Rectangle   // Player 4 = (end-2, 2)
               (
                  m_kSetup.getRectWidth(), m_kSetup.getRectHeight(),
                  m_kSetup.getEndX() - 3 * m_kSetup.getRectWidth(),
                  m_kSetup.getStartY() + 2 * m_kSetup.getRectHeight()
               )
            )
         );

         break;
      }

      default:
         throw std::runtime_error ("Default triggered in Snake::generateSpawn(), this should never happen.");
   }
}



/// Testing functions
bool Snake::intersects (const Rectangle& rect) const
{
   for (const auto& part : m_partsP)
   {
      if (rect.intersects (*part))
      {
         return true;
      }
   }

   return false;
}


/// Only tests the body of the Snake, useful for SnakeManager
bool Snake::intersectsBody (const Rectangle& rect) const
{
   bool first = true;

   for (const auto& part : m_partsP)
   {
      if (!first)
      {
         if (rect.intersects (*part))
         {
            return true;
         }
      }
      else
      {
         first = false;
      }
   }

   return false;
}


/// Prevent Snake objects from moving backwards
bool Snake::isValidMove (Movement move) const
{
   switch (move)
   {
      case Movement::Up:
         switch (m_lastMove)
         {
            case Movement::Up:
            case Movement::Left:
            case Movement::Right:
               return true;

            default:
               return false;
         }

      case Movement::Left:
         switch (m_lastMove)
         {
            case Movement::Left:
            case Movement::Up:
            case Movement::Down:
               return true;

            default:
               return false;
         }

      case Movement::Right:
         switch (m_lastMove)
         {
            case Movement::Right:
            case Movement::Up:
            case Movement::Down:
               return true;

            default:
               return false;
         }

      case Movement::Down:
         switch (m_lastMove)
         {
            case Movement::Down:
            case Movement::Left:
            case Movement::Right:
               return true;

            default:
               return false;
         }

      default:
         return false; // If Controller passes Movement::Null this will be triggered
   }

   return false;
}



/// Functionality
void Snake::draw (prg::Canvas& canvas)
{
   /// Calls each relevant draw() function
   bool first = true;

   for (const auto& part : m_partsP)
   {
      if (!first)
      {
         drawBody (canvas, *part); // Dereference the unique pointer
      }
      else
      {
         drawHead (canvas, *part);
         first = false;
      }
   }
}


/// The head is a triangle, pointing in the correct direction
void Snake::drawHead (prg::Canvas& canvas, const Rectangle& head)
{
   /// Get parameters for the sake of efficiency
   const unsigned int x = head.getX();
   const unsigned int y = head.getY();
   const unsigned int width = head.getWidth();
   const unsigned int height = head.getHeight();

   switch (m_lastMove)
   {
      case Movement::Up:
         // Bottom line
         canvas.drawLine (x,              y,
                          x + width,      y,                m_colour);

         // Left line
         canvas.drawLine (x,              y,
                          x + width / 2,  y + height,       m_colour);

         // Right line
         canvas.drawLine (x + width,      y,
                          x + width / 2,  y + height,       m_colour);
         break;

      case Movement::Left:
         // Right line
         canvas.drawLine (x + width,      y,
                          x + width,      y + height,       m_colour);

         // Bottom line
         canvas.drawLine (x + width,      y,
                          x,              y + height / 2,   m_colour);

         // Top line
         canvas.drawLine (x + width,      y + height,
                          x,              y + height / 2,   m_colour);
         break;

      case Movement::Right:
         // Left line
         canvas.drawLine (x,              y,
                          x,              y + height,       m_colour);

         // Bottom line
         canvas.drawLine (x,              y,
                          x + width,      y + height / 2,   m_colour);

         // Top line
         canvas.drawLine (x,              y + height,
                          x + width,      y + height / 2,   m_colour);
         break;

      case Movement::Down:
         // Top line
         canvas.drawLine (x,              y + height,
                          x + width,      y + height,       m_colour);

         // Left line
         canvas.drawLine (x,              y + height,
                          x + width / 2,  y,                m_colour);

         // Right line
         canvas.drawLine (x + width,      y + height,
                          x + width / 2,  y,                m_colour);
         break;

      default: // This can't happen
         break;
   }

   /// Draw death indicating lines
   if (!m_alive)
   {
      switch (m_lastMove) // Check separately to reduce code duplication
      {
         case Movement::Up:
         case Movement::Down:
            // Bottom to top line
            canvas.drawLine (x + width / 2,  y,
                             x + width / 2,  y + height,   m_colour);
            break;

         case Movement::Left:
         case Movement::Right:
            // Left to right line
            canvas.drawLine (x,              y + height / 2,
                             x + width,      y + height / 2,   m_colour);
            break;

         default: // This can't happen
            break;
      }
   }
}


/// Body parts are square
void Snake::drawBody (prg::Canvas& canvas, const Rectangle& body)
{
   /// Get parameters for the sake of efficiency
   const unsigned int x = body.getX();
   const unsigned int y = body.getY();
   const unsigned int width = body.getWidth();
   const unsigned int height = body.getHeight();

   // Bottom line
   canvas.drawLine (x,           y,
                    x + width,   y,          m_colour);

   // Top line
   canvas.drawLine (x,           y + height,
                    x + width,   y + height, m_colour);

   // Left line
   canvas.drawLine (x,           y,
                    x,           y + height, m_colour);

   // Right line
   canvas.drawLine (x + width,   y,
                    x + width,   y + height, m_colour);

   /// Draw death indicating lines
   if (!m_alive)
   {
      // Left diagonal
      canvas.drawLine (x,              y,
                       x + width,      y + height,       m_colour);

      // Right diagonal
      canvas.drawLine (x,              y + height,
                       x + width,      y,                m_colour);
   }
}


void Snake::moveSnake()
{
   // Pre-condition: Snake is alive
   if (m_alive)
   {
      /// Check if a controller can be used to get the next move
      Movement currentMove;
      auto controller = m_pController.lock();

      if (controller)
      {
         currentMove = controller->getMove();

         if (!isValidMove (currentMove))
         {
            currentMove = m_lastMove;
         }
      }

      else
      {
         currentMove = m_lastMove;
      }

      /// Create new front, ready for moving to its new position
      std::unique_ptr<Rectangle> toPush (new Rectangle (m_kSetup.getRectWidth(), m_kSetup.getRectHeight(),
                                         m_partsP.front()->getX(), m_partsP.front()->getY()));

      /// Ensure boundary checking so the Snake will appear at the other side
      switch (currentMove)
      {
         case Movement::Up:
            utility::moveCell (m_kSetup, *toPush, 0, 1);
            break;

         case Movement::Left:
            utility::moveCell (m_kSetup, *toPush, -1, 0);
            break;

         case Movement::Right:
            utility::moveCell (m_kSetup, *toPush, 1, 0);
            break;

         case Movement::Down:
            utility::moveCell (m_kSetup, *toPush, 0, -1);
            break;

         default: // Should never happen
            break;
      }

      /// Simulate movement and maintain last position to facilitate rolling back
      m_partsP.push_front (std::move (toPush));
      m_lastEnd = std::move (m_partsP.back());
      m_partsP.pop_back();

      m_lastMove = currentMove;
      m_passThrough = false;
   }
}


/// Check if the head collides with the body
void Snake::checkSelfCollision()
{
   // Make sure the head doesn't collide with itself
   bool first = true;
   const Rectangle& head = *m_partsP.front();

   for (const auto& body : m_partsP)
   {
      if (!first)
      {
         if (head.intersects (*body))
         {
            /// Need to roll back movement so call killSnake()
            killSnake();
            break;
         }
      }
      else
      {
         first = false;
      }
   }
}


/// Increase or decrease the size of the Snake
void Snake::alterSnakeSize (const int foodEffect)
{
   if (foodEffect > 0)
   {
      growSnake (foodEffect);
   }

   else if (foodEffect < 0)
   {
      /// If the effect is too large then the Snake dies
      if (!flakeSnake (foodEffect * -1))
      {
         m_alive = false;
      }
   }
}


/// Grows the Snake by foodEffect, can't kill the Snake
void Snake::growSnake (const int foodEffect)
{
   /// Avoid collision bugs by spawning it one cell behind the head
   auto head = *m_partsP.front();

   switch (m_lastMove)
   {
      case Movement::Up:
         utility::moveCell (m_kSetup, head, 0, -1);
         break;

      case Movement::Left:
         utility::moveCell (m_kSetup, head, 1, 0);
         break;

      case Movement::Right:
         utility::moveCell (m_kSetup, head, -1, 0);
         break;

      case Movement::Down:
         utility::moveCell (m_kSetup, head, 0, 1);
         break;

      default: // Can never happen
         break;
   }

   for (int i {0}; i < foodEffect; ++i)
   {
      // Insert as the second element to avoid rolling back and flaking bugs, this also creates the illusion
      // of the eaten food getting digested and so the tail grows once it reaches where the food was
      if (m_partsP.size() > 2)
      {
         auto it = m_partsP.begin();
         it++;
         m_partsP.insert (it, std::unique_ptr<Rectangle> (new Rectangle (head)));
      }
      else
      {
         m_partsP.push_back (std::unique_ptr<Rectangle> (new Rectangle (head)));
      }
   }
}


/// Flakes the snake by foodEffect, returns m_partsP.size() >= foodEffect
bool Snake::flakeSnake (const int foodEffect)
{
   if ( (unsigned int) foodEffect >= m_partsP.size())
   {
      return false;
   }

   for (int i {0}; i < foodEffect; ++i)
   {
      m_flakesP.push_back (std::move (m_partsP.back()));
      m_partsP.pop_back();
   }

   return true;
}


/// std::move() each Rectangle from m_flakesP to modify
void Snake::extractFlakes (std::vector<std::unique_ptr<Rectangle>>& modify)
{
   for (auto& flake : m_flakesP)
   {
      modify.push_back (std::move (flake));
   }

   m_flakesP.clear();
}



/// Assignment functions
void Snake::setController (const std::shared_ptr<Controller>& controller)
{
   /// Tests if controller is valid and if so it enables Controller functionality
   if (controller)
   {
      m_pController = controller;
   }
}


void Snake::incrementScore (const unsigned int toAdd)
{
   // Pre-condition: Not reached score limit
   if (m_score + toAdd  < m_score)
   {
      m_score = std::numeric_limits<unsigned int>::max();
   }

   else
   {
      m_score += toAdd;
   }
}


void Snake::decrementScore (const unsigned int toSubtract)
{
   // Pre-condition: Won't reduce below zero
   if (m_score - toSubtract  > m_score)
   {
      m_score = 0;
   }

   else
   {
      m_score -= toSubtract;
   }
}


/// Rolls back movement and sets Snake to dead
void Snake::killSnake()
{
   // Pre-condition: Can roll back
   if (m_lastEnd)
   {
      m_partsP.pop_front();
      m_partsP.push_back (std::move (m_lastEnd));
   }

   m_alive = false;
}



/// Getters
const Rectangle& Snake::getHead() const
{
   if (m_partsP.empty()) // This should never be able to happen but has helped to debug
   {
      throw std::runtime_error ("Catastrophic failure in Snake::getHead()");
   }

   return *m_partsP.front();
}
