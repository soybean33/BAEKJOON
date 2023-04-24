#include <iostream>
#include <algorithm>

int n, m;	// n: 도시의 수, m: 버스의 수
int arr[101][101];	// arr[i][j]: i 도시에서 j 도시로 가는데 필요한 최소 버스 비용

void sol() {
	for (int t = 1; t <= n; t++) {	// t: 경유지
		for (int a = 1; a <= n; a++) {	// a: 출발지
			for (int b = 1; b <= n; b++) {	// b: 도착지
				arr[a][b] = std::min(arr[a][b], arr[a][t] + arr[t][b]);	// 플로이드
			}
		}
	}

	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= n; i++) {
			if (arr[j][i] == 10e8) std::cout << "0 ";	// j 역에서 i 역으로 갈수 없는 경우 0
			else std::cout << arr[j][i] << ' ';	// j 역에서 i 역으로 갈 수 있는 최소 비용
		}
		std::cout << std::endl;
	}

	return;
}

void input() {
	std::cin >> n >> m;

	for (int j = 0; j <= n; j++) {
		for (int i = 0; i <= n; i++) {
			if (j == i) arr[j][i] = 0;	// 시작 도시와 도착 도시가 같은 경우 0
			else arr[j][i] = 10e8;	// j 도시에서 i 도시로 가는 비용 초기화
		}
	}

	for (int i = 0; i < m; i++) {
		int a, b, c;	// a: 출발 도시, b: 도착 도시, c: 비용
		std::cin >> a >> b >> c;
		arr[a][b] = std::min(arr[a][b], c);	// 시작 도시와 도착 도시를 연결하는 노선은 하나가 아닐 수 있음
	}
	
	return;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();
	sol();

	return 0;
}