# Cache_Simulator-LRU-Using C


It is a memory system simulator. This simulator can emulate a system with multiple levels of instruction and data caches, each of which can be configured for different sizes and organizations. This simulator is ideal for fast cache simulation if the effect of cache performance on execution time is not needed. The LRU caching scheme is to remove the least recently used frame when the cache is full and a new page is referenced which is not there in cache. We use two data structures to implement an LRU Cache :

Queue which is implemented using a doubly linked list. The maximum size of the queue will be equal to the total number of frames available (cache size). The most recently used pages will be near front end and least recently pages will be near the rear end. A Hash with page number as key and address of the corresponding queue node as value.Here i am using queue for LRU implementation. I am using queue for LRU implementation,
