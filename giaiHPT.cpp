#include <iostream>
#include <math.h>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

double MaTranKhu[100][100], x[100];
int rows, cols;
double saiso = 0.00000001;

void nhapMaTran(FILE *file)
{
    cin >> rows;
    cin >> cols;
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++)
            cin >> MaTranKhu[i][j];
}

void xuatMaTran()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
            cout << setw(15) << right << setprecision(10) << fixed << MaTranKhu[i][j];
        cout << endl;
    }
}

void hoanvi(double &a, double &b)
{
    double tmp = a;
    a = b;
    b = tmp;
}

int tinhRank(int row, int col)
{
    int rank = 0;
    if(row <= col)
    {
        for(int i = 0; i < row; i++)
            for(int j = 0; j < col; j++)
            {
                if (fabs(MaTranKhu[i][j]) >= saiso)
                {
                    rank++;
                    break;
                }
            }
    }
    else
    {
        for(int j = 0; j < col; j++)
        {
            for(int i = 0; i < row; i++)
                if (MaTranKhu[i][j] != 0)
                {
                    rank++;
                    break;
                }
        }
    }
    return rank;
}

void timNghiem()
{
    int rankA = tinhRank(rows, cols-1);
    int rankAbs = tinhRank(rows, cols);
    if(rankA != rankAbs)
    {
        cout << "HPT vo nghiem";
        return;
    }
    else
    {
        if(rankA == cols-1)
        {
            cout << "HPT co nghiem duy nhat" << endl;
            x[cols-2] = MaTranKhu[rows-1][cols-1]/MaTranKhu[rows-1][cols-2];
            for(int i = cols-3; i >= 0; i--)
            {
                x[i] = MaTranKhu[i][cols-1];
                for(int j = cols-2; j > i; j--)
                {
                    x[i] -= MaTranKhu[i][j]*x[j];
                }
                x[i] = x[i]/MaTranKhu[i][i];
            }
            for(int i = 0; i < rankA; i++)
            {
                cout << "x[" << i << "] = " << x[i] << endl;
            }
            return;
        }
    }
    cout << "HPT co vo so nghiem" << endl;
    int soThamSo = cols - 1 - rankA;
    int vitri[100], thamso[100];
    double y[100][100];
    for(int i = 0; i < rows; i ++)
    {
        for(int j = 0; j < cols-1; j++)
        {
            if(fabs(MaTranKhu[i][j]) > saiso)
            {
                vitri[i] = j;
                break;
            }
        }
    }
    int count = 0;
    for(int i = 0; i < rows; i++)
    {
        int check = 0;
        for(int j = 0; j < rows; j++)
        {
            if(vitri[j] == i) break;
            else check++;
        }
        if(check == rows) {thamso[count] = i; count++;}
    }
    for(int i = 0; i < soThamSo; i++)
    {
        for(int j = 0; j < rows; j++)
        {
            MaTranKhu[j][cols+i] = -MaTranKhu[j][thamso[i]];
        }
    }
    int col = cols-2;
    for(int i = rows-1-soThamSo; i >= 0; i--)
    {
        int check = 0;
        for(int j = 0; j < soThamSo; j++)
        {
            if(col == thamso[j])
            {
                check = 1;
                break;
            }
        }
        if(check == 1) {col--; i++; continue;}
        for(int j = 0; j <= soThamSo; j++)
        {
            y[col][j] = MaTranKhu[i][cols-1+j];
        }
        for(int j = cols-2; j > col; j--)
        {
            int checkk = 0;
            for(int k = 0; k < soThamSo; k++)
            {
                if(j == thamso[k])
                {
                    checkk = 1;
                    break;
                }
            }
            if(checkk == 1) continue;
            for(int k = 0; k <= soThamSo; k++)
                y[col][k] -= MaTranKhu[i][j]*y[j][k];
        }
        for(int k = 0; k <= soThamSo; k++)
            y[col][k] = y[col][k]/MaTranKhu[i][col];
        col--;
    }
    for(int i = 0; i < cols-1; i++)
    {
        int check = 0;
        for(int j = 0; j < soThamSo; j++)
        {
            if(i == thamso[j])
            {
                check = 1;
                break;
            }
        }
        if(check == 1) continue;
        cout << "x[" << i << "] = ";
        for(int j = 0; j <= soThamSo; j++)
        {
            cout << y[i][j];
            if(j > 0) cout << " . x[" << thamso[j-1] << "]";
            if(j < soThamSo) cout << "  +  ";
        }
        cout << endl;
    }
}
void ppKhuGauss()
{
    for(int i = 0; i < rows-1; i++)
    {
        cout << " === Lan lap thu " << i+1 << " ===" << endl;
        int col, index, fin = -1;
        for(int j = i; j < cols-1; j++)
        {
            index = -1;
            if(fabs(MaTranKhu[i][j]) <= saiso)
            {
                for(int k = i+1; k < rows; k++)
                {
                    if(fabs(MaTranKhu[k][j]) > saiso)
                    {
                        index = k;
                        break;
                    }
                }
                if(index == -1 && j == cols-2)
                {
                    fin = 1;
                    break;
                }
                if(index == -1) continue;
                else
                {
                    cout << "Hoan vi 2 hang " << i << " va " << index << endl;
                    for(int k = j; k < cols; k++)
                        hoanvi(MaTranKhu[i][k], MaTranKhu[index][k]);
                    col = j;
                }
            }
            else
            {
                index = i;
                col = j;
            }
            if(index != -1 && fin != 1)
            {
                cout << "Phan tu khu A[" << i << "][" << col << "] = " << MaTranKhu[i][col] << endl;
                for(int l = i+1; l < rows; l++)
                {
                    double gtriNhan = - MaTranKhu[l][col]/MaTranKhu[i][col];
                    for(int k = col; k < cols; k++)
                    {
                        MaTranKhu[l][k] = MaTranKhu[i][k]*gtriNhan + MaTranKhu[l][k];
                    }
                }
                break;
            }
        }
        xuatMaTran();
    }
    timNghiem();
}

