#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/signal.h>

#include <functional>
#include <memory>
#include <vector>
#include <thread>
#include <iostream>

#define _POSIX_SOURCE 1 /* POSIX compliant source */