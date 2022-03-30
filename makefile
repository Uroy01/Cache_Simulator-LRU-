How it works :
The memory address trace is read in from the specified file and stored in a dynamically allocated
array of mem_address structs called bank. Then the struct holds information about the memory
address: (the memory address itself, the tag bits, the index bits, and the offset bits). So there is a
mem_address struct generated for every memory address read in from the file.
Next, beginning with the first read memory address, in this case, bank[0], the memory address is
passed in check entry() for checking if it is in the cache. The algorithm checks the index bits of
the incoming mem_address struct and selects the appropriate set (list) from the cache vector
(which stores all sets in the cache).
The tag bits are compared against what is stored in the list, and if it is a match, the hits are
incremented. If it is a miss, the tag is put in the set on the LRU position.
Here is a brief showcase of how the LRU algorithm works (with arbitrary tags), with a cache of
associativity = 4
0x0040|-0x007C|-0x008D|-0x009C-|
TestCase:
- If an incoming tag= 0x748A is a miss in the cache, then it will be updated in this spot:
0x007C|-0x008D|-0x009C|-0x748A-|
Compile main.cpp, cache.h, and cache.cpp.
Include configuration file example.cfg, and example.trc
Compile with g++ using c++11 with the following command: g++ -std=c++11 Cache.cpp
main.cpp -o hw ./hw
- - -
Some of the sample runs :
Cache Size=32768 Block Size=64 Associativity=4 HIT RATE: 0.85424
Cache Size=32768 Block Size=64 Associativity=2 HIT RATE: 0.853662 Cache Size=16384 Block Size=64 Associativity=2 HIT RATE: 0.852278 Cache Size=16384 Block Size=64 Associativity=8 HIT RATE: 0.853008
