#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

class FileCharProxy
{
    public:
        FileCharProxy(fstream& stream, int index) : stream(stream), index(index) {}
        FileCharProxy& operator=(char ch)
        {
            stream.clear();
            stream.seekp(index);
            stream.put(ch);
            return *this;
        }
        ~FileCharProxy(){}
    private:
        fstream& stream;
        int index;
};