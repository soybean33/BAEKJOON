#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 계란의 수 1<=N<=8
std::vector<std::pair<int, int>> eggs;	// eggs[i]: i 번째 계란의 내구도와 무게

int answer;	// answer: 인범이가 깰 수 있는 계란의 최대 개수

void Dfs(int idx){	// idx: 계란 번호

	if(idx >= N){	// 모든 계란에 대해서 깨봄
		int cnt = 0;	// cnt: 깨진 계란의 개수
		for(const std::pair<int, int>& egg : eggs){	// egg: 계란 정보
			if(egg.first <= 0) {++cnt;}	// 계란이 깨졌으면 ++cnt
		}
		answer = std::max(answer, cnt);	// 최대로 깨진 계란 값 입력
		return;
	}

	if(eggs[idx].first <= 0) {Dfs(idx + 1);}	// 이미 깨져있는 계란이라면 다음 계란으로 넘어감
	else{
		bool flag = false;	// flag: 계란이 깨졌는지 확인
		for(int i=0; i<N; ++i){
			if(idx == i || eggs[i].first <= 0) {continue;}	// 자기 자신이거나, 이미 깨진 계란 continue

			// 계란 깨기
			eggs[i].first -= eggs[idx].second;
			eggs[idx].first -= eggs[i].second;

			flag = true;	// 계란을 깼음
			Dfs(idx + 1);	// 다음 계란

			// 깨진 계란 복구
			eggs[i].first += eggs[idx].second;
			eggs[idx].first += eggs[i].second;
		}
		if(flag == false) {Dfs(N);}	// 깰 수 있는 계란이 없었다면 종료
	}


	return;
}

void Solution(){

	Dfs(0);

	return;
}

void Input(){

	std::cin >> N;
	eggs.assign(N, std::pair<int, int>{0, 0});

	for(int i=0; i<N; ++i){
		std::cin >> eggs[i].first >> eggs[i].second;
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