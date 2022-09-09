// 二叉树

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <queue>
#include <stack>

// 二叉树结构
typedef struct binary_tree {
    int data;                   // 数据域
    struct binary_tree *left;   // 左节点指针
    struct binary_tree *right;  // 右节点指针

} Node;

// 二叉树初始化
/*
    malloc分配内存，然后初始化节点左右指针域为空，以及数据域为gain，
    最后*tree=temp把节点安装到树上，并且返回上一级；对于已经存在的树节点，
    我们需要往左右两分子扩展；当gain小于上一级的data，那就创建左子树并把值赋给该节点，
    当gain大于上一级的data，那就创建右子树并把值赋给该节点。
*/

//指向指针变量的指针，结果是指针tree所指向的值
void insert(Node **tree, int num)
{
    Node *temp = nullptr;
    // 判断是否有根节点
    if (!(*tree)) {
        // 创建根节点
        temp = (Node *)malloc(sizeof(Node));
        // 左右节点置位空 数据域赋值
        temp->left = nullptr;
        temp->right = nullptr;
        temp->data = num;
        // 将新创建的节点挂载到树上
        *tree = temp;
        return;
    }

    // 判断插入到左节点还是右节点
    if (num < (*tree)->data) {
        // 创建左子树
        insert(&(*tree)->left, num);
    } else {
        // 创建右子树
        insert(&(*tree)->right, num);
    }
}

// 前序遍历
void pre_order(Node *root)
{
    // root 左 右
    if (!root) {
        return;
    }

    Node *node = root;

    printf("%d ", node->data);
    pre_order(node->left);
    pre_order(node->right);
}

// 前序遍历 循环
void pre_order_loop(Node *root)
{
    if (root == nullptr) {
        return;
    }

    std::stack<Node *> stk;
    Node *node = root;
    // root 左 右
    while (node || !stk.empty()) {
        while (node) {
            printf("%d ", node->data);
            stk.push(node);
            node = node->left;
        }

        node = stk.top();
        stk.pop();

        node = node->right;
    }
}

// 中序遍历
void mid_order(Node *root)
{
    // 左 root 右
    if (root == nullptr) {
        return;
    }

    Node *node = root;

    mid_order(node->left);
    printf("%d ", node->data);
    mid_order(node->right);
}

// 中序遍历 循环
void mid_order_loop(Node *root)
{
    if (root == nullptr) {
        return;
    }

    std::stack<Node *> stk;
    Node *node = root;

    // 模拟递归压栈的过程
    while (!stk.empty() || node) {
        while (node) {
            // 不断往左子树方向走，每走一次就将当前节点保存到栈中
            // 这是模拟递归的调用
            stk.push(node);
            node = node->left;
        }

        // 当前节点为空，说明左边走到头了，从栈中弹出节点并保存
        // 然后转向右边节点，继续上面整个过程
        node = stk.top();
        stk.pop();
        printf("%d ", node->data);

        // 转向右边节点
        node = node->right;
    }
}

// 后序遍历
void last_order(Node *root)
{
    if (!root) {
        return;
    }
    // 左 右 root
    last_order(root->left);
    last_order(root->right);
    printf("%d ", root->data);
}

// 后序遍历 循环
void last_order_loop(Node *root)
{
    if (root == nullptr) {
        return;
    }
    // 左 右 root
    std::stack<Node *> stk;
    Node *node = root;
    // 比中序遍历多了一步判断,需要定义一个前置指针判断是否有右节点
    Node *prev = nullptr;

    while (node || !stk.empty()) {
        // 1.遍历到最左子节点
        while (node) {
            stk.push(node);
            node = node->left;
        }
        // 取出栈顶元素开始判断
        node = stk.top();
        stk.pop();

        // 2.遍历最左子节点的右子树(右子树存在 && 未访问过)
        if (node->right && node->right != prev) {
            // 重复压栈以记录当前路径分叉节点
            stk.push(node);
            // node开始访问右节点
            node = node->right;
        } else {
            // 后序：最后输出 在node->left和node->right后面
            // 注意：此时node的左右子树应均已完成访问
            printf("%d ", node->data);
            // 避免重复访问右子树[记录当前节点便于下一步对比]
            prev = node;
            // 避免重复访问左子树[设空节点]
            node = nullptr;
        }
    }
}

// 二叉树的层序遍历
void level_order(Node *root)
{
    if (root == nullptr) {
        return;
    }
    // 借助queue 数据结构

    std::queue<Node *> que;
    que.push(root);
    Node *node = NULL;

    while (!que.empty()) {
        size_t size = que.size();

        for (size_t i = 0; i < size; i++) {
            node = que.front();
            que.pop();
            std::cout << node->data << ' ';
            if (node->left) {
                que.push(node->left);
            }
            if (node->right) {
                que.push(node->right);
            }
        }
    }

    std::cout << std::endl;
}

// 释放二叉树
void destroy(Node *root)
{
    if (!root) {
        return;
    }
    // 采用后续遍历的方式删除
    destroy(root->left);
    destroy(root->right);
    free(root);
}

// int main(int argc, char const *argv[])
// {
//     Node *root;
//     root = nullptr;
//     insert(&root, 5);
//     insert(&root, 2);
//     insert(&root, 3);
//     insert(&root, 8);
//     insert(&root, 7);
//     insert(&root, 5);
//     insert(&root, 2);

//     // 遍历
//     printf("--------------pre_order--------------\n");
//     pre_order(root);
//     printf("\n--------------pre_order_loop--------------\n");
//     pre_order_loop(root);

//     printf("\n\n--------------mid_order--------------\n");
//     mid_order(root);
//     printf("\n--------------mid_order_loop--------------\n");
//     mid_order_loop(root);

//     printf("\n\n--------------last_order--------------\n");
//     last_order(root);
//     printf("\n--------------last_order_loop--------------\n");
//     last_order_loop(root);

//     printf("\n\n--------------level_order--------------\n");
//     level_order(root);

//     printf("\n");
//     // release
//     destroy(root);
//     return 0;
// }
