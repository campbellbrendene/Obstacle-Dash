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

#include <ncurses.h>
#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <string.h>

#include "GameState.h"

namespace obsgame
{

using namespace std;

// void onKey(int);
void gameLoop();
void quit(int);

const char *VERSION = "0.0.2";

const unsigned int GAME_W = 60;
const unsigned int GAME_H = 40;
const unsigned int OBSTACLE_COUNT = 1;
const unsigned int OBSTACLE_PER = 30;

bool RUNNING = true;
int DELAY = 100; // ms

GameState state(GAME_W, GAME_H);

int main()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, true);
  timeout(0);

  srand(time(0));

  int n = 3;

  mvprintw(n++, state.cols - (strlen("_____________        _____             ______     ") / 2), "_____________        _____             ______     ");
  mvprintw(n++, state.cols - (strlen("__  __ \\__  /__________  /______ _________  /____ ") / 2), "__  __ \\__  /__________  /______ _________  /____ ");
  mvprintw(n++, state.cols - (strlen("_  / / /_  __ \\_  ___/  __/  __ `/  ___/_  /_  _ \\") / 2), "_  / / /_  __ \\_  ___/  __/  __ `/  ___/_  /_  _ \\");
  mvprintw(n++, state.cols - (strlen("/ /_/ /_  /_/ /(__  )/ /_ / /_/ // /__ _  / /  __/") / 2), "/ /_/ /_  /_/ /(__  )/ /_ / /_/ // /__ _  / /  __/");
  mvprintw(n++, state.cols - (strlen("\\____/ /_.___//____/ \\__/ \\__,_/ \\___/ /_/  \\___/ ") / 2), "\\____/ /_.___//____/ \\__/ \\__,_/ \\___/ /_/  \\___/ ");
  mvprintw(n++, state.cols - (strlen("                                                  ") / 2), "                                                  ");
  mvprintw(n++, state.cols - (strlen("         ________              ______             ") / 2), "         ________              ______             ");
  mvprintw(n++, state.cols - (strlen("         ___  __ \\_____ __________  /_            ") / 2), "         ___  __ \\_____ __________  /_            ");
  mvprintw(n++, state.cols - (strlen("         __  / / /  __ `/_  ___/_  __ \\           ") / 2), "         __  / / /  __ `/_  ___/_  __ \\           ");
  mvprintw(n++, state.cols - (strlen("         _  /_/ // /_/ /_(__  )_  / / /           ") / 2), "         _  /_/ // /_/ /_(__  )_  / / /           ");
  mvprintw(n++, state.cols - (strlen("         /_____/ \\__,_/ /____/ /_/ /_/            ") / 2), "         /_____/ \\__,_/ /____/ /_/ /_/            ");

  mvprintw(state.rows - 4,
           state.cols - ((strlen("Obstacle Dash v") + strlen(VERSION)) / 2),
           "Obstacle Dash v%s", VERSION);
  mvprintw(state.rows - 2,
           state.cols - (strlen("Copyright (C) 2019 Brenden Campbell") / 2),
           "Copyright (C) 2019 Brenden Campbell");
  mvprintw(state.rows - 1,
           state.cols - (strlen("Licensed under GNU GPLv3") / 2),
           "Licensed under GNU GPLv3");
  mvprintw(state.rows,
           state.cols - (strlen("campbellbrendene.github.io") / 2),
           "campbellbrendene.github.io");

  mvprintw((state.rows / 2),
           state.cols - (strlen("Welcome to Obstacle Dash!") / 2),
           "Welcome to Obstacle Dash!");
  move(0, 0);
  refresh();
  usleep(3000 * 1000);
  mvprintw((state.rows / 2) + 1,
           state.cols - (strlen("Press LEFT and RIGHT arrows to dodge falling obstacles. SPACE to pause.") / 2),
           "Press LEFT and RIGHT arrows to dodge falling obstacles. SPACE to pause.");
  move(0, 0);
  refresh();
  usleep(3000 * 1000);
  mvprintw((state.rows / 2) + 2,
           state.cols - (strlen("Press any key to start!") / 2),
           "Press any key to start!");
  move(0, 0);
  refresh();
  flushinp();
  while (getch() == ERR)
  {
  }

  while (RUNNING)
  {
    gameLoop();
    if (!state.paused)
      usleep(DELAY * 1000);
  }

  return 0;
}

