/*
    Obstacle Dash - A simple text-based game.
    Copyright (C) 2019 Brenden Campbell <campbellbrendene@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef INC_GAMESTATE_H
#define INC_GAMESTATE_H

class GameState
{
private:
  /* data */
public:
  GameState(unsigned int cols, unsigned int rows);
  ~GameState();
  int cols, rows;
  unsigned int score;
  bool **field; // Dynamic 2D array
  unsigned int position;
  bool paused;
  unsigned int lives;
};

#endif
