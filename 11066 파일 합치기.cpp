#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 10e8;   // INF: 나올 수 없는 값

int K;  // K: 소설을 구성하는 장의 수
std::vector<int> PAGES; // PAGES[i]: i 번째 장의 파일의 크기

std::vector<int> sum;   // sum[i]: i 번째 장 까지의 파일의 크기의 합
int answer; // answer: 파일들을 하나의 파일로 합칠 때 필요한 최소 비용

void Solution(){

    std::vector<std::vector<int>> dp;   // dp[i][j]: i~j 번째 파일들을 합치는데 필요한 최소 비용

    dp.assign(K+1, std::vector<int>(K+1, 0));

    for(int i=1; i<=K; ++i){
        for(int j=1; j<=K-i; ++j){
            dp[j][i+j] = INF;   // j ~ i+j 번째 파일을 합치는데 필요한 최소 비용은 아직 탐색되지 않음
            for(int k=j; k<i+j; ++k){
                dp[j][i+j] = std::min(dp[j][i+j], dp[j][k] + dp[k+1][i+j] + sum[i+j] - sum[j-1]);   // j ~ k 최소 비용 + k+1 ~ i+j 최소 비용 + i ~ j 까지 파일 합
            }
        }
    }

    answer = dp[1][K];  // 1 ~ K 번째 파일을 합치는데 필요한 최소 비용

    return;
}

void Input(){    
    
    std::cin >> K;

    PAGES.assign(K+1, 0);
    sum.assign(K+1, 0);

    for(int i=1; i<=K; ++i){
        std::cin >> PAGES[i];
        sum[i] = sum[i-1] + PAGES[i];
    }

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;  // T: 테스트 케이스의 개수
    std::cin >> T;

    for(int tc=0; tc<T; ++tc){
        Input();
        Solution();
        std::cout << answer << '\n';
    }

    return 0;
}