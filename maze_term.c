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
volatile int ball_x = BALL_START_M1_X;
volatile int ball_y = BALL_START_M1_Y;
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

void draw_win(unsigned int x, unsigned int y) {
    move_cursor(x, y);
    uart_write_str("+===+", 5);
    move_cursor(x, y + 1);
    uart_write_str("| X |", 5);
    move_cursor(x, y + 2);
    uart_write_str("+===+", 5);
}

void draw_trap(unsigned int x, uunsigned int y){
    move_cursor(x, y);
    uart_write_str("XXX", 3);
    move_cursor(x, y + 1);
    uart_write_str("XXX", 3);
    move_cursor(x, y + 2);
    uart_write_str("XXX", 3);
}

void draw_maze1() {
    // Vert wall 1
    draw_vertical(WALL1_M1_X, WALL1_M1_Y, VERT_WALL_M1_LENGTH, '|');
    // Vert wall 2
    draw_vertical(WALL2_M1_X, WALL2_M1_Y, VERT_WALL_M1_LENGTH, '|');
    // Horz wall 1
    draw_horizontal(WALL3_M1_X, WALL3_M1_Y, HORZ_WALL_M1_LENGTH, '=');
    // Horz wall 2
    draw_horizontal(WALL4_M1_X, WALL4_M1_Y, HORZ_WALL_M1_LENGTH, '=');

    draw_trap(WALL1_M1_X-1, WALL1_M1_Y + VERT_WALL_M1_LENGTH);
    draw_trap(WALL3_M1_X + HORZ_WALL_M1_LENGTH, WALL3_M1_Y -1 );
    draw_trap(WALL4_M1_X + 3, WIDTH -3);
    // Maze
    draw_win(WIN_M1_X, WIN_M1_Y);
}

void draw_maze2() {
    // Vert wall 1
    draw_vertical(WALL1_M2_X, WALL1_M2_Y, VERT_WALL_M2_LENGTH - 1, '|');
    // Vert wall 2
    draw_vertical(WALL2_M2_X, WALL2_M2_Y,
                  VERT_WALL_M2_LENGTH - VERT_MAZE2_WIDTH, '|');
    // Vert wall 3
    draw_vertical(WALL3_M2_X, WALL3_M2_Y,
                  VERT_WALL_M2_LENGTH - 2 * VERT_MAZE2_WIDTH + 1, '|');
    // Vert wall 4
    draw_vertical(WALL4_M2_X, WALL4_M2_Y,
                  VERT_WALL_M2_LENGTH - 3 * VERT_MAZE2_WIDTH + 2, '|');
    // Horz wall 5
    draw_horizontal(WALL5_M2_X, WALL5_M2_Y, HORZ_WALL_M2_LENGTH, '=');
    // Horz wall 6
    draw_horizontal(WALL6_M2_X, WALL6_M2_Y,
                    HORZ_WALL_M2_LENGTH - HORZ_MAZE2_WIDTH, '=');
    // Horz wall 7
    draw_horizontal(WALL7_M2_X, WALL7_M2_Y,
                    HORZ_WALL_M2_LENGTH - 2 * HORZ_MAZE2_WIDTH, '=');
    // Horz wall 8

    draw_horizontal(WALL8_M2_X, WALL8_M2_Y,
                    HORZ_WALL_M2_LENGTH - 3 * HORZ_MAZE2_WIDTH, '=');

    draw_trap(2, WIDTH -3);
    draw_trap(WALL7_M2_X + 5, WALL7_M2_Y + 1 );
    draw_trap(WALL4_M2_X + 1, WALL4_M2_X -2);
    // Maze
    draw_win(WIN_M2_X, WIN_M2_Y);
}

