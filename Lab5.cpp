#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>

using namespace std;

pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

//struct for holding all the information about each process
struct process {
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

//vector for holding all the structs of each process
vector<process> processes;

//read in the processes from the binary file name
void readProcessesFromFile(string fileName){

    //variables for reading the file
    ifstream in;
    int size =0, totalMem = 0, numOfFiles = 0, x = 0, j;

    //open the binary file
    in.open(fileName, ::ifstream::binary);

    //get the length of the file  found at https://cplusplus.com/reference/istream/istream/tellg/
    in.seekg(0, in.end);
    size = in.tellg();
    in.seekg(0, in.beg);

    //read the process information from the binary file
    while (!in.eof()){

        //create struct for holding the data
        process proc;
        in.read(reinterpret_cast<char*>(&proc.name), sizeof(proc.name));
        in.read(reinterpret_cast<char*>(&proc.id), sizeof(proc.id));
        in.read(reinterpret_cast<char*>(&proc.status), sizeof(proc.status));
        in.read(reinterpret_cast<char*>(&proc.cpuTime), sizeof(proc.cpuTime));
        in.read(reinterpret_cast<char*>(&proc.base), sizeof(proc.base));
        in.read(reinterpret_cast<char*>(&proc.limit), sizeof(proc.limit));
        in.read(reinterpret_cast<char*>(&proc.type), sizeof(proc.type));
        in.read(reinterpret_cast<char*>(&proc.numFiles), sizeof(proc.numFiles));
        in.read(reinterpret_cast<char*>(&proc.priority), sizeof(proc.priority));
        in.read(reinterpret_cast<char*>(&proc.checkSum), sizeof(proc.checkSum));

        //make sure there are no duplicates
        if (x > 0) {
            j = x -1;
            if(processes[j].id == proc.id){
                break;}
        }

        //calculate the memory and the number of files
        totalMem += (proc.limit - proc.base);
        numOfFiles += proc.numFiles;

        //add the struct to a vector and increase x
        processes.push_back(proc);
        x++;
    }
    in.close();

    cout << "\nThe number of processes available in the file: " << x << endl;
    cout << "Total number of memory allocated by the processes is: " << totalMem << endl;
    cout << "Overall total number of open files: " <<numOfFiles << endl << endl;

}

void * priority(void * arg){


    return (void*)0;
}

void * shortestJob(void * arg){


    return (void*)0;
}

void * roundRobin(void * arg){


    return (void*)0;
}

void * firstComeFirstServe(void * arg){


    return (void*)0;
}

//prints the items that the user is missing from the command line arguments
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

//prints what's missing
//then it reads the binary file adding the processes to a struct and each struct to a vector
//then starts a thread
void getProcessors(int argc, char **argv){

    int sched;
    float perc;
    pthread_t myThreads[10];
    //printWhatsMissing(argc);
    //readProcessesFromFile(argv[1]);
    cout << endl;

    for (int i = 2, j = i + 1; i < argc; i += 2, j += 2) {
        try {
            sched = stoi(argv[i]);
            perc = stof(argv[j]);
        }catch(exception &err){
            cout << "\nInputted scheduling algorithm or percentage of pcb file is incorrect! \n";
            cout << "Should look like this: ./lab5 PCB.bin 1 0.4 2 0.5 3 0.1\n\n";
            exit(0);
        }

        
    }
}
int main(int argc, char *argv[]){
    getProcessors(argc, argv);
    return 0;
}
void junk(){
    for (int i = 0; i < processes.size(); ++i) {
        cout << "\nProcess["<<i<<"] Name: " << processes[i].name <<endl;
        cout << "Process ID: " << processes[i].id << endl;
        cout << "Activity Status: " << static_cast<int>(processes[i].status) << endl;
        cout << "CPU Burst Time: " << processes[i].cpuTime << endl;
        cout << "Base Register: " << processes[i].base << endl;
        cout << "Limit Register: " << processes[i].limit << endl;
        cout << "Process type: " << static_cast<int>(processes[i].type) << endl;
        cout << "Number of files: " << processes[i].numFiles << endl;
        cout << "Priority: " << static_cast<int>(processes[i].priority) << endl;
        cout << "Check sum: " << processes[i].checkSum << endl << endl;
    }
}
