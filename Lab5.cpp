#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <unistd.h>

using namespace std;

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



pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

//struct for holding all the information about each process


//vector for holding all the structs of each process
vector<process> processes;
vector<process> p0;
vector<process> p1;
vector<process> p2;
vector<process> p3;

vector<int> pos;

int totalProc = 0;

//read in the processes from the binary file name
void readProcessesFromFile(string fileName){

    //variables for reading the file
    ifstream in;
    int size =0, totalMem = 0, numOfFiles = 0, j;

    //open the binary file
    in.open(fileName, ::ifstream::binary);

    //get the length of the file  found at https://cplusplus.com/reference/istream/istream/tellg/
    in.seekg(0, in.end);
    size = in.tellg();
    in.seekg(0, in.beg);

    //read the process information from the binary file
    while (!in.eof()){

        //create struct for holding the data
        process proc = {};
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
        if (totalProc > 0) {
            j = totalProc - 1;
            if(processes[j].id == proc.id){
                break;}
        }

        //calculate the memory and the number of files
        totalMem += (proc.limit - proc.base);
        numOfFiles += proc.numFiles;

        //add the struct to a vector and increase x
        processes.push_back(proc);
        totalProc++;
    }
    totalProc--;
    in.close();

    cout << "\nThe number of processes available in the file: " << totalProc << endl;
    cout << "Total number of memory allocated by the processes is: " << totalMem << endl;
    cout << "Overall total number of open files: " <<numOfFiles << endl << endl;

}

//print the process information based on given start and end points
void print0(){
    int end = p0.size();
    end--;
    for (int i = 0; i <= end; ++i) {
        cout << "\nProcess["<<i<<"] Name: " << p0[i].name <<endl;
        cout << "Process ID: " << p0[i].id << endl;
        cout << "Activity Status: " << static_cast<int>(p0[i].status) << endl;
        cout << "CPU Burst Time: " << p0[i].cpuTime << endl;
        cout << "Base Register: " << p0[i].base << endl;
        cout << "Limit Register: " << p0[i].limit << endl;
        cout << "Process type: " << static_cast<int>(p0[i].type) << endl;
        cout << "Number of files: " << p0[i].numFiles << endl;
        cout << "Priority: " << static_cast<int>(p0[i].priority) << endl;
        cout << "Check sum: " << p0[i].checkSum << endl << endl;
    }
}
void print1(){
    int end = p1.size();
    end--;
    for (int i = 0; i <= end; ++i) {
        cout << "\nProcess["<<i<<"] Name: " << p1[i].name <<endl;
        cout << "Process ID: " << p1[i].id << endl;
        cout << "Activity Status: " << static_cast<int>(p1[i].status) << endl;
        cout << "CPU Burst Time: " << p1[i].cpuTime << endl;
        cout << "Base Register: " << p1[i].base << endl;
        cout << "Limit Register: " << p1[i].limit << endl;
        cout << "Process type: " << static_cast<int>(p1[i].type) << endl;
        cout << "Number of files: " << p1[i].numFiles << endl;
        cout << "Priority: " << static_cast<int>(p1[i].priority) << endl;
        cout << "Check sum: " << p1[i].checkSum << endl << endl;
    }
}
void print2(){
    int end = p2.size();
    end--;
    for (int i = 0; i <= end; ++i) {
        cout << "\nProcess["<<i<<"] Name: " << p2[i].name <<endl;
        cout << "Process ID: " << p2[i].id << endl;
        cout << "Activity Status: " << static_cast<int>(p2[i].status) << endl;
        cout << "CPU Burst Time: " << p2[i].cpuTime << endl;
        cout << "Base Register: " << p2[i].base << endl;
        cout << "Limit Register: " << p2[i].limit << endl;
        cout << "Process type: " << static_cast<int>(p2[i].type) << endl;
        cout << "Number of files: " << p2[i].numFiles << endl;
        cout << "Priority: " << static_cast<int>(p2[i].priority) << endl;
        cout << "Check sum: " << p2[i].checkSum << endl << endl;
    }
}
void print3(){
    int end = p0.size();
    end--;
    for (int i = 0; i <= end; ++i) {
        cout << "\nProcess["<<i<<"] Name: " << p0[i].name <<endl;
        cout << "Process ID: " << p0[i].id << endl;
        cout << "Activity Status: " << static_cast<int>(p0[i].status) << endl;
        cout << "CPU Burst Time: " << p0[i].cpuTime << endl;
        cout << "Base Register: " << p0[i].base << endl;
        cout << "Limit Register: " << p0[i].limit << endl;
        cout << "Process type: " << static_cast<int>(p0[i].type) << endl;
        cout << "Number of files: " << p0[i].numFiles << endl;
        cout << "Priority: " << static_cast<int>(p0[i].priority) << endl;
        cout << "Check sum: " << p0[i].checkSum << endl << endl;
    }
}

