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

#define BALL_START_X 8
#define BALL_START_Y 3

#define WIN_X 75
#define WIN_Y 20

//maze 1
#define HORZ_MAZE1_WIDTH 15
#define VERT_MAZE1_WIDTH 8
#define VERT_WALL_LENGTH (WIDTH - VERT_MAZE1_WIDTH)
#define HORZ_WALL_LENGTH  35

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

static volatile int win = 0;
void paint_terminal();
void check_maze1();

void set_ball_vels(int16_t x_vel, int16_t y_vel);
void update_ball(int16_t x_accel, int16_t y_accel);
inline void term_clear_screen();

static void draw_new_ball();
void print_bits(int16_t val);

#endif /* MAZE_TERM_H_ */
