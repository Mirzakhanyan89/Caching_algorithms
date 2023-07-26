/*	cache_node.h	*/

#ifndef CACH_NODE_H
#define CACH_NODE_H

#include <iostream>

struct CacheNode {
    int key;
    int value;
    CacheNode* prev;
    CacheNode* next;

    CacheNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};


#endif			// CACH_NODE_H
