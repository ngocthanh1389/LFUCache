#ifndef MAINMEMORY_H
#define MAINMEMORY_H

#include <string>

using namespace std;

class MainMemory
{
public:
    MainMemory(char* name);
    ~MainMemory();
    string readLine(int n);
    void writeLine(int n, const string& value);

private:
    string m_fileName = "";
};

#endif
