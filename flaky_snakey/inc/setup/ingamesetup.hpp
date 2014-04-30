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


#ifndef INGAMESETUP_H
#define INGAMESETUP_H


/// InGameSetup contains information relating to the mechanics and physical aspects of the game which many different
/// classes need to be aware of. This increases in-game performance for the sake of a tiny memory footprint.
class InGameSetup
{
   public:
      /// Constructors and destructor
      InGameSetup();
      InGameSetup (const InGameSetup& copy) = default;
      InGameSetup (InGameSetup&& move) = default;
      InGameSetup& operator= (const InGameSetup& copy) = default;
      virtual ~InGameSetup() {} // See IDrawable() destructor


      /// Testing functions
      bool isAspectRatioCorrected() const { return m_aspectCorrection; }


      /// Assignment functions
      /// Allow daisy chaining of assignment functions
      InGameSetup& setResolution (const unsigned int width, const unsigned int height);

      /// Allow calculation of m_foodRotInterval to change with setGrid
      virtual InGameSetup& setGrid (const unsigned int width, const unsigned int height);
      InGameSetup& setAspectRatioCorrection (const bool correct);


      /// Getters
      unsigned int getResX() const        { return m_resX; }
      unsigned int getResY() const        { return m_resY; }
      unsigned int getWorkingX() const    { return m_workingX; }
      unsigned int getWorkingY() const    { return m_workingY; }
      unsigned int getMarginX() const     { return m_marginX; }
      unsigned int getMarginY() const     { return m_marginY; }
      unsigned int getMarginUI() const    { return m_marginUI; }
      unsigned int getStartX() const      { return m_startX; }
      unsigned int getEndX() const        { return m_endX; }
      unsigned int getStartY() const      { return m_startY; }
      unsigned int getEndY() const        { return m_endY; }

      unsigned int getGridWidth() const   { return m_gridWidth; }
      unsigned int getGridHeight() const  { return m_gridHeight; }
      unsigned int getRectWidth() const   { return m_rectWidth; }
      unsigned int getRectHeight() const  { return m_rectHeight; }

   protected:
      /// Assignment Functions
      void recalculateMembers(); /// Recalculates each member variable
      void correctAspectRatio(); /// Adds margins to ensure m_rectWidth == m_rectHeight


      /// Members
      unsigned int m_resX;       /// The actual width of the screen
      unsigned int m_resY;       /// The actual height of the screen
      unsigned int m_workingX;   /// The available width after UI and other deductions
      unsigned int m_workingY;   /// The available height after UI and other deductions
      unsigned int m_marginX;    /// Used for centre alignment with the window
      unsigned int m_marginY;    /// Used for centre alignment with the window
      unsigned int m_marginUI;   /// Used for placing the UI at the sides
      unsigned int m_startX;     /// Used for placement of non-UI objects
      unsigned int m_endX;       /// Used for placement of non-UI objects, note this is where nothing is rendered

      /// Although this is the same as m_marginY, it's more explicit and the UI could change making them unequal
      unsigned int m_startY;
      unsigned int m_endY;
      bool m_aspectCorrection;   /// If true, aspect ratio will match grid size

      unsigned int m_gridWidth;  /// The width of the grid used by the level
      unsigned int m_gridHeight; /// The height of the grid used by the level
      unsigned int m_rectWidth;  /// The width of each single cell Rectangle object
      unsigned int m_rectHeight; /// The height of each single cell Rectangle object

   private:

};

#endif // INGAMESETUP_H
