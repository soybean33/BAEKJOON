#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 10e8;

int N;
std::vector<std::vector<int>> MATRIX;

int answer;

void Solution(){

    std::vector<std::vector<int>> dp;

    dp.assign(N+2, std::vector<int>(N+2, 0));

    for(int i=1; i<N; ++i){
        for(int j=1; i+j<=N; ++j){
            dp[j][i+j] = INF;
            for(int k=j; k<=i+j; ++k){
                dp[j][i+j] = std::min(dp[j][i+j], dp[j][k] + dp[k+1][i+j] + MATRIX[j][0] * MATRIX[k][1] * MATRIX[i+j][1]);
            }
        }
    }

    answer = dp[1][N];

    return;
}

void Input(){

    std::cin >> N;

    MATRIX.assign(N+1, std::vector<int>(2, 0));

    for(int i=1; i<=N; ++i){
        std::cin >> MATRIX[i][0] >> MATRIX[i][1];
    }

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}