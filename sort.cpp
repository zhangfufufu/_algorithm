#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

namespace Tool {
void for_each(vector<int> &arr)
{
    for (const int &val : arr) {
        cout << val << ' ';
    }
    cout << endl;
}

void random(vector<int> &arr, int n = 10)
{
    /*
    要取得 [a,b) 的随机整数，使用 (rand() % (b-a))+ a;
    要取得 [a,b] 的随机整数，使用 (rand() % (b-a+1))+ a;
    要取得 (a,b] 的随机整数，使用 (rand() % (b-a))+ a + 1;
    */
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % 50);
    }
}

}  // namespace Tool

// 实现元素的移动，让数列中的元素依据自身大小，分别移动到基准元素的左右两边。移动方式是挖坑法。
int _partition_move(vector<int> &arr, int start_index, int end_index)
{
    // 初始基准元素为数组第一位元素
    int pivot = arr[start_index];
    // 定义坑的位置 初始等于基准元素的位置
    int index = start_index;

    // 定义左右指针
    int left  = start_index;
    int right = end_index;

    // 大循环在左右指针重合时退出
    while (right >= left) {
        // 注意:一定要先从右开始 right 指针从右向左进行比较
        while (right >= left) {
            if (arr[right] < pivot) {
                // 最右边的数小于基准数 需要放入最左边的数的位置
                // left位置的数,初始基准数已经保存,所以直接覆盖
                arr[left] = arr[right];
                // 因为右边的数已经放到左边.所以此时坑的位置就是右边数的位置
                index = right;
                // 最左边的坑已经放了右边的数 所以需要右移以便放入新的数
                left++;
                break;
            }
            right--;
        }

        // left 指针从左向右进行比较
        while (right >= left) {
            if (arr[left] > pivot) {
                arr[right] = arr[left];
                index      = left;
                right--;
                break;
            }
            left++;
        }
    }

    // 循环结束 将之前保存的基准数放到index位置 此时 左边数 <= arr[index] <=
    // 右边数
    arr[index] = pivot;
    // cout << "----" << index << "----" << left << "----" << right << endl;
    return index;
}

// 实现元素的移动，让数列中的元素依据自身大小，分别移动到基准元素的左右两边。移动方式是指针交换法。
int _partition_swap(vector<int> &arr, int start_index, int end_index)
{
    // 基准数
    int pivot = arr[start_index];

    int left  = start_index;
    int right = end_index;

    // notice! 这里一定不能写 >=
    while (right > left) {
        // 从right开始比较 控制right指针左移
        // notice! 不能写 right>= left 会数组越界
        while (right > left && arr[right] >= pivot) {
            right--;
        }

        // 控制left指针右移
        // notice! 不能写 right>= left 会数组越界
        while (right > left && arr[left] <= pivot) {
            left++;
        }

        // 交换 left和right指向的元素
        if (left < right) {
            swap(arr[left], arr[right]);
        }
    }

    // 基准数和指针重合点进行交换 此时left=right
    swap(arr[left], pivot);
    // cout << "left=" << left << "right=" << right << endl;
    return left;
}

// 冒泡排序 基础版
void bubble_sort(vector<int> &arr)
{
    int len = arr.size();
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 冒泡排序 优化
void bubble_sort_plus(vector<int> &arr)
{
    int len = arr.size();
    // 记录最后一次交换的索引
    int last_change_index = 0;
    // 无序数组的边界 每次循环只需要比到这里
    int sort_border = len - 1;

    for (int i = 0; i < len; i++) {
        // 有序标记 标记序列是否有序
        bool is_sorted = true;
        for (int j = 0; j < sort_border; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                is_sorted = false;

                // 有元素交换 就更新最后一次交换的位置
                last_change_index = j;
            }
        }
        // 每一次循环之后 更新无序数组的边界
        sort_border = last_change_index;

        if (is_sorted)  // 没有经过交换说明数组已经有序 直接返回
        {
            break;
        }
    }
}

