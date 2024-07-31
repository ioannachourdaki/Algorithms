#include <iostream>

using namespace std;

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

    int N, K, mx = -1;
    cin >> N >> K;
    int* arr = new int[N];

    for(int i=0; i<N; i++){
        cin >> arr[i];
        mx = max(arr[i],mx);
    }
    cout << findMax(arr, mx, N, K) << endl;
    return 0;
}

