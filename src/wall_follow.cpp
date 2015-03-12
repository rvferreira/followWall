/*
 * wall_follow.cpp
 *
 * Trabalho 1 - Disciplina: Programacao de Robos Moveis Autonomos
 * prof.: Fernando Osorio
 *
 *  Created on: Apr 24, 2013
 *      Author: Raphael Victor Ferreira
 *      nUSP 7143889
 *
 *  Description: Wall following behavior functions
 */

#include "wall_follow.h"

#define MAX_FRONT_WALL_DISTANCE 0.8	/*free distance for walk in front of robot*/
#define EMERGENCY_CONST 5	/*divisor for max distance to get emergency distance (robot stop distance)*/

#define MAX_SIDE_WALL_DISTANCE 0.6	/*max range from side wall for robot*/
#define MIN_SIDE_WALL_DISTANCE 0.3	/*min range from side wall for robot*/

#define GENERAL_SPEED_CONST 1.3		/*speeds multiplier*/
#define SPEED_CONST GENERAL_SPEED_CONST*1		/*linear speed multiplier*/
#define TURN_SPEED_CONST GENERAL_SPEED_CONST*0.6/*rotation speed multiplier*/


void front_wall_avoid(double *speed, double *turn_rate, double *distance){
	/*speed reduction when near front wall*/
	*speed *= std::min(std::min(distance[TOP_RIGHT], distance[TOP_LEFT]), 2*distance[TOP_RIGHT_2]);

	/*rotate anti-clockwise to avoid front wall*/
	*turn_rate = TURN_SPEED_CONST*0.4;

	/*if the robot get in emergency distance, stop walking*/
	if ((distance[TOP_LEFT]< MAX_FRONT_WALL_DISTANCE/EMERGENCY_CONST)||
			(distance[TOP_RIGHT]< MAX_FRONT_WALL_DISTANCE/EMERGENCY_CONST)||
			(distance[TOP_LEFT_2]< MAX_FRONT_WALL_DISTANCE/(2*EMERGENCY_CONST))||
			(distance[TOP_RIGHT_2]< MAX_FRONT_WALL_DISTANCE/(2*EMERGENCY_CONST))){

		*speed = 0;

	}

}

/*robot navigation in case of aligned robot and no obstacles*/
void free_walk(double *speed, double *turn_rate){
	*speed += SPEED_CONST*0.35;
}

/*robot angle repair navigation*/
void side_wall_angle_correct(double right_top, double right_bot, double *speed, double *turn_rate){

	/*if the robot front part is the nearest from the wall*/
	if(right_bot > right_top){
		*turn_rate += TURN_SPEED_CONST*sqrt(right_bot - right_top);
	}
	/*if the robot back part is the nearest from the wall*/
	else if(right_bot < right_top){
		*turn_rate -= TURN_SPEED_CONST*sqrt(right_top - right_bot);
	}
}

/*robot navigation in case of right side too near from the wall*/
void side_wall_avoid(double *speed, double *turn_rate){
	*speed += SPEED_CONST*0.2;
	*turn_rate += TURN_SPEED_CONST*0.3;
}

/*robot navigation in case of right side too far from the wall*/
void side_wall_approach(double *speed, double *turn_rate){
	*speed += SPEED_CONST*0.3;
	*turn_rate += -TURN_SPEED_CONST*0.3;
}

/*wall following behavior*/
void wall_follow(double *speed, double *turn_rate, PlayerCc::RangerProxy *rp){

	double distance[SONAR_COUNT];

	/*control variables*/
	*speed = 0;
	*turn_rate = 0;

	/*reading the sonars data*/
	for (int i = 0; i<SONAR_COUNT; i++){
		distance[i] = rp->GetRange(i);
	}

	/*angle adjustments on free-walk*/
	side_wall_angle_correct(distance[RIGHT_TOP], distance[RIGHT_BOT], speed, turn_rate);

	/*distance adjustments on free-walk*/
	/*max distance adjust*/
	if (!(distance[RIGHT_BOT] < MAX_SIDE_WALL_DISTANCE) || !(distance[RIGHT_TOP] < MAX_SIDE_WALL_DISTANCE)){
		side_wall_approach(speed, turn_rate);
	}
	/*min distance adjust*/
	else if(!(distance[RIGHT_BOT] > MIN_SIDE_WALL_DISTANCE) || !(distance[RIGHT_TOP] > MIN_SIDE_WALL_DISTANCE)){
		side_wall_avoid(speed, turn_rate);
	}
	/*in case of no adjustments needed*/
	else free_walk(speed, turn_rate);

	/*avoiding front wall in case of need*/
	if ((distance[TOP_RIGHT] < 5*MAX_FRONT_WALL_DISTANCE/EMERGENCY_CONST)||
			(distance[TOP_LEFT] < 5*MAX_FRONT_WALL_DISTANCE/EMERGENCY_CONST)||
			(distance[TOP_RIGHT_2] < 2*MAX_FRONT_WALL_DISTANCE/EMERGENCY_CONST)||
			(distance[TOP_LEFT_2] < 2*MAX_FRONT_WALL_DISTANCE/EMERGENCY_CONST)){
		front_wall_avoid(speed, turn_rate, distance);
	}

}
