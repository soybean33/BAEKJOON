#include <iostream>
#include <string>
#include <cstring>

std::string scroll;	// scroll[i]: i 번째로 밟아야 하는 문자
std::string bridge[2];	// bridge[i]: 악마의 돌다리와 천사의 돌다리 -> 0: 악마의 돌다리, 1: 천사의 돌다리

int dp[100][2][20];	// dp[i][j][k]: j 돌다리의 ㅑ 번째 돌다리를 k 번째 문자로 밟았을 경우의 경우의 수
int ans;	// ans: 마법의 두루마리에 적힌 문자열의 순서대로 다리를 건너ㄷ갈 수 있는 방법의 수

int toCross(int idx, int bridgeNum, int scrollIdx){	// idx: 돌다리 순서, bridgeNum: 현재 밟고 있는 돌다리의 종류, scrollIdx: 밟아야 하는 문자의 인덱스
	if(scrollIdx == scroll.length()) return 1;	// 끝 발판 도착 -> 1가지 경우 완성

	int ret = dp[idx][bridgeNum][scrollIdx];	// ret: 현재까지 밟을 수 있는 경우
	if(ret != -1) return ret;	// 값이 있는 경우 return

	dp[idx][bridgeNum][scrollIdx] = 0;	// 0으로 초기화

	for(int i=idx; i<bridge[0].length(); i++){	// 다리 끝 까지 탐색
		if(bridge[bridgeNum][i] == scroll[scrollIdx]){	// 탐색하는 발판이 스크롤의 문자와 일치하는 경우
			dp[idx][bridgeNum][scrollIdx] += toCross(i + 1, !bridgeNum, scrollIdx + 1);	// 탐색
		}
	}

	return dp[idx][bridgeNum][scrollIdx];	// 탐색한 결과 return
}

void sol(){

	memset(dp, -1, sizeof(dp));	// -1로 초기화

	ans += toCross(0, 0, 0);	// 악마의 돌다리를 먼저 밟았을 경우
	ans += toCross(0, 1, 0);	// 천사의 돌다리를 먼저 밟았을 경우

	return;
}

void input(){

	std::cin >> scroll;

	std::cin >> bridge[0] >> bridge[1];

	return;
}

int main(){

	input();

	sol();

	std::cout << ans;

	return 0;
}