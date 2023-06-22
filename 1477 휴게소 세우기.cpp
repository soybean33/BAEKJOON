#include <iostream>
#include <vector>
#include <algorithm>

int N, M, L;	// N: 현재 휴게소의 개수, M: 더 지으려고 하는 휴게소의 개수, L: 고속도로의 길이
std::vector<int> v;	// v[i]: 위치를 기준으로 오름차순 정렬한 i 번째 휴게소 위치
int ans;	// ans: M 개의 휴게소를 짓고 난 후의 휴게소가 없는 구간의 최댓값의 최솟값

bool chk(int mid){

	int cnt = 0;	// cnt: 휴게소의 갯수

	for(int i=1; i<v.size(); i++){
		int dis = v[i] - v[i-1];	// dis: 두 휴게소 간의 거리
		cnt += dis / mid;	// 두 휴게소 간의 간격에 몇 개의 휴게소가 들어갈 수 있는가
		if(dis % mid == 0) cnt--;	// 원래 건물이 있는 위치 이므로 -1
	}

	return cnt > M;	// M개의 휴게소
}

void sol(){

	std::sort(v.begin(), v.end());	// 거리를 기준으로 오름차순 정렬

	int left = 1, right = L;	// left, right: 휴게소 간의 간격

	while(left <= right){
		int mid = (left + right) / 2;	// mid: 휴게소 간의 간격

		if(chk(mid)){	// M개의 휴게소를 지어서 답이 mid가 될 수 있으면 true
			left = mid + 1;	// 더 넓은 간격으로 휴게소 짓기
		}
		else{
			ans = mid;
			right = mid - 1;	// 더 좁은 간격으로 휴게소 짓기
		}
	}

	return;
}

void input(){

	std::cin >> N >> M >> L;

	v.resize(N);

	for(int i=0; i<N; i++) std::cin >> v[i];

	v.push_back(0);	// 시작점
	v.push_back(L);	// 끝점

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	std::cout << ans;

	return 0;
}