void printProcesses(){
    int size = processes.size();
    size -= 2;
    for (int i = 0; i <= size; ++i) {
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

void * priority(void * arg){
    int start = (int)(long)arg;
    int end;
    pthread_mutex_lock(&myMutex);
    for (int i = 0, j = i+1; i < pos.size(); ++i, ++j) {
        if(pos[i] == start){
            end = pos[j];
        }
    }
    //cout << "pos[i] : " << start << " pos[j] : " << end << endl;
    print3();

    pthread_mutex_unlock(&myMutex);

    return NULL;
}

void * shortestJob(void * arg){
    int start = (int)(long)arg;
    int end;
    pthread_mutex_lock(&myMutex);
    cout << "\nShortest Job!: " << start << endl;
//    for (int i = 0, j = i+1; i < pos.size(); ++i, ++j) {
//        if(pos[i] == start){
//            end = pos[j];
//        }
//    }
//    //cout << "pos[i] : " << start << " pos[j] : " << end << endl;
//    print2();
    pthread_mutex_unlock(&myMutex);
    return (void*)0;
}

void * roundRobin(void * arg){
    int start = (int)(long)arg;
    int end;
    pthread_mutex_lock(&myMutex);
    cout << "\nRound Robin!: " << start << endl;
    //print1();
    for (int i = 0; i <= (p1.size()-1); ++i) {
        p1[i].cpuTime -= 2;
        if(){
            p1.
            cout << p1[i].name << " has finished!\nMoving on to the next Process!\n\n";
        }
        usleep(20000);
    }
    cout << "First come first Serve has finished all of its processes!\n\n";
    pthread_mutex_unlock(&myMutex);
    return (void*)0;
}

void * firstComeFirstServe(void * arg){
    pthread_mutex_lock(&myMutex);
    cout << "\nFirst Come First Serve!" << endl;
   //print0();
    for (int i = 0; i <= (p0.size()-1); ++i) {
        int time = p0[i].cpuTime;
        while(time > 0){
            time -= 2;
            //cout << time << endl;
            usleep(20000);
        }
        cout << p0[i].name << " has finished!\nMoving on to the next Process!\n\n";
    }
    cout << "First come first Serve has finished all of its processes!\n\n";

    pthread_mutex_unlock(&myMutex);
    return (void*)0;
}

//prints the items that the user is missing from the command line arguments
void printWhatsMissing(int argc, char **argv){

    //check to see if they are missing everything
    if(argc == 1){
        cout << "\nYou need to provide: "
                "\nThe binary file."
                "\nThe scheduling algorithm."
                "\nAnd the percentage of processes that the algorithm is gonna run.\n\n";
        exit(0);
    }

    ////check to see if they are missing the algorithm and percentages
    if(argc == 2){
        cout << "\nYou need to provide: "
                "\nThe scheduling algorithm."
                "\nAnd the percentage of processes that the algorithm is gonna run.\n\n";
        exit(0);
    }

    //check to see if they are missing the percentage
    if(argc == 3){
        cout << "\nYou need to provide: "
                "\nThe percentage of processes that the algorithm is gonna run.\n\n";
        exit(0);
    }

    //check to see if they are an uneven amount of arguments
    //meaning there are some algorithm missing their percentages or vice versa
    if(argc > 3 && argc%2 != 0){
        cout << "\nThere is an uneven amount of scheduling algorithms and percentage!"
                "\nPlease try again!\n\n";
        exit(0);
    }

    //making sure that all the percentages add up to 100%
    float perc, total = 0;
    for(int i = 3, j = 2;i < argc; i += 2, j += 2){
        try {
            int algo = stoi(argv[j]);
            perc = stof(argv[i]);
            if(algo < 0 || algo > 3){
                cout << "\nThe inputted algorithm selection should be between 0 and 3.\n";
                cout << "Please try again with the correct algorithm choices.\n\n";
                exit(0);
            }
        }catch(exception &err){
            cout << "\nInputted percentages of pcb file are incorrect! \n";
            cout << "Should look something like this: ./lab5 PCB.bin 1 0.4 2 0.5 3 0.1\n\n";
            exit(0);
        }
        total += perc;
    }
    if(abs(total - 1.0) > 0.0001 ){
        cout << "\nYour percentages do not add up!\n\n";
        exit(0);
    }
    readProcessesFromFile(argv[1]);
}

//prints what's missing
//then it reads the binary file adding the processes to a struct and each struct to a vector
//then starts a thread
void getProcessors(int argc, char **argv){

    int sched;
    float perc;
    float max = 1.0;
    float total = 0;
    int x, temp, start;
    pthread_t myThreads[10];
    printWhatsMissing(argc, argv);


    int k=0;
    for (int i = 2, j = i + 1; i < argc; i += 2, j += 2, k++) {
        if(i == 2){start = 0;}
        else{start = temp;}
        try {
            sched = stoi(argv[i]);
            perc = stof(argv[j]);
        }catch(exception &err){
            cout << "\nInputted scheduling algorithm or percentage of pcb file is incorrect! \n";
            cout << "Should look something like this: ./lab5 PCB.bin 1 0.4 2 0.5 3 0.1\n\n";
            exit(0);
        }

        x = perc * totalProc;
        x--;
        if(i != 2){x += temp;}
        //cout <<  "x: " << x << " temp: " << temp << endl;

        if(sched == 0){
            //cout << "start: " << start << " x: " << x << endl;
            for (int l = start; l <= x; ++l) {
                p0.push_back(processes[l]);
            }
            pthread_create(&myThreads[k], 0, firstComeFirstServe, (void *)(long)start);
        }else if (sched == 1){
            //cout << "start: " << start << " x: " << x << endl;
            for (int l = start; l <= x; ++l) {
                p1.push_back(processes[l]);
            }
            pthread_create(&myThreads[k], 0, roundRobin, (void *)(long)start);
        }else if (sched == 2){
            //cout << "start: " << start << " x: " << x << endl;
            for (int l = start; l <= x; ++l) {
                p2.push_back(processes[l]);
            }
            pthread_create(&myThreads[k], 0, shortestJob, (void *)(long)start);
        }else if (sched == 3){
            //cout << "start: " << start << " x: " << x << endl;
            for (int l = start; l <= x; ++l) {
                p3.push_back(processes[l]);
            }
            pthread_create(&myThreads[k], 0, priority, (void *)(long)start);
        }

        if(i == 2){pos.push_back(0); pos.push_back(x);temp = ++x; continue;}
        pos.push_back(temp); pos.push_back(x);
        temp = ++x;
    }

    for (int i = 1; i < k; i++){
        pthread_join(myThreads[i], NULL);
    }
}
int main(int argc, char *argv[]){
    getProcessors(argc, argv);
//    for (int i = 0; i < pos.size(); ++i) {
//        cout << pos[i] << endl;
//    }

    return 0;
}

