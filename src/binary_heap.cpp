// 二叉堆
/*
二叉堆本质上是一种完全二叉树，它分为两个类型：
    1.最大堆 最大堆任何一个父节点的值，都大于等于它左右孩子节点的值。
    2.最小堆 最小堆任何一个父节点的值，都小于等于它左右孩子节点的值。
        二叉堆的根节点叫做堆顶。

    堆的自我调整
        对于二叉堆，如下有几种操作：
            -插入节点 二叉堆的节点插入，插入位置是完全二叉树的最后一个位置。
            -删除节点 二叉堆的节点删除过程和插入过程正好相反，所删除的是处于堆顶的节点。
            -构建二叉堆 构建二叉堆，也就是把一个无序的完全二叉树调整为二叉堆，本质上就是让所有非叶子节点依次下沉。
    堆的存储方式
        -二叉堆虽然是一颗完全二叉树，但它的存储方式并不是链式存储，而是顺序存储。换句话说，二叉堆的所有节点都存储在数组当中。
        假设父节点的下标是parent，那么它的左孩子下标就是 2*parent+1；它的右孩子下标就是  2*parent+2 。
    构造大根堆(小根堆):
        1.从最后一颗子树开始,从后往前调整
        2.每次调整,从下往上调整
        3.调整为大根堆(小根堆)
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 堆的上浮调整 新插入数据时候需要上浮调整以维护堆
void heap_up(vector<int> &arr)
{
    // 取出堆底的元素
    int child_index = arr.size() - 1;
    int parent_index = (child_index - 1) / 2;

    // 保存要调整的child节点  这里为了简单也可以直接交换父节点和子节点
    int temp = arr[child_index];
    while (child_index > 0 && temp < arr[parent_index]) {
        arr[child_index] = arr[parent_index];
        child_index = parent_index;
        // 一直往上寻找
        parent_index = (parent_index - 1) / 2;
    }
    // 找到了 交换
    arr[child_index] = temp;
}

// 堆的下沉调整 大数下沉成小堆 小数下沉成大堆 默认大堆
void heap_down(vector<int> &arr, int parent_index, int len, bool is_big = true)
{
    // 保存父节点
    int temp = arr[parent_index];

    // 初始默认为左孩子 因为左孩子一定存在,右孩子可能不存在
    int child_index = 2 * parent_index + 1;
    while (child_index < len) {
        // 构建大堆
        if (is_big) {
            // 定位到右孩子
            if (child_index + 1 < len && arr[child_index + 1] > arr[child_index]) {
                child_index++;
            }
            // 退出条件
            if (temp >= arr[child_index]) {
                break;
            }
            // 构建小堆
        } else {
            if (child_index + 1 < len && arr[child_index + 1] < arr[child_index]) {
                child_index++;
            }
            if (temp <= arr[child_index]) {
                break;
            }
        }

        // 无需真的交换 单项赋值就可以
        arr[parent_index] = arr[child_index];
        parent_index = child_index;
        child_index = 2 * parent_index + 1;
    }

    // 赋值
    arr[parent_index] = temp;
}

// 堆的创建
void creat_heap(vector<int> &arr)
{
    // 从最后一个非叶子节点开始,依次下沉调整堆
    for (int i = arr.size() / 2; i >= 0; i--) {
        heap_down(arr, i, arr.size());
    }
}

// 堆排序
void heap_sort(vector<int> &arr, int len)
{
    // 构造大顶堆
    // 一定要从后往前调整 初始为最后一个非叶节点,即至少有一个左孩子
    for (int i = len / 2 - 1; i >= 0; i--) {
        heap_down(arr, i, len);
    }

    // 循环交换堆顶元素,移到集合尾部,调节堆产生新的堆顶
    for (int i = len - 1; i > 0; --i) {
        swap(arr[i], arr[0]);
        // 每次循环后 堆最后一个元素即有序
        heap_down(arr, 0, i);
    }
}

int main(int argc, char const *argv[])
{
    vector<int> arr = {1, 3, 2, 6, 5, 7, 8, 9, 10, 0};
    heap_sort(arr, arr.size());

    for_each(arr.begin(), arr.end(), [](const int &val) { cout << val << ' '; });
    cout << endl;

    return 0;
}
