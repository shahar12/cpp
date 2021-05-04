#ifndef FILE_H
#define FILE_H
#define TEN 10
#include "FileCharProxy.h"

class File{
    public:
    /////////METODES////////////
    File();
    File(string& fname);
    File(const File& f);
    const File& operator=(const File& f);
    FileCharProxy operator[](int n);    //writing
    const char& operator[](int n)const; //reading
    string getName()const;
    void setName(string fname);
    fstream* getFile()const;
    void setFile(fstream &other);
    void updateTimeStamp();
    int getSize()const;
    int setSize();
    int getLineNum() const;
    void cat()const;
//    void head()const;
//    void head(int n)const;
//    void tail()const;
//    void tail(int n)const;
     ~File();
    ////////EXEPTIONS/////////
public:
    class FileDonstExist{
        public:
        FileDonstExist(string f):fileName(f){}
        void printError(){ cout<<"error: " +fileName+ " does not exist or cannot be processed."<<'\n'; }
        private:
        string fileName;
    };

    /*
  * file refcount
  * private struct
  */

private:
    struct FileValue {
        FileValue();
        FileValue(string& fname);
        ~FileValue();
        int refCount;
        fstream *file;
        string name;
        char *finame; //for fstream constructors
        int size;
    };
    FileValue *value;



};


#endif