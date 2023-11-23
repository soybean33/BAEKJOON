#include <iostream>
#include <vector>
#include <algorithm>

int N;  // N: 정수의 개수
std::vector<int> A; // A[i]: i 번째 수열

int answer; // answer: 연속된 수를 제거하였을 때 가장 큰 값

void Solution(){

    std::vector<std::vector<int>> dp;   // dp[i][j]: i 번째 까지 가장 큰 수

    dp.assign(N+1, std::vector<int>(2, 0));

    dp[0][0] = A[0];
    dp[0][1] = A[0];
    answer = A[0];

    for(int i=1; i<N; ++i) {
        dp[i][0] = std::max(dp[i-1][0] + A[i], A[i]);
        dp[i][1] = std::max(dp[i-1][0], dp[i-1][1] + A[i]);
        answer = std::max(answer, std::max(dp[i][0], dp[i][1]));
    }

    return;
}

void Input(){

    std::cin >> N;

    A.assign(N, 0);

    for(int i=0; i<N; ++i) {std::cin >> A[i];}

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}