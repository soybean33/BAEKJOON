#include <iostream>
#include <queue>

struct Coordinate{
	int N, M;	// N, M: N번 원판의 M번째 수
};

int N, M, T;	// N: 원판의 수, M: 원판에 적혀있는 숫자의 개수, T: 회전 수
int disk[55][55];	// disk[i][j]: i번 원판의 j번째 적힌 수
int diskIdx[55];	// diskIdx[i]: i번 원판의 12시 방향 인덱스
int ans;	// ans: 원판을 T번 회전시킨 후 원판에 적힌 수의 합

// 방향 벡터
int dirN[4] = { -1, 0, 1, 0 };
int dirM[4] = { 0, -1, 0, 1 };

void sol() {

	while (T > 0) {
		int x, d, k;	// x: x의 배수의 원판 회전, d: 회전 방향 -> 0 시계 1 반시계, k: k칸 회전
		std::cin >> x >> d >> k;
		
		// 원판 회전
		for (int i = x; i <= N; i += x) {
			if (d == 0) {	// 시계 방향
				diskIdx[i] = (diskIdx[i] + (-1 * k) + M) % M;	// 12시 인덱스는 --
			}
			else if (d == 1) {	// 반시계 방향
				diskIdx[i] = (diskIdx[i] + k) % M;	// 12시 인덱스는 ++
			}
		}

		// 같은 수 탐색
		int visited[55][55] = { 0, };	// visited[i][j]: i번째 원판의 j번째 수의 방문 여부
		int flag = 0;	// flag: 인접하면서 같은 수 있으면 1, 없으면 0
		for (int j = 1; j <= N; j++) {
			for (int i = 0; i < M; i++) {
				if (disk[j][i] == 0) continue;	// 이미 수가 지워진 곳이면 continue
				if (visited[j][i] != 0) continue;	// 이미 방문한 곳 continue

				int curNum = disk[j][i];	// curNum: 인접한 수를 구하려는 기준
				std::queue<Coordinate> q;	// q: bfs를 사용하기 위한 queue

				q.push({ j, i });	// 현재 위치 넣기
				visited[j][i] = 1;

				while (!q.empty()) {
					// curN, curM: N번 원판의 M번째 위치 (기준)
					int curN = q.front().N;
					int curM = q.front().M;
					q.pop();

					for (int dir = 0; dir < 4; dir++) {
						// newN, newM: N번 원판의 M번째 위치와 비교
						int newN = curN + dirN[dir];	// 왼쪽 혹은 오른쪽
						int newM;
						if (dirN[dir] == 0) {	// 같은 원판
							newM = (curM + dirM[dir] + M) % M;
						}
						else {	// 밖이나 안쪽 원판
							newM = (curM + (diskIdx[newN]-diskIdx[curN]) + M) % M;
						}

						if (newN < 1 || newN > N) continue;	// 원판 없으면 continue
						if (visited[newN][newM] == 1) continue;	// 이미 확인한 곳이면 continue
						if (disk[newN][newM] != curNum) continue;	// 같은 수가 아니면 continue

						visited[newN][newM] = 1;	// 방문 체크

						disk[curN][curM] = 0;	// 인접함에 기준이 되는 수 지우기
						disk[newN][newM] = 0;	// 인접한 수 지우기
						
						flag = 1;	// 인접한 수가 있었으므로 flag = 1

						q.push({ newN, newM });	// 다음 인접한 수를 찾기 위하여 push
					}
				}				
			}
		}	
		if (flag == 0) {	// 인접하면서 같은 수가 없었다면
			float cnt = 0;	// cnt: 원판에 남아있는 수의 개수
			float sum = 0;	// sum: 원판에 남아있는 수의 합
			for (int j = 1; j <= N; j++) {
				for (int i = 0; i < M; i++) {
					if (disk[j][i] == 0) continue;
					cnt++;
					sum += disk[j][i];
				}
			}
			float avg = sum / cnt;	// avg: 원판에 적힌 수의 평균

			for (int j = 1; j <= N; j++) {
				for (int i = 0; i < M; i++) {
					if (disk[j][i] == 0) continue;
					if (disk[j][i] < avg)	// 평균보다 작으면 1 더하기
						disk[j][i]++;
					else if (disk[j][i] > avg)	// 평균보다 크면 1 빼기
						disk[j][i]--;
				}
			}
		}
		T--;	// 회전 횟수 감소
	}

	// 원판에 적힌 수의 합
	for (int j = 1; j <= N; j++) {
		for (int i = 0; i < M; i++) {
			ans += disk[j][i];
		}
	}

	return;
}

void input() {
	std::cin >> N >> M >> T;
	for (int j = 1; j <= N; j++) {
		for (int i = 0; i < M; i++) {
			std::cin >> disk[j][i];
		}
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << ans;

	return 0;
}