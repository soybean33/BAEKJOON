#include <iostream>
#include <vector>
#include <stack>

int N;	// N: 빌딩의 개수
std::vector<int> H;	// H[i]: i 번째 빌딩의 높이
long long ans;	// ans: 옥상 정원을 확인할 수 있는 개수

void solution() {

	std::stack<int> building;	// building[i]: 옥상 정원을 확인할 수 있는 개수

	building.push(H[0]);	// 첫 번째 건물은 넣고 시작

	for (int i = 1; i < N; ++i) {	// 1 번 건물 부터 탐색
		while (!building.empty()) {	// 건물이 있을 경우
			if (building.top() > H[i]) break;	// 현재 건물보다 높은 건물 break
			building.pop();	// 낮거나 같은 건물 뺌
		}
		ans += building.size();	// 건물 추가
		building.push(H[i]);
	}


	return;
}

void input() {

	std::cin >> N;

	H.assign(N, 0);

	for (int i = 0; i < N; ++i) std::cin >> H[i];

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans;

	return 0;
}