#ifndef READERCREATOR_H
#define READERCREATOR_H

#include <thread>
#include <list>

using namespace std;

class ReaderCreator
{
public:
    ReaderCreator(char*);
    ~ReaderCreator();
    void waitFinish();
private:
    static void reader(string file);
    list<thread*> m_threads;

};

#endif
