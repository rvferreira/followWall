/*
 * wall_follow.h
 *
 * Trabalho 1 - Disciplina: Programacao de Robos Moveis Autonomos
 * prof.: Fernando Osorio
 *
 *  Created on: Apr 24, 2013
 *      Author: Raphael Victor Ferreira
 *      nUSP 7143889
 *
 *  Description: Wall following behavior header file
 */

#ifndef FOLLOWBOT_SRC_WALL_FOLLOW_H_
#define FOLLOWBOT_SRC_WALL_FOLLOW_H_

#include <player-3.0/libplayerc++/playerc++.h>	/*Player c++ default lib*/
#include <iostream>		/*for cout*/
#include <algorithm>    /*for min*/


#define SONAR_COUNT 16	/*Number of sonars at my robot (Ranger)*/

/*Index description for 16 sonars*/
#define LEFT_TOP 0
#define LEFT_TOP_2 1

#define TOP_LEFT_2 2
#define TOP_LEFT 3

#define TOP_RIGHT 4
#define TOP_RIGHT_2 5

#define RIGHT_TOP_2 6
#define RIGHT_TOP 7

#define RIGHT_BOT 8
#define RIGHT_BOT_2 9

#define BOT_RIGHT_2 10
#define BOT_RIGHT 11

#define BOT_LEFT 12
#define BOT_LEFT_2 13

#define LEFT_BOT_2 14
#define LEFT_BOT 15

void free_walk(double *speed, double *turn_rate);
void front_wall_avoid(double *speed, double *turn_rate, double *distance);
void side_wall_avoid(double *speed, double *turn_rate);
void side_wall_angle_correct(double right_top, double right_bot, double *speed, double *turn_rate);
void side_wall_approach(double *speed, double *turn_rate);
void wall_follow(double *speed, double *turn_rate, PlayerCc::RangerProxy *rp);


#endif /* FOLLOWBOT_SRC_WALL_FOLLOW_H_ */
