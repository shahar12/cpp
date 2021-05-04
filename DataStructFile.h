#ifndef DATASTRUCTFILE_H
#define DATASTRUCTFILE_H

#include "File.h"

class DataStructFile{
    public:
    DataStructFile();
    DataStructFile(const DataStructFile& f);
    DataStructFile& operator=(const DataStructFile& f);
    char read(string fileName, int n);
    void write(string fileName, int n,char c);
    void touch(string fileName);
    void copy(string copiedFile,string copyTo);
    void remove(string fileName);
    void move(string copiedFile,string copyTo);
    int findFile(string fileName)const; //if not found in array return -1
    vector<File> getArray()const;
    void setArray(vector<File>& other);
    void cat(string fileName)const;
    ~DataStructFile();

    private:
    vector<File> array;
};

#endif