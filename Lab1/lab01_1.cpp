#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>

using namespace std;
using namespace chrono;

bool isMedian(int* arr, int N, int K, int median, bool &exists) {
    int prefixSum[N];
    for (int i=0; i<N; i++) {
        if(arr[i] == median) exists = true; 
        prefixSum[i] = (arr[i] >= median) ? 1 : -1;
        if (i > 0) {
            prefixSum[i] += prefixSum[i-1];
        }
    }

    int maxSum = prefixSum[K-1];
    int minSum = 0;

    for (int i = K; i < N; i++) {
        minSum = min(minSum, prefixSum[i-K]);
        maxSum = max(maxSum, prefixSum[i] - minSum);
    }
    return maxSum > 0;
}


int findMax(int* arr, int max, int N, int K){   

    int low = 0, high = max, median = -1;
 
    while(low <= high){
        int mid = (low + high) / 2;
        bool exists = false;
        if(isMedian(arr, N, K, mid, exists)){
            if(exists) median = mid;
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
    return median;
}


int main(){

    // Clock starts
    auto start_time = high_resolution_clock::now();

    ifstream inFile;
    int N, K, mx = -1;

    for(int j=0; j<21; j++){
        inFile.open("cereal\\input" + to_string(j) + ".txt");

        if (!inFile.is_open()) {
            cerr << "Failed to open the input file." << std::endl;
            return 1;
        }

        inFile >> N;
        inFile >> K;

        int* arr = new int[N];

        for(int i=0; i<N; i++){
            inFile >> arr[i];
            mx = max(arr[i],mx);
        }

        inFile.close();
        
        int med = findMax(arr, mx, N, K);

        inFile.open("cereal\\output" + to_string(j) + ".txt");

        if (!inFile.is_open()) {
            cerr << "Failed to open the input file." << endl;
            return 1;
        }

        inFile >> N;
        if(med != N) {
            cout << "Error at ex" << j << ": " << med << " " << N << endl;
        }

        inFile.close();

    }

    // Clock stops
    auto end_time = high_resolution_clock::now();

    // Calculate the duration in milliseconds
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() /1000.0 << " seconds" << endl;

    return 0;
}

