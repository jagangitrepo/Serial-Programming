#include "SerialPortConnection.h"

#include <mutex>
#include <condition_variable>

bool ready_flag = false;
// Thread Sync for data reading
std::mutex m;
std::condition_variable cv;

int main(int argc, char *argv[])
{
  auto serial_conn = std::make_shared<SerialPortConnection>(argv[1], [](int status){
    std::cout << "received SIGIO signal.\n";
    ready_flag = true;
    std::unique_lock lk(m);
    cv.notify_one();
  });

  serial_conn->init();

  std::thread thrds[] = {
  std::thread([&cv, &m, port = serial_conn->getConnectionPort(), sleep_us = 100000](){
    bool stop_loop = false;
    while (!stop_loop)
    {
      std::unique_lock lk(m);
      cv.wait(lk, [](){ return ready_flag; });
      std::vector<char> buf(255, 0);
      int res = read(port, buf.data(), buf.size());
      std::cout << "Data: " << buf.data() << " Size: " << res << "\n";
      if (res == 1)
        stop_loop = true;    /* stop loop if only a CR was input */
      ready_flag = false; /* wait for new input */
    }
  }) };
  
  thrds[0].join();
  return 0;
}