#include <iostream>
#include <vector>

constexpr int MODULAR = 10e8 + 3;   // MODULAR: 모듈러 값

int N;  // N: 색상환에 포함된 색의 개수
int K;  // K: 선택할 색상의 개수

int answer; // answer: 어떤 인접한 두 색도 동시에 선택하기 않고 K개의 색을 고를 수 있는 경우를 모듈러 한 값

void Solution(){

    std::vector<std::vector<int>> dp;

    dp.assign(N+1, std::vector<int>(K+1, 0));

    for(int i=0; i<N; ++i){
        dp[i][0] = 1;
        dp[i][1] = i;
    }

    for(int i=2; i<=N; ++i){
        for(int j=2; j<=K; ++j){
            dp[i][j] = (dp[i-2][j-1] + dp[i-1][j]) % MODULAR;
        }
    }

    answer = (dp[N-1][K] + dp[N-3][K-1]) % MODULAR;

    return;
}

void Input(){

    std::cin >> N >> K;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}