#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int N, M, K;
    cin >> N >> M >> K;
    int answer=0;
    vector<int> a(N);
    for(int i=0; i<N; i++){
        cin >> a[i];
    }
    sort(a.rbegin(), a.rend());
/*
    for(int i=0; i<M; i++){
        for(int i=0; i<K; i++){
            answer += a[]
        }
    }
    */
    int index=0;
    while(M != 0){
        for(int i=0; i<K; i++){
            answer += a[index];
            M--;
            if(M ==0)
                break;
        }
        if(a[index+1] == a[index]){
            for(int i=0; i<K; i++){
                answer += a[index+1];
                M--;
                if(M == 0)
                    break;
            }
        }
        else
        {
            answer += a[index+1];
            M--;
        }
    }
    cout<<answer << '\n';
}