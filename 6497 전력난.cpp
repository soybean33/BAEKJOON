#include <iostream>
#include <vector>
#include <algorithm>

struct Road{    // Road: 도로 정보
    int x, y, z;    // x, y: 집 번호, z: 도로의 길이
};

int M, N;   // M: 집의 수, N: 도로의 수

std::vector<Road> v;    // v[i]: i 번째 도로 정보
int total;  // total: 모든 도로의 거리의 합
std::vector<int> parent;    // parent[i]: i 집의 소속 정보

int answer; // answer: 절약할 수 있는 최대 비용

int Find(int x) {   // x: 소속을 찾을 집의 번호
    if(x == parent[x]) return x;
    return parent[x] = Find(parent[x]);
}

void Union(int a, int b){   // a, b: 도로를 연결할 두 집의 번호
    int pa = Find(a);
    int pb = Find(b);

    if(pa == pb) {return;}

    parent[pb] = pa;

    return;
}

bool Cmp(const Road& a, const Road& b) {    // 도로의 길이를 기준으로 오름차순 정렬
    if(a.z != b.z) {return a.z < b.z;}
    return false;
}

void Solution(){

    parent.assign(M, 0);
    for(int i=0; i<M; ++i) {parent[i] = i;} // 소속 정보 초기화

    answer = total; // 도로의 길이 총합

    std::sort(v.begin(), v.end(), Cmp); // 도로의 길이를 기준으로 오름차순 정렬
    for(const Road& road : v) {
        if(Find(road.x) == Find(road.y)) {continue;}    // 이미 같은 소속이면 continue

        Union(road.x, road.y);  // 소속 합침
        answer -= road.z;   // 절약할 수 있는 최대 비용 감소
    }

    return;
}

void Input(){

    v.assign(N, {0, 0, 0});

    total = 0;

    for(int i=0; i<N; ++i) {
        std::cin >> v[i].x >> v[i].y >> v[i].z;
        total += v[i].z;
    }

    return;
}

int main(){

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    while(true){
        std::cin >> M >> N;

        if(M == 0 && N == 0) {break;}   // 0이 2개 주어지면 break

        Input();

        Solution();

        std::cout << answer << '\n';
    }

    return 0;
}