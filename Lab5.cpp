#include <iostream>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <cstdio>

using namespace std;

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

pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

//vector for holding all the structs of each process
vector<process> processes;
vector<process> p0;
vector<process> p1;
vector<process> p2;
vector<process> p3;

int fileSize = 0;

//read in the processes from the binary file name
void readProcessesFromFile(const char *fileName){

    //variables for reading the file
    ifstream in;
    int totalMem = 0, numOfFiles = 0, x=0,  j;

    FILE* file = fopen(fileName, "rb");

    //get the length of the file  found at https://cplusplus.com/reference/cstdio/ftell/
    fseek(file, 0, SEEK_END);
    fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fileSize /= 63;


    while(x < fileSize){
        process proc = {};
        fread(reinterpret_cast<char*>(&proc.name), sizeof(proc.name), 1, file);
        fread(reinterpret_cast<char*>(&proc.id), sizeof(proc.id), 1, file);
        fread(reinterpret_cast<char*>(&proc.status), sizeof(proc.status), 1, file);
        fread(reinterpret_cast<char*>(&proc.cpuTime), sizeof(proc.cpuTime), 1, file);
        fread(reinterpret_cast<char*>(&proc.base), sizeof(proc.base), 1, file);
        fread(reinterpret_cast<char*>(&proc.limit), sizeof(proc.limit), 1, file);
        fread(reinterpret_cast<char*>(&proc.type), sizeof(proc.type), 1, file);
        fread(reinterpret_cast<char*>(&proc.numFiles), sizeof(proc.numFiles), 1, file);
        fread(reinterpret_cast<char*>(&proc.priority), sizeof(proc.priority), 1, file);
        fread(reinterpret_cast<char*>(&proc.checkSum), sizeof(proc.checkSum), 1, file);
        processes.push_back(proc);

        //calculate the memory and the number of files
        totalMem += (proc.limit - proc.base);
        numOfFiles += proc.numFiles;
        x++;
    }
    fclose(file);
    cout << "\nThe number of processes available in the file: " << fileSize << endl;
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
    int end = p3.size();
    end--;
    for (int i = 0; i <= end; ++i) {
        cout << "\nProcess["<<i<<"] Name: " << p3[i].name <<endl;
        cout << "Process ID: " << p3[i].id << endl;
        cout << "Activity Status: " << static_cast<int>(p3[i].status) << endl;
        cout << "CPU Burst Time: " << p3[i].cpuTime << endl;
        cout << "Base Register: " << p3[i].base << endl;
        cout << "Limit Register: " << p3[i].limit << endl;
        cout << "Process type: " << static_cast<int>(p3[i].type) << endl;
        cout << "Number of files: " << p3[i].numFiles << endl;
        cout << "Priority: " << static_cast<int>(p3[i].priority) << endl;
        cout << "Check sum: " << p3[i].checkSum << endl << endl;
    }
}

//find the processor with the most processes
//then distribute it the empty vector
void loadBalancing(int empty){

    //finds the processor with the most processes left
    int proc1 = p0.size() - 1;
    int proc2 = p1.size() - 1;
    int proc3 = p2.size() - 1;
    int proc4 = p3.size() - 1;
    int largest = max({proc1, proc2, proc3, proc4});
    int half = largest/2;
    if(half <= 7){ return;}

    //determines which processor has the most
    cout << "\nTRANSFERRING\n\n";
    if(largest == proc1){

        //splits the proccessor amount in half then adds it to the one that is empty

        for (int i = p0.size()-1; i >= half; --i) {
            process temp = p0[i];
            if(empty == 1){ p1.push_back(temp);}
            if(empty == 2){ p2.push_back(temp);}
            if(empty == 3){ p3.push_back(temp);}
            p0.pop_back();
        }
    }else if(largest == proc2){

        //splits the processor amount in half then adds it to the one that is empty

        int half = largest/2;
        if(half <= 5){ return;}
        for (int i = p1.size()-1; i >= half; --i) {
            process temp = p1[i];
            if(empty == 0){ p0.push_back(temp);}
            if(empty == 2){ p2.push_back(temp);}
            if(empty == 3){ p3.push_back(temp);}
            p1.pop_back();
        }
    }else if(largest == proc3){

        //splits the processor amount in half then adds it to the one that is empty
        int half = largest/2;
        if(half <= 5){return;}
        for (int i = p2.size()-1; i >= half; ++i) {
            process temp = p2[i];
            cout << "half: " << half << endl;
            if(empty == 0){ p0.push_back(temp);}
            if(empty == 1){ p1.push_back(temp);}
            if(empty == 3){ p3.push_back(temp);}
            p2.pop_back();
        }

    }else if (largest == proc4){

        //splits the processor amount in half then adds it to the one that is empty
        int half = largest/2;
        if(half <= 5){return;}
        for (int i = p3.size()-1; i >= half; ++i) {
            process temp = p3[i];
            if(empty == 0){ p0.push_back(temp);}
            if(empty == 2){ p2.push_back(temp);}
            if(empty == 1){ p1.push_back(temp);}
            p3.pop_back();
        }
    }
}

