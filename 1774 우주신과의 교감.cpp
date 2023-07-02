#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Coordinate{	// 좌표
	int X, Y;	// X, Y: 좌표
};

struct SpaceDist{	// 우주신과 우주신의 거리 정보
	int spaceGodA, spaceGodB;	// spaceGodA, spaceGodB: 우주신 A, 우주신 B
	double dist;	// dist: 우주신 A와 우주신 B의 거리
};

int N, M;	// N: 우주신의 개수, M: 이미 연결된 신들과의 통로의 개수
std::vector<Coordinate> spaceGod;	//	spaceGod[i]: i 우주신 좌표
std::vector<std::pair<int, int>> linked;	// linked[i]: i 번째로 연결된 신들 정보
std::vector<int> parent;	// parent[i]: i 우주신의 소속 정보
std::vector<SpaceDist> spaceDist;	// spaceDist: 우주신과 우주신의 거리 정보
double ans;	// ans: 만들어야 할 최소의 통로 길이

bool cmp(SpaceDist left, SpaceDist right){	// 거리를 기준으로 오름차순 정렬
	if(left.dist != right.dist) return left.dist < right.dist;

	return false;
}

int find(int curr){	// curr: 소속을 찾고자 하는 우주신의 조상 소속
	if(curr == parent[curr]) return curr;
	return parent[curr] = find(parent[curr]);
}

bool unionNode(int nodeA, int nodeB){	// nodeA, nodeB: 연결된 신의 번호

	int nodeAParent = find(nodeA);	// nodeAParent: A 우주신의 소속
	int nodeBParent = find(nodeB);	// nodeBParent: B 우주신의 소속

	if(nodeAParent == nodeBParent) return false;	// 두 우주신이 이미 같은 소속이면 return false

	parent[nodeAParent] = nodeBParent;

	return true;
}

void solution(){

	parent.assign(N+1, 0);

	for(int i=0; i<N+1; ++i) parent[i] = i;	// 소속 정보 초기화

	for(int i=0; i<M; i++){
		std::pair<int, int> currLinked = linked[i];	// currLinked: i 번째 통로로 연결된 신들의 번호

		unionNode(currLinked.first, currLinked.second);	// 두 신을 연결
	}

	for(int j=1; j<=N; j++){
		for(int i=j+1; i<=N; i++){

			double dist = std::sqrt(std::pow(spaceGod[i].X - spaceGod[j].X, 2) + std::pow(spaceGod[i].Y - spaceGod[j].Y, 2));	// dist: 두 신의 거리

			spaceDist.push_back({j, i, dist});	// 두 신의 번호와 거리 정보 저장
		}
	}

	std::sort(spaceDist.begin(), spaceDist.end(), cmp);	// 두 신 사이의 거리를 기준으로 오름차순 정렬

	int spaceDistSize = spaceDist.size();	// spaceDistSize: 서로 다른 신과 신의 조합의 개수
	for(int i=0; i<spaceDistSize; i++){
		SpaceDist currSpaceDist = spaceDist[i];	// currSpaceDist: 현재 연결하고자 하는 통로 정보
		if(unionNode(currSpaceDist.spaceGodA, currSpaceDist.spaceGodB)) ans += currSpaceDist.dist;	// 두 우주신이 같은 소속이 아니여서 연결되는 경우 ans에 거리를 더함
	}

	return;
}

void input(){

	std::cin >> N >> M;

	spaceGod.assign(N+1, {0, 0});

	for(int i=1; i<=N; ++i){
		int x, y;	// x, y: 우주신의 좌표
		std::cin >> x >> y;
		spaceGod[i] = {x, y};
	}

	linked.assign(M, {0, 0});

	for(int i=0; i<M; ++i){
		int a, b;	// a, b: 연결된 신의 번호
		std::cin >> a >> b;
		linked[i] = {a, b};
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	input();

	solution();

	printf("%.2f", ans);

	return 0;
}