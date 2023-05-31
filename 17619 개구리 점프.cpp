#include <iostream>
#include <vector>
#include <algorithm>

struct Log{
	int logNum;	// logNum: 통나무 번호
	int x1, x2, y;	// x1, x2: 통나무의 시작 x 좌표와 끝 x 좌표, y: 통나무의 y 좌표
};

int N, Q;	// N: 통나무의 개수, Q: 질문의 개수
std::vector<Log> logs;	// logs[i]: i 번째로 입력된 통나무 정보
std::vector<std::pair<int, int>> query;	// query[i]: i 번째 질문 -> 한 통나무에서 다른 통나무로 한 번 이상의 점프로 이동이 가능하면 1, 아니면 0
std::vector<int> parent;	// parent[i]: i 통나무의 소속 정보

int Find(int now){	// now: 소속을 찾을 인덱스
	if(now == parent[now]) return now;	// 소속 찾음
	return parent[now] = Find(parent[now]);	// 갱신하며 소속 찾기
}

void Union(int A, int B){	// A, B: 소속을 합칠 두 인덱스
	// pa, pb: 두 인덱스의 소속
	int pa = Find(A);
	int pb = Find(B);

	if(pa == pb) return;	// 이미 같은 소속이면 return

	parent[pb] = pa;	// 소속 갱신

	return;
}

bool cmp(Log left, Log right){
	if(left.x1 != right.x2) return left.x1 < right.x1;	// 시작 위치 기준 오름차순 정렬

	return false;
}

void sol(){

	std::sort(logs.begin(), logs.end(), cmp);	// 통나무의 시작위치를 기준으로 오름차순 정렬

	parent.resize(N);

	for(int i=0; i<N; i++) parent[i] = i;	// 통나무의 소속 정보 초기화

	int idx = 0;	// idx: 개구리가 점프를 시작할 통나무 인덱스
	int logNum = logs[idx].logNum, logEnd = logs[idx].x2;	// logNun: idx 번째의 통나무 번호, logEnd: 갈 수 있는 가장 먼 거리

	for(int i=1; i<N; i++){
		if(logs[i].x1 <= logEnd){	// i 번째 통나무 보다 더 먼거리를 갈 수 있다면 -> 갈 수 있는 통나무
			logEnd = std::max(logEnd, logs[i].x2);	// 더 먼 거리를 갈 수 있는 통나무로 점프
			Union(logNum, logs[i].logNum);	// 한 번에 갈 수 있으므로 소속 묶음
		}
		else{	// 통나무의 길이가 모자름 -> 갈 수 없는 통나무
			idx = i;	// 개구리의 위치 옮김
			logNum = logs[idx].logNum;	// 개구리가 위치할 통나무 번호 갱신
			logEnd = logs[idx].x2;	// 통나무로 갈 수 있는 가장 먼 거리 갱신
		}
	}

	for(int i=0; i<Q; i++){
		if(Find(query[i].first) == Find(query[i].second))	// 서로 다른 두 통나무가 같은 소속이면
			std::cout << "1\n";
		else	// 두 통나무가 서로 다른 소속이면 -> 한 번에 갈 수 없으면
			std::cout << "0\n";
	}


	return;
}

void input(){

	std::cin >> N >> Q;

	logs.resize(N);
	query.resize(Q);

	for(int i=0; i<N; i++){
		int x1, x2, y;	// x1, x2: 통나무의 시작 x 좌표와 끝 x 좌표, y: 통나무의 y 좌표
		std::cin >> x1 >> x2 >> y;
		logs[i] = {i, x1, x2, y};
	}

	for(int i=0; i<Q; i++){
		int a, b;	// query[i]: i 번째 질문 -> 한 통나무에서 다른 통나무로 한 번 이상의 점프로 이동이 가능하면 1, 아니면 0
		std::cin >> a >> b;
		query[i] = {a - 1, b - 1};	// 입력드로 들어오는 통나무 번호는 1부터 시작하므로 1 씩 뺌
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	return 0;
}