void gameLoop()
{
  if (state.lives <= 0)
  {
    // We can just use state.cols because we double space the game tiles!
    mvprintw(state.rows / 2, state.cols - (strlen("G A M E   O V E R") / 2), "G A M E   O V E R");
    move(0, 0);
    refresh();
    usleep(2000 * 1000);
    flushinp();
    mvprintw((state.rows / 2) + 1, state.cols - (strlen("Press any key to exit.") / 2), "Press any key to exit.");
    refresh();
    while (getch() == ERR)
    {
    }
    quit(0);
  }

  if (state.paused)
  {
    if (getch() == ' ')
    {
      state.paused = false;
    }
    else
    {
      mvprintw(state.rows / 2, state.cols - (strlen("P A U S E D") / 2), "P A U S E D");
      move(0, 0);
      refresh();
      return;
    }
  }
  // Display the field
  move(0, 0);
  for (int i = 0; i < state.rows; i++)
  {
    for (int j = 0; j < state.cols; j++)
    {
      if (j < state.cols)
      {
        printw(" ");
      }
      printw("%c", state.field[i][j] ? '#' : ' ');
    }
    printw("\n");
  }

  // Display the player position
  printw("["); // Add \n at beginning to add extra line between player
  for (int i = 0; i < state.cols; i++)
  {
    if (state.position == (unsigned)i)
    {
      printw("0");
    }
    else
    {
      printw("-");
    }
    if (i + 1 < state.cols)
    {
      printw(" ");
    }
  }
  printw("]\n");

  // Display the score
  printw("\nScore: %d\n", state.score);

  // Check if tile collision occurred
  if (state.field[state.rows - 1][state.position])
  {
    state.lives--;

    // Display the number of lives
    printw("Lives remaining: %d\n", state.lives);

    if (state.lives > 0)
    {
      if (state.lives > 1)
      {
        mvprintw(state.rows / 2, state.cols - (strlen("n lives left") / 2), "%d lives left", state.lives);
      }
      else
      {
        mvprintw(state.rows / 2, state.cols - (strlen("1 life left") / 2), "1 life left");
      }
      move(0, 0);
      refresh();
      usleep(2000 * 1000);
      flushinp();
      // Clear field if lives remain
      for (int i = 0; i < state.rows; i++)
      {
        for (int j = 0; j < state.cols; j++)
        {
          state.field[i][j] = false;
        }
      }
    }
    return;
  }

  // Display the number of lives
  printw("Lives remaining: %d\n", state.lives);

  // Sync changes
  refresh();

  // Cascade field
  for (int i = state.rows - 1; i > 0; i--)
  {
    for (int j = 0; j < state.cols; j++)
    {
      state.field[i][j] = state.field[i - 1][j];
    }
  }
  for (int i = 0; i < state.cols; i++)
  {
    state.field[0][i] = ((unsigned)rand() % OBSTACLE_PER < OBSTACLE_COUNT);
  }

  // Check for user input
  switch (getch())
  {
  case KEY_LEFT:
    if (state.position > 0)
    {
      state.position--;
    }
    break;
  case KEY_RIGHT:
    if (state.position + 1 < (unsigned)state.cols)
    {
      state.position++;
    }
    break;
  case ' ':
    state.paused = true;
    break;
  default:
    break;
  }
  flushinp();

  // Increment score!
  state.score++;
}

void quit(int code)
{
  endwin();
  exit(code);
}

} // namespace obsgame

int main()
{
  return obsgame::main();
}