// 选择排序 每一轮选出最小着,交换到左侧
void select_sort(vector<int> &arr)
{
    int len = arr.size();
    for (int i = 0; i < len; i++) {
        // 一轮循环选出最小值
        int min_index = i;

        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
}

// 选择排序 优化版 一次找最大和最小两个元素
/*
普通方法在一次遍历后找到一个最值，既然这次遍历必不可少，我们希望在一次遍历中尽可能多的确定数字。所以我们可以使用二元选择排序，即在一次遍历中，找到最大值和最小值，将两个最值放到数组的两端，然后再递归处理夹在两个最值中间的待排数组。

因为我们每次可以确定两个位置的数字，所以我们只需要遍历数组的一半，即 (0, n//2)。
初始假定待排数组的正数第一位 i 为最小值，倒数第一位 n-i-1
为最大值，然后遍历整个数组(包括i和 n-i-1)，找到待排数组中的最大最小值，更新指针
min_index和 max_index。 如果待排序列中最大最小值相等nums[min_index] ==
nums[max_index]，证明这段序列所有元素都相等，不用继续比较，结束排序。
如果最大最小值不相等，判断最小值nums[min_index]是否和待排序列第一位 nums[i]
重合，如果是，不用交换，如果不是，则交换两个数字。 如果此时待排序列的第一位
nums[i] 刚好是最大值，在上一步第一位 nums[i]和最小值 nums[min_index]
交换后，这个第一位不再是最大值，最大值转移到了指针为min_index处，所以应该再次更新一下最大值指针
max_index = min_index。 如果待排序列的倒数第一位
nums[n-i-1]是最小值呢？如果先交换的是最小值，在交换 nums[i] 和 nums[n-i-1]
后，不影响最大值nums[max_index] 和 nums[n-i-1]
的交换。如果先交换的是最大值，那交换后 n-i-1
处就不再是最小值，就会影响最小值的交换。所以先进行交换的要处理这个特殊情况。

*/
void select_sort_plus(vector<int> &arr)
{
    int len = arr.size();

    // 只需要进行N/2次排序
    for (int i = 0; i <= len / 2; i++) {
        int min_index = i;
        int max_index = len - i - 1;

        for (int j = i; j < len - i; j++) {
            // 一次循环找出最大和最小的元素
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
            if (arr[j] > arr[max_index]) {
                max_index = j;
            }
        }

        if (arr[min_index] == arr[max_index]) {
            // 所有元素都相等 直接返回
            break;
        }

        if (min_index != i) {
            swap(arr[i], arr[min_index]);
            // 说明此次交换改变了最大数的下标 先进行交换的需要考虑特殊情况,
            // 所以需要将最大数下标重新归位
            if (i == max_index) {
                max_index = min_index;
            }
        }

        if (max_index != len - i - 1) {
            // 后进行交换的不用考虑特殊情况
            swap(arr[len - i - 1], arr[max_index]);
        }
    }
}

// 插入排序 交换法 思想:维护一个有序区,将元素一个一个插入到有序区
void insert_sort_swap(vector<int> &arr)
{
    int len = arr.size();
    for (int i = 1; i < len; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (arr[j] > arr[j + 1]) {
                // 这里直接进行两两交换
                swap(arr[j], arr[j + 1]);
            } else {
                // 因为前面是有序数组 比较是从后往前比较 只要最后比较的元素就绪
                // 就结束当前循环
                break;
            }
        }
    }
}

// 插入排序 挖坑法 优化版
void insert_sort_move(vector<int> &arr)
{
    int len = arr.size();
    for (int i = 1; i < len; i++) {
        // 挖坑
        int tmp = arr[i];
        int j;
        for (j = i - 1; j >= 0 && arr[j] > tmp; j--) {
            // 小数前置移位
            arr[j + 1] = arr[j];
        }
        // 填坑
        arr[j + 1] = tmp;
    }
}

