#include <iostream>
#include <vector>
#include <algorithm>

struct Coordinate{	// 좌표
	int y, x;	// y, x: 좌표
};

int N, l, M;	// N: 모눈종이의 크기, l: 그물의 길이, M: 물고기의 수
std::vector<Coordinate> v;	// v[i]: i 번째 물고기

int ans;	// ans: 잡을 수 있는 가장 많은 물고기의 마릿수

void sol(){

	int yLen, xLen;	// yLen: 그물의 세로 길이, xLen: 그물의 가로 길이

	for(int k=1; k<l/2; k++){	// 그물의 길이는 최소 1에서 최대 l/2 - 1

		yLen = k;
		xLen = l/2 - k;

		for(int j=0; j<M; j++){	// j: j 번째 물고기의 위치를 기준으로 그물 배치
			for(int m=0; m<=yLen; m++){	// m: 그물을 위로 m 만큼 움직임
				for(int n=0; n<=xLen; n++){	// n: 그물을 왼쪽으로 n 만큼 움직임

					Coordinate leftTop = {v[j].y - m, v[j].x - n};	// leftTop: 그물의 왼쪽 위 좌표
					Coordinate rightButtom = {leftTop.y + yLen, leftTop.x + xLen};	// rightButtom: 그물의 오른쪽 아래 좌표
			
					if(leftTop.y < 1 || leftTop.x < 1 || rightButtom.y > N || rightButtom.x > N) continue;	// 그물이 모눈종이를 벗어나는 경우 continue

					int fishCnt = 0;	// fishCnt: 그물에 잡힌 물고기의 수

					for(int i=0; i<M; i++){
						Coordinate curFish = v[i];	// curFish: 잡을 수 있는지 판단하는 물고기

						if(leftTop.y <= curFish.y && leftTop.x <= curFish.x && rightButtom.y >= curFish.y && rightButtom.x >= curFish.x) fishCnt++;	// 잡을 수 있음
					}

					ans = std::max(ans, fishCnt);	// 물고기의 마릿수 갱신
				}
			}
		}
	}

	return;
}

void input(){

	std::cin >> N >> l >> M;

	v.resize(M);

	for(int i=0; i<M; i++){
		int y, x;	// y, x: 물고기의 좌표
		std::cin >> y >> x;
		v[i] = {y, x};
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