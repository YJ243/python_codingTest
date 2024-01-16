#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#define MAX_N 50
using namespace std;

int subSum[MAX_N][3];       // [i][0]: bi+ci, [i][1]: ai+ci, [i][2]: ai+bi
int tmp[MAX_N];
int powerCnt[3];            // [0]: 힘(a) 개수, [1]: 지능(b) 개수, [2]: 민첩(c)개수
int ans;                    // 소멸되는 능력치의 전체 합
int n;                      // 요원 

bool isPass(){              // 모든 능력치 영역이 하나 이상 뽑혔는지 확인하는 함수
    for(int i=0; i<3; i++){
        if(powerCnt[i]==0)
            return false;
    }
    return true;
}

void FindMinPowerSum(){     // 소멸되는 능력치의 합이 최소가 되는 경우를 구하는 함수
    for(int i=0; i<n; i++){
        int curMin = INT_MAX;
        for(int j=0; j<3; j++){
            if(curMin > subSum[i][j]){
                curMin = subSum[i][j];
            }
        }
        for(int j=0; j<3; j++){
            if(curMin == subSum[i][j])
                powerCnt[j]++;
        }
        ans += curMin;
        tmp[i] = curMin;
    }
    //cout << ans << '\n';
    vector<int> zeros;
    for(int i=0; i<3;i++) 
        if(powerCnt[i]==0) zeros.push_back(i);
    
    int changeNum[n][3];
    
    for(int i=0; i<n; i++){
        for(int j=0; j<3; j++){
            changeNum[i][j] = subSum[i][j]-tmp[i];
            //cout << changeNum[i][j] << ' ';
        }
        //cout << '\n';
    }

    if(zeros.size()==0) return;   // 만약 모두 한 번 이상 선택되었다면 바로 리턴

    else if(zeros.size()==1){   // 그렇지 않다면
        // 하나 혹은 두개가 0일 것, 50개를 탐색하면서 확인해보기
        int toIdx = zeros[0];
        //cout << "hi" << toIdx << '\n';
        int plusMin = INT_MAX;

        for(int i=0; i<n; i++){
            for(int j=0; j<3; j++){
                if(changeNum[i][j]==0 && j != toIdx){
                    // 선택 후보인 아이
                    powerCnt[j]--;
                    powerCnt[toIdx]++;
                    //cout << i << ' ' << j << changeNum[i][j] << '\n';
                    if(isPass()){
                        //cout << "A";
                        plusMin = min(plusMin, changeNum[i][toIdx]);
                    	//cout << powerCnt[0] << ' ' << powerCnt[1] << ' ' << powerCnt[2] << '\n';
                    }
                    else{
                        for(int k=0; k<n; k++){
                            if(k == i) continue;
                            int z;
                            for(int l=0; l<3; l++){
                                if(l != toIdx && changeNum[k][l]==0) z=l;
                            }
                            
                            for(int l=0; l<3; l++){
                                if(changeNum[k][l] != 0 && l != toIdx){
                                    powerCnt[z]--;
                                    powerCnt[l]++;
                                    if(isPass()){
                                        plusMin = min(plusMin, changeNum[i][toIdx]+changeNum[k][l]);
                                    }
                                    powerCnt[z]++;
                                    powerCnt[l]--;
                                }
                            }
                            
                        }
                    }
                    powerCnt[j]++;
                    powerCnt[toIdx]--;
                }
            }
        }
        ans += plusMin;
        return;
    }
    else{
    // 2개
        pair<int, int> changes[n];
        for(int i=0; i<n; i++){
            changes[i].first=subSum[i][zeros[0]]-tmp[i];
            changes[i].second=subSum[i][zeros[1]]-tmp[i];                                       
        }
        // i는 첫번째, j는 두번째
        int minSub = INT_MAX;
        for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                minSub = min(changes[i].first+changes[j].second, minSub);
                minSub = min(changes[i].second+changes[j].first, minSub);
            }
        }        
        ans += minSub;
        return;
    }
    
}

void Initialize(){      // 능력치와 정답을 초기화하는 함수
    for(int i=0; i<3; i++)
        powerCnt[i] = 0;
    ans = 0;
}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> n;
        
        // 총 n명의 요원에 대해 세 가지 능력치 입력받기
        for(int i=0; i<n; i++){
            int a1, b1, c1;
            cin >> a1 >> b1 >> c1;
            subSum[i][0] = b1+c1;
            subSum[i][1] = a1+c1;
            subSum[i][2] = a1+b1;
            //cout << subSum[i][0] << ' ' << subSum[i][1] << ' ' << subSum[i][2] << '\n';
        }

        if(n < 3) ans = -1;     // 만약 갤럭시를 가동할 수 없다면(힘,지능,민첩 중 하나라도 공유받을 수 없다면)
        else{                   // 최정예 요원이 3명 이상이라면
            Initialize();
            FindMinPowerSum();
        }
        
        cout << "#" << test_case << ' ' << ans << '\n';
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}