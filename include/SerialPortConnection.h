#include "common.h"

using SerialConnectionSignalHandlerPtr = void(*)(int);
/**
 * @brief SerialPortConnection - Class used to main the serial port connection
 *
 */
class SerialPortConnection : public std::enable_shared_from_this<SerialPortConnection>
{
  // Serail port related details
  int port_fd{-1};
  std::string port_path;
  SerialConnectionSignalHandlerPtr handler;

  // Termios related settings
  struct termios oldtio , newtio;
  struct sigaction saio; /* definition of signal action */

public:
  explicit SerialPortConnection(const char *path_, SerialConnectionSignalHandlerPtr handler_);
  bool init();
  int getConnectionPort();
  std::shared_ptr<SerialPortConnection> getConection();  
  ~SerialPortConnection();
};