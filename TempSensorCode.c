#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <math.h>

int main(int argc, char *argv[])
{

	char exits[10];
	char data[2];
	int adc_data;
	float sensor_value_tmp;
	int bValue;
	float resistance;
	float cTemperature;
	
	bValue = 4250;
	
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-2";
	if((file = open(bus, O_RDWR)) < 0)
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, I2C address is 0x50
	ioctl(file, I2C_SLAVE, 0x50);

	
	while(strcmp(exits, "EXIT") != 0) {
	
	// Read 2 bytes of temperature data
	// temp msb, temp lsb
	if(read(file, data, 2) != 2) {
		printf("Error : Input/Output error \n");
	} else {
		// Convert the data
		
		adc_data = (data[1] | data[0] << 0x08);
		sensor_value_tmp = (adc_data / (float) 4095 * 2.95 * 2 / 3.3 * 1023);
		resistance = (1023 - sensor_value_tmp) * 10000 / sensor_value_tmp;		
		cTemperature = (1 / (log(resistance / 10000) / bValue + 1 / 298.15) - 273.15);
			

		// Output data to screen
		printf("Temperature in Celsius : %.2f C \n", cTemperature);

	}
	
	
	
	printf("'EXIT' to finish, other to resume... \n");
	scanf("%s", exits);
	
	}

	return 0;
	
}
