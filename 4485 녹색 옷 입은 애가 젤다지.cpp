#include <iostream>
#include <vector>
#include <queue>

struct Coordinate{
        int y, x;       // y, x: 칸의 좌표
};

struct Edge{
        Coordinate to;  // to: 현재 칸에서 갈 수 있는 칸의 좌표
        int cost;       // cost: to 칸까지 가는데 잃는 루피의 양

        bool operator < (Edge next) const {     // cost를 기준으로 오름차순
                if(cost < next.cost) return false;
                if(cost > next.cost) return true;

                return false;
        }
};

int N;  // N: 동굴의 한 변의 길이
int MAP[126][126];      // MAP[i][j]: i행 j열 칸에 도착하면 잃는 루피

// 방향 벡터
int dirY[] = {0, 1, 0, -1};
int dirX[] = {1, 0, -1, 0};

int sol(){
        int ans;        // ans: 링크가 잃을 수 밖에 없는 최소 금액
        std::vector<Edge> v[126][126];  // v[i][j]: i행 j열에서 갈 수 있는 칸의 정보

        for(int j=0; j<N; j++){
                for(int i=0; i<N; i++){
                        Coordinate now = {j, i};        // now: 현재 칸
                        for(int dir=0; dir<4; dir++){
                                Coordinate next = {now.y + dirY[dir], now.x + dirX[dir]};       // next: 상하좌우로 인접한 칸

                                if(next.x < 0 || next.y < 0 || next.x >= N || next.y >= N) continue;    // 동굴 범위 벗어나면 continue

                                v[now.y][now.x].push_back({{next.y, next.x}, MAP[next.y][next.x] });    // 갈 수 있는 칸 정보 넣음
                        }        
                }
        }

        std::priority_queue<Edge> pq;   // pq: 잃는 루피를 기준으로 오름차순 정렬한 pq
        int cost[126][126];     // cost[i][j]: i행 j열의 칸까지 최소로 잃는 루피
        for(int j=0; j<N; j++){
                for(int i=0; i<N; i++){
                        cost[j][i] = 21e8;      // 최대값으로 초기화
                }
        }
        pq.push({{0, 0}, MAP[0][0]});   // (0, 0)칸에는 MAP[0][0] 만큼의 루피를 잃음
        cost[0][0] = MAP[0][0]; // 잃는 누적 루피도 표시

        while(!pq.empty()){
                Edge now = pq.top();    // now: 현재 위치하고 있는 칸의 정보
                pq.pop();

                if(cost[now.to.y][now.to.x] < now.cost) continue;       // 현재 위치하고 있는 칸에서 갈 수 있는 칸이 현재 칸까지 오면서 누적된 잃은 루피보다 적으면 continue -> 이미 더 적은 루피을 잃는 방법을 찾음

                for(int i=0; i<v[now.to.y][now.to.x].size(); i++){
                        Edge next = v[now.to.y][now.to.x][i];   // next: 현재 위치하고 있는 칸에서 갈 수 있는 칸에 대한 정보
                        int nextCost = cost[now.to.y][now.to.x] + next.cost;    // nextCost: 현재 위치하고 있는 칸에서 다음 칸으로 이동하였을 때 잃는 루피

                        if(cost[next.to.y][next.to.x] <= nextCost) continue;    // 다음 칸 까지 누적된 잃는 루피보다 다음 칸에서 잃은 루피가 더 많으면 continue

                        cost[next.to.y][next.to.x] = nextCost;  // 잃은 루피 갱신

                        pq.push({{next.to.y, next.to.x}, nextCost});    // pq에 갈 수 있는 칸 추가
                }
        }

        return cost[N-1][N-1];  // 가장 오른쪽 아래칸 까지 가면서 잃은 최소 루피의 양
}

void input(){
        std::cin >> N;
        if(N == 0) exit(0);     // N이 0이면 종료

        for(int j=0; j<N; j++){
                for(int i=0; i<N; i++){
                        std::cin >> MAP[j][i];
                }
        }

        return;
}

int main(){
        int tc = 1;     // tc: 테스트 케이스 번호
        while(1){
                input();
                std::cout << "Problem " << tc << ": " << sol() << '\n';
                tc++;
        }

        return 0;
}
