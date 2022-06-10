#ifndef UTIL_H
#define UTIL_H

#include <mutex>
#include <thread>

using namespace std;

static mutex logMutex;

#define LOG(fmt,args...)  logMutex.lock(); printf("[Thread:%d] " fmt "\n", this_thread::get_id(), ##args);logMutex.unlock();
class Util
{
public:
    static bool checkReaderLine(const string& s, int& x);
    static bool checkWriterLine(const string& s, int& x, string& v);
};

#endif
