#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

struct Coordinate{	// 좌표
	int y, x;	// y, x: 좌표
};

struct SharkDir{	// 상어의 우선 순위 방향
	int dir[4][4];	// dir[i][j]: 상어가 i 방향일 때 j 번째 우선 순위 방향
};

struct SharkSmell{	// 상어의 냄새
	int sharkNum;	// sharkNum: 상어 번호
	int remainTime;	// remainTime: 냄새가 사라지기 까지 남은 시간
};

int N, M, K;	// N: 격자의 한 변의 크기, M: 상어의 수, K: 냄새가 사라지는 시간
int MAP[20][20];	// MAP[i][j]: i 행 j 열의 상어 번호
std::vector<int> shark;	// shark[i]: i 상어의 방향
std::vector<SharkDir> sharkDir;	// sharkDir[i]: i 상어의 우선 순위 방향
SharkSmell smell[20][20];	// smell[i][j]: i 행 j 열의 상어 냄새 정보

// 방향 벡터
int dirY[] = {-1, 1, 0, 0};
int dirX[] = {0, 0, -1, 1};

int ans;	// ans: 1번 상어만 격자에 남게 되기까지 걸리는 시간, 1000초가 넘어도 다른 상어가 격자에 남아 있으면 -1

void reset(){	// 초기화

	// 상어 냄새 초기화
	for(int j=0; j<N; j++){
		for(int i=0; i<N; i++){
			smell[j][i] = {-1, 0};
		}
	}

	return;
}

void sol(){

	reset();

	int remainShark = M;	// remainShark: 남아 있는 상어의 수
	int time = 0;	// time: 시간

	while(remainShark != 1){	// 1번 상어만 격자에 남게 될 때 까지 반복

		if(time >= 1000) {	// 1000초가 넘은 경우 종료
			time = -1;
			break;
		}

		time++;

		// 모든 상어가 자신의 위치에 자신의 냄새를 뿌린다
		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				if(MAP[j][i] == -1) continue;	// 상어가 없는 칸 continue
				smell[j][i] = {MAP[j][i], K + 1};	// 냄새를 뿌리고 바로 감소하므로 K + 1 시간을 갖음
			}
		}

		// 냄새 감소
		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				if(!smell[j][i].remainTime) continue;	// 냄새가 없는 칸 continue

				smell[j][i].remainTime--;	// 냄새가 사라지기 전까지 남은 시간 감소
				if(!smell[j][i].remainTime){	// 시간이 0 이라면
					smell[j][i] = {-1, 0};	// 냄새 사라짐
				}
			}
		}

		// 상어가 이동한다
		int tmpMAP[20][20];	// tmpMAP[i][j]: i 행 j 열로 이동한 상어 정보

		memset(tmpMAP, -1, sizeof(tmpMAP));

		for(int j=0; j<N; j++){
			for(int i=0; i<N; i++){
				if(MAP[j][i] == -1) continue;	// 상어가 없는 칸 continue

				int sharkNum = MAP[j][i];	// sharkNum: 이동할 상어 번호
				Coordinate curShark = {j, i};	// curShark; 이동할 상어 현재 위치
				Coordinate mySmell = {-1, -1};	// mySmell: 인접한 칸 중 냄새가 없는 칸이 없으면 자신의 냄새가 있는 칸으로 이동하기위한 좌표
				int mySmellDir;	// mySmellDir: 자신의 냄새로 이동하기 위한 방향

				bool flag = false;	// flag: 인접한 칸 중 아무 냄새가 없는 칸이 있으면 true

				for(int dir=0; dir<4; dir++){	// 인접한 4 방향 탐색
					Coordinate nextShark = {j + dirY[sharkDir[sharkNum].dir[shark[sharkNum]][dir]], i + dirX[sharkDir[sharkNum].dir[shark[sharkNum]][dir]]};	// nextShark: 상어가 이동할 좌표

					if(nextShark.y < 0 || nextShark.x < 0 || nextShark.y >= N || nextShark.x >= N) continue;	// 범위 벗어나면 continue

					if(!smell[nextShark.y][nextShark.x].remainTime){	// 냄새가 없는 칸이 있음
						if(tmpMAP[nextShark.y][nextShark.x] == -1) tmpMAP[nextShark.y][nextShark.x] = sharkNum;	// 다른 상어가 없는 경우
						else {	// 다른 상어가 있는 경우
							tmpMAP[nextShark.y][nextShark.x] = std::min(tmpMAP[nextShark.y][nextShark.x], sharkNum);	// 상어의 번호가 더 작은 상어가 우선권 가짐
							remainShark--;	// 번호가 더 큰 상어는 쫓겨남
						}
						shark[sharkNum] = sharkDir[sharkNum].dir[shark[sharkNum]][dir];
						flag = true;	// 인접한 칸 중 아무 냄새가 없는 칸 존재
						break;
					}

					if(mySmell.y == -1 && smell[nextShark.y][nextShark.x].sharkNum == sharkNum){	// 아무 냄새가 없는 칸이 없을 경우를 대비하여 자신의 위치가 있는 우선 순위 칸 저장
						mySmell = {nextShark.y, nextShark.x};
						mySmellDir = sharkDir[sharkNum].dir[shark[sharkNum]][dir];
					}
				}
				if(!flag){	// 인접한 칸 중 아무 냄새가 없는 칸이 없는 경우
					tmpMAP[mySmell.y][mySmell.x] = sharkNum;
					shark[sharkNum] = mySmellDir;
				}
			}
		}
		memcpy(MAP, tmpMAP, sizeof(MAP));	// 모든 상어의 이동을 마친 후 모두 갱신
	}

	if(time == -1) ans = -1;	// 1000초가 넘어도 다른 상어가 격자에 남아 있으면 -1
	else ans = time;

	return;
}

void input(){

	std::cin >> N >> M >> K;

	for(int j=0; j<N; j++){
		for(int i=0; i<N; i++){
			std::cin >> MAP[j][i];	// 상어 번호 입력
			MAP[j][i]--;	// 0번 상어 부터 시작
		}
	}

	shark.resize(M);

	for(int i=0; i<M; i++){
		std::cin >> shark[i];	// 상어 방향 입력
		shark[i]--;	// 0번 방향 부터 -> 상 하 좌 우 순서
	}

	sharkDir.resize(M);

	for(int k=0; k<M; k++){
		for(int j=0; j<4; j++){
			for(int i=0; i<4; i++){
				std::cin >> sharkDir[k].dir[j][i];	// k 상어의 우선 순위 방향
				sharkDir[k].dir[j][i]--;
			}
		}
	}

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