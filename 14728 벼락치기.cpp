#include <iostream>
#include <vector>
#include <algorithm>

int N, T;   // N: 이번 시험 단원 개수, T: 시험까지 공부 할 수 있는 총 시간
int K, S;   // K: 각 단원 별 예상 공부 시간, S: 단원 문제의 배점

int answer; // answer: 준석이가 얻을 수 있는 최대 점수

void Solution(){

    std::vector<int> dp;    // dp[i]: i 시간에 준석이가 얻을 수 있는 최대 점수
    dp.assign(T+1, 0);

    for(int i=0; i<N; ++i){
        std::cin >> K >> S;
        for(int j=T; j>=K; --j){
            dp[j] = std::max(dp[j], dp[j-K] + S);
        }
    }

    answer = dp[T];

    return;
}

void Input(){

    std::cin >> N >> T;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}