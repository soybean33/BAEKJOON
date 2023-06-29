#include <iostream>
#include <vector>
#include <algorithm>

const int INF = 100'000;	// 될 수 없는 값

int n, k;	// n: 사건의 개수, k: 알고 있는 사건의 전후 관계의 개수
std::vector<std::vector<int>> arr;	// arr[i][j]: i 사건이 j 사건 보다 앞에 발생하였다면 1
int s;	// s: 사건의 전후 관계를 알고 싶은 사건 쌍의 수
std::vector<std::pair<int, int>> query;	// query[i]: i 번째로 알고 싶은 사건 쌍

void solution(){

	// 플로이드
	for(int l=0; l<n; l++){
		for(int j=0; j<n; j++){
			for(int i=0; i<n; i++){
				arr[j][i] = std::min(arr[j][i], arr[j][l] + arr[l][i]);
			}
		}
	}

	for(int i=0; i<s; i++){
		std::pair<int, int> curQuery = query[i];	// curQuery: 알고 싶은 사건의 쌍

		if(arr[curQuery.first][curQuery.second] != INF) std::cout << "-1\n";	// 앞에 있는 번호의 사건이 먼저 일어남
		else{
			if(arr[curQuery.second][curQuery.first] != INF) std::cout << "1\n";	// 뒤에 있는 번호의 사건이 먼저 일어남
			else std::cout << "0\n";	// 유추할 수 없음 -> 양방향 모두 INF 의 값
		}
	}

	return;
}

void input(){

	std::cin >> n >> k;

	arr.assign(n, std::vector<int>(n, INF));	// 초기값 100,000을 갖도록 배열 초기화

	for(int i=0; i<k; i++){
		int pre, next;	// pre: 먼저 일어난 사건, next: 나중에 일어난 사건
		std::cin >> pre >> next;
		arr[pre-1][next-1] = 1;
	}

	std::cin >> s;
	query.assign(s, std::pair<int, int>(0, 0));	// 사건 초기화

	for(int i=0; i<s; i++){
		int pre, next;	// pre: 먼저 일어난 사건, next: 나중에 일어난 사건
		std::cin >> pre >> next;
		query[i] = {pre-1, next-1};
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	return 0;
}