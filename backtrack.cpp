#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 回溯算法 核心代码
void backtrack(vector<vector<int>> &res, vector<int> &arr, vector<int> &track)
{
    // 递归的出口
    if (track.size() == arr.size())
    {
        res.push_back(vector<int>(track));
        return;
    }

    // for 选择 in 选择列表
    for (int i = 0; i < arr.size(); i++)
    {
        // 排除重复选项
        if (count(track.begin(), track.end(), arr[i]))
        {
            continue;
        }

        // 进行选择
        track.push_back(arr[i]);
        // 进入下一层决策树
        backtrack(res, arr, track);
        // 撤销选择
        track.pop_back();
    }
}

// 全排列
void permute(vector<int> &arr)
{
    // 记录全排列的结果
    vector<vector<int>> res;
    // 记录路径
    vector<int> track;

    backtrack(res, arr, track);

    // 输出
    for (auto &vals : res)
    {
        for (auto &val : vals)
        {
            cout << val << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{

    vector<int> arr{1, 2, 3, 4};
    permute(arr);

    return 0;
}
