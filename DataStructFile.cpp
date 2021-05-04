#include "DataStructFile.h"

DataStructFile::DataStructFile(){
}

DataStructFile::DataStructFile(const DataStructFile& f) {
    array=f.getArray();
}

DataStructFile& DataStructFile::operator=(const DataStructFile& f) {
    if(this==&f) return *this;
    else
    {
        array=f.getArray();
    }
    return *this;
}

void DataStructFile::touch(string fileName) {
    int index=findFile(fileName);
    int len = fileName.length();
    char *name = new char[len+1];
    strcpy(name, fileName.c_str());
    if(index>=0)//file in array -> so exist in folder
    {
        array[index].updateTimeStamp();
        //cout<<"//file in array -> so exist in folder"<<endl;
    }
    else
    {
        if(ifstream(name)){//file exists in folder -> but not in the array
            File newFile(fileName);
            array.push_back(newFile);
            array[array.size()-1].updateTimeStamp();
            //cout<<"file exists in folder -> but not in the array"<<endl;
        }
        else//file dosnt exists
        {
            File newFile(fileName);
            array.push_back(newFile);
            //cout<<"file dosnt exists"<<endl;
        }
    }
    delete []name;
    return;
}

// exception rethrowed
void DataStructFile::copy(string copiedFile, string copyTo) {
    int len = copiedFile.length(), len2=copyTo.length();
    char *copiedFil = new char[len+1];
    char *copyT = new char[len2+1];
    strcpy(copiedFil, copiedFile.c_str());
    strcpy(copyT, copyTo.c_str());
    int index1 = findFile(copiedFile);
    try{
        if(index1<0){                               // cuppiedFile not in the array
            if(ifstream(copiedFil)){               // cuppiedFile in folder but not in the array
                touch(copiedFile);
                index1 = array.size()-1;
            }
            else throw File::FileDonstExist(copiedFile); // cuppiedFile dosnt exists
        }
        int index2 = findFile(copyTo);
        ifstream source(copiedFil, ios::binary);
        ofstream dest(copyT, ios::binary);
        if(index2>0){                   // copyTo not in the array
            array.erase(array.begin()+index2);
        }
        dest << source.rdbuf();
        dest.close();
        touch(copyTo);             // add copyTo to the array
        delete []copiedFil;
        delete []copyT;
    }
    catch(File::FileDonstExist& e){
        e.printError();
        throw;
    }
}

void DataStructFile::remove(string fileName) {
    try{
        int index = findFile(fileName);
        if(index<0) throw File::FileDonstExist(fileName);
        else{                                        
            array.erase(array.begin()+index);
        }
    }
    catch(File::FileDonstExist& e){
        e.printError();
    }
}

void DataStructFile::move(string copiedFile, string copyTo) {
    try{
        copy(copiedFile,copyTo);
        remove(copiedFile);
    }
    catch(File::FileDonstExist& e){
        e.printError();
    }
}

char DataStructFile::read(string fileName, int n){
    try{
        int len = fileName.length();
        char *name = new char[len+1];
        strcpy(name, fileName.c_str());
        const File *temp;
        char c;
        int index = findFile(fileName);
        fstream *file1 = new fstream();
        file1->open(name, ios::in);                         //open file if already exist in folder
        if(file1->is_open()){                                   // file already exists
            File f(fileName);
            if(f.getSize()==0) return '\0';                         //if file in size of 0 return
        }
        delete []name;
        if(index < 0) throw File::FileDonstExist(fileName);
        temp= array.data() + index;
        c=(*temp)[n];
        return c;
    }
    catch(File::FileDonstExist& e){
        e.printError();
    }
    return '\0';
}

void DataStructFile::write(string fileName, int n, char c){
    try{
        int len = fileName.length();
        char *name = new char[len+1];
        strcpy(name, fileName.c_str());
        File *temp, file;
        int index = findFile(fileName);
        fstream *file1 = new fstream();
        file1->open(name, ios::in);                         //open file if already exist in folder
        File f(fileName);

        if(file1->is_open()){                                   // file already exists
            if( f.getSize()+1 < n ) throw File::FileDonstExist(fileName);
        }
        if( f.getSize()+1 < n ) throw File::FileDonstExist(fileName);
        if(index<0) throw File::FileDonstExist(fileName);
        temp= array.data() + index;
        file = *temp;
        file[n]=c;
        file.getFile()->close();
        array.erase(array.begin()+index);
        touch(fileName);
        delete []name;
    }
    catch(File::FileDonstExist& e){
        e.printError();
    }
}

vector<File> DataStructFile::getArray()const{
    return array;
}

void DataStructFile::setArray(vector<File>& other){
    array=other;
}

int DataStructFile::findFile(string fileName)const{ //if not found in array return -1 index
    int size = (int)array.size();

    for(int i=0; i<size; i++){
        if(array[i].getName()==fileName) return i;
    }
    return -1;
}

void DataStructFile::cat(string fileName)const{
    try{
        int len = fileName.length();
        char *name = new char[len+1];
        strcpy(name, fileName.c_str());
        int index = findFile(fileName);
        fstream *file = new fstream();
        file->open(name, ios::in);                         //open file if already exist in folder
        if(file->is_open()){                                   // file already exists
            File f(fileName);
            if(f.getSize()==0) return;                         //if file in size of 0 return
        }
        delete []name;
        if(index<0) throw File::FileDonstExist(fileName);
        array[index].cat();
    }
    catch(File::FileDonstExist& e){
        e.printError();
    }
}


DataStructFile::~DataStructFile() {   
}