int timPTKhu(int hang[], int cot[], int &row, int &col)
{
    double max = -50;
    for(int i = 0; i < rows; i++)
    {
        if(hang[i] != -10)
        {
            for(int j = 0; j < cols-1; j++)
            {
                if(cot[j] != -10)
                {
                    if(fabs(MaTranKhu[hang[i]][cot[j]]) == 1)
                    {
                        max = 1;
                        row = hang[i];
                        col = cot[j];
                        hang[i] = -10;
                        cot[j] = -10;
                        return max; 
                    }
                    if(fabs(MaTranKhu[hang[i]][cot[j]]) > max)
                        max = fabs(MaTranKhu[hang[i]][cot[j]]);
                }
            }
        }
    }
    for(int i = 0; i < rows; i++)
    {
        if(hang[i] != -10)
        {
            for(int j = 0; j < cols-1; j++)
            {
                if(cot[j] != -10)
                {
                    if(fabs(MaTranKhu[hang[i]][cot[j]]) == max)
                    {
                        row = hang[i];
                        col = cot[j];
                        hang[i] = -10;
                        cot[j] = -10;
                        return max;
                    }
                }
            }
        }
    }
    return 0;
}

void ppKhuGaussJordan()
{
    int hang[100], cot[100];
    for(int i = 0; i < rows; i++)
        hang[i] = i;
    for(int i = 0; i < cols; i++)
        cot[i] = i;
    for(int i = 0; i < rows; i++)
    {
        int row = -1, col = -1;
        double max = timPTKhu(hang, cot, row, col);
        if(max == 0) break;
        cout << "Lan lap thu " << i+1 << endl;
        cout << "Phan tu khu A[" << row << "][" << col << "] = " << MaTranKhu[row][col] << endl;
        for(int j = 0; j < rows; j++)
        {
            double gtriNhan = -MaTranKhu[j][col]/MaTranKhu[row][col];
            for(int k = 0; k < cols; k++)
            {
                if(j != row)
                {
                    MaTranKhu[j][k] = MaTranKhu[row][k]*gtriNhan + MaTranKhu[j][k];
                }
            }
        }
        xuatMaTran();
    }
    int rankA = tinhRank(rows, cols-1);
    int rankAbs = tinhRank(rows, cols);
    if(rankA != rankAbs)
    {
        cout << "HPT vo nghiem";
        return;
    }
    else
    {
        if(rankA == cols-1)
        {
            cout << "HPT co nghiem duy nhat" << endl;
            double x[100];
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols-1; j++)
                {
                    if(fabs(MaTranKhu[i][j]) > saiso)
                    {
                        x[j] = MaTranKhu[i][cols-1]/MaTranKhu[i][j];
                        break;
                    }
                }
            }
            for(int i = 0; i < rankA; i++)
                cout << "x[" << i << "] = " << x[i] << endl;
            return;
        }
    }
    cout << "HPT co vo so nghiem" << endl;
    int soThamSo = cols - 1 - rankA;
    int vitri[100];
    double y[100][100];
    int count = 0;
    for(int j = 0; j < cols-1; j++)
    {
        int num0 = 0;
        for(int i = 0; i < rows; i++)
        {
            if(fabs(MaTranKhu[i][j]) > saiso) num0++;
        }
        if(num0 != 1)
        {
            vitri[count] = j;
            for(int k = 0; k < rows; k++)
                MaTranKhu[k][cols+count] = - MaTranKhu[k][j];
            count++;
        }
    }
    for(int i = 0; i < cols-1; i++)
    {
        int check = 0;
        for(int k = 0; k < soThamSo; k++)
            if(i != vitri[k]) check++;
        if(check == soThamSo)
        {
            for(int j = 0; j < rows; j++)
            {
                if(fabs(MaTranKhu[j][i]) > saiso)
                {
                    for(int k = 0; k <= soThamSo; k++)
                        y[i][k] = MaTranKhu[j][cols-1+k]/MaTranKhu[j][i];
                    break;
                }
            }
        }
    }
    for(int i = 0; i < cols-1; i++)
    {
        int check = 0;
        for(int j = 0; j < soThamSo; j++)
        {
            if(i == vitri[j])
            {
                check = 1;
                break;
            }
        }
        if(check == 1) continue;
        cout << "x[" << i << "] = ";
        for(int j = 0; j <= soThamSo; j++)
        {
            cout << y[i][j];
            if(j > 0) cout << " . x[" << vitri[j-1] << "]";
            if(j < soThamSo) cout << "  +  ";
        }
        cout << endl;
    }
}

int main()
{
    int selection;
    FILE *file = freopen("InputMaTran.txt", "r", stdin);
    nhapMaTran(file);
    fclose(file);
    freopen("CON", "r", stdin);
    cin.clear();
    cout << "Ma tran bo sung cua he phuong trinh can giai" << endl;
    xuatMaTran();
    cout << "=== Cac phuong phap giai he phuong trinh ===" << endl;
    cout << "1. Phuong phap khu Gauss" << endl;
    cout << "2. Phuong phap khu Gauss - Jordan" << endl;
    cout << "0. Thoat chuong trinh" << endl;
    cout << "Nhap lua chon cua ban: ";
    cin >> selection;
    switch(selection)
    {
        case 1:
            ppKhuGauss();
            break;
        case 2:
            ppKhuGaussJordan();
            break;
        case 0:
            return 0;
    }
    return 0;
}