/*	LRU_cache.h	*/

#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "cache_node.h"

#include <unordered_map>


class LRUCache {
private:
    int capacity;
	std::unordered_map<int, CacheNode*> cacheMap;
    CacheNode* head;
    CacheNode* tail;

    void moveToFront(CacheNode* node) {
        if (node == head)
            return;

        node->prev->next = node->next;
        if (node == tail)
            tail = tail->prev;
        else
            node->next->prev = node->prev;

        node->next = head;
        head->prev = node;
        head = node;
        node->prev = nullptr;
    }

public:
    LRUCache(int cap) : capacity(cap), head(nullptr), tail(nullptr) {}

    int get(int key) {
        if (cacheMap.find(key) != cacheMap.end()) {
            CacheNode* node = cacheMap[key];
            moveToFront(node);
            return node->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            CacheNode* node = cacheMap[key];
            node->value = value;
            moveToFront(node);
        } else {
            if (cacheMap.size() == capacity) {
                cacheMap.erase(tail->key);
                if (tail->prev)
                    tail->prev->next = nullptr;
                else
                    head = nullptr;
                tail = tail->prev;
            }
            CacheNode* newNode = new CacheNode(key, value);
            if (head)
                head->prev = newNode;
            else
                tail = newNode;
            newNode->next = head;
            head = newNode;
            cacheMap[key] = newNode;
        }
    }
};


#endif		//LRU_CACHE_H

