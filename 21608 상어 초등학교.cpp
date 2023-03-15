#include <iostream>
#include <queue>

struct Prefer{	// 자리 선호도
	int likeCnt;	// 1. 좋아하는 학생이 인접한 칸에 가장 많은 칸
	int emptyCnt;	// 2. 비어있는 칸이 가장 많은 칸
	int y, x;	// 3. 행의 번호가 가장 작은칸, 열의 번호가 가장 작은 칸

	bool operator < (Prefer next) const {
		if(likeCnt > next.likeCnt) return false;
		if(likeCnt < next.likeCnt) return true;

		if(emptyCnt > next.emptyCnt) return false;
		if(emptyCnt < next.emptyCnt) return true;

		if(y < next.y) return false;
		if(y > next.y) return true;

		if(x < next.x) return false;
		if(x > next.x) return true;

		return false;
	}
};

int N;	// N: 교실 한 변의 길이
int classRoom[20][20];	// classRoom[i][j]: i 행 j 열에 앉은 학생 번호
int like[401][4];	// like[i][j]: i 행생이 좋아하는 학생의 번호
int order[401];	// order[i]: i번째 학생의 번호
int ans;	// ans: 학생들의 만족도의 총 합

// 방향 벡터
int dirY[] = {-1, 0, 1, 0};
int dirX[] = {0, -1, 0, 1};

void sol(){
	for(int o=0; o<N*N; o++){
		int studentNum = order[o];	// studentNum: 자리를 정할 학생의 번호

		std::priority_queue<Prefer> pq;	// pq: 규칙에 따라 정해지는 학생 자리 정보

		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				if(classRoom[j][i] != 0) continue;	// 이미 j행 i열에 학생이 앉아 있다면 continue

				int likeCnt = 0;	// likeCnt: 인접한 칸의 좋아하는 학생 수
				int emptyCnt = 0;	// emptyCnt: 비어있는 칸의 좋아하는 학생 수

				for(int dir=0; dir<4; dir++){	// 인접한 칸에 대하여 조사
					int nextY = j + dirY[dir];
					int nextX = i + dirX[dir];

					if(nextY < 0 || nextX < 0 || nextY >= N || nextX >=N) continue;	// 범위 벗어나면 continue

					if(classRoom[nextY][nextX] != 0){	// 인접한 칸에 학생이 있다면
						for(int l=0; l<4; l++){	// 좋아하는 4명의 학생과 비교
							if(like[studentNum][l] == classRoom[nextY][nextX]){	// 좋아하는 학생이 있으면
								likeCnt++;
								break;
							}
						}
					}else{	// 인접한 칸에 학생이 없다면
						emptyCnt++;
					}
				}
				pq.push({likeCnt, emptyCnt, j, i});	// 우선 순위 큐에 넣음
			}
		}
		int seatY = pq.top().y;	// seatY: 가장 선호하는 자리의 y좌표
		int seatX = pq.top().x;	// seatX: 가장 선호하는 자리의 x좌표
		classRoom[seatY][seatX] = studentNum;	// 해당 자리에 학생 자리 정함
	}

	// 모든 학생의 자리 배치 후 만족도 조사
	for(int j=0; j<N; j++){
		for(int i=0; i<N; i++){
			int studentNum = classRoom[j][i];	// studentNum: 학생 번호
			int cnt = 0;	// cnt: 인접한 칸의 좋아하는 학생 수
			for(int dir = 0; dir < 4; dir++){	// 인접한 4가지 방향 중
				int nextY = j + dirY[dir];
				int nextX = i + dirX[dir];

				if(nextY < 0 || nextX < 0 || nextY >= N || nextX >= N) continue;	// 범위 벗어나면 continue

				for(int l=0; l<4; l++){
					if(like[studentNum][l] == classRoom[nextY][nextX]){	// 좋아하는 학생이라면
						cnt++;
						break;
					}
				}
			}

			// 종아하는 학생 수에 따른 만족도 점수 계산
			if(cnt == 0)
				ans += 0;
			else if (cnt == 1)
				ans += 1;
			else if (cnt == 2)
				ans += 10;
			else if (cnt == 3)
				ans += 100;
			else if (cnt == 4)
				ans += 1000;
		}
	}

	return;
}

void input(){
	std::cin >> N;
	for(int j=0; j<N*N; j++){
		std::cin >> order[j];	// 순서에 따라 학생 번호 입력
		for(int i =0; i<4; i++){	// 4명의 좋아하는 학생의 번호
			std::cin >> like[order[j]][i];
		}
	}

	return;
}

int main(){
	input();
	sol();
	std::cout << ans;
	
	return 0;
}