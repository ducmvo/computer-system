// AUTHOR: Duc Vo
// FILE: hw5.cpp
// DATE: 03/13/2022
// PURPOSE: This program allows simulate various CPU scheduling algorithms. 
// INPUT:   Prompts from user.
// PROCESS: the program prompts user for input file and scheduling type,
//          then read the process info form the file and run a simulation using
//          the provided scheduling algorithm then print the stats to screen
// OUTPUT:  Prints sorted CPU scheduling statistics

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <limits.h>
using namespace std;

struct Process
{
    unsigned id; // process id
    unsigned at; // process arrival time
    unsigned bt; // process burst time
    unsigned pr; // process priority
    unsigned tt = 0; // process termination time
    unsigned tat = 0; // process turn around Time
    unsigned wt = 0; //process wait time
};

// Shortest Job First Scheduling
void SJF(vector<Process> procs);

// Shortest Remaining Time First Scheduling
void SRTF(vector<Process> procs);

// Non-preemptive Priority Scheduling
void NP(vector<Process> procs);

// Preemptive Priority Scheduling
void PP(vector<Process> procs);

// Show user input command line usage
void show_usage(string name);

// Get the result statistics after run the simulation
void getStats(vector<Process> &procs);

// Print out all the processes info
void print(vector<Process> processes);

// Read processes from input file
void getProcesses(vector<Process> &processes, string fileName);

// Get the corresponding process type number
int getScheduleType(string scheduling);

// Run the processing simulation base on the input type
void runProcesses(vector<Process> processes, int scheduling);

int main(int argc, char *argv[])
{
    // Command line interface
    // if (argc < 2)
    // {
    //     show_usage(argv[0]);
    //     return -1;
    // }
    // string fileName = argv[1];
    // string schedule = argv[2];

    // vector<Process> processes;
    // int type = getScheduleType(schedule);
    // getProcesses(processes, fileName);
    // runProcesses(processes, type);

    
        // Below will run test on all scheduling algorithms
        string fileName = "input.txt";
        string scheduling = "SJF";

        int type;

        // GET PROCCESSES FROM FILE
        vector<Process> processes;
        getProcesses(processes, fileName);

        type = getScheduleType("SJF");
        runProcesses(processes, type);

        type = getScheduleType("SRTF");
        runProcesses(processes, type);

        type = getScheduleType("NP");
        runProcesses(processes, type);

        type = getScheduleType("PP");
        runProcesses(processes, type);
    
    return 0;
}

void runProcesses(vector<Process> processes, int scheduling)
{
    switch (scheduling)
    {
    case 0:
        return SJF(processes);
    case 1:
        return SRTF(processes);
    case 2:
        return NP(processes);
    case 3:
        return PP(processes);
    default:
        return;
    }
}

int getScheduleType(string type)
{
    string types[] = {"SJF", "SRTF", "NP", "PP"};
    bool isValid = false;
    for (string t : types)
        if (type == t)
            isValid = true;
    if (!isValid)
        throw invalid_argument("Invalid scheduler type");

    if (type == "SJF")
        return 0;
    if (type == "SRTF")
        return 1;
    if (type == "NP")
        return 2;
    if (type == "PP")
        return 3;
    return -1;
}

void getProcesses(vector<Process> &processes, string fileName)
{
    // CHECK INPUT FILE
    ifstream file(fileName);
    if (!file.is_open())
        throw invalid_argument("Ivalid input file");

    string line;
    stringstream ss;
    int num;
    while (getline(file, line))
    {
        Process p;
        ss.clear();
        ss.str(line);
        ss >> p.id;
        ss >> p.at;
        ss >> p.bt;
        ss >> p.pr;
        processes.push_back(p);
    }
    file.close();
}

void getStats(vector<Process> &procs)
{
    double cpu_utilization;
    double avg_wait_time;
    unsigned worst_wait_time = 0;

    unsigned total_time = 0;
    for (unsigned i = 0; i < procs.size(); i++)
    {
        avg_wait_time += procs[i].wt;
        cpu_utilization += procs[i].bt;
        worst_wait_time = max(worst_wait_time, procs[i].wt);
        total_time = max(total_time, procs[i].tt);
    }

    avg_wait_time /= procs.size();
    cpu_utilization /= total_time;
    cout << endl;
    cout << "CPU Utilization: " << setprecision(0) << fixed << (cpu_utilization * 100) << "%" << endl;
    cout << "Average waiting time: " << setprecision(2) << fixed << avg_wait_time << endl;
    cout << "Worst-case waiting time: " << worst_wait_time << endl;
    cout << endl;
}

void print(vector<Process> processes)
{
    // PRINT PROCESSES
    cout << "PID\tAT\tBT\tTT\tTAT\tWT\tPriority\n";
    for (auto p : processes)
    {
        cout << p.id << "\t";
        cout << p.at << "\t";
        cout << p.bt << "\t";
        cout << p.tt << "\t";
        cout << p.tat << "\t";
        cout << p.wt << "\t";
        cout << p.pr << "\n";
    }
}

void show_usage(string name)
{
    cout << "\nUsage: " << name << " <input-file> <scheduling-type>\n"
         << "\tSJF\tShortest Job First \n"
         << "\tSRTF\tShortest Remaining Time First\n"
         << "\tNP\tNonpreemptive Priority\n"
         << "\tPP\tPreemptive Priority\n"
         << std::endl;
}

