/* 在两个有序数组中求出它们的中位数 */

#include <iostream>

using namespace std;

int medianoftwo(int a[], int n, int b[], int m)
{
    /* 第一种方法，直接合并然后输出 O(n+m) */
    /*
    int *c = new int[n+m];
    int k = 0;

    for (int i = 0, j = 0; i < n || j < m;)
    {
        if (i >= n) // a is used for all
            c[k++] = b[j++];
        else if (j >= m) // b is used for all
            c[k++] = a[i++];
        else if (a[i] > b[j])
            c[k++] = b[j++];
        else
            c[k++] = a[i++];
    }

    int temp = c[(n+m)/2];
    delete []c;
    return temp;
    */
    /* 方法2. 二分法查找 o(log(n+m)) */
    int ma = (n-1)/2, mb = (m-1)/2;

    //cout << "len of a = " << n << endl;
    //cout << "len of b = " << m << endl;
    if (n == 1)
    {
        // 递归终止条件
        if (m == 1)
            return a[0] > b[0] ? b[0] : a[0];
        if (m % 2 == 0)
        {
            if (a[0] >= b[mb+1])
                return b[mb+1];
            else if (a[0] <= b[mb])
                return b[mb];
            else
                return a[0];
        }
        else
        {
            if (a[0] >= b[mb])
                return b[mb];
            else if (a[0] <= b[mb - 1])
                return b[mb-1];
            else
                return a[0];
        }
    }
    else if (m == 1) // 递归终止条件
    {
        if (n % 2 == 0)
        {
            if (b[0] >= a[ma+1])
                return a[ma + 1];
            else if (b[0] <= a[ma])
                return a[ma];
            else
                return b[0];
        }
        else
        {
            if (b[0] >= a[ma])
                return a[ma];
            else if (b[0] <= a[ma-1])
                return a[ma-1];
            else
                return b[0];
        }
    }
    else //继续递归
    {
        int cutLen = n / 2 > m / 2 ? m/2 : n / 2; // 截取其中较短的一部分
        if (a[ma] == b[mb])
                return a[ma];
        else if (a[ma] < b[mb])
            return medianoftwo(&a[cutLen], n - cutLen, b, m - cutLen);
        else
            return medianoftwo(a, n - cutLen, &b[cutLen], m - cutLen);
    }

}

int main()
{
    int a[5] = {1, 3, 5, 7, 9};
    int b[4] = {2, 4, 6, 8};

    cout << medianoftwo(a, 5, b, 4) << endl;

    return 0;
}
