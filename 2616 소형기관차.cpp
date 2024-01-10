#include <iostream>
#include <vector>
#include <algorithm>

int N;  // N: 기관차가 끌고 가던 객차의 수
std::vector<int> passenger; // passenger[i]: i 번째 객차에 타고 있는 손님의 수
int K;  // K: 소형 기관차가 최대로 끌 수 있는 객차의 수

int answer; // answer: 소형 기관차 3대를 이용하여 최대로 운송할 수 있는 손님의 수

void Solution(){

    std::vector<int> sum;   // sum[i]: i 번째 칸 까지의 손님 수 누적합
    std::vector<std::vector<int>> dp;   // dp[i][j]: i 번째 소형 기관차의 j 객차

    sum.assign(N+1, 0);
    dp.assign(4, std::vector<int>(N+1, 0));

    for(int i=1; i<=N; ++i) {sum[i] = sum[i-1] + passenger[i];} // 누적합 구함

    for(int i=1; i<=3; ++i){
        for(int j=i*K; j<=N; ++j){
            dp[i][j] = std::max(dp[i][j-1], dp[i-1][j-K] + sum[j] - sum[j-K]);
        }
    }

    answer = dp[3][N];


    return;
}

void Input(){

    std::cin >> N;

    passenger.assign(N+1, 0);

    for(int i=1; i<=N; ++i) {std::cin >> passenger[i];}

    std::cin >> K;

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}