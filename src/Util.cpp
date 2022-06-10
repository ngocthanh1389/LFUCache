#include "Util.h"

#include <regex>

bool Util::checkReaderLine(const string& s, int& x)
{
    regex rg("^\\d+$");
	if (regex_match(s, rg)) {
		x = stoi(s);
		return true;
	} 
    return false;
}

bool Util::checkWriterLine(const string& s, int &x, string& v)
{
    regex rg("^\\d+ .*");
	if (regex_match(s, rg)) {
		smatch m; 
		rg = regex("^\\d+ ");
		regex_search(s, m, rg); 
		x = stoi(m[0]);
        v = s;
		v.erase(0, m[0].length());
		return true;
	} 
	return false;
}
