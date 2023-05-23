#include <iostream>
#include <string>

std::string s;	// s: 수행할 함수
int n;	// n: 배열에 들어있는 수의 개수
int arr[100'001];	// arr[i]: i 번째 수

void sol() {


	int left = 0;	// left: 왼쪽 인덱스
	int right = n - 1;	// right: 오른쪽 인덱스
	int dir = 1;	// 방향, 1: 정방향, -1 역방향

	for (int i = 0; i < s.length(); i++) {
		char c = s[i];	// c: 명령어

		if (c == 'R') {	// 역방향
			dir *= -1;
		}
		else if (c == 'D') {	// 제거
			if (dir == 1) left += dir;	// 정방향의 경우 left++
			else right += dir;	// 역방향의 경우 right--

			if (left > right + 1) {
				std::cout << "error\n";	// 원소가 없을 경우 error
				return;
			}
		}
	}

	if (dir == -1) {	// 역방향으로 끝났을 경우
		std::cout << '[';
		for (int i = right; i >= left; i--) {	// 뒤 부터 출력
			std::cout << arr[i];
			if (i != left) std::cout << ',';
		}
	}
	else {	// 정방향으로 끝났을 경우
		std::cout << '[';
		for (int i = left; i <= right; i++) {	// 앞 부터 출력
			std::cout << arr[i];
			if (i != right) std::cout << ',';
		}
	}
	std::cout << "]\n";

	return;
}

void input() {
	
	std::cin >> s;
	std::cin >> n;

	std::string element;	// element[i]: 배열에 들어있는 정수 -> [ , ] 로 string 형태로 들어옴

	std::cin >> element;

	int num = 0;	// num: 배열에 들어있는 수
	int cnt = 0;	// cnt: 수의 개수
	for (int i = 0; i < element.length(); i++) {
		if (element[i] == '[') continue;	// 시작
		if (element[i] == ',' || element[i] == ']') {	// 한 수가 끝나거나 모든 수 입력받음
			arr[cnt] = num;
			num = 0;
			cnt++;
			continue;
		}
		
		num *= 10;
		num += element[i] - '0';
	}

	return;
}

int main() {

	int T;	// T: 테스트 케이스의 개수

	std::cin >> T;

	for (int tc = 0; tc < T; tc++) {	// tc: 테스트 케이스
		input();
		sol();
	}


	return 0;
}