void draw_maze3() {
    // Vert wall 1
    draw_vertical(WALL1_M3_X, WALL1_M3_Y, VERT_WALL_M3_LENGTH, '|');
    // Vert wall 2
    draw_vertical(WALL2_M3_X, WALL2_M3_Y, VERT_WALL_M3_LENGTH, '|');
    // Vert wall 3
    draw_vertical(WALL3_M3_X, WALL3_M3_Y, VERT_WALL_M3_LENGTH, '|');
    // Vert wall 4
    draw_vertical(WALL4_M3_X, WALL4_M3_Y, VERT_WALL_M3_LENGTH, '|');
    // Vert wall 5
    draw_vertical(WALL5_M3_X, WALL5_M3_Y, VERT_WALL_M3_LENGTH, '|');
    // Vert wall 6
    draw_vertical(WALL6_M3_X, WALL6_M3_Y, VERT_WALL_M3_LENGTH, '|');

    draw_trap(WALL2_M3_X-1, WALL2_M3_Y -3);
    draw_trap(WALL3_M3_X - 1, WALL3_M3_Y + VERT_WALL_M3_LENGTH);
    draw_trap(WALL5_M3_X -3, WALL5_M3_ Y - 5);
    draw_trap(LENGTH - 4, 2);
    // Maze
    draw_win(WIN_M3_X, WIN_M3_Y);
}

void set_ball_vels(int16_t x_vel, int16_t y_vel) {
    ball_x_vel = x_vel;
    ball_y_vel = y_vel;
}

