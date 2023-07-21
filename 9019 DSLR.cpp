#include <iostream>
#include <queue>
#include <string>
#include <cstring>

int A, B;	// A: 레지스터의 초기 값, B: 최종 값
bool visited[10'000];	// visited[i]: i 숫자 방문 여부

void solution(){

	memset(visited, false, sizeof(visited));	// 방문 초기화

	std::queue<std::pair<int, std::string>> q;	// q: 변환할 값을 넣은 큐
	
	// 값 A에서 시작
	q.push({A, ""});
	visited[A] = true;

	while(!q.empty()){
		std::pair<int, std::string> curr = q.front();	// curr: 이번에 변환할 값
		q.pop();

		for(int i=0; i<4; ++i){
			if(i==0){	// D
				int nextNum = (curr.first * 2) % 10000;	// nextNum: 변환 값 -> n을 두 배로 바꿈
				
				if(visited[nextNum]) continue;	// 이미 방문했다면 continue

				if(nextNum == B){	// 최종 값이라면
					std::cout << curr.second + "D";
					return;
				}
				
				q.push({nextNum, curr.second + "D"});	// 큐에 넣음
				visited[nextNum] = true;	// 방문 체크
			}
			else if(i==1){	// S
				int nextNum = curr.first == 0? 9999 : curr.first - 1;	// nextNum: 변환 값 -> n - 1

				if(visited[nextNum]) continue;	// 이미 방문했다면 continue

				if(nextNum == B){	// 최종 값이라면
					std::cout << curr.second + "S";
					return;
				}

				q.push({nextNum, curr.second + "S"});	// 큐에 넣음
				visited[nextNum] = true;	// 방문 체크
			}
			else if(i==2){	// L
				int nextNum = (curr.first % 1000) * 10 + (curr.first / 1000);	// nextNum: 변환 값 -> 왼편으로 회전

				if(visited[nextNum]) continue;	// 이미 방문했다면 continue

				if(nextNum == B){	// 최종 값이라면
					std::cout << curr.second + "L";
					return;
				}

				q.push({nextNum, curr.second + "L"});	// 큐에 넣음
				visited[nextNum] = true;	// 방문 체크
			}
			else if(i==3){	// R
				int nextNum = (curr.first / 10) + (curr.first % 10) * 1000;	// nextNum: 변환 값 -> 오른편으로 회전

				if(visited[nextNum]) continue;	// 이미 방문했다면 continue

				if(nextNum == B){	// 최종 값이라면
					std::cout << curr.second + "R";
					return;
				}

				q.push({nextNum, curr.second + "R"});	// 큐에 넣음
				visited[nextNum] = true;	// 방문 체크
			}
		}
	}

	return;
}

void input(){

	std::cin >> A >> B;

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;	// T: 테스트 케이스의 개수
	std::cin >> T;

	for(int tc=0; tc<T; ++tc){	// tc: 테스트 케이스 번호
		input();
		solution();
		std::cout << '\n';
	}

	return 0;
}