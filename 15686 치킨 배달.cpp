#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Coordinate{  // 좌표
    int y, x;
};

int N, M;   // N: 도시 한 변의 길이, M: 남아있는 치킨집의 수
std::vector<Coordinate> chicken, house; // chicken: 치킨 집의 좌표, house: 집의 좌표
std::vector<int> visited;   // visited: 선택 여부
int ans = 21e8; // 도시의 최소 치킨 거리

int calDis(){
    int ret = 0;    // ret: 모든 집과 선택되 치킨집 간의 도시의 치킨 거리

    for(int h=0; h<house.size(); h++){  // 모든 집에 대하여
        int minDis = 21e8;
        for(int c=0; c<chicken.size(); c++){    // M개의 치킨집과 거리를 비교
            if(visited[c] == 0) continue;   // visited가 0이면 선택되지 않은 치킨 집
            int dis = std::abs(house[h].y-chicken[c].y) + std::abs(house[h].x-chicken[c].x);
            minDis = std::min(minDis, dis); // h 집에서 가장 가까운 c 치킨집 까지의 거리
        }
        ret += minDis;  // 도시의 치킨거리는 모든 치킨 거리의 합
    }

    return ret;
}

void DFS(int now, int num){ // now: 현재 선택된 치킨집, num: 선택할 수 있는 남은 치킨집의 수

    if(num == 0){        
        ans = std::min(ans, calDis());  // M개의 치킨집으로 구할 수 있는 최소 치킨 거리
        return;
    }

    for(int i=now+1; i<chicken.size(); i++){    // M개의 치킨집 선택
        visited[i] = 1;
        DFS(i, num-1);
        visited[i] = 0;
    }
}

void sol(){
    DFS(-1, M); // DFS를 사용하여 M개의 치킨집 선택

    return;
}

// 입력
void input(){
    std::cin >> N >> M;
    for(int j=0; j<N; j++){
        for(int i=0; i<N; i++){
            int n;
            std::cin >> n;
            if(n==1){   // 집
                house.push_back({j, i});
            }
            if(n==2){   // 치킨집
                chicken.push_back({j, i});
                visited.push_back(0);   // visited 벡터도 치킨집의 개수만큼 생성
            }
        }
    }

    return;
}

int main(){
    input();
    sol();
    std::cout << ans;
    return 0;
}