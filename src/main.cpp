#include "Cache.h"
#include "MainMemory.h"
#include "Manager.h"
#include "ReaderCreator.h"
#include "WriterCreator.h"
#include "Util.h"

using namespace std;

int main(int argc, char *argv[])
{
    LOG("***************************************************************")
    LOG("*                                                             *")
    LOG("*                                                             *")
    LOG("*                                                             *")
    LOG("*                       HELLO APTIV                           *")
    LOG("*               This is my Cache Demonstrator                 *")
    LOG("*                                                             *")
    LOG("*                                                             *")
    LOG("*                                                             *")
    LOG("***************************************************************")
    LOG("")
    LOG("")
    LOG("")

    if (argc < 5) {
        LOG("You need to pass 4 parameters: Cache size, Readers file, Writers file and Main memory file.\nProgram will exit.")
        return EXIT_FAILURE;
    }
	
    Manager::getIns()->init(argv[1], argv[4]);
    ReaderCreator readers(argv[2]);
    WriterCreator writers(argv[3]);
    readers.waitFinish();
    writers.waitFinish();
    LOG("Program run successfully")
    return EXIT_SUCCESS;
}
