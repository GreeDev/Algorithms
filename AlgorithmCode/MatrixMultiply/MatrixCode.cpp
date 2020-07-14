#include <bits/stdc++.h>

using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(0)

class Matrix{
    using lli = long long int;
private:
    vector<vector<lli> > mat;
public:
    Matrix(int y_size = 1, int x_size = 1){
        mat.resize(y_size);
        for(int i = 0; i < y_size; i++){
            mat[i].resize(x_size);
        }
    }

    pair<size_t, size_t> size() const{
        return make_pair(mat.size(), mat[0].size());
    }

    Matrix operator*(const Matrix& cal) const{
        pair<size_t, size_t> aSize = size();
        pair<size_t, size_t> bSize = cal.size();
        if(aSize.second != bSize.first)
            throw -1;

        Matrix res(aSize.first, bSize.second);

        for(size_t i = 0; i < aSize.first; i++){
            for(size_t j = 0; j < bSize.second; j++){
                for(size_t k = 0; k < aSize.second; k++){
                    res[i][j] += (*this)[i][k] * cal[k][j];
                }
            }
        }

        return res;
    }
    bool operator==(const Matrix& cal) const{
        pair<size_t, size_t> aSize = size();
        pair<size_t, size_t> bSize = cal.size();
        if(aSize != bSize)
            return false;
        for(size_t i = 0; i < aSize.first; i++){
            for(size_t j = 0; j < aSize.second; j++){
                if((*this)[i][j] != cal[i][j])
                    return false;
            }
        }
        return true;
    }

    vector<lli>& operator[](int idx){
        return mat[idx];
    }
    const vector<lli>& operator[](int idx) const{
        return mat[idx];
    }

    void PrintMatrix() const{
        for(auto& m: mat){
            for(auto& v: m){
                cout << v << " ";
            }
            cout << '\n';
        }
    }
};

int main(){
    fastio;
    int n, m;
    cin >> n >> m;
    Matrix m1(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> m1[i][j];
        }
    }
    cin >> n >> m;
    Matrix m2(n, m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> m2[i][j];
        }
    }
    (m1 * m2).PrintMatrix();
}