void SJF(vector<Process> procs)
{
    cout << "\n==== SHORTEST JOB FIRST ====" << endl;
    vector<Process> completed_procs;
    unsigned time = 0;
    while (procs.size() != 0)
    {
        int idx = -1;
        unsigned minBT = UINT_MAX;
        unsigned minAT = UINT_MAX;
        for (int i = 0; i < procs.size(); i++)
        {
            if (procs[i].at <= time && procs[i].bt < minBT)
            {
                minBT = procs[i].bt;
                idx = i;
            }

            if (procs[i].at < minAT)
            {
                minAT = procs[i].at;
            }
        }

        cout << "Time " << time;
        if (idx != -1)
        {
            Process p = procs[idx];
            procs.erase(procs.begin() + idx);
            cout << " Process " << p.id << endl;

            p.tt = time + p.bt;
            p.tat = p.tt - p.at;
            p.wt = p.tat - p.bt;

            time = p.tt;
            completed_procs.push_back(p);
        }
        else
        {
            time = minAT;
            cout << " Idle" << endl;
        };
    }

    getStats(completed_procs);
    print(completed_procs);
}

void SRTF(vector<Process> procs)
{
    cout << "\n==== SHORTEST REMAINING TIME FIRST ====" << endl;
    vector<Process> original_procs = procs;
    vector<Process> completed_procs;
    unsigned time = 0;
    while (procs.size() != 0)
    {
        int idx = -1;
        unsigned minBT = UINT_MAX;
        unsigned minAT = UINT_MAX;
        for (int i = 0; i < procs.size(); i++)
        {
            if (procs[i].at <= time && procs[i].bt < minBT)
            {
                minBT = procs[i].bt;
                idx = i;
            }
            if (procs[i].at < minAT)
                minAT = procs[i].at;
        }

        cout << "Time " << time;

        if (idx != -1)
        {
            Process p = procs[idx];
            procs.erase(procs.begin() + idx);
            cout << " Process " << p.id << endl;

            unsigned minBT_rest = UINT_MAX;
            int next_idx = -1;
            for (int i = 0; i < procs.size(); i++)
            {
                if (procs[i].at <= time + p.bt && procs[i].bt < minBT_rest)
                {
                    minBT_rest = procs[i].bt;
                    if (procs[i].at > time)
                        next_idx = i;
                }
            }

            if (next_idx != -1)
            {
                Process next_proc = procs[next_idx];
                p.bt = p.bt - (next_proc.at - time);
                time = next_proc.at;
                procs.push_back(p);
            }
            else
            {
                time += p.bt;
                p.bt = 0;

                p.tt = time;
                p.tat = p.tt - p.at;
                for (auto op : original_procs)
                {
                    if (op.id == p.id)
                        p.bt = op.bt;
                }
                p.wt = p.tat - p.bt;
                completed_procs.push_back(p);
            }
        }
        else
        {
            time = minAT;
            cout << " Idle" << endl;
        };
    }

    getStats(completed_procs);
    print(completed_procs);
}

void NP(vector<Process> procs)
{
    cout << "\n==== NONPREEMPTIVE PRIORITY ====" << endl;
    vector<Process> completed_procs;
    unsigned time = 0;
    while (procs.size() != 0)
    {
        int idx = -1;
        unsigned highestPriority = UINT_MAX;
        unsigned minAT = UINT_MAX;
        for (int i = 0; i < procs.size(); i++)
        {
            if (procs[i].at <= time && procs[i].pr < highestPriority)
            {
                highestPriority = procs[i].pr;
                idx = i;
            }

            if (procs[i].at < minAT)
            {
                minAT = procs[i].at;
            }
        }

        cout << "Time " << time;
        if (idx != -1)
        {
            Process p = procs[idx];
            procs.erase(procs.begin() + idx);
            cout << " Process " << p.id << endl;

            p.tt = time + p.bt;
            p.tat = p.tt - p.at;
            p.wt = p.tat - p.bt;

            time = p.tt;
            completed_procs.push_back(p);
        }
        else
        {
            time = minAT;
            cout << " Idle" << endl;
        };
    }

    getStats(completed_procs);
    print(completed_procs);
}

void PP(vector<Process> procs)
{
    cout << "\n==== PREEMPTIVE PRIORITY ====" << endl;
    vector<Process> original_procs = procs;
    vector<Process> completed_procs;
    unsigned time = 0;
    while (procs.size() != 0)
    {
        int idx = -1;
        unsigned highestPriority = UINT_MAX;
        unsigned minAT = UINT_MAX;
        for (int i = 0; i < procs.size(); i++)
        {
            if (procs[i].at <= time && procs[i].pr < highestPriority)
            {
                highestPriority = procs[i].pr;
                idx = i;
            }

            if (procs[i].at < minAT)
                minAT = procs[i].at;
        }

        cout << "Time " << time;

        if (idx != -1)
        {
            Process p = procs[idx];
            cout << " Process " << procs[idx].id << endl;
            procs.erase(procs.begin() + idx);

            // Find first proc arrived within the current burst time has higher priority
            int next_idx = -1;
            for (int i = 0; i < procs.size(); i++)
            {
                if (procs[i].at < time + p.bt && procs[i].pr < p.pr && next_idx == -1)
                    next_idx = i;
            }

            if (next_idx != -1)
            {
                Process next_proc = procs[next_idx];
                p.bt = p.bt - (next_proc.at - time);
                time = next_proc.at;
                procs.push_back(p);
            }
            else
            {
                time += p.bt;
                p.bt = 0;

                p.tt = time;
                p.tat = p.tt - p.at;
                for (auto op : original_procs)
                    if (op.id == p.id)
                        p.bt = op.bt;

                p.wt = p.tat - p.bt;

                completed_procs.push_back(p);
            }
        }
        else
        {
            cout << " Idle" << endl;
            time = minAT;
        }
    }

    getStats(completed_procs);
    print(completed_procs);
}
