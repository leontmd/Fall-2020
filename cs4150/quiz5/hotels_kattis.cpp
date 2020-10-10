#include <climits>
#include <iostream>
#include <vector>

int main() {
    int n; 
    std::cin >> n;
    ++n;
    std::vector<int> distances(n);
    std::vector<long long> penalties(n);

    for (int i = 0; i < n; i++) 
    {
        int cur_hotel;
        std::cin >> cur_hotel;
        distances[i] = cur_hotel;
    }

    penalties[n-1] = 0;
    for (int i = n-2; i >= 0; i--) 
    {
        long long cur_penalty = 100000000;
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
    std::cout <<penalties[0];

    return 0;
}