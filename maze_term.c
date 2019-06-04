/*
 * maze_term.c
 *
 *  Created on: May 30, 2019
 *      Author: nical
 */

#include "maze_term.h"
#include <math.h>
#include <stdint.h>
#include "delay.h"
#include "scope_data.h"
#include "uart.h"

static unsigned char com[2] = {ESC, '['};
volatile int ball_x = BALL_START_X;
volatile int ball_y = BALL_START_Y;
volatile int ball_x_vel = 0;
volatile int ball_y_vel = 0;

inline void move_down(unsigned int val) {
    uart_write_str(com, 2);
    uart_write_int(val);
    uart_write('B');
}

inline void move_up(unsigned int val) {
    uart_write_str(com, 2);
    uart_write_int(val);
    uart_write('A');
}

inline void move_left(unsigned int val) {
    uart_write_str(com, 2);
    uart_write_int(val);
    uart_write('D');
}

inline void move_right(unsigned int val) {
    uart_write_str(com, 2);
    uart_write_int(val);
    uart_write('C');
}

inline void move_home() {
    unsigned char command[3] = {ESC, '[', 'H'};
    uart_write_str(command, 3);
}

inline void hide_cursor() {
    unsigned char command[6] = {ESC, '[', '?', '2', '5', 'l'};
    uart_write_str(command, 6);
}

inline void term_clear_screen() {
    unsigned char command[4] = {ESC, '[', '2', 'J'};
    uart_write_str(command, 4);
}

inline void clear_line() {
    unsigned char command[4] = {ESC, '[', '2', 'K'};
    uart_write_str(command, 4);
}
void move_cursor(unsigned int x, unsigned int y) {
    uart_write_str(com, 2);
    uart_write_int(y);
    uart_write(';');
    uart_write_int(x);
    uart_write('H');
}

inline void draw_horizontal(unsigned int x,
                            unsigned int y,
                            unsigned int length,
                            char c) {
    int i;
    move_cursor(x, y);
    for (i = 0; i < length; i++) {
        uart_write(c);
    }
}

inline void draw_vertical(unsigned int x,
                          unsigned int y,
                          unsigned int length,
                          char c) {
    int i;

    move_cursor(x, y);
    for (i = 0; i < length; i++) {
        uart_write(c);
        // y++;
        // move_cursor(x, y);
        move_down(1);
        move_left(1);
    }
}

void print_border() {
    // Top boarder
    draw_horizontal(2, 1, LENGTH - 2, '=');
    // Bottom boarder
    draw_horizontal(2, WIDTH, LENGTH - 2, '=');
    // Left boarder
    draw_vertical(1, 2, WIDTH - 2, '|');
    // Right boarder
    draw_vertical(LENGTH, 2, WIDTH - 2, '|');

    // Top left corner
    draw_vertical(1, 1, 1, '+');
    // Top right corner
    draw_vertical(LENGTH, 1, 1, '+');
    // Bottom right corner
    draw_vertical(LENGTH, WIDTH, 1, '+');
    // Bottom left corner
    draw_vertical(1, WIDTH, 1, '+');
}

void draw_maze1() {
    // Vert wall 1
    draw_vertical(WALL1_M1_X, WALL1_M1_Y, VERT_WALL_LENGTH, '|');
    // Vert wall 2
    draw_vertical(WALL2_M1_X, WALL2_M1_Y, VERT_WALL_LENGTH, '|');
    // Horz wall 1
    draw_horizontal(WALL3_M1_X, WALL3_M1_Y, HORZ_WALL_LENGTH, '=');
    // Horz wall 2
    draw_horizontal(WALL4_M1_X, WALL4_M1_Y, HORZ_WALL_LENGTH, '=');
    // Maze
    move_cursor(WIN_X, WIN_Y);
    uart_write('X');
}

void check_vert_wall(uint8_t wall_x, uint8_t wall_y, uint8_t wall_len) {
    int dist_wall_ball_x;

    // Not to the left or right of the wall
    if ((ball_y < wall_y) | (ball_y > wall_y + wall_len)) {
        return;
    }

    dist_wall_ball_x = wall_x - ball_x;


    if (dist_wall_ball_x == 0){
        return;
    }
    // moving right towards wall on right
    else if (dist_wall_ball_x > 0 && ball_x_vel > 0) {
        if (ball_x_vel >= dist_wall_ball_x) {
            ball_x_vel = dist_wall_ball_x - 1;
        }
    }
    // moving left towards wall on left
    else if (dist_wall_ball_x < 0 && ball_x_vel < 0) {
        if (ball_x_vel <= dist_wall_ball_x) {
            ball_x_vel = dist_wall_ball_x + 1;
        }
    }
}

void check_horz_wall(uint8_t wall_x, uint8_t wall_y, uint8_t wall_len) {
    int dist_wall_ball_y;

    // Not above or below the wall
    if ((ball_x < wall_x) | (ball_x > wall_x + wall_len)) {
        return;
    }

    dist_wall_ball_y = wall_y - ball_y;

    if (dist_wall_ball_y == 0){
        return;
    }
    // moving down towards wall below
    if (dist_wall_ball_y > 0 && ball_y_vel > 0) {
        if (ball_y_vel >= dist_wall_ball_y) {
            ball_y_vel = dist_wall_ball_y - 1;
        }
    }
    // moving up towards wall above
    else if (dist_wall_ball_y < 0 && ball_y_vel < 0) {
        if (ball_y_vel <= dist_wall_ball_y) {
            ball_y_vel = dist_wall_ball_y + 1;
        }
    }
}

