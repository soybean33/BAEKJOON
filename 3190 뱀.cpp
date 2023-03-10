#include <iostream>
#include <queue>
#include <deque>

struct Order {	// 명령
	int X;	// X: 게임 시작 후 명령이 내려지는 시간
	char C;	// C: 명령 종류
};

struct Coordinate {	// 좌표
	int y, x;
};

int N, K;	// N: 보드의 크기, K: 사과의 개수
int MAP[101][101];	// MAP[i][j]: i행 j열의 보드 정보, 0 빈칸 1 사과
int L;	// L: 뱀의 방향 변환 횟수
std::queue<Order> q;	// q: 명령
std::deque<Coordinate> snake;	// snake: 뱀 몸통 정보
int dir;	// dir: 뱀의 방향
int ans;	// ans: 게임 시작 후 경과 시간

// 방향 벡터 -> 우 하 좌 상
int dirY[] = { 0, 1, 0, -1 };
int dirX[] = { 1, 0, -1, 0 };

void sol() {
	Order order;	// order: 명령

	order = q.front();	// 첫 번째 명령 부터 시행
	q.pop();

	MAP[0][0] = 2;	// 초기 뱀의 위치 (0,0)
	snake.push_back({ 0,0 });	// 뱀 몸통 정보에 초기 정보 입력
	while (true) {		
		ans++;	// 시간 경과
		Coordinate head = snake.front();	// 뱀의 머리는 deque의 앞
		Coordinate tail = snake.back();	// 뱀의 꼬리는 deque의 뒤

		// 먼저 뱀의 몸 길이를 늘려 머리를 다음 칸에 위치
		head.y += dirY[dir];
		head.x += dirX[dir];

		if (head.x < 0 || head.y < 0 || head.x >= N || head.y >= N) return;	// 벽에 부딪혀 게임 끝
		if (MAP[head.y][head.x] == 2) return;	// 자기 자신의 몸과 부딪혀 게임 끝

		// 사과가 있다면
		if (MAP[head.y][head.x] == 1) {
			MAP[head.y][head.x] = 2;	// 사과가 없어지고 몸이 생김
			snake.push_front(head);	// 머리 정보 뱀의 봄통 정보에 추가 -> 머리는 deque의 앞
		}
		else {	// 사과가 없다면
			MAP[tail.y][tail.x] = 0;	// 꼬리가 위치한 칸을 바꿔줌
			MAP[head.y][head.x] = 2;	// 머리 이동
			snake.push_front(head);	// 머리 정보 수정
			snake.pop_back();	// 꼬리 정보 수정
		}			
		
		if (ans == order.X) {	// 명령의 시간이 되면
			if (order.C == 'D') {	// 오른쪽으로 회전
				dir = (dir + 1) % 4;
			}
			else {	// 왼쪽으로 회전
				dir = (dir - 1 + 4) % 4;
			}

			if (!q.empty()) {	// 다음 명령 뽑아 내기 -> 없다면 진행방향으로 계속 진행
				order = q.front();
				q.pop();
			}
		}
	}

	return;
}

void input() {
	std::cin >> N >> K;
	for (int k = 0; k < K; k++) {
		int y, x;
		std::cin >> y >> x;
		MAP[y-1][x-1] = 1;	// 좌표가 (1, 1) 부터 시작하므로 1씩 빼 줌
	}
	std::cin >> L;
	for (int l = 0; l < L; l++) {
		int X;
		char C;
		std::cin >> X >> C;
		q.push({ X, C });
	}

	return;
}

int main() {
	input();
	sol();
	std::cout << ans;

	return 0;
}