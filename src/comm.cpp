#include <ctime>
#include <iostream>

#include "../include/comm.h"

using namespace std;

namespace Tool {

void for_each(vector<int> &arr)
{
    for (const int &val : arr) {
        cout << val << ' ';
    }
    cout << endl;
}

void random(vector<int> &arr, int count)
{
    /*
    要取得 [a,b) 的随机整数，使用 (rand() % (b-a))+ a;
    要取得 [a,b] 的随机整数，使用 (rand() % (b-a+1))+ a;
    要取得 (a,b] 的随机整数，使用 (rand() % (b-a))+ a + 1;
    */
    srand((unsigned)time(NULL));
    for (int i = 0; i < count; i++) {
        arr.push_back(rand() % 50);
    }
}

int getrandom(int start, int end)
{
    srand((unsigned int)time(NULL));
    int num = (rand() % (end - start)) + start;
    return num;
}

}  // namespace Tool