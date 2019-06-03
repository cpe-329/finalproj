/*
 * maze_term.c
 *
 *  Created on: May 30, 2019
 *      Author: nical
 */

#include "maze_term.h"
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

void move_cursor(unsigned int x, unsigned int y) {
    uart_write_str(com, 2);
    uart_write_int(y);
    uart_write(';');
    uart_write_int(x);
    uart_write('H');
}

inline void draw_horizontal(unsigned int length,
                            unsigned int x,
                            unsigned int y,
                            char c) {
    int i;
    move_cursor(x, y);
    for (i = 0; i < length; i++) {
        uart_write(c);
    }
}

inline void draw_vertical(unsigned int length,
                          unsigned int x,
                          unsigned int y,
                          char c,
                          int bar) {
    int i;

    move_cursor(x, y);
    for (i = 0; i < length; i++) {
        uart_write(c);
        y--;
        move_cursor(x, y);
    }
}

void print_border() {
    draw_horizontal(LENGTH - 2, 2, 1, '=');
    draw_horizontal(LENGTH - 2, 2, WIDTH, '=');
    draw_vertical(WIDTH, LENGTH, WIDTH, '|', 0);
    draw_vertical(WIDTH, 1, WIDTH, '|', 0);
}

void draw_maze1(){
    draw_vertical(VERT_WALL_LENGTH, WALL1_M1_X, WALL1_M1_Y, '|' );
    draw_vertical(VERT_WALL_LENGTH, WALL2_M1_X, WALL2_M1_Y, '|');
    draw_horizontal(HORZ_WALL_LENGTH, WALL3_M1_X, WALL3_M1_Y, '=');
    draw_horizontal(HORZ_WALL_LENGTH, WALL4_M1_X, WALL4_M1_Y, '=');
}


void check_vert_wall(uint8_t wall_x, uint8_t wall_y, uint8_t wall_len){
    if ((wall_x - ball_x) > ball_x_vel){
        //wall not affecting ball

    }
    else if ((wall_x - ball_x) <= ball_x_vel &&
            ((wall_y - wall_len) <= ball_y <= wall_y)){
        //wall stops ball in x direction
        if (ball_x > wall_x){
            //if heading towards wall from the right
            ball_x += wall_x + 1;
        }
        else{
            //if heading towards wall from the left
            ball_x += wall_x - 1;
        }
        ball_x_vel = 0;
        ball_y += ball_y_vel;
    }
}

void check_horz_wall(uint8_t wall_x, uint8_t wall_y, uint8_t wall_len){
    if ((wall_y - ball_y) > ball_y_vel){
        //wall not affecting ball
    }
    else if ((wall_y - ball_y) <= ball_y_vel &&
            ((wall_x - wall_len) <= ball_x <= wall_x)){
        //wall stops ball in y direction
        if (ball_y > wall_y){
            //if heading towards wall from below
            ball_y += wall_y + 1;
        }
        else{
            //if heading towards wall from above
            ball_y += wall_y - 1;
        }
        ball_y_vel = 0;
        ball_x += ball_x_vel;
    }
}

void update_ball(int16_t x_accel, int16_t y_accel){
    ball_x_vel += x_accel;
    ball_y_vel += y_accel;

}

void check_border(){
    check_vert_wall(1, WIDTH, WIDTH);
    check_vert_wall(LENGTH, WIDTH , WIDTH);
    check_vert_wall(1, 1, LENGTH);
    check_vert_wall(1, WIDTH, LENGTH);
}

void check_maze1(){
    int old_ball_x = ball_x;
    int old_ball_y = ball_y;
    check_border();
    check_vert_wall(WALL1_M1_X, WALL1_M1_Y, VERT_WALL_LENGTH);
    check_vert_wall(WALL2_M1_X, WALL2_M1_Y, VERT_WALL_LENGTH);
    check_horz_wall(WALL3_M1_X, WALL3_M1_Y, HORZ_WALL_LENGTH);
    check_horz_wall(WALL4_M1_X, WALL4_M1_Y, HORZ_WALL_LENGTH);
    if(old_ball_x == ball_x && old_ball_y == ball_y){
        //if none of the walls affect the ball's movement
        ball_x += ball_x_vel;
        ball_y += ball_y_vel;
    }
    move_cursor(old_ball_x, old_ball_y);
    uart_write(' ');
    move_cursor(ball_x, ball_y);
    uart_write('O');

}

void scope_refresh_term() {

}

void paint_terminal() {
    term_clear_screen();
    hide_cursor();
    print_border();

    scope_refresh_term();
}




