#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

struct dot{
    long long x, y;
    bool operator==(const dot &input){
        return (x == input.x) && (y == input.y);
    }
};

dot standard;

int ccw(dot A, dot B, dot C) {
    long long val = (B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y);
    return (val > 0) - (val < 0);
}

bool compare1(dot n1, dot n2) {
    return (n1.y == n2.y) ? (n1.x < n2.x) : (n1.y < n2.y);
}

bool compare2(dot n1, dot n2) {
    int cp = ccw(standard, n1, n2);
    return cp ? (cp > 0) : (abs(n1.x + n1.y) < abs(n2.x + n2.y));
}

vector<dot> getHull(vector<dot> &dots){
    vector<dot> ret;
    sort(dots.begin(),dots.end(), compare1);
    standard = dots[0];
    sort(dots.begin()+1, dots.end(), compare2);
    ret.push_back(dots[0]);
    if(dots.size() < 2) {
        return ret;
    }
    ret.push_back(dots[1]);

    for(int i = 2; i < dots.size(); i++) {
        while(ret.size() >= 2){
            dot n1 = ret.back();
            ret.pop_back();
            dot n2 = ret.back();
            if(ccw(n2,n1,dots[i]) > 0) {
                ret.push_back(n1);
                break;
            }
        }
        ret.push_back(dots[i]);
    }
    return ret;
};

bool isInner(vector<dot> &dots, dot &p) {
    int dotCCW = ccw(dots[0], dots[1], p);
    for (int i = 1; i < dots.size(); i++) {
        if (dotCCW * ccw(dots[i], dots[(i + 1) % dots.size()], p) <= 0){
            return false;
        }
    }
    return true;
}

vector<dot> dots;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);

	int N;
	cin >> N;

	dot cow;
	cin >> cow.x >> cow.y;

	for (int i = 0; i < N; i++) {
        dot X;
		cin >> X.x >> X.y;
		dots.push_back(X);
	}
	
	int result = 0;

	while (true) {
		if (dots.size() < 3) break;

		vector<dot> hull = getHull(dots);
		if (isInner(hull, cow)) {
			result += 1;
			for (int i = 0; i < hull.size(); ++i){
				dots.erase(find(dots.begin(), dots.end(), hull[i]));
            }
		} else {
            break;
        }
	}

	cout << result << '\n';
	return 0;
}