#include <iostream>
#include <vector>

int N;	// N: 선수의 수
std::vector<int> arr;	// arr[i]: i 번째 선수
std::vector<bool> rank;	// rank[i]: i 번째 선수가 탈락했다면 false, 아직 탈락하지 않았다면 true
int ans;

void solution(){

	for(int i=N; i>0; --i){	// 가장 랭크가 낮은 (숫자가 큰) 선수 부터
		int currRank = i;	// currRank: 이번에 탈락시킬 선수 랭킹

		if(!rank[currRank]) continue;	// 이미 탈락했다면 continue

		for(int j=0; j<N; ++j){
			if(arr[j] != currRank) continue;	// 선수 순서 찾기

			int currRankIdx = j;	// currRankIdx: 현재 선수 위치

			rank[currRank] = false;	// 이번 선수는 무조건 탈락함 -> 이 선수 보다 낮은 랭킹의 선수는 존재 하지 않음

			int leftRank = -1, rightRank = -1;	// leftRank, rightRank: 왼쪽 오른쪽 선수의 랭킹
			int leftRankIdx = -1, rightRankIdx = -1;	// leftRankIdx, rightRankIdx: 왼쪽 오른쪽 선수의 순서

			int k = currRankIdx - 1;	// k: 선수 인덱스
			while(k >= 0){	// 왼쪽 선수 탐색
				if(!rank[arr[k]]){	// 이미 탈락했다면
					k--;
					continue;
				}
				leftRank = arr[k];
				leftRankIdx = k;
				break;
			}
			k = currRankIdx + 1;
			while(k < N){	// 오른쪽 선수 탐색
				if(!rank[arr[k]]){	// 이미 탈락했다면
					k++;
					continue;
				}
				rightRank = arr[k];
				rightRankIdx = k;
				break;
			}

			if(leftRank == -1 && rightRank == -1) return;	// 한 선수만 남으면 return
			else if(leftRank == -1){	// 오른쪽 선수만 있을 경우
				ans += currRank - rightRank;
			}
			else if(rightRank == -1){	// 왼쪽 선수만 있을 경우
				ans += currRank - leftRank;
			}
			else{	// 양쪽에 모두 선수가 있을 경우
				if(leftRank > rightRank){	// 랭킹이 더 낮은 (숫자가 큰) 선수와 게임을 진행
					ans += currRank - leftRank;
				}
				else{
					ans += currRank - rightRank;
				}
			}

		}
	}

	return;
}

void input(){

	std::cin >> N;

	// 공간 할당
	arr.assign(N, 0);
	rank.assign(N+1, true);	// 선수 번호는 1 ~ N

	for(int i=0; i<N; i++) std::cin >> arr[i];

	return;
}

int main(){

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	input();

	solution();

	std::cout << ans;

	return 0;
}