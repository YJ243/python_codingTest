#include <iostream>
#include <queue>
#include <string>

// 변수 선언
int n;
priority_queue<int> pq;

int main(){
    // 입력
    cin >> n;

    for(int i=0; i<n; i++){
        string command;
        cin >> command;
        if(command == "push"){
            int x;
            cin >> x;
            pq.push(x);
        }
        else if(command == "pop"){
            int v = pq.top();
            pq.pop();
            cout << v << '\n';
        }
        else if(command == "size"){
            cout << pq.size() << '\n';
        }
        else if(command == "empty"){
            if(pq.empty())
                cout << 1 << '\n';
            else
            {
                cout << 0 << '\n';
            }
        }
        else
        {
            cout << pq.top() << '\n';
        }
    }
    return 0;
}