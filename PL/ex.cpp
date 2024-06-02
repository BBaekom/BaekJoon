#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {

    unordered_map<string, int> m;
    vector<string> v;

    v.push_back("m");
    v.push_back("a");
    v.push_back("b");
    v.push_back("c");
    v.push_back("d");

    cout << v.front();
    

    // m["k"] = 3;
    // m["j"] = 4;
    // m["i"] = 0;
    // while (true) {
    //     string tmp;
    //     cin >> tmp;
    //     if (tmp == "terminate") {
    //         break;
    //     }
    //     if (m.find(tmp) != m.end()) {
    //         cout << "key : " << tmp << ", value : " << m[tmp] << '\n'; 
    //     } else {
    //         cout << "Can't find!" << '\n';
    //     }
    // }
    
    return 0;
}