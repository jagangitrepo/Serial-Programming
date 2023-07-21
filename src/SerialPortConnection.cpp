/**
 * @file SerialPortConnection.cpp
 * @author Jagan Kumar
 * @brief This base serial code,  I reffered from this (https://tldp.org/HOWTO/Serial-Programming-HOWTO/x115.html#AEN129) link
 * @version 0.1
 * @date 2023-07-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "SerialPortConnection.h"

SerialPortConnection::SerialPortConnection(const char *path_, SerialConnectionSignalHandlerPtr handler_) : port_path(path_), handler(handler_)
{
}

bool SerialPortConnection::init()
{
  /* open the device to be non-blocking (read will return immediatly) */
  port_fd = open(port_path.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
  if (port_fd < 0)
  {
    perror(port_path.c_str());
    return false;
  }

  /* install the signal handler before making the device asynchronous */
  saio.sa_handler = handler;
  saio.sa_mask = {0};
  saio.sa_flags = 0;
  saio.sa_restorer = NULL;
  sigaction(SIGIO, &saio, NULL);

  /* allow the process to receive SIGIO */
  fcntl(port_fd, F_SETOWN, getpid());
  /* Make the file descriptor asynchronous (the manual page says only
      O_APPEND and O_NONBLOCK, will work with F_SETFL...) */
  fcntl(port_fd, F_SETFL, FASYNC);

  tcgetattr(port_fd, &oldtio); /* save current port settings */
  /* set new port settings for canonical input processing */
  newtio.c_cflag = B9600 | CRTSCTS | CS8 | CLOCAL | CREAD;
  newtio.c_iflag = IGNPAR | ICRNL;
  newtio.c_oflag = 0;
  newtio.c_lflag = ICANON;
  newtio.c_cc[VMIN] = 1;
  newtio.c_cc[VTIME] = 0;
  tcflush(port_fd, TCIFLUSH);
  tcsetattr(port_fd, TCSANOW, &newtio);

  return true;
}

int SerialPortConnection::getConnectionPort()
{
  return port_fd;
}

std::shared_ptr<SerialPortConnection> SerialPortConnection::getConection()
{
  return shared_from_this();
}

SerialPortConnection::~SerialPortConnection()
{
  if (port_fd != -1)
  {
    /* restore old port settings */
    tcsetattr(port_fd, TCSANOW, &oldtio);

    /* Close the file*/
    close(port_fd);
  }
}