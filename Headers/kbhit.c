#include <stdio.h> //Biblioteca necessária...
#include <termios.h> //Biblioteca necessária...
#include <unistd.h> //Biblioteca necessária...
#include <sys/select.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include "kbhit.h"
enum boolean {
    false = 0, true = 1
};
typedef enum boolean bool;

int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

