#include <iostream>
#include <cmath>

int N, M;	// N: 이동하려고 하는 채널, M: 버튼의 개수

bool btn[10];	// btn[i]: i 버튼의 동작 / 고장 여부
int ans;	// ans: 채널 N으로 이동하기 위하여 눌러야 하는 최소 버튼 수

int btnChk(int ch) {	// ch: 버튼 이동으로 이동하고자 하는 채널

	int tmp = ch;	// tmp: 이동하고자 하는 채널 임시 저장
	int digitNum = 0;	// digitNum: 자릿수

	while (true) {
		int num = tmp % 10;	// num: 누를 버튼

		if (btn[num] == false) return -1;	// 눌러야하는 버튼이 고장났으면 return -1

		digitNum++;	// 버튼 누름
		tmp /= 10;	// 다음 자리를 위하여 10으로 나눔
		if (tmp == 0) return digitNum;	// 더 이상 버튼을 누르지 않아도 되면 누른 버튼수 return
	}

	return 0;
}

int sol() {

	ans = std::abs(N - 100);	// 현재 채널은 100번

	for (int i = 0; i <= 1'000'000; i++) {
		int push = btnChk(i);	// push: i 채널에 가기위해 누른 버튼 수

		if (push == -1) continue;	// 해당 채널을 버튼 입력으로 갈 수 없음

		ans = std::min(ans, push + std::abs(N - i));	// 누른 버튼 + +1 or -1 버튼 
	}

	return ans;
}

void input() {
	
	std::cin >> N >> M;

	for (int i = 0; i < 10; i++) btn[i] = true;	// 모든 버튼을 누를 수 있다고 reset

	for (int i = 0; i < M; i++) {
		int n;	// n: 고장난 버튼
		std::cin >> n;
		btn[n] = false;	// n 버튼이 고장났으므로 false
	}

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	std::cout << sol();

	return 0;
}