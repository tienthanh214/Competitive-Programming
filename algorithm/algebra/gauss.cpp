#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

namespace LES {
    static const double eps = 1e-9;
    vector<int> where;
    vector<double> res;
    vector<vector<double>> gauss;

    vector<vector<double>> Gauss(vector<vector<double>> a) {
        // cerr << " ------------ Running Gauss Elimination --------------" << endl;
        int n = a.size(), m = a[0].size() - 1;
        where.assign(m, -1);
        for (int col = 0, row = 0; row < n && col < m; ++col) {
            int select = row;
            for (int i = row; i < n; ++i) 
                if (abs(a[i][col]) > abs(a[select][col]))
                    select = i;
            if (abs(a[select][col]) < eps) // col i row i -> n all zero, can't convert
                continue;
            if (abs(a[row][col]) < eps)
                for (int j = 0; j < a[row].size(); ++j) // basic swap operator
                    swap(a[row][j], a[select][j]);
            where[col] = row;
            for (int i = row + 1; i < n; ++i) { // elimination 
                double coef = a[i][col] / a[row][col]; 
                for (int j = col; j < a[i].size(); ++j)
                    a[i][j] -= coef * a[row][j];
            }
            ++row; 

            /*
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j)
                    printf("%6.2f ", a[i][j]);
                printf("| %6.2f\n", a[i].back());
            }
            putchar('\n');
            */
            
        }
        return a;  
    }

    int getResult(const vector<vector<double>> &a) {
        int n = a.size(), m = a[0].size() - 1; //number of equation, number of variable
        res.assign(m, 0);
        for (int col = m - 1; col >= 0; --col) {
            int row = where[col];
            //cout << col << " " << row << endl;
            if (row == -1) continue; //cot khong the chuan hoa
            res[col] = a[row].back();
            for (int i = col + 1; i < m; ++i) 
                res[col] -= a[row][i] * res[i];
            
            res[col] /= a[row][col];
        }
        // check conflict
        for (int i = 0; i < n; ++i) {
            bool check = true;
            for (int j = 0; j < m; ++j) 
                check &= abs(a[i][j]) < eps;
            if (check && abs(a[i].back()) > eps) // 0x + 0y + 0z + ... = x (x != 0)
                return 0;
        }
        // check infinity
        for (int i = 0; i < m; ++i)
            if (where[i] == -1)
                return -1;
        return 1;
    }

    int Solve(vector<vector<double>> a) {
        gauss = Gauss(a);
        
        /*
        cerr << "------------- After Gauss - elimination -------------\n";

        for (int i = 0; i < a.size(); ++i) {
            for (int j = 0; j < a[i].size(); ++j)
                printf("%6.2f ", gauss[i][j]);
            printf("| %6.2f\n", gauss[i].back());
        }
        */
        return getResult(gauss);
    }
}

void readEquations(vector<vector<double>> &a) {
    int n, m; scanf("%d%d", &n, &m);
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        a[i].resize(m + 1);
        for (int j = 0; j < m; ++j)
            scanf("%lf", &a[i][j]);
    }
    for (int i = 0; i < n; i++) 
        scanf("%lf", &a[i][m]);
}

int main() {
    while (true) {
        vector<vector<double>> a;
        readEquations(a);
        
        if (a.size() == 0) break;
        /*
        cerr << "------------- Linear Equations -------------\n" << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                printf("%6.2f ", a[i][j]);
            printf("| %6.2f\n", a[i].back());
        }
        putchar('\n');
        */
           
        /*
        
        */
        int ans = LES::Solve(a);
        
        if (ans == 0) puts("inconsistent");
        else if (ans == -1) {
            puts("multiple");
            for (int i = 0; i < LES::res.size(); ++i)
                if (LES::where[i] == -1)
                    printf("? ");
                else 
                    printf("%.4f ", LES::res[i]);
            putchar('\n');
            
        }
        else {
            for (int i = 0; i < LES::res.size(); ++i)
                printf("%.4f ", LES::res[i]);
            putchar('\n');
        }
    }
    return 0;
}
/*
3
4 5
1 -1 3 -2 0
3 -1 8 -6 2
2 4 6 -6 7 
-2 6 -5 2 5 
4 5 -11 -20

4 4
5 -19 12 -15
-2 8 -5 7
4 -8 9 4
-7 15 -17 -4
-16 7 2 0
4 4
2 -1 0 5
-4 -1 4 -12
-2 -5 7 -6
6 0 -3 20
3 18 38 -14
3 3
1 -2 0
2 -4 0
1 -2 1
3 6 4

4 4
1 2 3 -2
-2 1 2 3
3 2 -1 2
2 -3 2 1 
6 -8 4 -8
//1 2 -1 2

4 5
3 1 -2 1 -1
2 -1 7 -3 5
1 3 -2 5 -7
3 -2 7 -5 8
1 2 3 3
// vo nghiem

4 5
1 1 0 -3 -1
1 -1 2 -1 0
4 -2 6 3 -4
2 4 -2 4 -7
-2 1 7 1


0
*/