//print all the processes
void printProcesses(){
    for (int i = 0; i < fileSize; ++i) {
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

void priOrder(int end){
    //order them in terms of priority
    for (int i = 0; i < end; ++i) {
        for (int j = i+1; j < end+1; ++j) {
            if(p3[i].priority > p3[j].priority){
                swap(p3[i], p3[j]);
            }
        }
    }
}

//priority scheduling thread function
void * priority(void * arg){

    //start variables
    int start = (int)(long)arg;
    int end =  p3.size() - 1;

    //order them in terms of priority
    priOrder(end);

    while(true) {

        //check if the vector is empty and then get more

        if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){break;}
        if(p3.empty()){pthread_mutex_lock(&myMutex); loadBalancing(3); pthread_mutex_unlock(&myMutex);
            priOrder(end);}
        if(p3.size() < 1){ while(1){if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){return (void*)0;}}}

        //subtract cpu time  until below 1 then remove it and announce it
        int time = p3[0].cpuTime;
        while(time > 1){
            time -= 2;
            usleep(20000);
        }

        cout << "Priority: " <<  p3[0].name << " has finished!\nMoving on to the next Process!\n\n";
        p3.erase(p3.begin());
    }
    return (void*)0;
}

void shortOrder(int end){
    //order the processes with the least amount of cpu time to the most
    for (int i = 0; i < end; ++i) {
        for (int j = i+1; j < end+1; ++j) {
            if(p2[i].cpuTime > p2[j].cpuTime){
                swap(p2[i], p2[j]);
            }
        }
    }
}
//shortest job scheduling thread function
void * shortestJob(void * arg){

    //start variables
    int start = (int)(long)arg;
    int end = p2.size() - 1;

    //order the processes with the least amount of cpu time to the most
    shortOrder(end);


    while(true) {

        //check if the vector if empty and call load balancing to get more
        if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){break;}
        if(p2.empty()){pthread_mutex_lock(&myMutex); loadBalancing(2); pthread_mutex_unlock(&myMutex);
            shortOrder(end);}
        if(p2.size() < 1){ while(1){if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){return (void*)0;}}}


        //subtract time one at a time until its below 1 then remove it and announce it
        int time = p2[0].cpuTime;
        while(time > 1){
            time -= 2;
            usleep(20000);
        }
        cout << "SJF: " <<  p2[0].name << " has finished!\nMoving on to the next Process!\n\n";
        p2.erase(p2.begin());
    }
    return (void*)0;
}

//round-robin scheduling thread function
void * roundRobin(void * arg){

    //start variables
    int start = (int)(long)arg;
    int end = p1.size() -1, i = 0;

    while (true) {

        //check if the vector is empty and call load balancing to get more processes

        if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){break;}
        if(p1.empty()){pthread_mutex_lock(&myMutex); loadBalancing(1); pthread_mutex_unlock(&myMutex);}
        if(p1.size() < 1){ while(1){if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){return (void*)0;}}}

        //if all the processes have been completed exit.

        //cout << "p1 size: " << p1.size()   << " p0 size: " << p0.size() << endl;
        //subtract the cpu time from each  and if one gets below 1 then remove it and announce it
        p1[i].cpuTime -= 2;
        if(p1[i].cpuTime < 1){
            cout << "RR: " <<  p1[i].name << " has finished!\nMoving on to the next Process!\n\n";
            p1.erase(p1.begin() + i);
            end--;
            if(end == 0){i = 0;}
        }

        usleep(20000);
        if(i == end || i > end){i = 0; continue;}
        i++;
    }
    return (void*)0;
}

