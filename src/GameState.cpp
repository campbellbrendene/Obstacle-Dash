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

GameState::GameState(unsigned int _cols, unsigned int _rows)
{
  cols = _cols;
  rows = _rows;

  score = 0;

  field = new bool*[rows];
  for (int i = 0; i < rows; i++) {
    field[i] = new bool[cols];
    for (int j = 0; j < cols; j++) {
      field[i][j] = false;
    }
  }

  position = 0;
  paused = false;
  lives = 3;
}

GameState::~GameState()
{
  for (int i = 0; i < rows; i++) {
    delete[] field[i];
  }
  delete[] field;
}
