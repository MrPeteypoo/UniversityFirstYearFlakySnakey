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


#ifndef BUTTON_H
#define BUTTON_H


/// Third party
#include <prg/core/font.hpp>  // draw()
#include <prg/core/image.hpp> // draw()


/// Personal
#include <interfaces/idrawable.hpp> // Parent
#include <misc/snakeutilities.hpp>  // setText()


/// The Button class is used to represent every clickable button in the game. Unfortunately it's functionality is very basic
/// and used to perform common UI based tasks instead of being able to perform specific game actions. My preference would
/// be for this to act like a VB.NET or C# style button but within the context of the PRG library this would result in huge
/// amounts of code duplication.
/// Button is a leaf class.
class Button final : IDrawable
{
   public:
      /// Constructors and destructor
      Button (const Rectangle& clickableArea = {0, 0, 0, 0}, const prg::Colour& colour = {255, 255, 255});

      Button (const Button& copy) = default;
      Button (Button&& move) = default;
      Button& operator= (const Button& copy) = default;
      Button& operator= (Button&& move) = default;
      ~Button() override = default;


      /// Testing functions
      bool intersects (const unsigned int x, const unsigned int y) const;

      bool intersects (const Rectangle& position) const { return position.intersects(m_area); }


      /// Functionality
      void draw (prg::Canvas& canvas) override;


      /// Assignment functions
      void setText (const std::string& text);

      /// Allow the conversion of int to string for draw()
      void setText (const int value);
      void setText (const unsigned int value);

      void setClickableArea (const Rectangle& area)   { m_area = area; }
      void setColour (const prg::Colour& colour)      { m_colour = colour; }
      void setMouseOver (const bool isOver)           { m_mouseOver = isOver; }


      /// Getters
      const Rectangle& getClickableArea() const { return m_area; }
      const prg::Colour& getColour() const      { return m_colour; }
      const std::string& getText() const        { return m_text; }

   protected:

   private:
      /// Core requirements
      void setupFont();


      /// Members
      /// Font object used for rendering, there's a massive performance issue having to create one every time draw()
      prg::Font m_font;

      Rectangle m_area;       /// The clickable area of the button
      prg::Colour m_colour;   /// The colour the button will be drawn
      std::string m_text;     /// The text printed on the screen
      bool m_mouseOver;       /// Whether the cursor is hovering atop the button
};

#endif // BUTTON_H
