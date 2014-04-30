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


#ifndef SNAKE_H
#define SNAKE_H


/// STL
#include <list>      // m_partsP
#include <memory>    // m_partsP and m_flakesP
#include <vector>    // m_flakesP


/// Third party
#include <prg/core/image.hpp> // m_kColour and draw()


/// Personal
#include <interfaces/idrawable.hpp>    // Parent
#include <misc/movement.hpp>           // m_lastMove
#include <misc/rectangle.hpp>          // m_partsP and m_flakesP
#include <misc/snakeutilities.hpp>     // moveSnake()
#include <setup/ingamesetup.hpp>       // m_kSetup


/// Forward declarations
class Controller;


/// Snake is the primary gameplay class used by both the AI and the players. Although it should always have a controller,
/// it can perform basic functions without one, albeit stupidly.
/// Snake is a leaf class.
class Snake final : public IDrawable
{
   public:
      /// Constructors and destructor
      Snake (const InGameSetup& setup, const unsigned int playerNumber, const std::string& name = {""});

      Snake (Snake&& move) = default;
      ~Snake() = default;

      /// Explicitly disallow (Effective C++: Item 6)
      Snake (const Snake& copy) = delete;
      Snake& operator= (const Snake& copy) = delete;

      /// Testing functions
      bool intersects (const Rectangle& rect) const;
      bool intersectsBody (const Rectangle& rect) const;

      bool isAlive() const { return m_alive; }
      bool isFlakey() const { return !m_flakesP.empty(); }
      bool canPassThrough() const { return m_passThrough; }


      /// Functionality
      void draw (prg::Canvas& canvas) override;
      void moveSnake();
      void checkSelfCollision(); /// Check if the head collides with the body

      /// Increase or decrease the size of the Snake
      void alterSnakeSize (const int foodEffect);

      /// std::move() each Rectangle from m_flakesP to modify
      void extractFlakes (std::vector<std::unique_ptr<Rectangle>>& modify);


      /// Assignment functions
      void setController (const std::shared_ptr<Controller>& controller);
      void incrementScore (const unsigned int toAdd);
      void decrementScore (const unsigned int toSubtract);
      /// Rolls back movement and sets Snake to dead
      void killSnake();

      void setName (const std::string& name) { m_name = name; }
      void setPassThrough (const bool passThrough) { m_passThrough = passThrough; }


      /// Getters
      const Rectangle& getHead () const;

      const std::string& getName() const { return m_name; }
      unsigned int getPlayerNumber() const { return m_kPlayerNumber; }
      unsigned int getScore() const { return m_score; }
      unsigned int getSize() const { return m_partsP.size(); }
      Movement getLastMove() const { return m_lastMove; }

   protected:

   private:
      /// Core requirements
      void generateSpawn();   /// Generate spawn point based on m_playerNumber


      /// Testing functions
      bool isValidMove (Movement move) const;   /// Checks if it's a valid move


      /// Functionality
      void drawHead (prg::Canvas& canvas, const Rectangle& head);  /// Draws the living or dead image of the head
      void drawBody (prg::Canvas& canvas, const Rectangle& body);  /// Draws the living or dead image of the body
      void growSnake (const int foodEffect);    /// Grows the Snake by foodEffect, can't kill the Snake
      bool flakeSnake (const int foodEffect);   /// Flakes the snake by foodEffect, returns m_partsP.size() > foodEffect


      /// Members
      std::list<std::unique_ptr<Rectangle>> m_partsP;    /// Stores all drawable and collidable body parts
      std::vector<std::unique_ptr<Rectangle>> m_flakesP; /// Stores all flaked off pieces, ready for extraction
      std::unique_ptr<Rectangle> m_lastEnd;              /// Keeps the previous end element to facilitate rolling back
      std::weak_ptr<Controller> m_pController;           /// If available, allows the use of a Controller for input

      const InGameSetup m_kSetup;         /// Contains all game data necessary for the Snake to function
      const unsigned int m_kPlayerNumber; /// Keeps track of which player the Snake represents

      std::string m_name;                 /// The name the player wishes the Snake to reference
      prg::Colour m_colour;               /// What colour should the Snake be drawn?
      bool m_alive;                       /// Simply whether it's alive or not
      bool m_passThrough;                 /// Can the Snake pass through other snakes?
      unsigned int m_score;               /// The total score obtained by the Snake
      Movement m_lastMove;                /// The last movement the Snake made on the screen
};

#endif // SNAKE_H
