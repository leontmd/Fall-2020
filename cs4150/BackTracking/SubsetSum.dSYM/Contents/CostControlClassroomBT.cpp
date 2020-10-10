#include <iostream>
#include <vector>
#include <utility>

int minCost(std::vector<std::pair<int,int> > classrooms_list, int num_students, int start_index)
{
    if(num_students <= 0) return 0;

    int length = classrooms_list.size();

    int answer = INT_MAX;

    for(int i = start_index; i < length; ++i)
    {
        int sub_cost = minCost(classrooms_list, num_students - classrooms_list[i].first, i + 1);
        if(sub_cost != INT_MAX && sub_cost + classrooms_list[i].second < answer)
        {
            answer = sub_cost + classrooms_list[i].second;
        }
    }
    return answer;
}

int main()
{
    //  For each pair, the first value is the capacity C, the second value is the cleaning expense E
    std::pair<int,int> pair1(30,80);
    std::pair<int,int> pair2(40,20);
    std::pair<int,int> pair4(40,20);
    std::pair<int,int> pair3(70,90);
    
 
    std::vector<std::pair<int,int> > classrooms;
    classrooms.push_back(pair1);
    classrooms.push_back(pair4);
    classrooms.push_back(pair2);
    classrooms.push_back(pair3);
    

    int ans = minCost(classrooms, 70, 0);

    std::cout << ans << "\n"; //    RESULT IS 40 (20 + 20)
    return 0;
}