#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int file, count;

    if (argc != 3) {
        printf("Invalid number of arguments, exiting!\n");
        return -2;
    }

    if ((file = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
        perror("UART: Failed to open the file.\n");
        return -1;
    }

    struct termios options;

    tcgetattr(file, &options);

    cfmakeraw(&options);
    // B115200 --> makes shure that transmitter and receiver between arduino and
    // pi have same board-rate
    options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
    options.c_iflag = IGNPAR | ICRNL;
    tcflush(file, TCIFLUSH);
    tcsetattr(file, TCSANOW, &options);

    // examplary input of user: << ./command LED 255 >>
    if (strcmp(argv[1], "LED") == 0) {
        int value =
            atoi(argv[2]);  // "int" allows also higher input than 255 and lower
                            // input than 0 --> can be corrected in that manner
        // send the string plus the null character
        if (value >= 0 && value <= 255) {  // only allow values in that range
            if ((count = write(file, &value, 1)) < 0) {
                perror("Failed to write to the output\n");
                return -1;
            }
        } else {
            printf("Error: %d is out of range.\n", value);
        }
    } else {
        printf(
            "The application was called in the wrong way. Please exectue it "
            "again as follows: ./command LED [value]\n");
    }

    usleep(100000);

    unsigned char receive[100];

    if ((count = read(file, (void *)receive, 100)) < 0) {
        perror("Failed to read from the input\n");
        return -1;
    }

    if (count == 0)
        printf("There was no data available to read!\n");
    else {
        receive[count] = 0;  // There is no null character sent by the Arduino
        printf("The following was read in [%d]: %s\n", count, receive);
    }

    close(file);
    return 0;
}
