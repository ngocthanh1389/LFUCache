#include "ReaderCreator.h"
#include <fstream>
#include "Manager.h"
#include "Util.h"

void ReaderCreator::reader(string file)
{
	fstream stream;
	stream.open(file, fstream::in);
	if (stream.is_open()) {
        LOG("Opened reader: %s", file.c_str())
		ofstream outFile(file + ".out");
		if (outFile.is_open()) {
            string s;
			bool miss = false;
            while (getline(stream, s)) {
                int x;
                if ((s.size()>0) && (s[s.size()-1] == '\r'))
                    s.erase(s.size()-1);
                if (Util::checkReaderLine(s,x) && x>0) {
				outFile << Manager::getIns()->getValue(x, miss);
				if (miss)
					outFile << " Disk\n";
				else 
					outFile << " Cache\n";
                } else {
                    LOG("INVALID read line %s", s.c_str())
                    outFile << "INVALID\n";
                }
			} 
		}else {
            LOG("Can't open result for reader: %s", file.c_str())
		}
		outFile.close();
	} else {
        LOG("Can't open reader: %s", file.c_str())
	}
	stream.close();
}

ReaderCreator::ReaderCreator(char* file)
{
	fstream stream;
	stream.open(file, fstream::in);
	if (stream.is_open()) {
        LOG("Opened reader creator: %s", file);
        string s;
        while (getline(stream, s)) {
            thread* t = new thread(reader, s);
            m_threads.push_back(t);
		} 
	} else {
        LOG("Can't open reader creator: %s", file)
	}
	stream.close();
}

ReaderCreator::~ReaderCreator()
{
    for(auto t : m_threads){
        delete t;
    }
    m_threads.clear();
}

void ReaderCreator::waitFinish()
{
    for(auto t : m_threads){
        t->join();
	}
}

