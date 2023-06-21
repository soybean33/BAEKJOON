#include <iostream>
#include <vector>
#include <cstring>

struct Coordinate{	// 좌표
	int y, x;	// y, x: 좌표
};

int MAP[9][9];	// MAP[i][j]: i 행 j 열의 숫자
std::vector<Coordinate> v;	// v[i]: i 번째 빈칸의 좌표
bool flag = false;	// false: 수도쿠가 완성되면 true

bool chk(Coordinate cur){	// cur: 칸을 채울 빈칸의 좌표

	bool numbers[10];	// numbers[i]: i 숫자가 중복되는지 판단
	memset(numbers, false, sizeof(numbers));

	for(int i=0; i<9; i++) {
		if(!MAP[cur.y][i]) continue;	// 빈 칸의 경우 continue
		if(numbers[MAP[cur.y][i]]) return false;	// 중복된 숫자가 있으면 false return
		numbers[MAP[cur.y][i]] = true;	// 숫자 표기
	}

	memset(numbers, false, sizeof(numbers));
	for(int j=0; j<9; j++) {
		if(!MAP[j][cur.x]) continue;	// 빈 칸의 경우 continue
		if(numbers[MAP[j][cur.x]]) return false;	// 중복된 숫자가 있으면 false return
		numbers[MAP[j][cur.x]] = true;	// 숫자 표기
	}

	// y, x: 3 x 3 칸의 왼쪽 위 좌표
	int y = (int)(cur.y / 3) * 3;
	int x = (int)(cur.x / 3) * 3;

	memset(numbers, false, sizeof(numbers));

	for(int j=0; j<3; j++){
		for(int i=0; i<3; i++){
			if(!MAP[y+j][x+i]) continue;	// 빈 칸의 경우 continue
			if(numbers[MAP[y+j][x+i]]) return false;	// 중복된 숫자가 있으면 false return
			numbers[MAP[y+j][x+i]] = true;	// 숫자 표기
		}
	}

	return true;
}

void DFS(int idx){	// idx: 숫자를 채울 idx 번째 빈 칸

	if(idx == v.size()){	// 모든 빈칸에 숫자가 채워지면
		flag = true;	// flag 참으로 바꿈
		return;
	}

	for(int i=1; i<=9; i++){	// 1 ~ 9 까지 숫자 중에 후보가 있음
		MAP[v[idx].y][v[idx].x] = i;	// 숫자 i를 넣음
		if(!chk(v[idx])){	// 타당성 체크하였을 때 false라면
			MAP[v[idx].y][v[idx].x] = 0;	// 다시 빈칸으로 바꿈
			continue;
		}
		else DFS(idx + 1);	// 다음 빈칸 채우기
		if(flag) return;	// 이미 모든 칸에 타당한 숫자를 채웠다면 숫자를 지우지 않고 return
		MAP[v[idx].y][v[idx].x] = 0;	// 다시 빈칸으로 복구
	}

	return;
}

void sol(){

	DFS(0);

	return;
}

void input(){

	for(int j=0; j<9; j++){
		for(int i=0; i<9; i++){
			std::cin >> MAP[j][i];
			if(!MAP[j][i]) v.push_back({j, i});	// 빈 칸 좌표 저장
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

	for(int j=0; j<9; j++){
		for(int i=0; i<9; i++){
			std::cout << MAP[j][i] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}