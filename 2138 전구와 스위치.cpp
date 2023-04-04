#include <iostream>
#include <bitset>
#include <string>

std::bitset<100001> bulbA1, bulbA2, bulbB;	// bulbA1: 현재 상태, bulbA2: 현재 상태에서 0번 전구를 누른 상태, bulbB: 만들고자 하는 상태
int N;	// N: 전구의 수
int ans = 21e8;	// ans: 스위치를 누른 최소 수

int main() {
	std::cin >> N;

	std::string s;	// s: 전구의 상태
	std::cin >> s;
	for (int i = 0; i < N; i++) {	// 현재 상태
		(s[i] == '0') ? bulbA1[i] = false : bulbA1[i] = true;		
	}
	std::cin >> s;
	for (int i = 0; i < N; i++) {	// 만들고자 하는 상태
		(s[i] == '0') ? bulbB[i] = false : bulbB[i] = true;
	}

	// 0번 스위치를 누른 bulbA2
	bulbA2 = bulbA1;
	bulbA2[0] = ~bulbA2[0];
	bulbA2[1] = ~bulbA2[1];


	int cnt = 0;	// cnt: 스위치를 누른 횟수

	for (int i = 1; i < N; i++) {	// 1번 전구부터 탐색 -> i번 전구만이 i-1번 전구의 상태를 바꿀 수 있음
		if (bulbA1[i - 1] == bulbB[i - 1]) continue;	// 스위치를 누를 필요 없으면 continue

		cnt++;	// 스위치를 누름
		bulbA1[i - 1] = ~bulbA1[i - 1];
		bulbA1[i] = ~bulbA1[i];
		if (i + 1 >= N) continue;	// 가장 마지막 전구의 오른쪽에는 전구가 없으므로 cotninue
		bulbA1[i + 1] = ~bulbA1[i + 1];
	}
	int flag = 0;	// flag: 스위치를 누른 전구가 만들고자 하는 상태가 같으면 0 아니면 1
	for (int i = 0; i < N; i++) {
		if (bulbA1[i] != bulbB[i]) {	// 상태가 다름
			flag = 1;
			break;
		}
	}

	if (flag == 0)	// 만들고자 하는 전구와 같은 상태면 최소값 갱신
		ans = std::min(ans, cnt);

	cnt = 1;	// 0번 스위치를 먼저 눌렀기 때문에 cnt = 1
	for (int i = 1; i < N; i++) {
		if (bulbA2[i - 1] == bulbB[i - 1]) continue;	// 스위치를 누를 필요 없으면 continue

		cnt++;	// 스위치를 누름
		bulbA2[i - 1] = ~bulbA2[i - 1];
		bulbA2[i] = ~bulbA2[i];
		if (i + 1 >= N) continue;	// 가장 마지막 전구의 오른쪽에는 전구가 없으므로 cotninue
		bulbA2[i + 1] = ~bulbA2[i + 1];
	}
	flag = 0;	// flag: 스위치를 누른 전구가 만들고자 하는 상태가 같으면 0 아니면 1
	for (int i = 0; i < N; i++) {
		if (bulbA2[i] != bulbB[i]) {	// 상태가 다름
			flag = 1;
			break;
		}
	}

	if (flag == 0)	// 만들고자 하는 전구와 같은 상태면 최소값 갱신
		ans = std::min(ans, cnt);

	if (ans == 21e8)	// 만들고자 하는 전구의 상태로 만들 수 없는 경우
		std::cout << -1;
	else
		std::cout << ans;
	
	return 0;
}