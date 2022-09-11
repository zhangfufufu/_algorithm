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
        arr.push_back(rand() % 10);
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
void _count_sort_maxs(vector<int> &arr)
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

// 计数排序优化为稳定排序  填充玩统计数组后 需要对统计数组做变形
// 统计数组从第二个元素开始，每一个元素都加上前面所有元素之和。
void _count_sort_plus(vector<int> &arr)
{
    //获取最大值和最小值 求出差值
    int max_num = *max_element(arr.begin(), arr.end());
    int min_num = *min_element(arr.begin(), arr.end());
    int d_value = max_num - min_num;

    // 创建统计数组
    vector<int> count_arr(d_value + 1);
    // 填充数据
    for (int i = 0; i < arr.size(); i++) {
        count_arr[arr[i] - min_num]++;
    }

    // 统计数组做变形,让统计数组存储的元素值，等于相应整数的最终排序位置。
    // 比如下标是9的元素值为5，代表原始数列的整数9，最终的排序是在第5位。
    int sum = 0;
    for (int i = 0; i < count_arr.size(); i++) {
        sum += count_arr[i];
        count_arr[i] = sum;
    }

    // 倒叙遍历原始数列,从统计数组找到正确位置,输出到结果数组
    vector<int> tmp(arr.size());
    for (int i = arr.size() - 1; i >= 0; i--) {
        // 找到原数组中的数在count_arr中的位置 -1是因为统计数组长度比原数组多1.防止原数组下标越界
        int index = count_arr[arr[i] - min_num];
        tmp[index - 1] = arr[i];
        // 这里不能写index-- 要改变count_arr中的值
        count_arr[arr[i] - min_num]--;
    }
    // 交换结果数组和原数组值
    // arr.swap(tmp);

    // 拷贝到arr
    // copy(tmp.begin(), tmp.end(), arr.begin());

    // 将tmp数据直接给原数组
    arr = tmp;
}

int main(int argc, char const *argv[])
{
    vector<int> arr;
    _random(arr);
    // 测试
    // _count_sort(arr);
    _count_sort_plus(arr);

    for_each(arr.begin(), arr.end(), [](const int &val) { cout << val << ' '; });
    cout << endl;

    return 0;
}