//FCFS thread algorithm
void * firstComeFirstServe(void * arg){
    //starting variables
    int end = p0.size()-1;
    int i = 0;

    //while loop to simulate running the processes
    while (true) {

        //checks if the queue is empty and if so it will then load balance
        //to get more process to run

        if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){break;}
        if(p0.empty()){pthread_mutex_lock(&myMutex); loadBalancing(0); pthread_mutex_unlock(&myMutex);}
        if(p0.size() < 1){ while(1){if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){return (void*)0;}}}

        //if there are no more processes then break

        //cout << "p0 size: " << p0.size() << endl;
        //get the cpu time and inside a loop bring it down to 0
        int time = p0[i].cpuTime;
        while(time > 0){
            time -= 2;
            usleep(20000);
        }

        //print what process has finished and erase it from the vector
        cout << "FCFS: " <<  p0[0].name << " has finished!\nMoving on to the next Process!\n\n";
        p0.erase(p0.begin());

        if(end == 0){i = 0;}
        if(i == end){i = 0; continue;}
        i++;
    }
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

    //start varibles
    int sched;
    float perc;
    float max = 1.0;
    float total = 0;
    int x, temp, start, k = 0;
    pthread_t myThreads[10];

    //finds what is missing from the command line arguments
    printWhatsMissing(argc, argv);


    for (int i = 2, j = i + 1; i < argc; i += 2, j += 2, k++) {

        //get the start position
        if(i == 2){start = 0;}
        else{start = temp;}

        //try and get the int and double from the user
        try {
            sched = stoi(argv[i]);
            perc = stof(argv[j]);
        }catch(exception &err){
            cout << "\nInputted scheduling algorithm or percentage of pcb file is incorrect! \n";
            cout << "Should look something like this: ./lab5 PCB.bin 1 0.4 2 0.5 3 0.1\n\n";
            exit(0);
        }

        //calculate the amount of processes from the percentage and total amount of processes
        x = perc * fileSize;
        x--;
        if(i != 2){x += temp;}

        //depending on the sceduling algorithm chosen by user
        //it will then add the correct processes to the correct vector then create the thread for that algorithm
        if(sched == 0){

            for (int l = start; l <= x; ++l) {
                p0.push_back(processes[l]);
            }
            pthread_create(&myThreads[k], 0, firstComeFirstServe, (void *)(long)start);
            if(perc == 1){
                while (1){
                    if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){break;}
                }
            }
        }else if (sched == 1){

            for (int l = start; l <= x; ++l) {
                p1.push_back(processes[l]);
            }

            pthread_create(&myThreads[k], 0, roundRobin, (void *)(long)start);
            if(perc == 1){
                while (1){
                    if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){break;}
                }
            }
        }else if (sched == 2){

            for (int l = start; l <= x; ++l) {
                p2.push_back(processes[l]);
            }

            pthread_create(&myThreads[k], 0, shortestJob, (void *)(long)start);
            if(perc == 1){
                while (1){
                    if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){break;}
                }
            }
        }else if (sched == 3){

            for (int l = start; l <= x; ++l) {
                p3.push_back(processes[l]);
            }

            pthread_create(&myThreads[k], 0, priority, (void *)(long)start);
            if(perc == 1){
                while (1){
                    if(p0.empty() && p1.empty() && p2.empty() && p3.empty()){break;}
                }
            }
        }
        temp = ++x;
    }

    //join all the threads at the end
    for (int i = 1; i < k; i++){
        pthread_join(myThreads[i], NULL);
    }
}
int main(int argc, char *argv[]){
    getProcessors(argc, argv);
    cout << "\nAll the processes are done!\n\n";
    return 0;
}

