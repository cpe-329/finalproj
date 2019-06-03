/*
 * maze_term.h
 *
 *  Created on: May 30, 2019
 *      Author: nical
 */

#ifndef MAZE_TERM_H_
#define MAZE_TERM_H_

#define ESC 0x1B
#define WIDTH 24
#define LENGTH 80

//maze 1
#define HORZ_MAZE1_WIDTH 15
#define VERT_MAZE1_WIDTH 6
  //Vertical walls start position
#define WALL_1_X 15
#define WALL_1_Y (WIDTH - VERT_MAZE1_WIDTH)
#define WALL_2_X 30
#define WALL_2_Y WIDTH
  //Horizontal walls start position
#define WALL_3_X WALL_2_X
#define WALL_3_Y WALL_2_Y
#define WALL_4_X (WALL_2_X + HORZ_MAZE1_WIDTH)
#define WALL_4_Y (WALL_3_Y + VERT_MAZE1_WIDTH)
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


#endif /* MAZE_TERM_H_ */
