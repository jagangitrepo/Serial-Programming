# Serial Programming
This repo contains modern C++ serial programing related codes

### Generate CMake
To generate the CMake to build, compile and run use the below command

```
./external/premake-5.0.0-beta2-linux/premake5.exe --script=./external/premake-cmake-master --file=./premake5.lua cmake
```

### Run Program
To test this program, we need to create a serial port using `scot` utility.
```
socat -d -d pty,raw,echo=0 pty,raw,echo=0
```
Read from the socat created serial port 
```
./Serial-Async "/dev/pts/1"
```
Write to the socat created serial port 
```
echo "Test" > /dev/pts/3
```
Stop the Serial-Async 
```
echo "" > /dev/pts/3
```

### Valgrind Check
Run the `Serial-Async` program with the Valgrind tool to check the memory leak.
After running the program, we should see the below log statement in the `valgrind-out.txt` file.
```
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose        
  --log-file=valgrind-out.txt ./Serial-Async "/dev/pts/1"
```
Result:
```
==1266== All heap blocks were freed -- no leaks are possible
==1266== 
```