#include <iostream>
#include <vector>
#include <algorithm>

constexpr int INF = 21e8;   // INF: 나올 수 없는 값

int N;  // N: SCV의 수
std::vector<int> HP;    // HP[i]: i 번째 SCV의 HP

std::vector<std::vector<std::vector<int>>> dp;  // dp[i][j][k]: 각 SCV의 채력이 i, j, k 일 때 공격 횟수

int answer; // answer: 모든 SCV를 파괴하기 위해 공격해야 하는 횟수의 최솟값

int Dfs(int x, int y, int z) {  // x, y, z: 각 SCV의 채력

    if(x<0) {return Dfs(0, y, z);}  // 첫 번째 SCV 파괴
    if(y<0) {return Dfs(x, 0, z);}  // 두 번째 SCV 파괴
    if(z<0) {return Dfs(x, y, 0);}  // 세 번쨰 SCV 파괴

    if(x==0 && y==0 && z==0) {return 0;}    // 모두 파괴

    int& result = dp[x][y][z];  // result: 현재 채력의 공격 횟수

    if(result != -1) {return result;}   // 이러한 채력이 나온적 있다면

    result = INF;

    // 최소 공격 횟수 찾기
    result = std::min(result, Dfs(x-9, y-3, z-1) + 1);
    result = std::min(result, Dfs(x-9, y-1, z-3) + 1);
    result = std::min(result, Dfs(x-3, y-9, z-1) + 1);
    result = std::min(result, Dfs(x-1, y-9, z-3) + 1);
    result = std::min(result, Dfs(x-3, y-1, z-9) + 1);
    result = std::min(result, Dfs(x-1, y-3, z-9) + 1);

    return result;
}

void Solution(){

    dp.assign(61, std::vector<std::vector<int>>(61, std::vector<int>(61, -1)));

    answer = Dfs(HP[0], HP[1], HP[2]);

    return;
}

void Input(){

    std::cin >> N;

    HP.assign(N, 0);

    for(int i=0; i<N; ++i) {std::cin >> HP[i];}

    return;
}

int main(){

    Input();

    Solution();

    std::cout << answer;

    return 0;
}