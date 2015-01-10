/*
Bartender LegoNXT 

Motor A - Opener
Motor B - Claws
Botor C - Wheels

2 - Blue - Bacardi + Coke
3 - Green - Sprite
4 - Yellow - Captain Morgan + Coke
5 - Red - Coke
6 - White - Captain Morgan + Sprite
*/

const int start = 0;
const int shakestart = 650;
const int distances [5][2] = {{360, 1130}, {1368, 0}, {618, 1130} , {1130, 0}, {618, 1368}};

void closeClaws()
{
	motor[motorB] = -40;
	wait10Msec(20);
	motor[motorB] = 0;
}

int moveGlass (int sdist, int fdist)
{
	time1[0] = 0;
	nMotorEncoder[motorC] = 0;
	motor[motorC] = -30;
	while (nMotorEncoder[motorC] > -(fdist - sdist));
	motor[motorC] = 0;
	return time1[0];
}

void pourDrink ()
{
	// open bottle
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = 720;
	motor[motorA] = 70;
	while (nMotorRunState[motorA] != runStateIdle);
	motor[motorA] = 0;
	wait10Msec(50);
	// close bottle
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = -1800;
	motor[motorA] = -70;
	while (nMotorRunState[motorA] != runStateIdle);
	motor[motorA] = 0;
}

void pourChase (int speed)
{
	// open bottle
	nMotorEncoder[motorA] = 0;
	motor[motorA] = 70;
	wait1Msec(600);
	motor[motorA] = 0;
	wait10Msec(50);
	// close bottle
	motor[motorA] = -70;
	wait1Msec(1200);
	motor[motorA] = 0;
	// move away from bottle
	motor[motorC] = speed;
	wait1Msec(200);
	motor[motorC] = 0;
	// adjust opening gear
	nMotorEncoder[motorA] = 0;
	nMotorEncoderTarget[motorA] = 250;
	motor[motorA] = -75;
	while (nMotorRunState[motorA] != runStateIdle);
	// return to bottle
	motor[motorC] = -speed;
	wait1Msec(200);
	motor[motorC] = 0;
}

int shakeDrink (int dist)
{
	time1[1] = 0;
	nMotorEncoder[motorC] = 0;
	motor[motorC] = 30;
	while (nMotorEncoder[motorC] < dist - shakestart);
	int t = time1[1];
	for (int i = 0; i < 3; i++)
	{
		motor[motorC] = 70;
		wait10Msec(40);
		motor[motorC] = -70;
		wait10Msec(80);
		motor[motorC] = 70;
		wait10Msec(40);
	}
	return t;
}

void returnGlass (int time)
{
	time1[1] = 0;
	motor[motorC] = 30;
	while (time1[1] < time);
	motor[motorC] = 0;
}

void openClaws ()
{
	motor[motorB] = 40;
	wait10Msec(20);
	motor[motorB] = 0;
}

task main()
{
	// initialize
	SensorType[S4] = sensorTouch;
	SensorType[S1] = sensorCOLORFULL;
	int a, b, c, time ;
	// loop to make program continuous
	while (1)
	{
		// detect a glass being placed
		while (SensorValue[S4] == 0);
		
		// grasp glass
		closeClaws();
		
		// detect type of drink
		int type = SensorValue[S1] - 2;
		
		// move glass to bottle
		a = moveGlass(start, distances[type][0]);
		
		// pour drink
		pourDrink();
		
		// move glass to chase if needed
		if (distances[type][1] != 0)
			b = moveGlass(distances[type][0], distances[type][1]);
		// use appropriate pour function
		if (type == 0 || type == 2 || type == 3)
				pourChase(-50);
		else
			pourChase(50);
		// calculate time
		if (distances[type][1] != 0)
		{
			c = shakeDrink(distances[type][1]);
			// a removal of 2 seconds from return time due to shake
			function's inaccuracy
			time = a + b - c - 400 ;
		}
		else
			time = a;
		
		// return glass to original position
		returnGlass(time);
		// release grasp on glasses
		openClaws();
	}
}
