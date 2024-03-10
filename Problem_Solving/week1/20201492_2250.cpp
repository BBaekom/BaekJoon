#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Child{
    int leftChild;
    int rightChild;
    int level;
};

int index = 1;

void inorderTraversal(unordered_map<int, Child>& nodes, int currentNode, int level, vector<int>& levels, vector<int>& array) {
    if (currentNode == -1) return;

    inorderTraversal(nodes, nodes[currentNode].leftChild, level + 1, levels, array);

    nodes[currentNode].level = level;
    levels[currentNode] = level;
    array[index++] = currentNode;

    inorderTraversal(nodes, nodes[currentNode].rightChild, level + 1, levels, array);
}



int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N;
    cin >> N;

    int parent, left, right;

    unordered_map<int, Child> nodes;
    vector<int> parents(N+1);


    
    for (int i = 0; i < N; i++) {
        cin >> parent >> left >> right;
        Child child;
        child.leftChild = left;
        child.rightChild = right;
        nodes[parent] = child;
        if (left != -1) parents[left] = parent;
        if (right != -1) parents[right] = parent;
    }

    int root = min_element(parents.begin() + 1, parents.end()) - parents.begin();

    vector<int> levels(N+1);
    vector<int> array(N+1);

    inorderTraversal(nodes, root, 1, levels, array);

    int max_width = 0, max_width_level = 1; 

    vector<int> min_index(N+1, -1); 
    vector<int> max_index(N+1, 0); 

    for (int i = 1; i < N+1; i++) {
        int level = levels[array[i]];
        if (min_index[level] == -1) {
            min_index[level] = i;
        }
        max_index[level] = i; 
        int width = max_index[level] - min_index[level] + 1;
        if (width > max_width || (width == max_width && level < max_width_level)) {
            max_width = width;
            max_width_level = level;
        }
    }

    cout << max_width_level << " " << max_width << endl;

    return 0;
}
