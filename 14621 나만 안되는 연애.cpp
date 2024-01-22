#include <iostream>
#include <vector>
#include <algorithm>

struct Edge{	// Edge: 두 학교를 연결하는 도로 정보
	int u, v, d;	// u, v: 연결되어 있는 학교 번호, d: 두 학교의 거리
};

int N, M;	// N: 학교의 수, M: 학교를 연결하는 도로의 개수
std::vector<char> schoolType;	// schoolType[i]: i 학교가 남초 대학교라면 'M', 여초 대학교라면 'W'
std::vector<Edge> edges;	// edges[i]: 학교 연결 정보

std::vector<int> parent;	// parent[i]: i 학교의 소속 정보
int answer;	// answer: 경로의 길이

int Find(int x) {	// 소속 정보 찾음
	if(parent[x] == x) {return x;}
	return parent[x] = Find(parent[x]);
}

void Union(int a, int b) {	// 두 학교 연결
	int pa = Find(a);
	int pb = Find(b);

	if(pa == pb) {return;}

	if(pa < pb) {parent[pa] = pb;}
	else {parent[pb] = pa;}

	return;
}

bool Cmp(const Edge& left, const Edge& right) {	// 거리를 기준으로 오름차순 정렬
	if(left.d != right.d) {return left.d < right.d;}

	return false;
}

void Solution() {

	parent.assign(N + 1, 0);
	for(int i=1; i<=N; ++i) {parent[i] = i;}	// 각 학교의 소속 정보 초기화

	std::sort(edges.begin(), edges.end(), Cmp);	// 짧은 도로부터 연결하기 위해 거리를 기준으로 오름차순 정렬

	int cnt = 0;	// cnt: 연결된 도로의 개수
	for(const Edge& edge : edges) {	// edge: 연결을 시도할 도로의 정보
		if(Find(edge.u) == Find(edge.v)) {continue;}	// 같은 소속이라면 도로를 연결할 필요 없음

		Union(edge.u, edge.v);	// 두 학교 연결
		answer += edge.d;	// 거리 추가
		++cnt;	// 연결된 학교 갯수 추가

		if(cnt == N - 1) {return;}	// N-1개의 도로가 연결되면 모든 학교가 연결된 것
	}

	answer = -1;	// 모든 학교를 연결하는 경로가 없을 경우 -1

	return;
}

void Input() {

	std::cin >> N >> M;

	schoolType.assign(N + 1, ' ');
	for(int i=1; i<=N; ++i) {std::cin >> schoolType[i];}	// 학교 타입 입력

	for(int i=0; i<M; ++i) {
		int u, v, d;	// u, v: 학교 번호, d: 두 학교를 연결하는 도로의 거리
		std::cin >> u >> v >> d;

		if(schoolType[u] == schoolType[v]) {continue;}	// 사심 경로는 같은 타입의 대학교끼리는 연결하지 않음

		edges.push_back({u, v, d});
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	std::cout << answer;

	return 0;
}