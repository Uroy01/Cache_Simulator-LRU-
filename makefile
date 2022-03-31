TestCase:
- If an incoming tag= 0x748A is a miss in the cache, then it will be updated in this spot:
0x007C|-0x008D|-0x009C|-0x748A-|
Compile main.cpp, cache.h, and cache.cpp.
Include configuration file example.cfg, and example.trc
Compile with g++ using c++11 with the following command:

g++ -std=c++11 Cache.cpp
main.cpp -o hw ./hw
- - -
Some of the sample runs :
Cache Size=32768 Block Size=64 Associativity=4 HIT RATE: 0.85424
Cache Size=32768 Block Size=64 Associativity=2 HIT RATE: 0.853662 Cache Size=16384 Block Size=64 Associativity=2 HIT RATE: 0.852278 Cache Size=16384 Block Size=64 Associativity=8 HIT RATE: 0.853008