void check_vert_wall(uint8_t wall_x, uint8_t wall_y, uint8_t wall_len) {
    int dist_wall_ball_x;

    // Not to the left or right of the wall
    if ((ball_y < wall_y) | (ball_y > wall_y + wall_len)) {
        return;
    }

    dist_wall_ball_x = wall_x - ball_x;

    if (dist_wall_ball_x == 0) {
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

void check_wall_box(uint8_t wall_corner_x,
                    uint8_t wall_corner_y,
                    uint8_t wall_width,
                    uint8_t wall_height) {
    int wall_x = wall_corner_x;
    int wall_y = wall_corner_y;
    int dist_x;
    int dist_y;

    if (ball_x >= wall_corner_x + wall_width) {
        wall_x += wall_width;
    }
    if (ball_y >= wall_corner_y + wall_height) {
        wall_y += wall_height;
    }

    dist_x = wall_x - ball_x;
    dist_y = wall_y - ball_y;

    // Left of right of vertical wall
    if (!((ball_y < wall_y) | (ball_y > wall_y + wall_width))) {
        if (dist_x != 0) {
            // moving right towards wall on right
            if (dist_x > 0 && ball_x_vel > 0) {
                if (ball_x_vel >= dist_x) {
                    ball_x_vel = dist_x - 1;
                }
            }
            // moving left towards wall on left
            else if (dist_x < 0 && ball_x_vel < 0) {
                if (ball_x_vel <= dist_x) {
                    ball_x_vel = dist_x + 1;
                }
            }
        }
    }
    // Above or below the horizontal wall
    if (!((ball_x < wall_x) | (ball_x > wall_x + wall_width))) {
        if (dist_y != 0) {
            // moving down towards wall below
            if (dist_y > 0 && ball_y_vel > 0) {
                if (ball_y_vel >= dist_y) {
                    ball_y_vel = dist_y - 1;
                }
            }
            // moving up towards wall above
            else if (dist_y < 0 && ball_y_vel < 0) {
                if (ball_y_vel <= dist_y) {
                    ball_y_vel = dist_y + 1;
                }
            }
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

    if (dist_wall_ball_y == 0) {
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

void reset_ball(uint8_t maze_num){
    switch(maze_num){
        case 1:
            maze1();
            break;
        case 2:
            maze2();
            break;
        case 3:
            maze3();
            break;
        default:
            maze1();
    }
}

void check_trap(uint8_t trap_x, uint8_t trap_y, uint8_t maze_num){
    int8_t dist_x = ball_x - trap_x;
    int8_t dist_y = ball_y - trap_y;
    if ((dist_x >= -1 && dist_x <= -1) && (dist_y >= -1 && dist_y <= 1)){
        reset_ball(maze_num);
    } 
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
    uart_write(BALL_CHAR);

    move_home();
}

void check_maze1() {
    int old_ball_x = ball_x;
    int old_ball_y = ball_y;
    check_border();
    check_vert_wall(WALL1_M1_X, WALL1_M1_Y, VERT_WALL_M1_LENGTH);
    check_vert_wall(WALL2_M1_X, WALL2_M1_Y, VERT_WALL_M1_LENGTH);
    check_horz_wall(WALL3_M1_X, WALL3_M1_Y, HORZ_WALL_M1_LENGTH);
    check_horz_wall(WALL4_M1_X, WALL4_M1_Y, HORZ_WALL_M1_LENGTH);

    // We should unconditionally move by the velocity because
    //   the vlocity should already take into account the collision
    // if (old_ball_x == ball_x && ball_x_vel != 0) {
    // if one of the walls affect the ball's movement
    // This does indicate a collision because the ball did
    //   not move even though it had velocity
    check_trap(WALL1_M1_X-1, WALL1_M1_Y + VERT_WALL_M1_LENGTH, 1);
    check_trap(WALL3_M1_X + HORZ_WALL_M1_LENGTH, WALL3_M1_Y -1, 1);
    check_trap(WALL4_M1_X + 3, WIDTH -3, 1);
    ball_x += ball_x_vel;
    // }
    // if (old_ball_y == ball_y && ball_y_vel != 0) {
    ball_y += ball_y_vel;
    // }
    move_cursor(old_ball_x, old_ball_y);
    uart_write(' ');
    draw_new_ball();
}

void check_maze2() {
    int old_ball_x = ball_x;
    int old_ball_y = ball_y;
    check_border();
    check_vert_wall(WALL1_M2_X, WALL1_M2_Y, VERT_WALL_M2_LENGTH);

    check_vert_wall(WALL2_M2_X, WALL2_M2_Y,
                    VERT_WALL_M2_LENGTH - VERT_MAZE2_WIDTH);
    check_vert_wall(WALL3_M2_X, WALL3_M2_Y,
                    VERT_WALL_M2_LENGTH - 2 * VERT_MAZE2_WIDTH);
    check_vert_wall(WALL4_M2_X, WALL4_M2_Y,
                    VERT_WALL_M2_LENGTH - 3 * VERT_MAZE2_WIDTH);
    check_horz_wall(WALL5_M2_X, WALL5_M2_Y, HORZ_WALL_M2_LENGTH);
    check_horz_wall(WALL6_M2_X, WALL6_M2_Y,
                    HORZ_WALL_M2_LENGTH - HORZ_MAZE2_WIDTH);
    check_horz_wall(WALL7_M2_X, WALL7_M2_Y,
                    HORZ_WALL_M2_LENGTH - 2 * HORZ_MAZE2_WIDTH);
    check_horz_wall(WALL8_M2_X, WALL8_M2_Y,
                    HORZ_WALL_M2_LENGTH - 3 * HORZ_MAZE2_WIDTH);

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
}

void check_maze3() {
    int old_ball_x = ball_x;
    int old_ball_y = ball_y;
    check_border();
    check_vert_wall(WALL1_M3_X, WALL1_M3_Y, VERT_WALL_M3_LENGTH);
    check_vert_wall(WALL2_M3_X, WALL2_M3_Y, VERT_WALL_M3_LENGTH);
    check_vert_wall(WALL3_M3_X, WALL3_M3_Y, VERT_WALL_M3_LENGTH);
    check_vert_wall(WALL4_M3_X, WALL4_M3_Y, VERT_WALL_M3_LENGTH);
    check_vert_wall(WALL5_M3_X, WALL5_M3_Y, VERT_WALL_M3_LENGTH);
    check_vert_wall(WALL6_M3_X, WALL6_M3_Y, VERT_WALL_M3_LENGTH);
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
}

int check_win(unsigned int x, unsigned int y) {
    return ((ball_x >= x && ball_x <= x + 4) &&
            (ball_y >= y && ball_y <= y + 2));
}

void start_animation() {
    move_cursor(START_TITLE_X, START_TITLE_Y);
    uart_write_str("THE MAZE GAME", 13);
    draw_horizontal(START_TITLE_X - 2, START_TITLE_Y + 2, 17, '*');
    draw_horizontal(START_TITLE_X - 2, START_TITLE_Y - 2, 17, '*');
    draw_vertical(START_TITLE_X - 2, START_TITLE_Y - 2, 5, '*');
    draw_vertical(START_TITLE_X + 14, START_TITLE_Y - 2, 5, '*');
    move_cursor(START_TITLE_X - 5, START_TITLE_Y + 4);
    uart_write_str("CPE 329 - Final Project", 23);
    move_cursor(START_TITLE_X - 10, START_TITLE_Y + 6);
    uart_write_str("By: Spencer Shaw and Danica Fujiwara", 36);
    draw_horizontal(2, 1, LENGTH - 2, 'v');
    draw_horizontal(2, WIDTH, LENGTH - 2, 'v');
    draw_vertical(LENGTH, 1, WIDTH, 'v');
    draw_vertical(1, 1, WIDTH, 'v');
    delay_ms_auto(10000);
    draw_horizontal(2, 1, LENGTH - 2, '^');
    draw_horizontal(2, WIDTH, LENGTH - 2, '^');
    draw_vertical(LENGTH, 1, WIDTH, '^');
    draw_vertical(1, 1, WIDTH, '^');
}

void level_animation(unsigned int level) {
    term_clear_screen();
    move_cursor(START_TITLE_X + 2, START_TITLE_Y);
    uart_write_str("LEVEL ", 6);
    uart_write_int(level);
    draw_horizontal(START_TITLE_X - 2, START_TITLE_Y + 2, 15, '*');
    draw_horizontal(START_TITLE_X - 2, START_TITLE_Y - 2, 15, '*');
    draw_vertical(START_TITLE_X - 2, START_TITLE_Y - 2, 5, '*');
    draw_vertical(START_TITLE_X + 12, START_TITLE_Y - 2, 5, '*');
    delay_ms_auto(100000);
}

void win_animation() {
    term_clear_screen();
    move_cursor(START_TITLE_X + 2, START_TITLE_Y);
    uart_write_str("YOU WIN!", 8);
    draw_horizontal(START_TITLE_X - 2, START_TITLE_Y + 2, 15, '*');
    draw_horizontal(START_TITLE_X - 2, START_TITLE_Y - 2, 15, '*');
    draw_vertical(START_TITLE_X - 2, START_TITLE_Y - 2, 5, '*');
    draw_vertical(START_TITLE_X + 12, START_TITLE_Y - 2, 5, '*');
    delay_ms_auto(100000);
}

void restart_ball(unsigned int x, unsigned int y) {
    ball_x = x;
    ball_y = y;
    ball_x_vel = 0;
    ball_y_vel = 0;
}

void paint_terminal() {
    int i;
    term_clear_screen();
    hide_cursor();
    for (i = 0; i < 3; i++) {
        start_animation();
        delay_ms_auto(10000);
    }
}

void maze1() {
    term_clear_screen();
    print_border();
    draw_maze1();
    restart_ball(BALL_START_M1_X, BALL_START_M1_Y);
    draw_new_ball();
}

void maze2() {
    term_clear_screen();
    print_border();
    draw_maze2();
    restart_ball(BALL_START_M2_X, BALL_START_M2_Y);
    draw_new_ball();
}

void maze3() {
    term_clear_screen();
    print_border();
    draw_maze3();
    restart_ball(BALL_START_M3_X, BALL_START_M3_Y);
    draw_new_ball();
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
