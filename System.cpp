#include "System.h"

System::System(): line(""){
    dsf = new DataStructFile();
    numWords=TEN;
}

System::System(string l): line(l){
    dsf = new DataStructFile();
    numWords=TEN;
    setStrWords();
}

System::System(const System& s) {
    numWords=TEN;
    line=s.getLine();
    *dsf=getDsf();
    setStrWords();
}

const System& System::operator=(const System& s) {
    if(this==&s) return *this;
    else{
        line=s.getLine();
        *dsf=getDsf();
        numWords=s.getNumWords();
        setStrWords();
    }
    return *this;
}

void System::setLine(string l) {
    line=l;
}

string System::getLine() const {
    return line;
}

DataStructFile& System::getDsf()const{
    return *dsf;
}

void System::setDsf(DataStructFile& f){
    dsf=&f;
}

void System::setStrWords() {
    int counter=0;
    int size=(int)line.length();
    for(int i=0; i<numWords; i++){
        strWords[i]="";
    }
    for(int i = 0; i<size; i++){
        if(line[i]=='\0' || line[i]=='\n')break;
        if(line[i] == ' '){
            if(i!=size-1) counter++;
        } 
        else  strWords[counter] += line[i];
    }
    setNumWords(counter+1);
}

void System::setNumWords(int n){
    numWords=n;
}

void System::callFunctions() {
    int number=0;
    string strNum;
    setStrWords();
    int size;
    try{
        if(strWords[0]=="read"){
            if(numWords!=3){
                 throw wrongUsage("read FILENAME POSITION");
            }
            strNum= strWords[2];
            size = (int)strNum.length();
            for(int i=0; i<size ; i++)
                if(!isdigit(strNum[i]))throw wrongUsage("read FILENAME POSITION");
            number=atoi(strWords[2].c_str());
            if(number<0)throw wrongUsage("read FILENAME POSITION");
            char c = dsf->read(strWords[1],number);
            if( c == '\0') return;
            cout<<c<<endl;
        }
        else if(strWords[0]=="touch"){
            if(numWords!=2) throw wrongUsage("touch FILENAME");
            checkFileName(strWords[1]);
            dsf->touch(strWords[1]);
        }
        else if(strWords[0]=="copy"){
            if(numWords!=3) throw wrongUsage("copy SOURCE_FILENAME TARGET_FILENAME");
            dsf->copy(strWords[1],strWords[2]);
        }
        else if(strWords[0]=="write"){
            if(numWords!=4) throw wrongUsage("write FILENAME POSITION CHARACTER");
            strNum= strWords[2];
            size = (int)strNum.length();
            for(int i=0; i<size; i++)
                if(!isdigit(strNum[i])) throw wrongUsage("write FILENAME POSITION CHARACTER");
            number=atoi(strWords[2].c_str());
            if(number<0) throw wrongUsage("write FILENAME POSITION CHARACTER");
            if(strWords[3].length()!=1) throw wrongUsage("write FILENAME POSITION CHARACTER");
            strNum=strWords[3];
            const char *c = new char[1];
            c = strNum.c_str();
            dsf->write(strWords[1],number,c[0]);
        }
        else if(strWords[0]=="remove"){
            if(numWords!=2) throw wrongUsage("remove FILENAME");
            dsf->remove(strWords[1]);
        }
        else if(strWords[0]=="move"){
            if(numWords!=3) throw wrongUsage("move SOURCE_FILENAME TARGET_FILENAME");
            dsf->move(strWords[1],strWords[2]);
        }
        else if(strWords[0]=="cat"){
            if(numWords!=2)throw wrongUsage("cat FILENAME");
            dsf->cat(strWords[1]);
        }
        else if(strWords[0]=="exit"){
            if(numWords!=1) throw wrongUsage("exit");
        }
        else throw UnknownCommand();
    }
    catch(File::FileDonstExist &e){
        e.printError();
    }
    catch(System::UnknownCommand &e){
        cout<<"error: command is not supported."<<'\n';
    }
    catch(System::wrongUsage &e){
        e.printError();
    }
}

int System::getNumWords() const{
    return numWords;
}

void System::checkFileName(string fileName){
    int numOfDots=0;
    int size=(int) fileName.length();
    for(int i=0; i<size ; i++)
    {
        char c = fileName[i];
        if( c == '.' ) numOfDots++;
        if( isalpha(c) > 0 && isdigit(c) > 0 ) throw File::FileDonstExist(fileName);
        if(numOfDots>1) throw File::FileDonstExist(fileName);        
    }
    if(numOfDots==0) throw File::FileDonstExist(fileName);
}

System::~System() {
    
}
