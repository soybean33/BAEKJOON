#include <iostream>
#include <vector>
#include <algorithm>

int N;  // N: 보드 한 변의 길이
int MAP[25][25];    // MAP[j][i]: J행 i열의 정보
int max = 0;    // max: 최대값

void DFS(int M[25][25], int d){

    if(d==0){   // 5번 모두 시도 했음
        for(int j=1; j<=N; j++){
            for(int i=1; i<=N; i++){
                max = std::max(max, M[j][i]);   // 최대값 갱신
            }
        }

        return; // return을 까먹지 않아야 함
    }

    for(int dir=0; dir<4; dir++){   // 상 하 좌 우 4가지 방법 모두 해봐야함
        int copyM[25][25] = {0, };  // 다음 재귀 함수로 보낼 함수 복사 -> 복구 안해줘도 됨
        
        if(dir==0){ // 위
            for(int i=1; i<=N; i++){
                std::vector<int> tmpLine;   // tmpLine: 한 줄의 중간에 포함된 0을 제거하고, 앞과 뒤에 padding
                std::vector<int> line;  // line: 합칠 수 있는 수를 합친 계산이 완료된 라인

                tmpLine.push_back(0);   // 앞 padding
                for(int j=1; j<=N; j++){    // 0 제거
                    if(M[j][i] == 0) continue;
                    tmpLine.push_back(M[j][i]);
                }
                tmpLine.push_back(0);   // 뒤 padding

                for(int j=0; j<tmpLine.size(); j++){
                    if(tmpLine[j] == 0) continue;   // padding 제거

                    if(tmpLine[j] == tmpLine[j+1]){ // 같은 숫자가 연속해서 발생하면
                        line.push_back(tmpLine[j]*2);   // 값 2배
                        j++;    // 연속되었던 숫자 건너뛰기
                    }else{
                        line.push_back(tmpLine[j]); // 연속되지 않았으면 그대로 line에 넣기
                    }
                }
                for(int j=0; j<line.size(); j++){   // 다음 함수로 보내기 위하여 배열에 저장
                    copyM[j+1][i] = line[j];
                }
            }
            DFS(copyM, d-1);
        }else if(dir==1){   // 아래
            for(int i=1; i<=N; i++){
                std::vector<int> tmpLine;
                std::vector<int> line;
                
                tmpLine.push_back(0);
                for(int j=1; j<=N; j++){
                    if(M[j][i] == 0) continue;
                    tmpLine.push_back(M[j][i]);
                }
                tmpLine.push_back(0);

                for(int j=tmpLine.size()-1; j>0; j--){
                    if(tmpLine[j] == 0) continue;

                    if(tmpLine[j] == tmpLine[j-1]){
                        line.push_back(tmpLine[j]*2);
                        j--;
                    }else{
                        line.push_back(tmpLine[j]);
                    }
                }
                for(int j=0; j<line.size(); j++){
                    copyM[N-j][i] = line[j];
                }
            }
            DFS(copyM, d-1);
        }else if(dir==2){   // 왼쪽
            for(int j=1; j<=N; j++){
                std::vector<int> tmpLine;
                std::vector<int> line;

                tmpLine.push_back(0);
                for(int i=1; i<=N; i++){
                    if(M[j][i] == 0) continue;
                    tmpLine.push_back(M[j][i]);
                }
                tmpLine.push_back(0);

                for(int i=0; i<tmpLine.size(); i++){
                    if(tmpLine[i] == 0) continue;

                    if(tmpLine[i] == tmpLine[i+1]){
                        line.push_back(tmpLine[i]*2);
                        i++;
                    }else{
                        line.push_back(tmpLine[i]);
                    }                    
                }
                for(int i=0; i<line.size(); i++){
                    copyM[j][i+1] = line[i];
                }
            }
            DFS(copyM, d-1);
        }else if(dir==3){   // 오른쪽
            for(int j=1; j<=N; j++){
                std::vector<int> tmpLine;
                std::vector<int> line;

                tmpLine.push_back(0);
                for(int i=1; i<=N; i++){
                    if(M[j][i] == 0) continue;
                    tmpLine.push_back(M[j][i]);
                }
                tmpLine.push_back(0);

                for(int i=tmpLine.size()-1; i>0; i--){
                    if(tmpLine[i] == 0) continue;

                    if(tmpLine[i] == tmpLine[i-1]){
                        line.push_back(tmpLine[i]*2);
                        i--;
                    }else{
                        line.push_back(tmpLine[i]);
                    }                    
                }
                for(int i=0; i<line.size(); i++){
                    copyM[j][N-i] = line[i];
                }
            }
            DFS(copyM, d-1);
        }
    }

    return;
}

void sol(){
    DFS(MAP, 5);

    return;
}

void input(){
    std::cin >> N;
    for(int j=1; j<=N; j++){
        for(int i=1; i<=N; i++){
            std::cin >> MAP[j][i];
        }
    }

    return;
}

int main(){
    input();
    sol();
    std::cout << max;
    return 0;
}