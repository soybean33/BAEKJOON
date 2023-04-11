#include <iostream>

int N;	// N: 1부터 N까지의 오름차순 수
int path[11];	// path[i]: i번째 연산자

void DFS(int cur, long long cal, long long hold, int pre){	// cur: 현재 연산하고자 하는 수, cal: 현재까지 연산된 수, hold: 현재 연산 대기 중인 수, pre: 가장 최근에 나온 연산자

	if(cur == N){	// 모든 수에 대하여 연산자를 지정했다면
		if(pre == 1){	// 가장 최근 연산자가 + 인 경우
			cal += hold;
		}
		else if(pre == 2){	// 가장 최근 연산자가 - 인 경우
			cal -= hold;
		}
		if(cal == 0){	// 수식의 결과가 0 이라면 출력
			for(int i=1; i<N; i++){
				std::cout << i;
				if(path[i] == 0) std::cout << ' ';
				else if(path[i] == 1) std::cout << '+';
				else if(path[i] == 2) std::cout << '-';
			}
			std::cout << N << std::endl;
		}

		return;
	}

	for(int i=0; i<3; i++){
		path[cur] = i;	// 경로 저장
		if(i==0){	// 빈칸
			DFS(cur+1, cal, hold*10+cur+1, pre);	// 들고 있는 수를 계산하고 최근의 연산자를 이어서 넘겨줌
		}
		else if(i==1){	// '+'
			int tmp = 0;	// tmp: 연산 값
			if(pre == 1){	// 가장 최근의 연산자가 '+' 인 경우
				tmp = cal + hold;
			}
			else if(pre == 2){	// 가장 최근의 연산자가 '-' 인 경우
				tmp = cal - hold;
			}
			DFS(cur+1, tmp, cur+1, i);
		}
		else if(i==2){	// '-'
			int tmp = 0;	// tmp: 연산 값
			if(pre == 1){	// 가장 최근의 연산자가 '+' 인 경우
				tmp = cal + hold;
			}
			else if(pre == 2){	// 가장 최근의 연산자가 '-' 인 경우
				tmp = cal - hold;
			}
			DFS(cur+1, tmp, cur+1, i);
		}
	}

	return;
}

void sol(){
	DFS(1, 0, 1, 1);	// 초기값 -> 숫자 1의 앞에는 항상 '+' 연산이 있음 -> 1이라는 수에 대하여 연산을 하고자하고, 현재 까지 계산된 수는 아직 0 이며, 1은 아직 연산이 완료되어 있지 않기 때문에 들고 있고, 1 앞의 연산자는 항상 '+'
	return;
}

int main(){
	int T;	// T: 테스트케이스 수
	std::cin >> T;

	for(int tc=0; tc<T; tc++){
		std::cin >> N;
		sol();	
		std::cout << std::endl;	
	}

	return 0;
}