#include <iostream>
#include <vector>
#include <util.h>

int minExpense(std::vector<std::pair<int,int> > classrooms_list, int students, int start_index)
{
    if(students <= 0) return 0;
    int minExp = INT_MAX;
    
    int m = classrooms_list.size();

    for(int i = start_index; i < m; ++i)
    {
        int curExpense = minExpense(classrooms_list, students - classrooms_list[i].first, i + 1);
        if(curExpense != INT_MAX && curExpense + classrooms_list[i].second < minExp)
            minExp = curExpense + classrooms_list[i].second;
    }
    return minExp;
}

int main()
{
    std::pair<int,int> classroom_1(30,9);
    std::pair<int,int> classroom_2(40,6);
    std::pair<int,int> classroom_3(40,5);
    std::pair<int,int> classroom_4(40,1);

    std::vector<std::pair<int, int> > classrooms_list;
    classrooms_list.push_back(classroom_1);
    classrooms_list.push_back(classroom_2);
    classrooms_list.push_back(classroom_3);
    classrooms_list.push_back(classroom_4);

    int expense = minExpense(classrooms_list, 85, 0);

    std::cout << expense;
    return 0;
}