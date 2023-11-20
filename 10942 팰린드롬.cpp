#include <iostream>
#include <vector>

int N;  // N: 자연수의 개수
std::vector<int> V; // V[i]: i 번째 자연수
int M;  // M: 질문의 개수

std::vector<std::vector<bool>> dp;  // dp[i][j]: i 번째 자연수부터 j 번째 자연수까지 팰린드롬 여부

void Solution(){

    dp.assign(N+1, std::vector<bool>(N+1, false));

    for(int i=1; i<=N-1; ++i){
        if(V[i] == V[i+1]) {dp[i][i+1] = true;} // 연속된 수가 같다면 펠린드롬
    }

    for(int i=1; i<=N; ++i){dp[i][i] = true;}   // 자연수 한개는 펠린드롬

    for(int i=N-1; i>=1; --i){  // N-1부터 1까지 탐색
        for(int j=i+2; j<=N; ++j){  // i+2부터 N까지 탐색
            if(V[i] == V[j] && dp[i+1][j-1] == true) {dp[i][j] = true;} // 시작 수와 같은 수면서 펠린드롬이였다면 true
        }
    }

    return;
}

void Input(){

    std::cin >> N;

    V.assign(N+1, 0);

    for(int i=1; i<=N; ++i){std::cin >> V[i];}

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    std::cin >> M;

    for(int i=0; i<M; ++i){
        int S, E;   // S: 시작 수 인덱스, E: 끝 수 인덱스
        std::cin >> S >> E;

        std::cout << dp[S][E] << '\n';
    }

    return 0;
}
