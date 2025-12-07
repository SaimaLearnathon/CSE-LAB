**Submission Date:** November 23, 2025  
**Experiment No:** 04  
**Experiment Name:** Study of Priority Scheduling Algorithm. 

---

## **Theory**
<div align="justify">

### **Priority Scheduling Algorithm**

Priority Scheduling is a **CPU scheduling algorithm** where each process is assigned a **priority**. The CPU is allocated to the process with the **highest priority** (usually the lowest numerical value indicates the highest priority).

* **Types:**

  1. **Preemptive Priority Scheduling** – A running process can be preempted if a higher priority process arrives.
  2. **Non-Preemptive Priority Scheduling** – The currently running process continues until it finishes, even if a higher priority process arrives.

* **Key Terms:**

  * **Waiting Time** – Time a process spends waiting in the ready queue.
  * **Turnaround Time** – Total time taken from arrival to completion of a process.

Priority Scheduling is commonly used in **real-time systems**, where certain tasks must be executed before others.




## **Task 1**  

**Priority Scheduling Algorithm(non-preemptive).**

---
### **C++ Code**
```cpp

#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid;
    int burst;
    int priority;
    int waiting;
    int turnaround;
};

int main() {
    int n;
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cin >> p[i].burst >> p[i].priority;
    }

    sort(p.begin(), p.end(), [](Process a, Process b) {
        return a.priority < b.priority;
    });

    int totalWaiting = 0, totalTurnaround = 0;
    p[0].waiting = 0;
    p[0].turnaround = p[0].burst;
    totalTurnaround += p[0].turnaround;

    for (int i = 1; i < n; i++) {
        p[i].waiting = p[i-1].waiting + p[i-1].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
        totalWaiting += p[i].waiting;
        totalTurnaround += p[i].turnaround;
    }

    cout << "\nProcess\tBurst\tPriority\tWaiting\tTurnaround\n";
    for (auto &proc : p) {
        cout << "P" << proc.pid << "\t" << proc.burst << "\t"
             << proc.priority << "\t\t" << proc.waiting << "\t"
             << proc.turnaround << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (double)totalWaiting / n;
    cout << "\nAverage Turnaround Time: " << (double)totalTurnaround / n << endl;

    return 0;
}



```
## *Output :* 
<p align="center">
<img alt="2110047_lab1_task1" src="./images/priority.jpg">
</p>



## *Discussion :*
<div align="justify">
In this experiment, we studied the Priority Scheduling CPU scheduling algorithm, where each process is assigned a priority, and the CPU is allocated to the process with the highest priority first. We analyzed how this scheduling affects waiting time, turnaround time, and process execution order, considering both preemptive and non-preemptive scenarios. Through the experiment, we observed that higher-priority processes are executed earlier, reducing their waiting time, but lower-priority processes may experience longer delays. The results highlight the importance of priority assignment in managing CPU resources efficiently and demonstrate how priority scheduling influences overall system performance and process execution fairness in operating systems.
</div>