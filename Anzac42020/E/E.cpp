// MuMonash

#include <cstdio>
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {

    int n,m;
    cin >> n >> m >> ws;

    vector<int> starts = vector<int>();
    vector<int> ends = vector<int>();

    for (int i=0; i<n; i++) {
        int a, s;
        cin >> a >> s >> ws;
        starts.push_back(a);
        ends.push_back(a+s);
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int start_pointer = 0;
    int end_pointer = 0;

    int saves = 0;

    queue<int> workstations_available = queue<int>();

    while (start_pointer != starts.size()) {
        // First, if no new starts, then handle all previous ends
        while ((end_pointer != ends.size()) && (start_pointer != starts.size()) && (ends[end_pointer] <= starts[start_pointer])) {
            workstations_available.push(ends[end_pointer++]);
        }
        // Next, try to resolve new starts before previous ends.
        while ((end_pointer == ends.size()) || ((start_pointer != starts.size()) && (ends[end_pointer] > starts[start_pointer]))) {
            // Assign the next start.
            bool found = false;
            while ((workstations_available.size() != 0)) {
                int t = workstations_available.front();
                workstations_available.pop();
                if (starts[start_pointer] - t <= m) {
                    found = true;
                    break;
                }
            }
            if (found) {
                saves++;
            }
            start_pointer++;
        }
    }

    cout << saves << endl;

    return 0;
}
