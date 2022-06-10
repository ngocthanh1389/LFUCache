#include "WriterCreator.h"
#include <fstream>
#include "Manager.h"
#include "Util.h"

void WriterCreator::writer(string file)
{
    fstream stream;
    stream.open(file, fstream::in);
    if (stream.is_open()) {
        LOG("Opened writer: %s", file.c_str())
        string s;
        while (getline(stream, s)) {
            int x;
            string y;
            if ((s.size()>0) && (s[s.size()-1] == '\r'))
                s.erase(s.size()-1);
            if (Util::checkWriterLine(s, x, y) && x>0) {
                Manager::getIns()->setValue(x, y);
            } else {
                LOG("INVALID write line %s", s.c_str())
            }
        }
    } else {
        LOG("Can't open writer: %s", file.c_str())
    }
    stream.close();
}

WriterCreator::WriterCreator(char* file)
{
    fstream stream;
    stream.open(file, fstream::in);
    if (stream.is_open()) {
        LOG("Opened writer creator: %s", file)
        string s;
        while (getline(stream, s)) {
            thread* t = new thread(writer, s);
            m_threads.push_back(t);
        }
    } else {
        LOG("Can't open write creator: %s", file)
    }
    stream.close();
}

WriterCreator::~WriterCreator()
{
    for(auto t : m_threads){
        delete t;
    }
    m_threads.clear();
}

void WriterCreator::waitFinish()
{
    for(auto t : m_threads){
        t->join();
    }
}
