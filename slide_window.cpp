// 滑动窗口算法

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// 滑动窗口算法框架
void __slide_window(string s, string t)
{
    unordered_map<char, int> need, window;
    for (char c : t) {
        need[c]++;
    }
    int left = 0, right = 0;
    int valid = 0;
    while (right < s.size()) {
        /* c是即将要移入窗口的字符 */
        char c = s[right];
        // 右移窗口
        right++;
        // 进行窗口内数据一系列更新...

        // debug 输出位置
        printf("window: [%d, %d]\n", left, right);

        // 判断左侧窗口是否要收缩
        while (1 /*window needs shrink*/) {
            // d 是即将被移出窗口的字符
            char d = s[left];
            // 左移窗口
            left++;

            // 进行窗口内数据的一系列更新...
        }
    }
}

// 实现最小覆盖子串问题
// 链接：https://leetcode.cn/problems/minimum-window-substring

/*
    给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s
中不存在涵盖 t 所有字符的子串， 则返回空字符串 "" 。 注意：

    对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
    如果 s 中存在这样的子串，我们保证它是唯一的答案。

    示例 1：

    输入：s = "ADOBECODEBANC", t = "ABC"
    输出："BANC"
*/
string minWindow(string s, string t)
{
    unordered_map<char, int> need, window;

    // 初始化need窗口
    for (char c : t) {
        need[c]++;
    }

    int left  = 0;
    int right = 0;
    int valid = 0;  // 计数器 有效位数

    // 定义最小覆盖子串的索引和长度
    int start = 0;
    int len   = INT_MAX;
    while (right < s.size()) {
        // 开始滑动
        // 取出一个字符
        char c = s[right];
        right++;

        // 进行窗口内数据更新
        if (need.count(c)) {
            window[c]++;
            if (window[c] == need[c]) {
                valid++;
            }
        }

        // 判断左侧窗口是否需要收缩
        while (valid == need.size()) {
            // 更新最小覆盖子串
            if (right - left < len) {
                start = left;
                len   = right - left;
            }

            // d是将要移出的字符
            char d = s[left];
            left++;
            // 进行窗口数据更新
            if (need.count(d)) {
                if (window[d] == need[d]) {
                    valid--;
                }
                window[d]--;
            }
        }
    }
    // 返回最小的覆盖子串
    return len == INT_MAX ? "" : s.substr(start, len);
}

int main(int argc, char const *argv[])
{
    string s("ADOBECODEBANC");
    string t("ABC");
    cout << minWindow(s, t) << endl;

    return 0;
}
