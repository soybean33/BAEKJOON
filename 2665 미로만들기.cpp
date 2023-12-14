#include <iostream>
#include <string>
#include <vector>
#include <queue>

constexpr int INF = 10e8;   // INF: 나올 수 없는 값
// 방향 벡터
constexpr int dirY[4] = {0, 1, 0, -1};
constexpr int dirX[4] = {1, 0, -1, 0};

struct Node{    // Node: 현재 탐색 위치 정보
    int y, x;   // y, x: 좌표
    int cnt;    // cnt: 흰방으로 바꾸어야 하는 검은 방의 개수

    const bool operator < (Node next) const {   // 바꾼 방의 개수 오름차순 정렬
        if(cnt != next.cnt) return cnt > next.cnt;
        return false;
    }
};

int N;  // N: 한 줄에 들어가는 방의 수
std::vector<std::vector<bool>> MAP; // MAP[i][j]: i 행 j 열의 방의 정보 -> true: 흰방, false: 검은 방

int answer; // answer: 흰 방으로 바꾸어야 할 최소의 검은 방의 수

void Solution(){

    std::priority_queue<Node> pq;   // pq: 탐색 위치 정보 우선순위큐 저장
    std::vector<std::vector<int>> dp;   // dp[i][j]: i 행 j 열 까지 흰방으로 바꾸어야 하는 검은 방의 최소 개수

    dp.assign(N, std::vector<int>(N, INF));

    pq.push({0, 0, 0});
    dp[0][0] = 0;

    while(!pq.empty()){
        Node curr = pq.top();   // curr: 현재 탐색 정보
        pq.pop();

        if(curr.cnt > dp[curr.y][curr.x]) {continue;}   // 더 많은 방을 변경해야 하면 continue

        if(curr.y == N - 1 && curr.x == N - 1) {    // 끝방에 도착한 경우
            answer = curr.cnt;  // 우선순위 큐를 사용했으므로 저장 후 return
            return;
        }

        for(int dir=0; dir<4; ++dir){
            Node next = {curr.y + dirY[dir], curr.x + dirX[dir], curr.cnt}; // next: 현재 방에서 갈 수 있는 다음 방의 정보

            if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= N) {continue;}  // 범위 벗어나면 continue;
            if(MAP[next.y][next.x] == false) {++next.cnt;} // 검은 방의 경우 ++

            if(next.cnt >= dp[next.y][next.x]) {continue;}  // 더 적은 방을 변경할 수 있는 경우 continue

            pq.push(next);  // 탐색을 위해 우선순위 큐에 추가
            dp[next.y][next.x] = next.cnt;  // 최소 값 갱신
        }
    }

    return;
}

void Input(){

    std::cin >> N;

    MAP.assign(N, std::vector<bool>(N, false));

    for(int y=0; y<N; ++y){
        std::string S;  // S: 한 행의 정보
        std::cin >> S;
        for(int x=0; x<N; ++x){MAP[y][x] = S[x] == '0' ? false : true;} // 0인 경우 검은 방, 1인 경우 흰방
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