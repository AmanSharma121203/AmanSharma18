#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    list<int> cache; // doubly linked list to store the pages
    unordered_map<int, list<int>::iterator> pageMap; // map to store page number and its iterator in the list
    int capacity; // capacity of cache

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    void refer(int pageNumber) {
        // If page is not present in cache
        if (pageMap.find(pageNumber) == pageMap.end()) {
            // If cache is full, remove the least recently used page
            if (cache.size() == capacity) {
                int leastRecentPage = cache.back();
                cache.pop_back();
                pageMap.erase(leastRecentPage);
            }
        }
        else {
            // Page is present in cache, remove it from current location and update cache and map
            cache.erase(pageMap[pageNumber]);
        }
        // Add the page to the front of cache and update the map
        cache.push_front(pageNumber);
        pageMap[pageNumber] = cache.begin();
    }
    
    void display() {
        for (auto it = cache.begin(); it != cache.end(); ++it)
            cout << *it << " ";
        cout << endl;
    }
};

int main() {
    // Cache size is 4
    LRUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(3);
    cache.refer(1);
    cache.refer(4);
    cache.refer(5);
    cache.display(); // Output should be: 5 4 1 3
    return 0;
}
