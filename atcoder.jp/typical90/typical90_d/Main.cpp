#include <iostream>
using namespace std;

int H, W;
int A[2000][2000], B[2000][2000];
int Row[2000], Col[2000];

int main(int argc, char const *argv[])
{
    cin >> H >> W;
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            Row[i] += A[i][j];
            Col[j] += A[i][j];
        }
    }

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            B[i][j] += Row[i] + Col[j] - A[i][j];
        }
    }

    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}