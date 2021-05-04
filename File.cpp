#include "File.h"

File::File(): value(new FileValue()){}

File::File(string &fname){
    value = new FileValue(fname);
}


File::FileValue::FileValue()  : refCount(1),name(""),size(0){
    file = new fstream();
}

File::FileValue::~FileValue(){
    delete finame;
    delete file;
}

File::FileValue::FileValue(string& fname) :refCount(1),size(0) {
    file = new fstream();
    int len = fname.length();
    finame = new char[len+1];
    strcpy(finame, fname.c_str());     
    name=fname;
    file->open(finame, ios::in);                         //open file if already exist in folder
    if(!file->is_open()) file->open(finame, ios::out);   //is dosnt exist in folder open a new one
    file->open(finame,ios::out | ios::in );              //at last: open the file for writing and 
    if( !file->is_open() ) throw FileDonstExist(name);
}

/*using shallow copy*/
File::File(const File& f)
: value(f.value)
{
  ++value->refCount;
}

const File& File::operator=(const File& f){
    if(value==f.value) {
        return *this;
    }
    else if(--value->refCount == 0 ){
        delete value;
    }
    /*using shallow copy*/
    value = f.value;
    ++value->refCount;

    return *this;
}

FileCharProxy File::operator[](int n){
    if(n<0 || n>getSize()) throw FileDonstExist(value->name);
    else if(value->refCount > 1){
            --value->refCount;
            value = new File::FileValue(value->name.append("_copy"));
            return FileCharProxy(*value->file,n);
    }
    else{
        return FileCharProxy(*value->file,n);
    }
}

const char& File::operator[](int n) const {
    char *c = new char();
    if( n<0 || n>getSize() ) throw FileDonstExist(value->name);
    else{
        value->file->clear();
        value->file->seekg(n);
        *c=value->file->get();
        return *c;
    }
}

void File::cat() const {
    string str="";
    if(value->size==0) return;
    value->file->clear();
    value->file->seekp(ios::beg);
    int tempSize = value->size-1;
    char tempChar = value->file->get();
    
    while( value->file->good() && tempSize-- )
    {
        str+=tempChar;
        tempChar = value->file->get();
    }
    if(tempChar=='\n') cout<<str;
    else  cout<<str<<endl;
    return;
}



void File::updateTimeStamp(){
    value->file->open(value->finame,ios::out | ios::in );
    value->file->close();
    value->file->open(value->finame,ios::out | ios::in );
}

int File::setSize(){
    string str="";
    value->file->clear();
    value->file->seekg(ios::beg);
    char tempChar = value->file->get();
    if(!value->file->good()){
        value->size = 0;
        return 0;
    }
    str+=tempChar;
    while(value->file->good())
    {
        tempChar = value->file->get();
        str+=tempChar;
    }
    value->size=str.length();
    return str.length();
}

int File::getSize()const{
    return value->size;
}

string File::getName()const {
    return value->name;
}

void File::setName(string fname){
    value->name = fname;
}

fstream* File::getFile() const{
    return value->file;
}

void File::setFile(fstream &other){
    value->file=&other;
}

int File::getLineNum() const{
    string line;
    char c;
    int count=0;
    value->file->clear();
    value->file->seekp(ios::beg);
    while(!value->file->eof()){
        line = "";
        while(value->file->get(c)){
            line+= c;
            if(c=='\n') break;
        }
        count++;
    }
    return count;
}



File::~File() {
    if(--value->refCount == 0 ){
        delete value;
    }
}
