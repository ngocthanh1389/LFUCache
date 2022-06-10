#ifndef MANAGER_H
#define MANAGER_H

#include <mutex>
#include "Cache.h"
#include "MainMemory.h"

using namespace std;

class Manager
{
public:
    static Manager* getIns();
    void init(char* sizeCache, char* fileName);
    string getValue(int key, bool &miss);
    void setValue(int key, const string& value);
private:
    Manager();
    ~Manager();
    static Manager* mIns;
    Cache* m_cache;
    MainMemory* m_mainMemory;
    mutex m_cacheMutex, m_fileMutex;

};

#endif
