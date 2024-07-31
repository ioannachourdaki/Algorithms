#include <iostream>

using namespace std;


int getMaxProfit(int* p, int N, int K) {
    
    int dp[K+1], minCost[K+1];

    // Initialize variables for dynamic programming
    for(int i=0; i < K+1; i++){
        dp[i] = 0;
        minCost[i] = p[0];
    }

    // Iterate through prices array
    for (int i = 1; i < N; i++) {
        // Iterate through transactions 
        for (int m = 1; m <= K; m++) {
            // Update minimum cost for the current transaction
            minCost[m] = min(minCost[m], p[i] - dp[m-1]);
            // Update maximum profit for the current transaction
            dp[m] = max(dp[m], p[i] - minCost[m]);
        }
    }

    return dp[K];
}

int main() {

    int N, K;

    cin >> N >> K;

    int* p = new int[N];
    for(int i=0; i < N; i++) {
        cin >> p[i];
    }

    cout << getMaxProfit(p, N, K) << endl;
    return 0;
}
