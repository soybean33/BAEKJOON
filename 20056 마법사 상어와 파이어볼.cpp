#include <iostream>
#include <vector>

struct FireBall {
	int m, s, d;	// m: 질량, s: 속력, d: 방향
};

int N, M, K;	// N: 격자의 한 변의 길이, M: 발사하는 파이어 볼
std::vector<FireBall> MAP[51][51];	// MAP[i][j]: i행 j열에 있는 파이어볼
int ans;	// ans: 남아있는 파이어볼 질량의 합

// 방향 벡터
int dirY[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dirX[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

void sol() {
	for (int k = 0; k < K; k++) {

		std::vector<FireBall> tmpMAP[51][51];	// tmpMAP[i][j]: i행 j열의 임시 저장소

		// 이동
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < N; i++) {
				if (MAP[j][i].empty()) continue;	// 이동할 파이어볼이 없으면 continue

				while (!MAP[j][i].empty()) {	// 해당 칸의 모든 파이어 볼에 대하여 이동
					FireBall now = MAP[j][i].back();
					MAP[j][i].pop_back();

					// newY, newX: d 방향으로 s 만큼 이동
					int newY = (j + dirY[now.d] * now.s + N * 300) % N;
					int newX = (i + dirX[now.d] * now.s + N * 300) % N;

					tmpMAP[newY][newX].push_back(now);	// 임시 저장소에 넣기

				}				
			}
		}

		// 같은 칸 파이어볼 모두 하나로 합쳐짐
		for (int j = 0; j < N; j++) {
			for (int i = 0; i < N; i++) {
				if (tmpMAP[j][i].empty()) continue;	// 합칠 파이어볼이 없으면 continue

				if (tmpMAP[j][i].size() < 2) {	// 2개 이하 -> 즉 1개라면
					MAP[j][i].push_back(tmpMAP[j][i].back());	// MAP[j][i]에 복사만 함
					tmpMAP[j][i].pop_back();
					continue;
				}

				int num = tmpMAP[j][i].size();	// num: 해당 칸의 파이어볼의 수
				int dirFlag = 0;	// dirFlag: 0이면 모두 짝수거나 홀수, 1이면 그렇지 않음
				int dir = tmpMAP[j][i][0].d % 2;	// dir: 첫 번째 파이어볼을 기준으로 짝수 or 홀수
				int newM = 0;	// newM: 합쳐진 파이어볼 질량의 합 / 5
				int newS = 0;	// newS: 합ㅊ진 파이어볼 속력의 합 / 합쳐진 파이어볼의 개수
				while (!tmpMAP[j][i].empty()) {	// j행 i열의 모든 파이어볼에 대하여 조사
					FireBall now = tmpMAP[j][i].back();
					tmpMAP[j][i].pop_back();

					if (dir != now.d % 2)	// 방향이 첫 번째 파이어볼과 다르다면
						dirFlag = 1;	// dirFlag = 1
					newM += now.m;
					newS += now.s;
				}
				
				newM = newM / 5;

				if (newM == 0) continue;	// 질량이 0인 파이어볼은 소멸

				newS = newS / num;

				for (int d = 0; d < 8; d++) {
					if (d % 2 != dirFlag) continue;	// dirFlag가 1이면 1 3 5 7, 0이면 0 2 4 6

					MAP[j][i].push_back({ newM, newS, d });
				}
			}
		}
	}

	// 남아있는 파이어볼 질량의 합 구함
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (MAP[j][i].empty()) continue;

			while (!MAP[j][i].empty()) {
				ans += MAP[j][i].back().m;
				MAP[j][i].pop_back();
			}
		}
	}

}

void input() {
	std::cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		std::cin >> r >> c >> m >> s >> d;
		MAP[r - 1][c - 1].push_back({ m, s, d });
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << ans;
	return 0;
}