// 希尔排序 直接插入排序的升级版
void shell_sort(vector<int> &arr)
{
    int d = arr.size();
    while (d > 1) {
        // 使用希尔增量方式 每次除半
        d /= 2;
        for (int x = 0; x < d; x++) {
            for (int i = x + d; i < arr.size(); i += d) {
                // 挖坑
                int tmp = arr[i];
                int j;
                for (j = i - d; j >= 0 && arr[j] > tmp; j -= d) {
                    // 移位
                    arr[j + d] = arr[j];
                }
                // 填坑
                arr[j + d] = tmp;
            }
        }
    }
}

// 快速排序 挖坑法
// 快速排序在每一轮挑选一个基准元素，并让其他比它大的元素移动到数列一边，比它小的元素移动到数列的
//  另一边，从而把数列拆解成了两个部分。分治法
void quick_sort_move(vector<int> &arr, int start_index, int end_index)
{
    // 递归的出口
    if (start_index >= end_index) {
        return;
    }

    // 得到基准元素位置  左边数 <= arr[pivot_index] <= 右边数
    int pivot_index = _partition_move(arr, start_index, end_index);

    // 递归分治数组两端
    quick_sort_move(arr, start_index, pivot_index - 1);
    quick_sort_move(arr, pivot_index + 1, end_index);
}

// 快速排序指针交换法 效率比挖坑法高
void quick_sort_swap(vector<int> &arr, int start_index, int end_index)
{
    if (start_index >= end_index) {
        return;
    }

    // 定义基准数下标
    int pivot_index = _partition_swap(arr, start_index, end_index);

    // 递归左右
    quick_sort_swap(arr, start_index, pivot_index - 1);
    quick_sort_swap(arr, pivot_index + 1, end_index);
}

// 合并两个有序数组到大数组中
void _merge(vector<int> &arr, int start_index, int mid_index, int end_index)
{
    // 获取两个子序列的第一个下标
    int i = start_index;
    int j = mid_index + 1;
    //创建临时容器来保存合并结果，同时指定容器大小
    vector<int> tmp(end_index - start_index + 1);
    // 临时容器的索引
    int p = 0;
    // 比较两个小集合的元素 依次放入大集合
    while (i <= mid_index && j <= end_index) {
        if (arr[i] <= arr[j]) {
            tmp[p++] = arr[i++];
        } else {
            tmp[p++] = arr[j++];
        }
    }

    // 左侧有序数组可能还有值 依次放入大集合尾部
    while (i <= mid_index) {
        tmp[p++] = arr[i++];
    }

    // 右侧有序数组可能还有值 依次放入大集合尾部
    while (j <= end_index) {
        tmp[p++] = arr[j++];
    }

    //将临时容器元素复制给原始容器得到结果
    for (int n = 0; n < p; n++) {
        arr.at(start_index++) = tmp.at(n);
    }
    // copy(tmp.begin(), tmp.end(), arr.begin() + start_index);
}

// 归并排序
void merge_sort(vector<int> &arr, int start_index, int end_index)
{
    if (start_index >= end_index) {
        return;
    }

    // 拆成小集合 分别递归
    int mid_index = start_index + (end_index - start_index) / 2;
    merge_sort(arr, start_index, mid_index);
    merge_sort(arr, mid_index + 1, end_index);

    // 把两个有序小集合 归并成一个大集合
    _merge(arr, start_index, mid_index, end_index);
}

int main(int argc, char const *argv[])
{
    vector<int> arr;
    Tool::random(arr);

    // test

    // quick_sort_swap(arr, 0, arr.size() - 1);
    // select_sort_plus(arr);
    // bubble_sort_plus(arr);
    shell_sort(arr);

    // merge_sort(arr, 0, arr.size() - 1);
    Tool::for_each(arr);
    return 0;
}