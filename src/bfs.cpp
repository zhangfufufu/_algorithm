// 广度优先算法

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 求二叉树的最大深度 BFS
int maxDepth(TreeNode *root)
{
    if (root == nullptr) {
        return 0;
    }

    // 定义队列
    queue<TreeNode *> que;
    que.push(root);

    int depth = 0;

    while (!que.empty()) {
        int sz = que.size();
        for (int i = 0; i < sz; i++) {
            TreeNode *cur = que.front();
            que.pop();

            if (cur->left) {
                que.push(cur->left);
            }
            if (cur->right) {
                que.push(cur->right);
            }
        }
        depth++;
    }
    return depth;
}

// 求二叉树的最小高度
int minDepth(TreeNode *root)
{
    if (root == nullptr) {
        return 0;
    }

    queue<TreeNode *> que;
    que.push(root);

    // root本身就是1层
    int depth = 1;

    while (!que.empty()) {
        int sz = que.size();
        // 将当前队列的所有子节点向四周扩散
        for (int i = 0; i < sz; i++) {
            TreeNode *cur = que.front();
            que.pop();
            // 退出条件 最靠近根节点的叶子节点(节点左右节点均为NULL的节点)
            if (cur->left == nullptr || cur->right == nullptr) {
                return depth;
            }
            // 将当前cur的相邻节点加入队列
            if (cur->left) {
                que.push(cur->left);
            }
            if (cur->right) {
                que.push(cur->right);
            }
        }
        depth++;
    }
    return depth;
}
