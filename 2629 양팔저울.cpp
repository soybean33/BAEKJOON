#include <iostream>
#include <vector>
#include <cmath>

int N;  // N: 추의 개수
std::vector<int> WEIGHTS;   // WEIGHTS[i]: 추의 무게
int M;  // M: 무게를 확인하고자 하는 구슬의 개수
std::vector<int> CHK_WEIGHTS;   // CHK_WEIGHTS: 확인하고자 하는 구슬의 무게

std::vector<std::vector<bool>> dp;  // dp[i][j]: i 개의 추를 사용해서 j 무게를 만들 수 있으면 true

void Dfs(int i, int w){ // i: 사용한 추의 개수, w: 추의 무게

    if(i > N || dp[i][w] == true) {return;} // 추의 개수를 초과하거나 이미 확인할 수 있는 무게면 return

    dp[i][w] = true;    // i 개의 추를 사용해 w 무게를 확인할 수 있음

    Dfs(i + 1, w + WEIGHTS[i]); // 추 추가
    Dfs(i + 1, std::abs(w - WEIGHTS[i]));   // 추 제거
    Dfs(i + 1, w);  // 다음 번 추 사용

    return;
}

void Solution(){

    dp.assign(N+1, std::vector<bool>(15'001, false));

    Dfs(0, 0);

    return;
}

void Input(){

    std::cin >> N;

    WEIGHTS.assign(N, 0);

    for(int i=0; i<N; ++i) {std::cin >> WEIGHTS[i];}

    std::cin >> M;

    CHK_WEIGHTS.assign(M, 0);

    for(int i=0; i<M; ++i) {std::cin >> CHK_WEIGHTS[i];}

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    Input();

    Solution();

    for(const int& chkWeight : CHK_WEIGHTS) {   // chkWeight: 확인하고자 하는 무게
        if(chkWeight > 15'000) {std::cout << "N ";} // 30개의 추 * 500g == 15,000g 까지 측정 가능
        else if(dp[N][chkWeight]) {std::cout << "Y ";}
        else {std::cout << "N ";}
    }

    return 0;
}