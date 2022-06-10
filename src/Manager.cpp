#include "Manager.h"
#include "Util.h"

Manager* Manager::mIns = nullptr;
Manager::Manager()
{
}

Manager::~Manager()
{
	delete m_cache;
	delete m_mainMemory;
}

Manager* Manager::getIns()
{
	if (!mIns)
		mIns = new Manager();
	return mIns;
}

void Manager::init(char* sizeCache, char* fileName)
{
    int size;
    if (!Util::checkReaderLine(string(sizeCache), size)) {
        LOG("INVALID CACHE SIZE. Program will be exit")
		exit(EXIT_FAILURE);
	} else {
		LOG("Init cache with size: %d", size)
	}
	m_cache = new Cache(size);
	m_mainMemory = new MainMemory(fileName);
}

string Manager::getValue(int key, bool &miss)
{
	m_cacheMutex.lock();
	auto rs = m_cache->getValue(key, miss);
	m_cacheMutex.unlock();
	if (miss) {
		m_fileMutex.lock();
		rs = m_mainMemory->readLine(key);
		m_fileMutex.unlock();
		m_cacheMutex.lock();
		m_cache->addValue(key, rs);
		m_cacheMutex.unlock();
	}
	return rs;
}

void Manager::setValue(int key, const string& value)
{
	m_fileMutex.lock();
	m_mainMemory->writeLine(key, value);
	m_fileMutex.unlock();
	m_cacheMutex.lock();
	m_cache->updateValue(key, value);
	m_cacheMutex.unlock();
}

