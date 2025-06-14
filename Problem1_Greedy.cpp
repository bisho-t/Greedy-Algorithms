#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int childIndex = 0, cookieIndex = 0;
        int contentChildren = 0;

        while (childIndex < g.size() && cookieIndex < s.size()) {
            if (s[cookieIndex] >= g[childIndex]) {
                contentChildren++;
                childIndex++;
            }
            cookieIndex++;
        }

        return contentChildren;
    }
};

int main() {
    Solution sol;  // Create an instance of the Solution class

    vector<int> g1 = {1, 2, 3};
    vector<int> s1 = {1, 1};
    cout << "Output (Example 1): " << sol.findContentChildren(g1, s1) << endl;

    vector<int> g2 = {1, 2};
    vector<int> s2 = {1, 2, 3};
    cout << "Output (Example 2): " << sol.findContentChildren(g2, s2) << endl;

    return 0;
}
