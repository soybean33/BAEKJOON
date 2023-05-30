#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

struct Coordinate{	// 좌표
	int y, x;	// y, x: y 좌표 x 좌표
};

int N;	// N: 마을의 크기
char MAP[50][50];	// MAP[i][j]: 마을의 i행 j열의 정보 -> P 우체국, K, 집, .: 목초지
int height[50][50];	// height[i][j]: 마을의 i행 j열의 고도
int houseCnt;	// houseCnt: 마을에 있는 집의 개수
std::set<int> heightSet;	// heightSet: 마을에 존재하는 고도의 집합
std::vector<int> v;	// v[i]: 마을에 위치하는 고도의 집합의 i 번째 고도
int visited[50][50];	// visited[i][j]: 마을의 i행 j열 방문 정보

int left, right;	// left, right: 마을에서 이동가능한 고도 v[left] ~ v[right]

Coordinate postOffice;	// postOffice: 우체국의 좌표 -> 시작 위치

// 방향 벡터 -> 8 방향
int dirY[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dirX[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int ans = 21e8;	// ans: 가장 작은 피로도

void sol(){

	for(std::set<int>::iterator it = heightSet.begin(); it != heightSet.end(); ++it){
		v.push_back(*it);	// 집합의 정보에 인덱스로 접근하기 위하여 벡터에 저장
	}

	while(left < v.size()){	// 고도의 left 인덱스가 없을 때 까지

		if(v[right] < height[postOffice.y][postOffice.x]){	// 우체국에서 출발할 수 있을 때 까지 right 인덱스 증가
			right++;
			continue;
		}

		if(v[left] > height[postOffice.y][postOffice.x]) break;	// 우체국에서 출발할 수 없는 경우 종료

		memset(visited, 0, sizeof(visited));	// 방문 정보 초기화

		std::queue<Coordinate> q;	// q: 방문한 위치 정보를 담고 있는 큐
		q.push(postOffice);
		visited[postOffice.y][postOffice.x] = 1;

		int leftHouse = houseCnt;	// leftHouse: 방문해야하는 남은 집의 개수

		while(!q.empty()){

			Coordinate cur = q.front();	// cur: 현재 집의 위치
			q.pop();

			for(int dir=0; dir<8; dir++){
				Coordinate next = {cur.y + dirY[dir], cur.x + dirX[dir]};	// next: 8가지 방향 탐색

				if(next.y < 0 || next.x < 0 || next.x >= N || next.y >= N) continue;	// 범위 벗어나면 continue

				if(height[next.y][next.x] < v[left] || height[next.y][next.x] > v[right]) continue;	// 인덱스에 의해 제한된 고도에 해당하지 않은 고도면 continue

				if(visited[next.y][next.x] != 0) continue;	// 이미 방문한 곳이면 continue
				
				if(MAP[next.y][next.x] == 'K') leftHouse--;	// 집에 방문

				q.push(next);
				visited[next.y][next.x] = 1;
			}

		}

		if(leftHouse == 0){	// 모든 집에 방문 하였다면
			ans = std::min(ans, v[right] - v[left]);	// 최소 피로도 갱신
			left++;	// 범위를 더 작게 설정
		}
		else{	// 모든 집에 방문하지 못했다면
			if(right < v.size() - 1) right++;	// 더 넓은 범위 탐색
			else break;	// 더 이상 넓은 범위를 탐색할 수 없음
		}
	}

	return;
}

void input(){

	std::cin >> N;

	for(int j=0; j<N; j++){
		std::string s;	// s: 마을의 i 행 정보
		std::cin >> s;
		for(int i=0; i<N; i++){
			MAP[j][i] = s[i];	// j행 i열 정보 입력

			if(MAP[j][i] == 'P') postOffice = {j, i};	// 우체국은 마을에 1개만 존재하는 시작점
			else if(MAP[j][i] == 'K') houseCnt++;	// 방문해야하는 집의 개수 세기
		}
	}

	for(int j=0; j<N; j++){
		for(int i=0; i<N; i++){
			std::cin >> height[j][i];	// 마을의 j행 i열의 고도
			heightSet.insert(height[j][i]);	// 고도 정보를 중복없이 오름차순으로 정렬하기 위하여 집합 사용
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