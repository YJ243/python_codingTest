/*
 * 24.01.16
 * 내 풀이
 * 아무리 완전탐색이라도 for문이 너무 많아서 가독성이 좋지 않음
 * 그리고 또 m자리에 n을 잘못 써서 계속 틀렸음!!!
 * 제발 끝까지 코드에 집중해라!!
*/
#include <iostream>
#include <climits>
#define MAX_NM 5

using namespace std;

int n, m;
int grid[MAX_NM][MAX_NM];
int ans = INT_MIN;

int getSum(int x, int y, int w, int h){
    int curr = 0;
    for(int i=x; i<=x+h; i++){
        for(int j=y; j<=y+w; j++)
            curr += grid[i][j];
    }
    return curr;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> grid[i][j];
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            // (i,j)는 첫번째 직사각형의 맨 왼쪽 위 점
            for(int w1=0; w1<m; w1++){
                for(int h1=0; h1<n; h1++){
                    if(i+h1 >= n || j+w1 >= m) continue;
                    for(int k=0; k<n; k++){
                        for(int l=0; l<m; l++){
                            for(int w2=0; w2<m; w2++){
                                for(int h2=0; h2<n; h2++){
                                    if(k+h2 >= n || l+w2 >= m) continue;
                                    if(i+h1 < k || j+w1 < l){
                                        // 두 직사각형이 겹치지 않는 경우에만 
                                        int rectangle1 = getSum(i,j,w1,h1);
                                        int rectangle2 = getSum(k,l,w2,h2);
                                        ans = max(ans, rectangle1+rectangle2);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << ans;
    return 0;
}