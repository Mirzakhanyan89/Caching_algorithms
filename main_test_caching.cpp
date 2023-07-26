/*	main_test_caching.cpp	*/

#include <iostream>
#include "LRU_cache.h" // Replace with the appropriate header file for LRUCache
#include "MRU_cache.h" // Replace with the appropriate header file for MRUCache
#include "LFU_cache.h" // Replace with the appropriate header file for LFUCache

int main() {
    // Test parameters
    int cacheCapacity = 3;
    int testData[] = {1, 2, 3, 4, 5};

    // Test LRU Cache
    std::cout << "Testing LRU Cache:" << std::endl;
    LRUCache lruCache(cacheCapacity);
    for (int data : testData) {
        lruCache.put(data, data * 10);
        std::cout << "Put (" << data << ", " << data * 10 << ")" << std::endl;
    }

    std::cout << "Getting data from LRU Cache:" << std::endl;
    for (int data : testData) {
        int value = lruCache.get(data);
        if (value != -1) {
            std::cout << "Key: " << data << ", Value: " << value << std::endl;
        } else {
            std::cout << "Key: " << data << ", Value: Not found" << std::endl;
        }
    }

    // Test MRU Cache
    std::cout << "\nTesting MRU Cache:" << std::endl;
    MRUCache mruCache(cacheCapacity);
    for (int data : testData) {
        mruCache.put(data, data * 10);
        std::cout << "Put (" << data << ", " << data * 10 << ")" << std::endl;
    }

    std::cout << "Getting data from MRU Cache:" << std::endl;
    for (int data : testData) {
        int value = mruCache.get(data);
        if (value != -1) {
            std::cout << "Key: " << data << ", Value: " << value << std::endl;
        } else {
            std::cout << "Key: " << data << ", Value: Not found" << std::endl;
        }
    }

    // Test LFU Cache
    std::cout << "\nTesting LFU Cache:" << std::endl;
    LFUCache lfuCache(cacheCapacity);
    for (int data : testData) {
        lfuCache.put(data, data * 10);
        std::cout << "Put (" << data << ", " << data * 10 << ")" << std::endl;
    }

    std::cout << "Getting data from LFU Cache:" << std::endl;
    for (int data : testData) {
        int value = lfuCache.get(data);
        if (value != -1) {
            std::cout << "Key: " << data << ", Value: " << value << std::endl;
        } else {
            std::cout << "Key: " << data << ", Value: Not found" << std::endl;
        }
    }

    return 0;
}

