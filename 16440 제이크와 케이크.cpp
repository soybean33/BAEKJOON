#include <iostream>
#include <string>

struct Fruit {
	int kiwi;	// 키위의 개수
	int strawberry;	// 딸기의 개수
};

int N;	// N: 케이크 위에 있는 과일의 개수
std::string s;	// s: 케이크의 정보가 담긴 길이가 N인 문자열

void sol() {

	int left = 0, right = 0;	// left: 왼쪽 자르기, right: 오른쪽 자르기
	Fruit fruit = { 0,0 };	// fruit: 과일의 개수 -> 키위, 딸기

	if (s[0] == 's') fruit.strawberry++;	// 초기과일이 딸기인 경우 딸기 수 증가
	else fruit.kiwi++;	// 키위인 경우 키위 증가

	while (true) {
		if (fruit.kiwi > N / 4 || fruit.strawberry > N / 4) {	// 둘 중 하나의 수가 많은 경우
			if (s[left] == 's') fruit.strawberry--;	// 딸기 제거
			else fruit.kiwi--;	// 키위 제거
			left++;	// 한 칸 오른쪽 자르기
			
		}
		else {	// 과일이 모자른 경우
			right++;	// 한 칸 오른쪽 자르기
			if (s[right] == 's') fruit.strawberry++;	// 딸기 증가
			else fruit.kiwi++;	// 키위 증가
		}

		if (fruit.kiwi == N / 4 && fruit.strawberry == N / 4) {	// 두 과일의 개수가 적절한 경우
			if (left == 0) {	// 왼쪽 칼질은 하지 않았으므로 1번만 자름
				std::cout << "1\n" << right + 1;
			}
			else {	// 2번의 칼질
				std::cout << "2\n" << left << ' ' << right + 1;
			}		
			
			return;
		}
	}

}

void input() {

	std::cin >> N;

	std::cin >> s;

	return;
}

int main() {

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	sol();

	return 0;
}