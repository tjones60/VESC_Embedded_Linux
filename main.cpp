// Main program to test UART communication from BBB to VESC
// Last modified on 7/4/2017 by: Ryan Owens
#include <stdio.h>
#include "bldc.h"
#include "motortypes.h"
#include <unistd.h> // for usleep

int main(void) {
	// variables
	int command = 0;
	int sleep = 3000;
	int reads = 0;
	bool decrement = false;
	bool loop = true;
	
	float val = 0;
	float brake = 0;
	float pos = 0;
	
	RxData testData = {};
	
	// Initialize the Serial interface
	BLDC::init((char*)"/dev/ttyO1");
	
	// Initialize motor objects
	// Parameters are defined in motortypes.h
	BLDC leftMotor(VESC1, motor1);
	BLDC rightMotor(VESC2, motor2);
	
	// Main loop 
	while(loop) {
		printf("Choose a command\n");
		printf("    1 : Set speed\n");
		printf("    2 : Set current\n");
		printf("    3 : Apply brake\n");
		printf("    4 : Set duty cycle\n");
		printf("    5 : Set position\n");
		printf("    6 : Sweep position 0-360 degrees\n");
		printf("    7 : Get values\n");
		printf("    8 : Send alive\n");
		printf("    9 : Get Position\n");
		printf("Other : End\n");
		printf("Enter a number: ");
		scanf("%d", &command);
		switch(command) {
			case 1:
				printf("Enter desired speed in RPM: ");
				scanf("%f", &val);
				leftMotor.set_Speed(val);
				rightMotor.set_Speed(val);
				printf("Speed set to %f RPM\n\n", val);
				break;
			case 2:
				printf("Enter desired current in Amps: ");
				scanf("%f", &val);
				leftMotor.set_Current(val);
				rightMotor.set_Current(val);
				printf("Current set to %f Amps\n\n", val);
				break;
			case 3:
				printf("Enter desired brake current in Amps: ");
				scanf("%f", &brake);
				leftMotor.apply_Brake(brake);
				rightMotor.apply_Brake(brake);
				printf("Brake current set to %f Amps\n\n", brake);
				break;
			case 4:
				printf("Enter desired duty cycle -1.0 to 1.0: ");
				scanf("%f", &val);
				leftMotor.set_Duty(val);
				rightMotor.set_Duty(val);
				printf("Duty cycle set to %f\n\n", val);
				break;
			case 5:
				printf("Enter desired position 0-360 degrees: ");
				scanf("%f", &pos);
				leftMotor.set_Pos(pos);
				rightMotor.set_Pos(pos);
				printf("Position set to %f\n\n", pos);
				break;
			case 6:
				printf("Sweeping position from 0-360 degrees\n\n");
				while (true) {
					leftMotor.set_Pos(pos);
					rightMotor.set_Pos(pos);
					if (pos == 360)
						decrement = true;
					else if (pos == 0)
						decrement = false;

					if (decrement == true)
						pos -= 1;
					else
						pos += 1;
					usleep(sleep);
				}
				break;
			case 7:
				// Loop through state machine until all reads are finished.
				// Must call the sample_Data() function continuously, or 
				// run inside a thread to read continuously
				// sample_Data() is non-blocking
				while (reads < BLDC::num_Motors()){
					if(BLDC::sample_Data())
						reads++;
				}
				leftMotor.print_Data();
				rightMotor.print_Data();
				break;
			case 8:
				leftMotor.send_Alive();
				rightMotor.send_Alive();
				printf("Alive sent\n\n");
				break;
			case 9:
				leftMotor.request_Pos();
				break;
			default:
				loop = false;
				break;
		}
		command = 0;
		val = 0;
		brake = 0;
		reads = 0;
		}
	leftMotor.apply_Brake(3);
	rightMotor.apply_Brake(3);
	BLDC::close();
}
