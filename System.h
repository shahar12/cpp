#include <algorithm>
#include "DataStructFile.h"
#include <cctype>

class System{
    public:
    /////////METODES/////////////
    System();
    System(string l);
    System(const System& s);
    const System& operator=(const System& s);
    void setLine(string l);
    string getLine()const;
    void print_prompt();
    int getNumWords() const;
    void setNumWords(int n);
    void checkFileName(string fileName);
    DataStructFile& getDsf()const;
    void setDsf(DataStructFile& f);
    void setStrWords();
    void callFunctions();
    ~System();

    ////////EXEPTIONS/////////
    class wrongUsage{
        public:
        wrongUsage(string s): commandUsage(s) {}
        void printError() { cout<<"error: USAGE "<<commandUsage<<"."<<'\n'; }
        private:
        string commandUsage;
    };
    class UnknownCommand {};

    private:
    string line;
    string strWords[TEN];
    DataStructFile *dsf;
    int numWords;
};