#include <iostream>
#include <vector>
#include <string>

struct Coordinate{	// Coordinate: 좌표
	int y, x;	// y, x: 좌표
};

std::vector<std::vector<int>> MAP;	// MAP[i][j]: i 행 j 열의 값
std::vector<std::vector<bool>> row;	// row[i][j]: i 행의 j 값이 있으면 true
std::vector<std::vector<bool>> column;	// column[i][j]: i 열에 j 값이 있으면 true
std::vector<std::vector<bool>> square;	// square[i][j]: i 번 사각형에 j 값이 있으면 true

bool flag = false;	// flag: 정답을 찾으면 true

void Dfs(int n) {	// n: 탐색 순서

	if(n == 81) {	// 모두 탐색 했다면

		flag = true;	// 정답을 찾음

		return;
	}

	Coordinate curr = {n / 9, n % 9};	// curr: 현재 탐색 순서를 좌표 값으로 변경
	int squareNum = (curr.y / 3) * 3 + (curr.x / 3);	// squareNum: 탐색하는 사각형의 번호

	if(MAP[curr.y][curr.x] != 0) {Dfs(n+1);}	// 빈 칸이 아니라면 다음 순서 탐색
	else{	// 빈 칸인 경우
		for(int i=1; i<=9; ++i){	// 1 부터 9 까지의 값을 넣어봄
			if(row[curr.y][i] == true) {continue;}	// 현재 행에 이미 i 값이 있다면 continue
			if(column[curr.x][i] == true) {continue;}	// 현재 열에 이미 i 값이 있다면 continue
			if(square[squareNum][i] == true) {continue;}	// 현재 사각형에 이미 i 값이 있다면 continue

			// 값 채움
			row[curr.y][i] = true;
			column[curr.x][i] = true;
			square[squareNum][i] = true;
			MAP[curr.y][curr.x] = i;

			Dfs(n + 1);	// 다음 칸 탐색

			if(flag == true) {return;}	// 정답을 찾았다면 원래 상태로 되돌리지 않고 return

			// 값 원래 상태도 되돌림
			MAP[curr.y][curr.x] = 0;
			square[squareNum][i] = false;
			column[curr.x][i] = false;
			row[curr.y][i] = false;		
		}
	}

	return;
}

void Solution(){

	Dfs(0);

	return;
}


void Input(){

	MAP.assign(9, std::vector<int>(9, 0));
	row.assign(9, std::vector<bool>(10, false));
	column.assign(9, std::vector<bool>(10, false));
	square.assign(9, std::vector<bool>(10, false));

	for(int y=0; y<9; ++y){
		std::string S;	// S: 한 행을 나타내는 문자열
		std::cin >> S;
		for(int x=0; x<9; ++x){
			int n = S[x] - '0';	// n: y 행 x 열의 값

			MAP[y][x] = n;
			
			if(n == 0) {continue;}

			row[y][n] = true;
			column[x][n] = true;
			square[(y / 3) * 3 + (x / 3)][n] = true;
		}
	}

	return;
}


int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	for(int y=0; y<9; ++y){
		for(int x=0; x<9; ++x){
			std::cout << MAP[y][x];
		}
		std::cout << '\n';
	}

	return 0;
}