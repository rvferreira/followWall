/*
 * main.cpp
 *
 * Trabalho 1 - Disciplina: Programacao de Robos Moveis Autonomos
 * prof.: Fernando Osorio
 *
 *  Created on: Apr 24, 2013
 *      Author: Raphael Victor Ferreira
 *      nUSP 7143889
 *
 *  Description: Default steps for setting up a connection
 *  with PlayerStage and call a behavior
 */

#include "wall_follow.h"

int main(int argc, char *argv[]) {

	try
	{
		/*Setting up robot and sensors*/
		PlayerCc::PlayerClient robot("localhost", 6665);
		PlayerCc::RangerProxy rp(&robot, 0);
		PlayerCc::Position2dProxy pp(&robot, 0);

		/*variables for new speeds setting*/
		double newspeed;
		double newturnrate;

		/*motor habilitation*/
		pp.SetMotorEnable (true);

		for(;;)
		{
			/*Reading sensors*/
			robot.Read();

			/*Setting behavior acording to read data*/
			wall_follow(&newspeed, &newturnrate, &rp);

			/*print out the new speeds*/
			std::cout << "Speed: " << newspeed
					<< "  Turn speed: " << newturnrate
					<< std::endl << std::endl;

			/*robot speed setting up*/
			pp.SetSpeed(newspeed, newturnrate);
		}

	}
	catch (PlayerCc::PlayerError & e)
	{
		/*Exception treatment*/
		std::cerr << e << std::endl;
		return -1;
	}
	return 0;
}
