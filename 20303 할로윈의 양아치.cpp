#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Group{	// 그룹
	int candyNum;	// candyNum: 그룹의 사탕 수
	int childNum;	// childNum: 그룹의 아이들의 수
};

int N, M, K;	// N: 거리에 있는 아이들의 수, M: 아이들의 친구 관계 수, K: 울음소리가 공명하기 위한 최소 아이의 수
std::vector<int> C;	// C[i]: i 번째 아이의 사탕의 수

std::vector<int> parents;	// parents[i]: i 아이의 그룹

int answer;	// answer: 스브러스가 어른들에게 들키지 않고 아이들로부터 뺏을 수 있는 최대 사탕의 수

// 그룹 찾기
int Find(int x){	// x: 그룹을 찾을 원소
	if(parents[x] == x) {return x;}
	return parents[x] = Find(parents[x]);
}

// 그룹 합치기
void Union(int a, int b){	// a, b: 그룹을 합칠 원소

	// pa, pb: 두 원소의 그룹
	int pa = Find(a);
	int pb = Find(b);

	if(pa == pb) return;	// 같은 그룹이라면 return

	parents[pb] = pa;	// 다른 그룹이라면 그룹 합침

	return;
}

void Solution(){

	std::unordered_map<int, Group> um;	// um[i]: i 그룹의 그룹 정보 -> 사탕 수, 아이들의 수

	for(int i=0; i<N; ++i){
		int group = Find(i);	// group: i 아이의 그룹

		if(um.find(group) != um.end()) {um[group] = {um[group].candyNum + C[i], um[group].childNum + 1};}	// 이 그룹이 um에 포함되어 있다면
		else{um[group] = {C[i], 1};}	// 처음 보는 그룹이라면
	}

	std::vector<Group> groups;	// groups[i]: i 번째 그룹

	for(const std::pair<int, Group>& group : um) {	// group: 그룹 정보
		groups.push_back(group.second);
	}

	int groupSize = groups.size();	// groupSize: 그룹 사이즈

	std::vector<std::vector<int>> dp;	// dp[i][j]: i 번째 그룹이 j 명의 아이들에게 사탕을 뺏겼을 때 최대 사탕의 개수
	dp.assign(groupSize+1, std::vector<int>(K+1, 0));

	for(int i=0; i<groupSize; ++i){
		for(int j=(K-1); j>=0; --j){
			if(j-groups[i].childNum >= 0) {	// 울음소리가 공명하기 전
				dp[i+1][j] = std::max(dp[i][j], dp[i][j-groups[i].childNum] + groups[i].candyNum);
			}
			else{	// 울음소리가 공명
				dp[i+1][j] = dp[i][j];
			}
			answer = std::max(answer, dp[i+1][j]);	// 스브러스가 어른들에게 들키지 않고 아이들로부터 뺏을 수 있는 최대 사탕의 수
		}
	}

	return;
}

void Input(){

	std::cin >> N >> M >> K;

	C.assign(N, 0);

	for(int i=0; i<N; ++i) {std::cin >> C[i];}	// i 번째 아이의 사탕의 수 입력

	parents.assign(N, 0);
	for(int i=0; i<N; ++i){
		parents[i] = i;	// 소속 정보 초기화
	}

	for(int i=0; i<M; ++i){
		int a, b;	// a, b: 두 아이들 번호
		std::cin >> a >> b;
		--a;
		--b;

		Union(a, b);	// 친구의 친구는 친구다
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
