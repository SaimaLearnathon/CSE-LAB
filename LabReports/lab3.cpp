#include <bits/stdc++.h>
using namespace std;

class Process {
public:
    int id, arrival, burst, remaining, waiting = 0, turnaround = 0, finish = 0;
};

int main() {
    int n, quantum, overhead = 1;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Process " << p[i].id << ": ";
        cin >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    // Sort processes by arrival time
    sort(p.begin(), p.end(), [](Process &a, Process &b) {
        return a.arrival < b.arrival;
    });

    queue<int> q;
    vector<bool> inQueue(n, false);
    int currentTime = 0, completed = 0;
    double totalWaiting = 0, totalTurnaround = 0;

    // Push the first process
    q.push(0);
    inQueue[0] = true;
    currentTime = p[0].arrival;

    while (!q.empty()) {
        int i = q.front();
        q.pop();
        inQueue[i] = false;

        // Execute process i
        if (p[i].remaining > quantum) {
            currentTime += quantum;
            p[i].remaining -= quantum;
        } else {
            currentTime += p[i].remaining;
            p[i].remaining = 0;
            p[i].finish = currentTime;
            p[i].turnaround = p[i].finish - p[i].arrival;
            p[i].waiting = p[i].turnaround - p[i].burst;
            totalWaiting += p[i].waiting;
            totalTurnaround += p[i].turnaround;
            completed++;
        }

        // Add overhead time (CPU context switch)
        currentTime += overhead;

        // Add newly arrived processes to queue
        for (int j = 0; j < n; j++) {
            if (p[j].arrival <= currentTime && p[j].remaining > 0 && !inQueue[j]) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // If current process not finished, requeue it
        if (p[i].remaining > 0) {
            q.push(i);
            inQueue[i] = true;
        }

        
        if (q.empty()) {
            for (int j = 0; j < n; j++) {
                if (p[j].remaining > 0) {
                    currentTime = max(currentTime, p[j].arrival);
                    q.push(j);
                    inQueue[j] = true;
                    break;
                }
            }
        }
    }

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (auto &x : p) {
        cout << "P" << x.id << "\t" << x.arrival << "\t"
             << x.burst << "\t" << x.waiting << "\t"
             << x.turnaround << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaiting / n;
    cout << "\nAverage Turnaround Time: " << totalTurnaround / n << endl;

    return 0;
}
