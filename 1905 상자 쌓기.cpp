#include <iostream>
#include <vector>
#include <algorithm>

struct Coordinate {	// Coordinate: 좌표
	int y, x;	// y, x: 좌표
};

struct Box {	// Box: 쌓인 상자 정보
	Coordinate leftBottom;	// leftBottom: 왼쪽 아래
	Coordinate rightTop;	// rightTop: 오른쪽 위
	long long height;	// height: 상자의 고도
};

int Lx, Ly, N;	// Lx: 창고의 가로 길이, Ly: 창고의 세로 길이, N: 입고되는 상자의 개수
std::vector<Box> box;	// box[i]: i 번째로 입고되는 상자 정보
long long ans;	// ans: 가장 높은 위치의 고도

void solution() {

	for(int i=0; i<N; ++i) {
		Box currBox = box[i];	// currBox: 이번에 쌓을 상자
		long long prevHeighest = 0;	// prevHeighest: 이번에 쌓을 상자가 쌓을 위치에 가장 높은 상자의 고도

		for(int j=0; j<i; ++j){
			Box prevBox = box[j];	// prevBox: 쌓인 상자

			// 상자가 겹치지 않는 경우 continue
			if(currBox.rightTop.y <= prevBox.leftBottom.y || currBox.rightTop.x <= prevBox.leftBottom.x) continue;
			if(currBox.leftBottom.y >= prevBox.rightTop.y || currBox.leftBottom.x >= prevBox.rightTop.x) continue;

			prevHeighest = std::max(prevHeighest, prevBox.height);	// 상자가 겹치는 경우 가장 높은 고도 계산
		}

		box[i].height += prevHeighest;	// 상자 쌓음
		ans = std::max(ans, box[i].height);	// 가장 높은 위치의 고도 게산
	}

	return;
}

void input() {

	std::cin >> Lx >> Ly >> N;

	box.assign(N, {0, 0, 0, 0, 0});	// 상자 공간 할당

	for(int i=0; i<N; ++i) {
		int lx, ly, lz, px, py;	// lx: 상자의 가로 길이, ly: 상자의 세로 길이, lz: 상자의 높이 길이, px, py: 상자의 가장 남서쪽에 있는 좌표
		std::cin >> lx >> ly >> lz >> px >> py;
		box[i] = {{py, px}, {py+ly, px+lx}, lz};
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	input();

	solution();

	std::cout << ans;

	return 0;
}