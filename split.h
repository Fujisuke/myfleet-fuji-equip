#include <sstream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

vector<string> &split(const string &s, char separator, vector<string> &output)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, separator)) {
        output.push_back(item);
    }
    return output;
}

vector<string> split(const string &s, char separator)
{
    vector<string> output;
    split(s, separator, output);
    return output;
}
