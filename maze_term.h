/*
 * maze_term.h
 *
 *  Created on: May 30, 2019
 *      Author: nical
 */

#ifndef MAZE_TERM_H_
#define MAZE_TERM_H_
#include <stdint.h>

#define ESC 0x1B
#define WIDTH 24
#define LENGTH 80

#define START_TITLE_X  35
#define START_TITLE_Y 10

//maze 1
#define BALL_START_M1_X 8
#define BALL_START_M1_Y 3

#define WIN_M1_X 70
#define WIN_M1_Y 19

#define HORZ_MAZE1_WIDTH 15
#define VERT_MAZE1_WIDTH 8
#define VERT_WALL_M1_LENGTH (WIDTH - VERT_MAZE1_WIDTH)
#define HORZ_WALL_M1_LENGTH  35

  //Vertical walls start position
#define WALL1_M1_X 15
#define WALL1_M1_Y (2)
#define WALL2_M1_X 30
#define WALL2_M1_Y (VERT_MAZE1_WIDTH)

  //Horizontal walls start position
#define WALL3_M1_X WALL2_M1_X
#define WALL3_M1_Y VERT_MAZE1_WIDTH
#define WALL4_M1_X (WALL2_M1_X + HORZ_MAZE1_WIDTH)
#define WALL4_M1_Y (WALL3_M1_Y + VERT_MAZE1_WIDTH)

//  MAZE1
//   +-----15-----+
//  +-----------------------------------------------------------------------------+
//  |              X                                                              |
//  |              X                                                              |
//  |              X                                                              |
//  |              X                                                              |
//  |              X                                                              |
//  |              X                                                              |
//  |              X              XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX               |
//  |              X              X                                               |
//  |              X              X                                               |
//  |              X              X                                               |
//  |              X              X                                               |
//  |              X              X                                               |
//  |              X              X                                               |
//  |              X              X                XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX|
//+ |                             X                                               |
//| |                             X                                               |
//| |                             X                                               |
//| |                             X                                               |
//6 |                             X                                               |
//| |                             X                                               |
//| |                             X                                               |
//+ +-----------------------------------------------------------------------------+


//maze 2
#define BALL_START_M2_X 5
#define BALL_START_M2_Y 3

#define WIN_M2_X 54
#define WIN_M2_Y 11

#define HORZ_MAZE2_WIDTH 10
#define VERT_MAZE2_WIDTH 5
#define VERT_WALL_M2_LENGTH (WIDTH - VERT_MAZE2_WIDTH)
#define HORZ_WALL_M2_LENGTH (LENGTH - 2 * HORZ_MAZE2_WIDTH + 1)

  //Vertical walls start position
#define WALL1_M2_X 10
#define WALL1_M2_Y 2
#define WALL2_M2_X 70
#define WALL2_M2_Y VERT_MAZE2_WIDTH + 1
#define WALL3_M2_X 20
#define WALL3_M2_Y VERT_MAZE2_WIDTH
#define WALL4_M2_X 60
#define WALL4_M2_Y 9

  //Horizontal walls start position
#define WALL5_M2_X WALL1_M2_X
#define WALL5_M2_Y (WIDTH - VERT_MAZE2_WIDTH)
#define WALL6_M2_X WALL3_M2_X
#define WALL6_M2_Y VERT_MAZE2_WIDTH
#define WALL7_M2_X WALL3_M2_X
#define WALL7_M2_Y 15
#define WALL8_M2_X 30
#define WALL8_M2_Y 9
//MAZE2
//         10
//    +----------+
//    +------------------------------------------------------------------------+
//    |          |                                                             |
//    |          |                                                             |
//    |          |                                                             |
//    |          |                                     6                       |
//    |          |          +---------------------------------------+          |
//    |          |          |                                       |          |
//    |          |          |                                       |          |
//    |         1|          |                                       |          |
//    |          |          |                          8            |          |
//    |          |          |          +-----------------+          |          |
//    |          |          |                            |          |          |
//    |          |         3|                        xx  |4         |          |
//    |          |          |                        xx  |          |2         |
//    |          |          |                            |          |          |
//    |          |          +----------------------------+          |          |
//    |          |                                      7           |          |
//    |          |                                                  |          |
//    |          |                                                  |          |
//    |          |                                                  |          |
//  + |          +--------------------------------------------------+          |
//  | |                                               5                        |
//4 | |                                                                        |
//  | |                                                                        |
//  + +------------------------------------------------------------------------+

//maze 3
#define BALL_START_M3_X 5
#define BALL_START_M3_Y 3

#define WIN_M3_X 73
#define WIN_M3_Y 19

#define HORZ_MAZE3_WIDTH 11
#define VERT_MAZE3_WIDTH 5
#define VERT_WALL_M3_LENGTH (WIDTH - VERT_MAZE3_WIDTH)

  //Vertical walls start position
#define WALL1_M3_X HORZ_MAZE3_WIDTH
#define WALL1_M3_Y 2
#define WALL2_M3_X 2*HORZ_MAZE3_WIDTH
#define WALL2_M3_Y VERT_MAZE3_WIDTH
#define WALL3_M3_X 3*HORZ_MAZE3_WIDTH
#define WALL3_M3_Y 2
#define WALL4_M3_X 4*HORZ_MAZE3_WIDTH
#define WALL4_M3_Y VERT_MAZE3_WIDTH
#define WALL5_M3_X 5*HORZ_MAZE3_WIDTH
#define WALL5_M3_Y 2
#define WALL6_M3_X 6*HORZ_MAZE3_WIDTH
#define WALL6_M3_Y VERT_MAZE3_WIDTH


//Maze 3
//         10
//    +----------+
//    +--------------------------------+---------------------+---------------------+
//    |          |                     |                     |                     |
//    |          |                     |                     |                     |
//    |          |                     |                     |                     |
//    |          |                     |                     |                     |
//    |          |          +          |          +          |          +          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//    |          |          |          |          |          |          |          |
//  + |          +          |          +          |          +          |          |
//  | |                     |                     |                     |          |
//4 | |                     |                     |                     |    XX    |
//  | |                     |                     |                     |    XX    |
//  | |                     |                     |                     |          |
//  + +---------------------+---------------------+---------------------+----------+

void paint_terminal();
void check_maze1();
void check_maze2();
void check_maze3();
void set_ball_vels(int16_t x_vel, int16_t y_vel);
void update_ball(int16_t x_accel, int16_t y_accel);
void win_animation();
int check_win(unsigned int x, unsigned int y);
void level_animation(unsigned int level);
inline void term_clear_screen();
void maze1();
void maze2();
void maze3();

static void draw_new_ball();
void print_bits(int16_t val);

#endif /* MAZE_TERM_H_ */
