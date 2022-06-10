#include "MainMemory.h"
#include <fstream>
#include "Util.h"

MainMemory::MainMemory(char* name)
{
    m_fileName = string(name);
}

MainMemory::~MainMemory()
{
}

string MainMemory::readLine(int n)
{
    if (n <=0)
        return "";
    fstream stream;
    stream.open(m_fileName, fstream::in);
    if (!stream.is_open()) {
        LOG("CAN'T ACCESS MAIN MEMORY")
        return "";
    }
    int count = 0;
    string s = "";
    while (count < n && getline(stream, s)) {
        count++;
    }
    stream.close();
    return count < n ? "" : s;			// if read line > size of file return empty
}
void MainMemory::writeLine(int n, const string& value)
{
    if (n <=0)
        return;
    fstream stream;
    stream.open(m_fileName, fstream::in);
    if (!stream.is_open()) {
        LOG("CAN'T ACCESS MAIN MEMORY")
        return ;
    }
    ofstream tmpStream(m_fileName + ".tmp");
    int count = 0;
    string s = "";
    while (count < n-1  && getline(stream, s)) {
        count++;
        tmpStream << s << '\n';
    }
    if (count < n - 1) {				// case insert line greater than number line of file
        for (int i = count + 1; i < n; i++) {
            tmpStream <<'\n';
        }
        tmpStream << value << '\n';
    } else {							// case replace line of file
        tmpStream << value << '\n';
        getline(stream, s);
        while (getline(stream, s)) {
            tmpStream << s << '\n';
        }
    }
    stream.close();
    tmpStream.close();
    remove(m_fileName.c_str());
    rename(string(m_fileName + ".tmp").c_str(), m_fileName.c_str());
}
