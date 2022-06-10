README:
	This program demo Least Frequently Used caching. 
	In this program, the least frequently used cache block is removed whenever the cache is overflowed.
	Cache access in memory of program. Main Memory access by file.

BUILD:
	I built in g++ (Ubuntu 5.5.0-12ubuntu1~14.04) 5.5.0 20171010
	c++11	
	Go to folder src/  
	make clean
	make
	Cache binary file will be complied

RUN: 
	./Cache CacheSize Readers Writers MainMemory
	-CacheSize is maximum element cache can store
	-Readers is file contain reader file
	-Writer is file contain wirter file
	-MainMemory is file store data
	-Program will be read data in reader file and store in reader file name + ".out"
	-Program will be write data from writer file into MainMemory
	
EXCEPTIONS:
	If not enough arguments, program will be exit with failure.
	If CacheSize < 0, program will be exit with failure.
	If Can't open file, program will notify
	If MainMemory file can't open, get value return ""
	Each line of reader must be positive integer, if not return INVALID
	Each line of writer must have format: positive integer + " " + value
	
Thank for your time