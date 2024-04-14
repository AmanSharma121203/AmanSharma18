#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LFUCache {
private:
    int capacity;
    unordered_map<int, pair<int, int>> cache; // key-value and frequency
    unordered_map<int, list<int>> freqMap;   // frequency and list of keys
    unordered_map<int, list<int>::iterator> keyMap; // key and its iterator in freqMap list
    int minFreq;

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        minFreq = 0;
    }
    
    void updateFrequency(int key) {
        int freq = cache[key].second;
        // Remove key from current frequency list
        freqMap[freq].erase(keyMap[key]);
        // If the list becomes empty and it was the minimum frequency, update minFreq
        if (freqMap[freq].empty() && freq == minFreq)
            minFreq++;
        // Increase frequency and move the key to the new frequency list
        freq++;
        cache[key].second = freq;
        freqMap[freq].push_back(key);
        keyMap[key] = --freqMap[freq].end();
    }
    
    void evict() {
        // Find the least frequently used key to evict
        int key_to_evict = freqMap[minFreq].front();
        // Remove the key from cache and keyMap
        cache.erase(key_to_evict);
        keyMap.erase(key_to_evict);
        // Remove the key from the frequency list
        freqMap[minFreq].pop_front();
    }
    
    void refer(int key) {
        if (capacity <= 0)
            return;

        // If key is already present in cache, update its frequency
        if (cache.find(key) != cache.end()) {
            updateFrequency(key);
            return;
        }

        // If cache is full, evict the least frequently used key
        if (cache.size() >= capacity)
            evict();

        // Add the new key to cache with frequency 1
        cache[key] = {0, 1};
        freqMap[1].push_back(key);
        keyMap[key] = --freqMap[1].end();
        minFreq = 1;
    }
    
    void display() {
        for (auto& kv : cache)
            cout << kv.first << " ";
        cout << endl;
    }
};

int main() {
    // Cache size is 4
    LFUCache cache(4);
    cache.refer(1);
    cache.refer(2);
    cache.refer(3);
    cache.refer(1);
    cache.refer(4);
    cache.refer(5);
    cache.display(); // Output should be: 5 4 1 3
    return 0;
}