void set_ball_vels(int16_t x_vel, int16_t y_vel) {
    move_home();
    uart_write_str("X: ",3);
    uart_write_int(x_vel);
    uart_write_str("\tY: ",4);
    uart_write_int(y_vel);
    ball_x_vel = x_vel;
    ball_y_vel = y_vel;
}

void update_ball(int16_t x_accel, int16_t y_accel) {
    // Apply friction?
    if (x_accel == 0 && ball_x_vel > 0) {
        x_accel = -1;
    } else if (x_accel == 0 && ball_x_vel < 0) {
        x_accel = 1;
    }

    if (y_accel == 0 && ball_y_vel > 0) {
        y_accel = -1;
    } else if (y_accel == 0 && ball_y_vel < 0) {
        y_accel = 1;
    }
    ball_x_vel += x_accel;
    ball_y_vel += y_accel;
}

void check_border() {
    // Left boarder
    check_vert_wall(1, 1, WIDTH);
    // Right boarder
    check_vert_wall(LENGTH, 1, WIDTH);
    // Top boarder
    check_horz_wall(1, 1, LENGTH);
    // Bottom border
    check_horz_wall(1, WIDTH, LENGTH);
}

static void draw_new_ball() {
    move_cursor(ball_x, ball_y);
    uart_write('O');
}

void check_maze1() {
    int old_ball_x = ball_x;
    int old_ball_y = ball_y;
    check_border();
    check_vert_wall(WALL1_M1_X, WALL1_M1_Y, VERT_WALL_LENGTH);
    check_vert_wall(WALL2_M1_X, WALL2_M1_Y, VERT_WALL_LENGTH);
    check_horz_wall(WALL3_M1_X, WALL3_M1_Y, HORZ_WALL_LENGTH);
    check_horz_wall(WALL4_M1_X, WALL4_M1_Y, HORZ_WALL_LENGTH);

    // We should unconditionally move by the velocity because
    //   the vlocity should already take into account the collision
    // if (old_ball_x == ball_x && ball_x_vel != 0) {
    // if one of the walls affect the ball's movement
    // This does indicate a collision because the ball did
    //   not move even though it had velocity
    ball_x += ball_x_vel;
    // }
    // if (old_ball_y == ball_y && ball_y_vel != 0) {
    ball_y += ball_y_vel;
    // }
    move_cursor(old_ball_x, old_ball_y);
    uart_write(' ');
    draw_new_ball();

    if (ball_x == WIN_X && ball_y == WIN_Y) {
        win = 1;
    }
}

void start_animation() {
    move_cursor(START_TITLE_X, START_TITLE_Y);
    uart_write_str("THE MAZE GAME", 13);
    draw_horizontal( START_TITLE_X - 2, START_TITLE_Y + 2, 17,'*');
    draw_horizontal( START_TITLE_X - 2, START_TITLE_Y - 2, 17, '*');
    draw_vertical(START_TITLE_X - 2, START_TITLE_Y - 2, 5,  '*');
    draw_vertical(START_TITLE_X + 14, START_TITLE_Y - 2, 5, '*');
    move_cursor(START_TITLE_X - 5, START_TITLE_Y + 4);
    uart_write_str("CPE 329 - Final Project", 23);
    move_cursor(START_TITLE_X - 10, START_TITLE_Y + 6);
    uart_write_str("By: Spencer Shaw and Danica Fujiwara", 36);
    draw_horizontal( 2, 1,LENGTH - 2, 'v');
    draw_horizontal( 2, WIDTH,LENGTH - 2, 'v');
    draw_vertical(LENGTH, 1,WIDTH,  'v');
    draw_vertical( 1, 1,WIDTH, 'v');
    delay_ms_auto(10000);
    draw_horizontal( 2, 1,LENGTH - 2, '^');
    draw_horizontal(2, WIDTH, LENGTH - 2, '^');
    draw_vertical( LENGTH, 1,WIDTH, '^');
    draw_vertical( 1, 1,WIDTH, '^');
}

void paint_terminal() {
    int i;
    term_clear_screen();
    hide_cursor();
    for (i = 0; i < 3; i++) {
        start_animation();
        delay_ms_auto(10000);
    }
    term_clear_screen();
    print_border();
    draw_maze1();
    draw_new_ball();
}

static void draw_new_ball() {
    move_cursor(ball_x, ball_y);
    uart_write('O');
    move_home();
}

void print_bits(int16_t val) {
    unsigned int i = 0b1000000000000000;
    while (i != 0) {
        if (val & i) {
            uart_write('1');
        } else {
            uart_write('0');
        }
        if (i == 0x0100 | i == 0x1000 | i == 0x0010) {
            uart_write('_');
        }
        i = i >> 1;
    }
}
