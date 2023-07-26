/*	MRU_cache.h	*/

#ifndef MRU_CACHE_H
#define MRU_CACHE_H

#include "cache_node.h"

#include <unordered_map>

class MRUCache {
private:
    int capacity;
    std::unordered_map<int, CacheNode*> cacheMap;
    CacheNode* head;
    CacheNode* tail;

    void moveToBack(CacheNode* node) {
        if (node == tail)
            return;

        node->next->prev = node->prev;
        if (node == head)
            head = head->next;
        else
            node->prev->next = node->next;

        tail->next = node;
        node->prev = tail;
        node->next = nullptr;
        tail = node;
    }

public:
    MRUCache(int cap) : capacity(cap), head(nullptr), tail(nullptr) {}

    int get(int key) {
        if (cacheMap.find(key) != cacheMap.end()) {
            CacheNode* node = cacheMap[key];
            moveToBack(node);
            return node->value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (cacheMap.find(key) != cacheMap.end()) {
            CacheNode* node = cacheMap[key];
            node->value = value;
            moveToBack(node);
        } else {
            if (cacheMap.size() == capacity) {
                cacheMap.erase(head->key);
                if (head->next)
                    head->next->prev = nullptr;
                else
                    tail = nullptr;
                head = head->next;
            }
            CacheNode* newNode = new CacheNode(key, value);
            if (tail)
                tail->next = newNode;
            else
                head = newNode;
            newNode->prev = tail;
            tail = newNode;
            cacheMap[key] = newNode;
        }
    }
};


#endif			//MRU_CACH_H
