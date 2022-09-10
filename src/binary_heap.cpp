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
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void _random(vector<int> &arr, int n = 10)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % 20);
    }
}

// 堆的上浮调整 堆的插入需要上浮调整以维护堆的结构
void adjust_up(vector<int> &arr, int child_index)
{
    int parent_index = (child_index - 1) / 2;

    // 保存要调整的child节点
    int temp = arr[child_index];
    //建小堆后面用小于号，建大堆后面用大于号
    while (child_index > 0 && temp > arr[parent_index]) {
        //建小堆用小于号，建大堆用大于号
        if (temp > arr[parent_index]) {
            arr[child_index] = arr[parent_index];
            child_index = parent_index;
            // 一直往上寻找
            parent_index = (parent_index - 1) / 2;
        } else {
            break;
        }
    }
    // 赋值
    arr[child_index] = temp;
}

// 堆的下沉调整。堆的删除需要上浮调整以维护堆的结构
void adjust_down(vector<int> &arr, int parent_index, int len)
{
    // 保存父节点
    int temp = arr[parent_index];

    // 初始默认为左孩子 因为左孩子一定存在,右孩子可能不存在
    int child_index = 2 * parent_index + 1;
    while (child_index < len) {
        // 挑出两个子节点中更大或更小的那个
        // 建立小堆后面用小于号 建立大堆后面用大于号
        if (child_index + 1 < len && arr[child_index + 1] > arr[child_index]) {
            child_index++;
        }
        // 儿子和父亲作比较
        // 建立小堆用小于号 建立大堆用大于号
        if (arr[child_index] > temp) {
            // 无需真的交换 单项赋值就可以
            arr[parent_index] = arr[child_index];
            parent_index = child_index;
            child_index = 2 * parent_index + 1;
        } else {
            // 找到合适的位置就退出
            break;
        }
    }
    // 赋值
    arr[parent_index] = temp;
}

// 堆的创建
void _creat_heap(vector<int> &arr)
{
    // 方法1: 向上调整建立堆法
    for (int i = 0; i < arr.size(); i++) {
        adjust_up(arr, i);
    }

    // 方法2: 向下调整建堆法，叶子节点不用调，从最后一个父节点调即可
    // n-1为最后一个叶子节点，再减1除2是它的父节点，即整棵树的最后一个父节点
    // for (int i = (arr.size() - 1 - 1) / 2; i >= 0; i--) {
    //     adjust_down(arr, i, arr.size());
    // }
}

// 堆的插入 只能在堆的末尾进行操作，否则会破坏堆的整个结构。
void _push_heap(vector<int> &arr, int val)
{
    // 加入到末尾
    arr.push_back(val);
    // 末尾数上浮调整堆的结构
    adjust_up(arr, arr.size() - 1);
}

// 堆的删除 堆的删除要求在原有堆的基础上，删掉第一个元素，通过调整，形成新的堆
void _pop_heap(vector<int> &arr)
{
    // 交换首节点和尾结点的值
    swap(arr.at(0), arr.at(arr.size() - 1));
    // 删除最后一个节点
    arr.pop_back();
    // 下沉首节点调整堆的结构
    adjust_down(arr, 0, arr.size());
}

// 堆排序
void _heap_sort(vector<int> &arr, int len)
{
    // 构造大顶堆
    // 一定要从后往前调整 初始为最后一个非叶节点,即至少有一个左孩子
    for (int i = (len - 1 - 1) / 2; i >= 0; i--) {
        adjust_down(arr, i, len);
    }

    // 循环交换堆顶元素,移到集合尾部,调节堆产生新的堆顶
    for (int i = len - 1; i > 0; --i) {
        swap(arr[i], arr[0]);
        // 每次循环后 堆最后一个元素即有序
        adjust_down(arr, 0, i);
    }
}

int main(int argc, char const *argv[])
{
    // 二叉堆数据结构
    vector<int> arr{4, 2, 3, 7, 5, 4};
    // _random(arr);

    // _heap_sort(arr, arr.size());
    _creat_heap(arr);
    _push_heap(arr, 0);
    _pop_heap(arr);

    for_each(arr.begin(), arr.end(), [](const int &val) { cout << val << ' '; });
    cout << endl;

    return 0;
}
