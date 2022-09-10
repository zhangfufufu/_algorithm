// 计数排序

#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

void _random(vector<int> &arr, int count = 10)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < count; i++) {
        arr.push_back(rand() % 20);
    }
}

// 计数排序
void _count_sort(vector<int> &arr)
{
    // 求出arr最大值 确定统计数组长度
    vector<int>::iterator max_ = max_element(arr.begin(), arr.end());
    vector<int> count_arr(*max_ + 1);

    // 按照下标依次放进去
    for (int i = 0; i < arr.size(); i++) {
        count_arr[arr[i]]++;
    }

    // 将结果复制到原数组中
    int index = 0;
    for (int i = 0; i < count_arr.size(); i++) {
        while (count_arr[i]--) {
            // cout << i << ' ';
            arr[index++] = i;
        }
    }
}

// 计数排序优化
/*
    问题:只以数组最大值确定统计数组的长度不严谨,容易造成空间浪费 比如 [67,55,88,99,77] 前面0-55空间被浪费
    优化点: 以数组最大值和最小值得差值确定统计数组的长度
*/
void _count_sort_plus(vector<int> &arr)
{
    int max_num = *max_element(arr.begin(), arr.end());
    int min_num = *min_element(arr.begin(), arr.end());
    // 差值
    int d_value = max_num - min_num;
    // 确定统计数组的长度
    vector<int> count_arr(d_value + 1);

    for (int i = 0; i < arr.size(); i++) {
        // 下标=数组值-最小值
        count_arr[arr[i] - min_num]++;
    }

    int index = 0;
    for (int i = 0; i < count_arr.size(); i++) {
        while (count_arr[i]--) {
            arr[index++] = i + min_num;
        }
    }
}

// 计数排序优化为稳定排序

int main(int argc, char const *argv[])
{
    vector<int> arr;
    _random(arr);
    // 测试
    _count_sort(arr);
    // _count_sort_plus(arr);

    for_each(arr.begin(), arr.end(), [](const int &val) { cout << val << ' '; });
    cout << endl;

    return 0;
}
