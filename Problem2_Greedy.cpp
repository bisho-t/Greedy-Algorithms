#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        if (tasks.empty()) {
            return 0;
        }

        // 1. Task Frequency Analysis (using std::map)
        map<char, int> frequencyMap;
        for (char task : tasks) {
            frequencyMap[task]++;
        }

        // 2. Determine Peak Frequency
        int peakFrequency = 0;
        for (const auto& pair : frequencyMap) {
            peakFrequency = max(peakFrequency, pair.second);
        }

        // 3. Count Tasks with Peak Frequency
        int peakFrequencyCount = count_if(frequencyMap.begin(), frequencyMap.end(),
                                          [&](const auto& pair) { return pair.second == peakFrequency; });

        // 4. Interval Calculation
        int parts = peakFrequency - 1;
        int slotsPerPart = n - (peakFrequencyCount - 1);
        int availableIdleSlots = max(0, parts * slotsPerPart);

        // Calculate the number of tasks which are not the most frequent tasks
        int nonFrequentTasks =accumulate(frequencyMap.begin(), frequencyMap.end(), 0, [&](int sum, const auto& pair) {
            if (pair.second != peakFrequency)
                return sum + pair.second;
            return sum;
        });

        int requiredIdles = max(0, availableIdleSlots - nonFrequentTasks);

        return tasks.size() + requiredIdles;
    }
};

int main() {
    Solution solution; // Create an instance of the Solution class

    // Test Cases
    vector<char> testCase1 = {'A', 'A', 'A', 'B', 'B', 'B'};
    cout << "Test Case 1: " << solution.leastInterval(testCase1, 2) << endl;

    vector<char> testCase2 = {'A', 'C', 'A', 'B', 'D', 'B'};
    cout << "Test Case 2: " << solution.leastInterval(testCase2, 1) << endl;

    vector<char> testCase3 = {'A', 'A', 'A', 'B', 'B', 'B'};
    cout << "Test Case 3: " << solution.leastInterval(testCase3, 3) << endl;

    vector<char> testCase4 = {};
    cout << "Test Case 4: " << solution.leastInterval(testCase4, 3) << endl;

    return 0;
}
