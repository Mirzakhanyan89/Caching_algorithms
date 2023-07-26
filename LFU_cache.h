/*	LFU_cache.h		*/

#ifndef LFU_CACHE_H
#define LFU_CACHE_H

struct CacheNode2 {
    int key;
    int value;
    int frequency;
	CacheNode2* prev;
    CacheNode2* next;

    CacheNode2(int k, int v) : key(k), value(v), frequency(0), prev(nullptr), next(nullptr) {}
};

#include <unordered_map>
#include <list>

class LFUCache {
private:
    int capacity;
    std::unordered_map<int, CacheNode2*> cacheMap;
    std::unordered_map<int, std::list<CacheNode2*>> frequencyMap;
    int minFrequency;

public:
    LFUCache(int cap) : capacity(cap), minFrequency(0) {}

    int get(int key) {
        if (cacheMap.find(key) != cacheMap.end()) {
            CacheNode2* node = cacheMap[key];
            int freq = node->frequency;

            frequencyMap[freq].remove(node);
            if (frequencyMap[freq].empty()) {
                frequencyMap.erase(freq);
                if (minFrequency == freq)
                    minFrequency++;
            }

            node->frequency++;
            frequencyMap[node->frequency].push_back(node);

            return node->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (capacity == 0)
            return;

        if (cacheMap.find(key) != cacheMap.end()) {
            CacheNode2* node = cacheMap[key];
            int freq = node->frequency;

            frequencyMap[freq].remove(node);
            if (frequencyMap[freq].empty()) {
                frequencyMap.erase(freq);
                if (minFrequency == freq)
                    minFrequency++;
            }

            node->value = value;
            node->frequency++;
            frequencyMap[node->frequency].push_back(node);
        } else {
            if (cacheMap.size() == capacity) {
                auto& lfuList = frequencyMap[minFrequency];
                CacheNode2* nodeToRemove = lfuList.front();
                cacheMap.erase(nodeToRemove->key);
                lfuList.pop_front();
                delete nodeToRemove;
            }

            CacheNode2* newNode = new CacheNode2(key, value);
            newNode->frequency = 1;
            frequencyMap[1].push_back(newNode);
            cacheMap[key] = newNode;
            minFrequency = 1;
        }
    }
};


#endif		// LFU_CACH_H


