#include <iostream>
#include <vector>
using namespace std; 
  
int minCoins(std::vector<int>coins, int V) 
{ 
   // base case 
   if (V == 0) return 0; 
  
   // Initialize result 
   int res = INT_MAX; 
  
   // Try every coin that has smaller value than V 
   for (int i=0; i<coins.size(); i++) 
   { 
     if (coins[i] <= V) 
     { 
         int sub_res = minCoins(coins, V-coins[i]); 
  
         // Check for INT_MAX to avoid overflow and see if 
         // result can minimized 
         if (sub_res != INT_MAX && sub_res + 1 < res) 
            res = sub_res + 1; 
     } 
   } 
   return res; 
} 
  
// Driver program to test above function 
int main() 
{ 
    std::vector<int> coins;
    coins.push_back(9);
    coins.push_back(6);
    coins.push_back(5);
    coins.push_back(1);

    int W = 13;

    std::cout << minCoins(coins, W);
    
    return 0; 
}