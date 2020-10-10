#include <climits>
#include <iostream>
#include <vector>

int main() {
    int n = 3; 
    ++n;
    std::vector<int> distances;
    std::vector<long long> penalties(n);

    distances.push_back(0);
    distances.push_back(350);
    distances.push_back(450);
    distances.push_back(700);

    penalties[n-1] = 0;
    for (int i = n-2; i >= 0; i--) 
    {
        long long cur_penalty = 10000000;
        for (int j = i + 1; j < n; j++) 
        {
            long long penalty = (400 - (distances[j]-distances[i])) * (400 - (distances[j]-distances[i])) + penalties[j];
            if (penalty < cur_penalty) 
            {
                cur_penalty = penalty;
            }
        }
        penalties[i] = cur_penalty;
    }

    for(int i = 0; i < penalties.size(); ++i)
    {
        std::cout << penalties[i] << "\n";
    }

    return 0;
}