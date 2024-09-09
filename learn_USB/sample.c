#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
 
/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.
 */
  
int open_port(void)
{
  int fd; /* File descriptor for the port */
 
  fd = open("/dev/tty.usbserial-DN02Z1QJ", O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
    {
      /*
       * Could not open the port.
       */
 
      perror("open_port: Unable to open /dev/ttyS0 - ");
    }
  else
    fcntl(fd, F_SETFL, FNDELAY);
 
  printf ( "In Open port fd = %i\n", fd);
 
  return (fd);
}
int main()

{
  int fd;  // File descriptor
  int n;
 
  fd = open_port();
   for ( n = 0 ; n < 1000000000 ; n++)
    {
      n++;
      n--;
    }


  // Read the configureation of the port 
 
  struct termios options;
  tcgetattr( fd, &options );
 
  /* SEt Baud Rate */
 
  cfsetispeed( &options, B9600 );
  cfsetospeed( &options, B9600 );
  
  //I don't know what this is exactly 
 
  options.c_cflag |= ( CLOCAL | CREAD );
 
  // Set the Charactor size
 
  options.c_cflag &= ~CSIZE; /* Mask the character size bits */
  options.c_cflag |= CS8;    /* Select 8 data bits */
 
  // Set parity - No Parity (8N1)
   
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
 
  // Disable Hardware flowcontrol
 
  //  options.c_cflag &= ~CNEW_RTSCTS;  -- not supported
 
  // Enable Raw Input
   
  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
 
  // Disable Software Flow control
 
  options.c_iflag &= ~(IXON | IXOFF | IXANY); 

  // Chose raw (not processed) output
 
  options.c_oflag &= ~OPOST;
 
  if ( tcsetattr( fd, TCSANOW, &options ) == -1 )
    printf ("Error with tcsetattr = %s\n", strerror ( errno ) );
  else
    printf ( "%s\n", "tcsetattr succeed" );
 
  fcntl(fd, F_SETFL, FNDELAY);
 
	//int *st;
	//*st = 1; 
  // Write some stuff !!!
  //n = write(fd, "1", 4);
	char writer_buffer[] ="1";
	n = write(fd,&writer_buffer,sizeof(writer_buffer));
  if (n < 0)
    fputs("write() of 4 bytes failed!\n", stderr);
  else
		printf("\n  %s \n written to \n",writer_buffer);
    printf ("Write succeed n = %i\n", n );
 
  for ( n = 0 ; n < 1000000000 ; n++)
    {
      n++;
      n--;
    }

  char buf[40];
 
  n = read( fd, &buf, 40 );
 
  if ( n == -1 )
      printf ( "Error = %s\n", strerror( errno ) );
 
  printf ( "Number of bytes to be read = %i\n", n );
  printf ( "Buf = %s\n", buf );
 
  close( fd );

}       
/*
issue#1
---
there are three steps, open serial port, write, read.
in between those steps, there should be delays for the port to react
issue#2
---
using screen + port + baud rate
it can not only monitor the port, but also sent data to it

*/ 

