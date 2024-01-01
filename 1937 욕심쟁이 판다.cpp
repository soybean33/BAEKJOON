#include <iostream>
#include <vector>
#include <algorithm>

// 방향 벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Coordinate{  // Coordinate: 좌표
    int y, x;
};

int N;  // N: 칸의 개수
std::vector<std::vector<int>> MAP;  // MAP[i][j]: i 행 j 열의 대나무의 개수

std::vector<std::vector<int>> dp;   // dp[i][j]: 욕심쟁이 판다의 이동 횟수

int answer; // answer: 판다가 이동할 수 있는 칸의 수의 최댓값

int Dfs(int y, int x){

    if(dp[y][x] != 0) {return dp[y][x];}    // 이미 기록된 값이 있다면 값 return

    dp[y][x] = 1;

    Coordinate curr = {y, x};   // curr: 현재 좌표

    for(int dir=0; dir<4; ++dir){
        Coordinate next = {curr.y + dirY[dir], curr.x + dirX[dir]}; // next: 판다가 이동한 좌표

        if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) {continue;}  // 밖으로 나가면 continue

        if(MAP[curr.y][curr.x] < MAP[next.y][next.x]) {dp[curr.y][curr.x] = std::max(dp[curr.y][curr.x], Dfs(next.y, next.x) + 1);} // 대나무가 더 많으면 이동
    }
    return dp[y][x];
}

void Solution(){

    dp.assign(N, std::vector<int>(N, 0));

    for(int y=0; y<N; ++y){
        for(int x=0; x<N; ++x){
            answer = std::max(answer, Dfs(y, x));   // 모든 좌표에서 시작해서 최댓값 찾기
        }
    }

    return;
}

void Input(){

    std::cin >> N;

    MAP.assign(N, std::vector<int>(N, 0));

    for(int y=0; y<N; ++y){
        for(int x=0; x<N; ++x){
            std::cin >> MAP[y][x];
        }
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