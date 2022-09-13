// 带头单链表

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// 定义链表结构
typedef struct link_list {
    int data;                // 数据域
    struct link_list *next;  // 指针域 指向下一个节点

} Node;

// 创建头结点
Node *creat_head_node() {
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    return head;
}

// 创建节点
Node *_creat_node(int x) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = NULL;

    return newNode;
}

// 头插节点
void push_front_node(Node *head, int num) {
    assert(head);

    Node *newNode = _creat_node(num);
    // 如果只有一个头结点
    if (head->next == NULL) {
        head->next = newNode;
    } else {
        // p指针保存头结点指向的第一个节点
        Node *tmp = head->next;
        head->next = newNode;
        newNode->next = tmp;
    }
}

// 尾插节点
void push_back_node(Node *head, int num) {
    assert(head);
    // 首先遍历到链表的尾部
    Node *cur = head;
    while (cur->next) {
        cur = cur->next;
    }

    // cur next指向新节点 新节点next置空
    Node *newNode = _creat_node(num);
    cur->next = newNode;
}

// 头删节点
void front_pop_node(Node *head) {
    if (head == NULL || head->next == NULL) {
        // 没有可以删除的节点
        printf("没有可以删除的节点...\n");
        return;
    }

    Node *tmp = head->next;
    head->next = head->next->next;
    free(tmp);  // 一定要最后再释放
}
// 尾删节点
void back_pop_node(Node *head) {
    if (head == NULL || head->next == NULL) {
        // 没有可以删除的节点
        printf("没有可以删除的节点...\n");
        return;
    }

    // 判断有一个节点还是多个节点
    if (head->next->next == NULL) {
        // 只有一个节点 直接删除
        free(head->next);
        head->next = NULL;
    } else {
        // 多个节点删除最后一个节点 必须找到最后一个节点和倒数第二个节点
        Node *cur = head->next;
        Node *pre = NULL;
        while (cur->next) {
            pre = cur;
            cur = cur->next;
        }
        // cur 当前指向最后一个节点
        free(cur);
        // pre 当前指向倒数第二个节点
        pre->next = NULL;
    }
}

// 遍历链表
void traverse_node(Node *Head) {
    if (Head == NULL) {
        return;
    }
    Node *p = Head;
    while (p->next) {
        p = p->next;
        printf("%d ", p->data);
    }
    printf("\n");
}

// 清空单链表 不销毁头节点
void clear_node(Node *Head) {
    Node *cur = Head;
    Node *next = NULL;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    Head->next = NULL;
}

// 销毁单链表 包括头节点 要改变头指针的值 所以需要传入二级指针
void destroy_node(Node **Head) {
    clear_node(*Head);
    // 销毁头指针
    free(*Head);
    *Head = NULL;
}

// 查找值为x的节点并返回节点的指针
Node *find_node(Node *head, int x) {
    if (head == NULL || head->next == NULL) {
        return NULL;
    }
    Node *cur = head->next;
    while (cur) {
        if (cur->data == x) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

// 链表的长度
int get_size(Node *head) {
    if (head == NULL || head->next == NULL) {
        return 0;
    }

    int count = 0;
    Node *cur = head->next;
    while (cur) {
        ++count;
        cur = cur->next;
    }
    return count;
}

// 排序

// 反转

int main(int argc, char const *argv[]) {
    Node *head = creat_head_node();

    // 头插法插入数据
    push_front_node(head, 5);
    push_front_node(head, 3);
    push_front_node(head, 7);
    // 尾插法插入数据
    push_back_node(head, 4);
    push_back_node(head, 8);
    push_back_node(head, 1);

    // 头删法删除数据
    // front_pop_node(head);
    // front_pop_node(head);

    // 尾删 删除数据
    back_pop_node(head);
    back_pop_node(head);

    // 遍历
    traverse_node(head);

    printf("linked_list size is %d\n", get_size(head));

    // clear_node(head);
    // traverse_node(head);

    return 0;
}
