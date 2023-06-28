#include <iostream>
#include <vector>

int N, M;	// N: 도시의 수, M: 여행 계획에 속한 도시들의 수
std::vector<int> v[201];	// v[i]: i 도시와 연결된 도시의 번호
std::vector<int> cityNum;	// cityNum[i]: 여행 계획
std::vector<int> parent;	// parent[i]: i 도시의 소속
bool flag;	// flag: 여행 목적 달성 여부

int Find(int now){	// now: 소속을 찾을 도시의 번호
	if(now == parent[now]) return now;	// 소속을 찾음
	return parent[now] = Find(parent[now]);	// 계속해서 소속 찾음
}

void Union(int a, int b){	// a, b: 같은 소속으로 합칠 도시 번호

	// pa, pb: 두 도시의 소속 정보
	int pa = Find(a);
	int pb = Find(b);

	if(pa == pb) return;

	// 같은 소속으로 합침
	parent[pa] = pb;

	return;
}

void solution(){

	parent.resize(N + 1);

	for(int i=0; i<N+1; i++) parent[i] = i;	// 소속 정보 초기화

	for(int j=1; j<=N; j++){	// j 도시와
		for(int i=0; i<v[j].size(); i++){	// v[j][i] 도시는 
			Union(j, v[j][i]);	// 연결되어 있으므로 같은 소속
		}
	}

	flag = true;

	int firstCityNum = parent[cityNum[0]];	// firstCityNum: 기준 도시 소속 

	for(int i=1; i<M; i++){
		if(Find(firstCityNum) != Find(cityNum[i])) {	// 비교하는 두 도시의 소속이 다르다면
			flag = false;	// flag를 false로 변경하고 종료
			return;
		}
	}

	return;
}

void input(){

	std::cin >> N >> M;

	for(int j=1; j<=N; j++){
		for(int i=1; i<=N; i++){
			int linked;	// linked: 연결 정보 -> 0: 연결이 되지 않음, 1: 연결이 됨
			std::cin >> linked;
			if(linked) v[j].push_back(i);	// 1 이면 연결 도시에 추가
		}
	}

	cityNum.resize(M);

	for(int i=0; i<M; i++) std::cin >> cityNum[i];	// 여행 계획

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	if(flag) std::cout << "YES";	// 가능한 경우
	else std::cout << "NO";	// 불가능한 경우

	return 0;
}