#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

using lli = long long int;

const lli MOD = 1e9 + 7;

struct Matrix{
    vector<vector<lli>> mat;

    Matrix(int n, int m){
        mat.resize(n);
        for(int i = 0; i < n; i++)
            mat[i].resize(m);
    }
    Matrix operator*(Matrix m){
        if(mat[0].size() != m.mat.size())
            throw -1;
        Matrix res = Matrix(mat.size(), m.mat[0].size());
        for(int i = 0; i < mat.size(); i++){
            for(int j = 0; j < m.mat[0].size(); j++){
                for(int k = 0; k < m.mat.size(); k++){
                    res[i][j] += mat[i][k] * m.mat[k][j];
                    res[i][j] %= MOD;
                }
            }
        }
        return res;
    }
    vector<lli>& operator[](int i){
        return mat[i];
    }
    void PrintMat(){
        for(int i = 0; i < mat.size(); i++){
            for(int j = 0; j < mat[0].size(); j++){
                cout << mat[i][j] << " ";
            }
            cout << '\n';
        }
    }
};

Matrix GetRes(Matrix x, int n){
    if(n == 1)
        return x;
    if(n & 1)
        return x * GetRes(x * x, n >> 1);
    return GetRes(x * x, n >> 1);
}

int main(){
    fastio;
    int k, n;
    cin >> k >> n;
    int i;

    Matrix powMat(k + 2, k + 2);
    for(i = 0; i <= k + 1; i++){
        for(int j = 0; j <= k + 1; j++){
            powMat[i][j] = (i <= j);
        }
    }

    cout << GetRes(powMat, n)[0][k + 1];
    return 0;
}
