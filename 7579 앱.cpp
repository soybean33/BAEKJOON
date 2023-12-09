#include <iostream>
#include <vector>
#include <algorithm>

int N, M;   // N: 활성화된 앱의 수, M: 새로운 앱 B를 실행하고자 하여 필요한 메모리의 크기
std::vector<int> m; // m[i]: 활성화 되어있는 i 번째 앱의 메모리
std::vector<int> c; // c[i]: 활성화 되어있는 i 번째 앱을 비활성화 했을 경우의 비용

int sum;    // sum: 활성화 되어 있는 앱을 모두 비활성화 하였을 때의 비용
int answer;

void Solution(){

    std::vector<std::vector<int>> dp;   // dp[i][j]: i 번째 앱까지 탐색하였을 때, j 비용을 소모해서 얻을 수 있는 최대 메모리
    dp.assign(N+1, std::vector<int>(100 * 100 + 1, 0)); // 비용의 범위는 100개 앱 * 비활성화 최대 비용 100 -> 10'000

    for(int i=1; i<=N; ++i){    // i 번째 앱까지 탐색
        for(int j=0; j<=sum; ++j){  // 모든 앱을 비활성화하는 최대 비용까지 ㅏㅁ색
            if(j - c[i] >= 0) {dp[i][j] = std::max(dp[i][j], dp[i-1][j-c[i]] + m[i]);}
            dp[i][j] = std::max(dp[i][j], dp[i-1][j]);
        }
    }
    for(int i=0; i<=sum; ++i){
        if(dp[N][i] >= M) { // N 번쨰 앱 까지 탐색하였을 때 비활성화 최소 비용
            answer = i;
            break;
        }
    }

    return;
}

void Input(){

    std::cin >> N >> M;

    m.assign(N+1, 0);
    c.assign(N+1, 0);

    for(int i=1; i<=N; ++i) {std::cin >> m[i];}
    for(int i=1; i<=N; ++i) {
        std::cin >> c[i];
        sum += c[i];
    }

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    std::cout << answer;

    return 0;
}