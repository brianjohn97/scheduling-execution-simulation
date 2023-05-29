#include <iostream>
#include <fstream>

using namespace std;

pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

struct processes {
    char name[32];
    int id;
    char status;
    int cpuTime;
    int base;
    long long limit;
    char type;
    int numFiles;
    char priority;
    int checkSum;
};
void readProcessesFromFile(string fileName){

    processes p;
    ifstream binaryFile;
    int size =0;
    int totalMem = 0;

    //open the binary file
    binaryFile.open(fileName, ::ifstream::binary);


    //get the length of the file  found at https://cplusplus.com/reference/istream/istream/tellg/
    binaryFile.seekg(0, binaryFile.end);
    size = binaryFile.tellg();
    binaryFile.seekg(0, binaryFile.beg);

    cout << "Number of processes in the binary file is: " << size << endl;

    //read the process information from the binary file
    int i=0;
    while (binaryFile.tellg() < size){
        binaryFile.read(reinterpret_cast<char*>(&p.name), sizeof(p.name));
        binaryFile.read(reinterpret_cast<char*>(&p.id), sizeof(p.id));
        binaryFile.read(reinterpret_cast<char*>(&p.status), sizeof(p.status));
        binaryFile.read(reinterpret_cast<char*>(&p.cpuTime), sizeof(p.cpuTime));
        binaryFile.read(reinterpret_cast<char*>(&p.base), sizeof(p.base));
        binaryFile.read(reinterpret_cast<char*>(&p.limit), sizeof(p.limit));
        binaryFile.read(reinterpret_cast<char*>(&p.type), sizeof(p.type));
        binaryFile.read(reinterpret_cast<char*>(&p.numFiles), sizeof(p.numFiles));
        binaryFile.read(reinterpret_cast<char*>(&p.priority), sizeof(p.priority));
        binaryFile.read(reinterpret_cast<char*>(&p.checkSum), sizeof(p.checkSum));

        totalMem += (p.limit - p.base);

        cout << "Process["<<i<<"] Name: " << p.name <<endl;
        cout << "Process ID: " << p.id << endl;
        cout << "Activity Status: " << static_cast<int>(p.status) << endl;
        cout << "CPU Burst TIme: " << p.cpuTime << endl;
        cout << "Base Register: " << p.base << endl;
        cout << "Limit Register: " << p.limit << endl;
        cout << "Process type: " << static_cast<int>(p.type) << endl;
        cout << "Number of files: " << p.numFiles << endl;
        cout << "Priority: " << static_cast<int>(p.priority) << endl;
        cout << "Check sum: " << p.checkSum << endl;
        cout << endl;
        i++;

    }
    cout << "Total memory allocated by the processors is: " << totalMem << endl;
    binaryFile.close();
}

void * player(void * arg){


    return (void*)0;
}

void printWhatsMissing(int argc){
    if(argc == 1){
        cout << "\nYou need to provide: "
                "\nThe binary file."
                "\nThe scheduling algorithm."
                "\nAnd the percentage of processes that the algorithm is gonna run.\n\n";
        exit(0);
    }
    if(argc == 2){
        cout << "\nYou need to provide: "
                "\nThe scheduling algorithm."
                "\nAnd the percentage of processes that the algorithm is gonna run.\n\n";
        exit(0);
    }
    if(argc == 3){
        cout << "\nYou need to provide: "
                "\nThe percentage of processes that the algorithm is gonna run.\n\n";
        exit(0);
    }
    if(argc > 3 && argc%2 != 0){
        cout << "\nThere is an uneven amount of scheduling algorithms and percentage!"
                "\nPlease try again!\n\n";
        exit(0);
    }
}

void getProcessors(int argc, char **argv){
    printWhatsMissing(argc);

}
int main(int argc, char *argv[]){
    //readProcessesFromFile("b.bin");

    getProcessors(argc, argv);


    return 0;
}
