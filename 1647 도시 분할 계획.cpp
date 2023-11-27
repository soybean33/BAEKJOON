#include <iostream>
#include <vector>
#include <algorithm>

struct Edge{    // Edge: 길의 정보
    int A, B, C;    // A: 집 번호, B: 집 번호, C: 길의 유지비
};

int N, M;   // N: 집의 개수, M: 길의 개수
std::vector<Edge> edges;    // edges[i]: i 번째로 길의 유지비가 작은 길의 정보

std::vector<int> parent;    // parent[i]: i 집의 소속 정보
int answer; // answer: 첫째 줄을 없애고 남은 길 유지비의 합의 최솟값

int Find(int x){    // x: 소속을 찾을 집 번호
    if(x == parent[x]) return x;    // 소속을 찾음
    return parent[x] = Find(parent[x]); // 계속해서 소속을 찾음
}

void Union(int a, int b){   // a, b: 소속을 합칠 두 집 번호
    int pa = Find(a);   // pa: a의 소속
    int pb = Find(b);   // pb: b의 소속

    if(pa == pb) return;    // 두 집 소속이 이미 같다면 return

    parent[pb] = pa;    // 소속 합침

    return;
}

bool Cmp(Edge& left, Edge& right){  // left, right: 비교할 두 집
    if(left.C != right.C) return left.C < right.C;  // 유지비를 기준으로 오름차순 정렬
    return false;
}

void Solution(){

    std::sort(edges.begin(), edges.end(), Cmp); // 유지비를 기준으로 오름차순 정렬

    parent.assign(N+1, 0);  // 소속 정보를 저장할 공간 할당

    for(int i=1; i<=N; ++i) {parent[i] = i;}    // 소속 정보 초기화

    int longestDist;    // longestDis: 두 마을로 분리하기 위한 가장 긴 길의 길이

    for(const Edge& edge: edges){   // edge: 연결할 길 정보
        if(Find(edge.A) != Find(edge.B)) {  // 두 마을이 다른 소속이라면
            Union(edge.A, edge.B);  // 길 연결
            answer += edge.C;   // 길의 유지비 합
            longestDist = edge.C;   // 가장 큰 유지비를 갖는 길은 제거하기 위하여 저장
        }
    }

    answer -= longestDist;  // 가장 큰 유지비를 갖는 길 제거

    return;
}

void Input(){

    std::cin >> N >> M;

    edges.assign(M, {0, 0, 0});

    for(int i=0; i<M; ++i){std::cin >> edges[i].A >> edges[i].B >> edges[i].C;}

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