#include <iostream>
#include <vector>
#include <algorithm>

struct Hero{	// 용사 정보
	long long maxHP;	// maxHP: 용사의 최대 생명력, 이 값은 1이상이어야 하며 던전에 들어간 이후로 변하지 않음
	long long curHP;	// curHP: 현재 용사의 생명력, 던전에 들어가기 전 이 값은 용사의 최대 생명력 HMaxHP와 같음, 이 값은 용사의 최대 생명력보다 커질 수 없음.
	long long ATK;	// ATK: 용사의 공격력
};

struct RoomInfo{	// 던전의 방 정보
	int t;	// t: 1인 경우 몬스터가 있는 방, 2인 경우 포션이 있는 방
	int a;	// a: t가 1인 경우 공격력이 a인 몬스터가 있음, t가 2인 경우 용사의 공격력을 a만큼 증가시킴
	int h;	// h: t가 1인 경우 생명력이 h인 몬스터가 있음, t가 2인 경우 용사의 현재 생명력을 h만큼 회복시킴
};

int N;	// N: 방의 개수
int heroATK;	// heroATK: 용사의 초기 공격력

std::vector<RoomInfo> roomInfo;	// roomInfo[i]: i 번째 방의 정보

Hero hero;	// hero: 용사 정보
long long ans;	// ans: 용사가 N번째 방에 있는 용을 쓰러트리기 위한 최소의 maxHP

bool func(long long maxHP){	// maxHP: 용사의 최대 채력

	hero = {maxHP, maxHP, heroATK};	//용사 정보 갱신

	for(int i=0; i<N; i++){
		RoomInfo curRoomInfo = roomInfo[i];	// curRoomInfo: 현재 방의 정보

		if(curRoomInfo.t == 1){	// 몬스터가 있는 방

			long long turn;	// turn: 용사와 몬스터가 싸우는 횟수

			if(curRoomInfo.h % hero.ATK == 0) turn = curRoomInfo.h / hero.ATK - 1;	// 몬스터의 채력 / 용사의 공격력 - 1
			else turn = curRoomInfo.h / hero.ATK;	// 몬스터의 채력 / 용사의 공격력

			hero.curHP -= curRoomInfo.a * turn;	// 몬스터의 공격력 * 공격한 횟수 만큼 용사의 채력이 깍임

			if(hero.curHP <= 0)	return false;	// 용사의 채력이 0 이하가 되면 몬스터를 쓰러트리지 못함
			
		}
		else if(curRoomInfo.t == 2){	// 포션이 있는 방
			hero.ATK += curRoomInfo.a;	// 용사의 공격력 증가
			hero.curHP = std::min(hero.curHP + curRoomInfo.h, hero.maxHP);	// 최대 최력 이하로 채력 회복
		}
	}

	return true;
}

void solution(){

	long long left = 1, right = 1e18;	// left, right: 이분 탐색 범위

	while(left <= right){
		long long mid = (left + right) / 2;	// mid: 탐색할 용사의 최대 채력

		if(func(mid)){	// N 번째 방에 있는 용을 쓰러트렸다면
			right = mid - 1;	// 더 적은 채력으로 도전
			ans = mid;
		}
		else{	// N 번째 방에 있는 용을 쓰러트리지 못했다면
			left = mid + 1;	// 더 많은 채력으로 도전
		}
	}

	return;
}

void input(){

	std::cin >> N >> heroATK;

	roomInfo.resize(N);	// 방 갯수 만큼 할당

	for(int i=0; i<N; i++){
		int t, a, h;	// t, a, h: 방 정보 입력
		std::cin >> t >> a >> h;
		roomInfo[i] = {t, a, h};
	}

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