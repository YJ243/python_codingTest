/* 2023.10.06*/

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// 변수 선언
int n;
unordered_map<int, int> m;

int main(){
    // 입력:
    cin >> n;

    for(int i=0; i<n; i++){
        string command;
        cin >> command;

        if(command == "add"){
            int k, v;
            cin >> k >> v;
            m[k] = v;
        }
        else if(command == "remove"){
            int k;
            cin >> k;
            m.erase(k);
        }
        else{
            int k;
            cin >> k;
            if(m.find(k) == m.end())
                cout << "None" << '\n';
            else
            {
                cout << m[k] << '\n';
            }
        }
    }
    return 0;
}