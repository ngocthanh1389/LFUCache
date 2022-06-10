#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <list>

using namespace std;

class Cache
{
public:
    Cache(int size) : m_size(size) {};
    string getValue(int key, bool& miss);
    void updateValue(int key, const string& value);
    void addValue(int key, const string& value);
private:
    int m_size = 0;
    int m_minFreq = 0;
    unordered_map<int, list<int>> m_freqToKeys;  // frequence to keys
    unordered_map<int, tuple<string, int, list<int>::iterator>> m_keysToTuple; //key to value, freq, iter
};

#endif // CACHE_H
