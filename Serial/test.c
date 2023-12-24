#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <time.h>
#include <sys/types.h>

int main(){
	printf("Hello World\n");	
	
	// Method 1
	//Open communication with arduino	
	int portName = open(" /dev/tty.usbserial-DN02Z1QJ ", O_RDWR | O_NOCTTY | O_NDELAY);
	
	struct termios options;
	tcgetattr(portName, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	options.c_cflag |= (CLOCAL | CREAD);
	tcsetattr(portName, TCSANOW, &options);
	//8 bit characters	
	options.c_cflag &= ~CSIZE; /* Mask the character size bits */
	options.c_cflag |= CS8;    /* Select 8 data bits */
	//No parity
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	
	//Send Take Sample command to arduino
	int num[] = {1};
		
	int	written = write(portName,&num, sizeof(int));
	printf("write returned %d\n",written);
	//Close communication
	close(portName);

	return 0;
}
