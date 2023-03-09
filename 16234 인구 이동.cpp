#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>

struct Coordinate {
	int y, x;
};

int N;	// N: 땅의 한 변의 길이
int L, R;	// 인구 차이 L명 이상, R명 이하
int A[51][51];	// A[j][i]: j행 i열의 인구 수
int cnt;	// cnt: 인구 이동이 발생하는 날의 수

// 방향 벡터 -> 꼭 4가지 방향 모두 해야하는가? -> yes!!
int dirY[] = { 1, 0, -1, 0 };
int dirX[] = { 0, 1, 0, -1 };

void sol() {
	while (true) {	// 인구이동이 없을 때 까지 계속하여 반복
		int visited[51][51] = { 0, };	// visited[j][i]: j행 i열의 확인 여부
		std::vector<Coordinate> linked[51][51];	// linked[j][i]: j행 i열의 마을과 연결된 마을의 좌표
		int sum[51][51] = { 0, };	// sum[j][i]: j행 i열과 연결된 나라의 인구 수 합
		int flag = 0;	// flag: 인구 이동 여부, 0 없음, 1 있음

		// j행 i열의 나라에 대하여
		// linked[j][i]에 국경을 개방한 나라의 좌표 (j, i)가 들어 있음
		// sum[j][i]와 연결된 나라의 인구수의 합

		// 국경 개방 및 개방한 나라의 인구수 합
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < N; i++) {
				if (visited[j][i] == 1) continue;	// 이미 확인한 나라 continue

				visited[j][i] = 1;	// 방문 확인
				sum[j][i] = A[j][i];	// 초기 값 설정 -> j행 i열 나라는 국경을 개방하지 않아도 인구수는 A[j][i]
				
				std::queue<Coordinate> q;	// q: 인구수를 확인해 볼 인접한 나라
				q.push({ j, i });

				while (!q.empty()) {
					Coordinate now = q.front();	// now: 현재 나라의 좌표
					q.pop();

					for (int dir = 0; dir < 4; dir++) {	// 다음 방문할 나라를 4가지 방향으로 확인
						int nextY = now.y + dirY[dir];
						int nextX = now.x + dirX[dir];

						if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= N) continue;	// 땅의 범위를 벗어나면 continue
						if (visited[nextY][nextX] != 0) continue;	// 이미 확인했던 나라는 continue

						int diff = std::abs(A[now.y][now.x] - A[nextY][nextX]);	// now 나라와 next 나라간 인구수 차이 계산

						if (!(diff >= L && diff <= R)) continue;	// 인구 차이 밖이면 continue

						flag = 1;	// 인구 차이가 지정된 범위 안쪽이면 무조건 인구 이동이 있음 -> flag = 1
						q.push({ nextY, nextX });
						visited[nextY][nextX] = 1;
						sum[j][i] += A[nextY][nextX];	// j행 i열에 인구수 누적해서 더함
						linked[j][i].push_back({ nextY, nextX });
					}
				}
			}
		}

		if (flag == 0)	// 인구 이동 없었으면 while문 종료
			break;
		cnt++;
		
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < N; i++) {
				if (sum[j][i] == 0) continue;

				int div = sum[j][i] / (linked[j][i].size() + 1);	// div: 인구 이동은 (연합의 인구수) / (연합을 이루고 있는 나라의 개수)

				A[j][i] = div;	// linked에는 j행 i열 나라에 대한 좌표가 없으므로 먼저 넣어줌

				for (int v = 0; v < linked[j][i].size(); v++) {	// linked에 저장된 나라에 대하여 인구수 분배
					A[linked[j][i][v].y][linked[j][i][v].x] = div;
				}

			}
		}
	}

	return;
}

void input() {
	std::cin >> N;
	std::cin >> L >> R;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			std::cin >> A[j][i];
		}
	}

	return;
}

void reset() {
	memset(A, 0, sizeof(A));
	cnt = 0;

	return;
}

int main() {
	reset();
	input();
	sol();
	std::cout << cnt;

	return 0;
}