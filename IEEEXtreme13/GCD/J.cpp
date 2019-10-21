#include <iostream>
#include <cmath>

#define MAX 100001

using namespace std;


// n is size of arr[] and m is sizeof gcd[]
int ccountSubsets(int arr[], int n, int gcd[], int m, int k)
{
    // Map to store frequency of array elements
    int freq[MAX];

    // Map to store number of subsets with given gcd
    int subsets[MAX];
    int minK[MAX];

    for (int i=0; i<MAX; i++) {
        minK[i] = -1;
    }

    // Initialize maximum element. Assumption: all array
    // elements are positive.
    int arrMax = 0;

    // Find maximum element in array and fill frequency
    // map.
    for (int i=0; i<n; i++)
    {
        arrMax = max(arrMax, arr[i]);
        freq[arr[i]]++;
        minK[arr[i]] = 1;
    }

    // Run a loop from max element to 1 to find subsets
    // with all gcds
    for (int i=arrMax; i>=1; i--)
    {
        int sub = 0;
        int add = freq[i];

        // Run a loop for all multiples of i
        for (int j = 2; j*i <= arrMax; j++)
        {
            // Sum the frequencies of every element which
            // is a multiple of i
            add += freq[j*i];

            // Excluding those subsets which have gcd > i but
            // not i i.e. which have gcd as multiple of i in
            // the subset for ex: {2,3,4} cnsidering i = 2 and
            // subset we need to exclude are those havng gcd as 4
            sub += subsets[j*i];
        }

        // Number of subsets with GCD equal to 'i' is pow(2, add)
        // - 1 - sub
        subsets[i] = (1<<add) - 1 - sub;
    }

    // IDK wtf to do for specific K.

    int amount=0;
    for (int i=0; i<m; i++)
        if ((subsets[gcd[i]] && k != 1) || (minK[gcd[i]] == 1) && k == 1)
            amount++;

    return amount;
}

int main() {
    int n, k;

    cin >> n >> k;

    int arr[n];
    int gcd[MAX];
    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }
    for (int i=0; i<MAX-1; i++) gcd[i] = i+1;

    cout << ccountSubsets(arr, n, gcd, MAX, k) << endl;

}
