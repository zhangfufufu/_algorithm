#include <iostream>
#include <vector>

using namespace std;

// 查找目标数
int binary_search(vector<int> &arr, int target) {
    if (arr.empty()) {
        return -1;
    }
    // 二分查找 有序数组
    int left = 0;
    int right = arr.size() - 1;

    // 注意点:一定要left <= right
    // 每次循环后更新mid值
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (target < arr[mid]) {
            // 缩减右边界
            right = mid - 1;
        } else if (target > arr[mid]) {
            // 缩减左边界
            left = mid + 1;
        }
    }

    return -1;
}

// 查找左边界 返回left 需要判断left是否>=数组长度
int binary_search_left(vector<int> &arr, int target) {
    if (arr.empty()) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (target == arr[mid]) {
            right = mid - 1;
        } else if (target < arr[mid]) {
            right = mid - 1;
        } else if (target > arr[mid]) {
            left = mid + 1;
        }
    }

    // cout << "left=" << left << endl;
    // cout << "right=" << right << endl;

    // 因为返回的是left,而循环退出条件是left=right+1,所以需要判断left的右边界
    if (left >= arr.size() || arr[left] != target) {
        return -1;
    }
    return left;
}

// 查找右边界 返回right 需要判断right是否<0
int binary_search_right(vector<int> &arr, int target) {
    if (arr.empty()) {
        return -1;
    }

    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            // 因为要找右边界 所以需要收缩左边界
            left = mid + 1;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else if (arr[mid] > target) {
            right = mid - 1;
        }
    }
    // cout << "left=" << left << endl;
    // cout << "right=" << right << endl;

    // 因为返回的是right,而循环退出条件为right=left-1,所以需要判断right的左边界
    if (right < 0 || arr[right] != target) {
        return -1;
    }

    return right;
}
