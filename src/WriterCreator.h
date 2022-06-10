#ifndef WRITERCREATOR_H
#define WRITERCREATOR_H

#include <thread>
#include <list>

using namespace std;

class WriterCreator
{
public:
    WriterCreator(char*);
    ~WriterCreator();
    void waitFinish();
private:
    static void writer(string file);
    list<thread*> m_threads;
};

#endif
