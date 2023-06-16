#include <iostream>
#include <vector>
#include <algorithm>

int N, M;	// N: 임국심사대의 수, M: 상근이와 친구들의 수
std::vector<int> T;	// T[i]: i 번째 입국 심사대가 심사를 하는데 걸리는 시간
int minTime = 21e8;	// minTime: 가장 짧은 시간이 소요되는 입국심사관의 시간
long long ans;	// ans: 상근이와 친구들이 심사를 마치는데 걸리는 시간의 최솟값

void sol(){

	long long left = 1, right = (long long)minTime * M;	// left, right: 이분 탐색

	while(left <= right){
		long long mid = (left + right) / 2;	// mid: 심사를 받는데 걸리는 시간

		long long tmp = 0;	// tmp: 심사를 받은 사람의 수
		for(int i = 0; i < N; i++){
			tmp += mid / T[i];
		}

		if(tmp >= M){	// 상근이와 친구들의 수보다 더 많은 사람이 심사를 받음
			right = mid - 1;
			ans = mid;
		}
		else left = mid + 1;	// 더 적은 사람이 심사를 받음 -> 답이 될 수 없는 경우
	}

	return;
}

void input(){

	std::cin >> N >> M;

	T.resize(N);

	for(int i=0; i<N; i++){
		std::cin >> T[i];
		minTime = std::min(minTime, T[i]);	// 최소 소요 입국심사관 시간 갱신
	}	

	return;
}

int main(){

	input();

	sol();

	std::cout << ans;

	return 0;
}