/* RMQ 是ST(sparse table 稀疏表)算法，可以再预处理时间复杂度
   O(nlogn)，查找时间O(1)的复杂度情况下完成数组中的范围最值查找。
   比如n长度的数组A，查找A[i, j]（A中i到j范围内的最大值）.
   方法1. 顺序遍历一次，O(n),缺点在于多次查找时时间代价太大
   方法2. DP，用O(n*n)的空间存储所有范围内最值，缺点在于空间复杂度过大
   方法3. RMQ，时间复杂度O(1),预处理O(nlogn)只要一次，空间复杂度O(nlogn)
   方法4. 线段树
   算法说明网站 http://comzyh.com/blog/archives/273/ 有动画演示，非常清晰。
   二维RMQ from likunjk http://www.likunjk.com/article/1399210862.html
 */

#include <iostream>
#include <cstdlib>
#include <cmath>

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

// 顺序查找，O(n)
int sequece_search(int *a, int i, int j)
{
    int max = a[i];
    for (int k = i + 1; k <= j; ++ k)
    {
        max = (max < a[k] ? a[k] : max);
    }
    return max;
}

// 普通DP
int dp[N][N]; // dp[i][j] (j >= i) 表示i-j中的最大值
void initial_dp(int *a)
{
    for (int i = 0; i < N; ++ i)
        dp[i][i] = a[i];

    // 从下往上求去DP
    for (int j = N - 2; j >= 0; --j)
    {
        for (int k = j + 1; k < N; ++ k)
        {
            dp[j][k] = max(dp[j+1][k], dp[j][k-1]);
        }
    }
}

int dp_search(int *a, int i, int j)
{
    return dp[i][j];
}

// RMQ
// 计算n以2为底数的log值
int logtwo(int n)
{
    if (n == 0)
        return 0;
    int re = 0;
    while(n)
    {
        ++ re;
        n >>= 1;
    }

    return (re-1);
}

int **rmq_dp;

void initial(int *a)
{
    int row = logtwo(N) + 1;
    int column = N;

    // allocate rmq_dp
    rmq_dp = new int*[row];
    for (int i = 0; i < row; ++ i)
        rmq_dp[i] = new int[column];

    // 初始化
    // f(i, 0)
    for (int i = 0; i < column; ++ i)
        rmq_dp[0][i] = a[i];
     // f(i, j)
    int size = 1;
    for (int i = 1; i < row; ++ i)
    {
        size *= 2; // pow(2, i)
        for (int j = 0; j + size <= N; ++ j)
        {
            // f(i, j + 1) = max(f(i, j), f(i + size, j))
            rmq_dp[i][j] = max(rmq_dp[i-1][j], rmq_dp[i-1][j + size >> 1]);
        }
    }
    /*
    // show
    for (int i = 0; i < N; ++ i)
        cout << i + 1 << "\t";
    cout << endl;
    for (int i = 0 ;i < row; ++ i)
    {
        for (int j = 0; j < column; ++ j)
            cout << rmq_dp[i][j] << "\t";
        cout << endl;
    }
    */

}

int rmq_search(int *a, int i, int j)
{
    int len = j - i + 1;
    int row = logtwo(len);
    return max(rmq_dp[row][i], rmq_dp[row][j - (1<<row)]);
}


// 测试
void test(int *a, int func(int *, int , int))
{
    cout << "max in 1, 9 : " << func(a, 0, 8) << endl;
    cout << "max in 2, 5 : " << func(a, 1, 4) << endl;
    cout << "max in 6, 6 : " << func(a, 5, 5) << endl;
}


int main()
{
    int a[N];

    // 随机产生一组N大小的数组
    rand_array(a);
    show(a);


    // 顺序测试
    cout << "顺序查找测试:" << endl;
    test(a, sequece_search);

    // 普通DP测试
    cout << "普通DP查找测试:" << endl;
    initial_dp(a);
    test(a, dp_search);

    // rmq_dp test
    cout << "RMQ查找测试:" << endl;
    initial(a);
    test(a, rmq_search);

    // clear
    for (int i = 0; i <= logtwo(N); ++ i)
        delete []rmq_dp[i];
    delete []rmq_dp;

    return 0;
}
