#include <iostream>
#include <vector>
#include <algorithm>

int N;	// N: 학생의 수
std::vector<int> students;	// students[i]: i 번째 학생의 번호
int max;	// max: 가장 큰 학생의 번호

std::vector<int> answer;	// answer[i]: i 번째 학생의 머리를 친 학생의 수 + 1

void Solution(){

	std::vector<int> DAT;	// DAT[i]: i를 배수로 갖는 학생의 수
	DAT.assign(max + 1, 0);

	answer.assign(N, 0);

	for(int i=0; i<N; ++i) {++DAT[students[i]];}	// 자기 자신

	for(int i=0; i<N; ++i) {	// N 명의 학생에 대하여
		for (int j = 1; j * j <= students[i]; ++j) {	// 약수를 구함
			if (students[i] % j == 0) {	// 약수라면
				if (students[i] / j != j)
					answer[i] += DAT[j] + DAT[students[i]/j];
				else
					answer[i] += DAT[j];
			}
		}
	}

	for(int i=0; i<N; ++i){
		std::cout << answer[i] - 1 << '\n';
	}

}

void Input(){

	std::cin >> N;
	students.assign(N, 0);
	for(int i=0; i<N; ++i) {
		std::cin >> students[i];
		max = std::max(max, students[i]);
	}

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	Input();

	Solution();

	return 0;
}