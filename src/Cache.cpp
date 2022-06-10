#include "Cache.h"
#include "Util.h"

string Cache::getValue(int key, bool& miss)
{
    if (m_keysToTuple.find(key) == m_keysToTuple.end()) {          // cache miss when can't find key
        miss = true;
        LOG("Cache size: %d miss get key: %d", m_keysToTuple.size(), key)
        return "";
    } else {
        miss = false;                                              // if found key increase frequence 1 and return value
        auto tmp = m_keysToTuple[key];
        int freq = get<1>(tmp);
        string value = get<0>(tmp);
        auto it = get<2>(tmp);
        m_freqToKeys[freq].erase(it);
        if (m_freqToKeys[freq].empty()) {
            m_freqToKeys.erase(freq);
            if (m_minFreq == freq)
                m_minFreq = freq + 1;
        }
        m_freqToKeys[freq+1].push_front(key);
        m_keysToTuple[key] = make_tuple(value, freq+1, m_freqToKeys[freq+1].begin());
        LOG("Cache size: %d hit get key: %d value: %s", m_keysToTuple.size(), key, value.c_str())
        return value;
    }
}

void Cache::updateValue(int key, const string& value)
{
    if (m_keysToTuple.find(key) == m_keysToTuple.end()) {          	// don't update when can't find key
        return;
    } else {
        auto tmp = m_keysToTuple[key];                          	// update value for key
        int freq = get<1>(tmp);
        auto it = get<2>(tmp);
        m_keysToTuple[key] = make_tuple(value, freq, it);
        LOG("Cache size: %d update key: %d value: %s", m_keysToTuple.size(), key, value.c_str())
    }
}

void Cache::addValue(int key, const string& value)
{
    if (m_size <= 0)
        return;
    if (m_keysToTuple.find(key) == m_keysToTuple.end()) {       	// if key not in cache
        if (m_keysToTuple.size() == m_size) {                   	// if cache is full, remove least frequence key then insert key
            int rmKey = m_freqToKeys[m_minFreq].back();
            if (m_freqToKeys[m_minFreq].size() == 1)
                m_freqToKeys.erase(m_minFreq);
            else
                m_freqToKeys[m_minFreq].pop_back();
            m_keysToTuple.erase(rmKey);
            LOG("Cache size: %d remove key: %d freq: %d", m_keysToTuple.size(), rmKey, m_minFreq)
        }
        m_freqToKeys[1].push_front(key);
        m_keysToTuple[key] = make_tuple(value, 1, m_freqToKeys[1].begin());
        m_minFreq = 1;
        LOG("Cache size: %d add key: %d value: %s freq: 1", m_keysToTuple.size(), key, value.c_str())
        m_minFreq = 1;
    } else {                                                    	// if key in cache
        auto tmp = m_keysToTuple[key];                          	// increase frequence 1 and update value
        int freq = get<1>(tmp);
        auto it = get<2>(tmp);
        m_freqToKeys[freq].erase(it);
        if (m_freqToKeys[freq].empty()) {
            m_freqToKeys.erase(freq);
            if (m_minFreq == freq)
                m_minFreq = freq + 1;
        }
        m_freqToKeys[freq+1].push_front(key);
        m_keysToTuple[key] = make_tuple(value, freq+1, m_freqToKeys[freq+1].begin());
        LOG("Cache size: %d add key: %d value: %s freq: %d", m_keysToTuple.size(), key, value.c_str(), freq+1)
    }
}
