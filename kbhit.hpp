#if defined (_WIN32) || (_WIN64)
#include <conio.h>

#else
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

int kbhit()
{
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

#endif
