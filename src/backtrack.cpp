#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 回溯算法 全排列问题
void backtrack(vector<vector<int>> &res, vector<int> &arr, vector<int> &track, vector<bool> &used) {
    // 递归的出口
    if (track.size() == arr.size()) {
        res.push_back(vector<int>(track));
        return;
    }

    // for 选择 in 选择列表
    for (int i = 0, last = -1; i < arr.size(); i++) {
        // 路径走过，直接跳过
        if (used[i]) {
            continue;
        }
        // 上次的选择和本次一样，直接跳过 防止重复
        if (last != -1 && arr[i] == arr[last]) {
            continue;
        }
        last = i;
        // 进行选择
        track.push_back(arr[i]);
        used[i] = true;
        // 进入下一层决策树
        backtrack(res, arr, track, used);
        // 撤销选择
        track.pop_back();
        used[i] = false;
    }
}

// 全排列 可包含重复数字
vector<vector<int>> permute(vector<int> &arr) {
    // 记录全排列的结果
    vector<vector<int>> res;
    // 记录路径
    vector<int> track;
    // 记录路径是否已经走过
    vector<bool> used(arr.size(), false);

    // 需要先排序将相同元素放在一起好过滤
    sort(arr.begin(), arr.end());

    backtrack(res, arr, track, used);

    return res;
}

void output(vector<vector<int>> &arr) {
    // 输出
    for (auto &vals : arr) {
        for (auto &val : vals) {
            cout << val << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char const *argv[]) {
    vector<int> arr = {1, 3, 1, 4};
    vector<vector<int>> res = permute(arr);
    output(res);
    return 0;
}
