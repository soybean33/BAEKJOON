#include <iostream>
#include <vector>
#include <algorithm>

struct Edge{	// Edge: 간선 정보
	int a, b;	// a, b: 연결되어 있는 두 컴퓨터
	int cost;	// cost: a 컴퓨터와 b 컴퓨터를 연결하는데 비용 c
};

int N, M;	// N: 컴퓨터의 수, M: 연결할 수 있는 선의 수
std::vector<Edge> edges;	// edges[i]: i 번째 선

std::vector<int> parent;	// parent[i]: 소속 정보
int answer;	// answer: 모든 컴퓨터를 연결하는데 필요한 최소비용

int Find(int node){	// node: 소속을 찾을 컴퓨터
	if(parent[node] == node) return node;

	return parent[node] = Find(parent[node]);
}

void Union(int a, int b){	// a, b: 연결할 두 컴퓨터
	int pa = Find(a);
	int pb = Find(b);

	if(pa == pb) return;

	parent[pb] = pa;	// 연결

	return;
}

bool Cmp(const Edge& left, const Edge& right){	// 연결하는 비용을 기준으로 오름차순 정렬
	if(left.cost != right.cost) return left.cost < right.cost;

	return false;
}

void Solution(){

	std::sort(edges.begin(), edges.end(), Cmp);	// 비용을 기준으로 정렬

	parent.assign(N+1, 0);

	for(int i=1; i<=N; ++i) {parent[i] = i;}	// 소속 초기화

	for(const Edge& edge : edges){	// edge: 연결을 시도할 선
		if(Find(edge.a) == Find(edge.b)) {continue;}	// 이미 같은 소속이면 continue

		answer += edge.cost;	// 비용 추가
		Union(edge.a, edge.b);	// 연결
	}

	return;
}

void Input(){

	std::cin >> N >> M;

	edges.assign(M, {0, 0, 0});

	for(int i=0; i<M; ++i) {std::cin >> edges[i].a >> edges[i].b >> edges[i].cost;}

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