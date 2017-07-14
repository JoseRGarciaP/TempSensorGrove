#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{

	char comandoSalir[5];
	
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

	
	sleep(1);
	
	while(strcmp(comando, "FIN") != 0) {
	
	// Read 2 bytes of temperature data
	// temp msb, temp lsb
	if(read(file, data, 2) != 2) {
		printf("Error : Input/Output error \n");
	} else {
		// Convert the data
		float cTemp = (((data[0] * 256 + data[1]) * 175.72) / 65536.0) - 46.85;
		float fTemp = cTemp * 1.8 + 32;

		// Output data to screen
		printf("Temperature in Celsius : %.2f C \n", cTemp);
		printf("Temperature in Fahrenheit : %.2f F \n", fTemp);
	}
	
	
	
	printf("'FIN' para acabar \n");
	scanf("%s", comando);
	
	}

	
}
