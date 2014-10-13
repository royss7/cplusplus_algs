/* 简单线段树实现数组区间查找，时间复杂度O(logn),空间O(n) */
#include <iostream>
#include <cstdlib>

using namespace std;

const int N = 9; // 数组大小

void rand_array(int *a)
{
    for (int i = 0; i < N; ++ i)
        a[i] = static_cast<int>(rand()) % 100;
}

void show(int *a)
{
    for (int i = 0; i < N; ++ i)
        cout << a[i] << " ";
    cout << endl;
}

struct node
{
    int start, end; // 区间开始和结束的下标
    int val; // 该区间的最大值
};

node tree[N + N]; // 线段树是一个完全二叉树，用数组实现即可
// build the interval tree
// root 是当前数的根节点所在位置，s是当前区间的起始位置，e是当前区间的结束位置
void build(int *a, int root, int s, int e)
{
    tree[root].start = s;
    tree[root].end = e;
    // 当前区间只有一个节点
    if (s == e)
    {
        tree[root].val = a[s];
        return ;
    }

    // 先构造孩子，然后去的val值
    build(a, root*2, s, (s + (e-s)/2));
    build(a, root*2 + 1, (s + (e-s)/2 + 1), e);
    tree[root].val = max(tree[root*2].val, tree[root*2 + 1].val);
}

void show_tree()
{
    // 按层序输出
    int endline = 1;
    for (int i = 1; i < N + N; ++ i)
    {
        cout << "[" << tree[i].start << ", " << tree[i].end << "]" << "-> " << tree[i].val << " |||| " ;
        if (endline == i)
        {
            cout << endl;
            endline *= 2;
            ++ endline;
        }
    }
    cout << endl;
}

// interval tree search
int interval_tree_search(int *a, int root, int i, int j)
{
    if (i == j)
        return a[i];
    if (i == tree[root].start && j == tree[root].end)
        return tree[root].val;

    int mid = (tree[root].start + tree[root].end)/2;
    if (mid >= j) // left
        return interval_tree_search(a, root * 2, i, j);
    if (i > mid) // right
        return interval_tree_search(a, root * 2 + 1, i, j);
    // 被分割在两边
    return max(interval_tree_search(a, root * 2, i, mid), interval_tree_search(a, root*2 + 1, mid + 1, j));
}

// 测试
void test(int *a, int func(int *, int, int , int))
{
    cout << "max in 1, 9 : " << func(a, 1, 0, 8) << endl;
    cout << "max in 2, 5 : " << func(a, 1, 1, 4) << endl;
    cout << "max in 6, 6 : " << func(a, 1, 5, 5) << endl;
}


int main()
{
    int a[N];

    // 随机产生一组N大小的数组
    rand_array(a);
    show(a);


    // interval tree test
    cout << "interval tree查找测试:" << endl;
    build(a, 1, 0, N-1);
    // show_tree();
    test(a, interval_tree_search);

    return 0;
}

