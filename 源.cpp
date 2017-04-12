#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <iomanip>
#include<algorithm>
#include "head.h"


using namespace std;
//��������
double minG(vector<double> x, vector<double> GiT, double R, double T, int ng, int ns, double Xsum);
vector<double> GiT(vector<double> Gif, vector<double> Cip, vector<double> Si, double T);
double Xsum(vector<double> x, int ng);
bool youxiao(vector<double> x);
bool fecture2(vector<double> x, int j, int m);
vector<double> bSearch(vector<vector<double>> x, vector<double> x0, double r, double rp, double R, double T);
vector<double> calux1(vector<double> x_0, vector<double> x_1, double r);
vector<double> calux2(vector<double> x_0, vector<double> x_1, double r);

//����һ��vector�����������ϵĿ���
vector<vector<int>>zuhe;
//����vector����ʾ����ǰ���x
vector<vector<double>> xBeforeSort;
vector<vector<double>> xAfterSort;
//����һ��map����ʾG��x�Ķ�Ӧ��ϵ
map<double, vector<double>> xvalg;
//����vector���nimG��ֵ
vector<double> gVal;
//����X0
vector<double> xzero;

int ng = 6, ns = 6, m = 4;
//����һ��vector��ʾ��󾭹�����ĵ�12����xi��ֵ
vector<vector<double>> xfinal;
//����a,b,c,d,aij��Gif,Si,Cip������,�������ݴ���������,�ǵø�ng��ns��ֵ
vector<double> a = { 28.409, 44.141, 14.150, 29.957, 27.280, 29.999, 24.439, 69.454, 103.470, 144.934, 46.484, 33.434};
vector<double> b = { 4.100, 9.037, 75.496, 4.184, 3.264, 10.711, 0.435, 10.209, 35.062, 45.271, 8.117,4.247};
vector<double> c = { -0.460, - 8.535, 0.000, -1.674, 0.502, 0.335, -31.627, -16.234, -13.514, -9.205, -3.682, 0.000};
vector<double> d = { 0.000, 0.000, -17.990, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000};
vector<double> Gif = { -169.440, -457.210, -50.720, -61.130, -38.930, -298.080, -1.710, -535.910, -990.790, -1435.480, -402.770, -9.540};
vector<double> Si = { 197.550, 213.660, 186.264, 205.040, 130.580, 188.720, 5.740, 53.140, 113.720, 164.010, 59.830, 32.010};
vector<double> Cip = { 33.4233, 55.1933, 79.5734, 35.0740, 31.2719, 43.0986, 24.9710, 81.9396, 146.3508, 200.3004, 56.4111, 38.6281};
vector<double> Git(ng + ns,0);
vector<vector<int>> aij{ 
	{ 1, 1, 0, 0 },
	{ 1, 2, 0, 0 },
	{ 1, 0, 4, 0 },
	{ 0, 2, 0, 0 },
	{ 0, 0, 2, 1 },
	{ 0, 1, 2, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 2, 0, 1 },
	{ 0, 3, 0, 2 },
	{ 0, 4, 0, 3 },
	{ 0, 1, 0, 1 },
	{ 0, 0, 0, 1 },
};


int main()
{
	double r = 0.5, rp = 0.001;
	double R, T, y;
	cout << "������T,R,y���ÿո�ֿ�(����ctrl+z�˳�):" << endl;
	while (cin >> T >> R >> y)
	{
		double b1 = 7.9212;
		double b2 = 2.5656 + y / 1600;
		double b3 = 2.0799 + y / 100;
		double b4 = 0.0466 + y / 5500;
		zuhe = go(0, 4);
		int len = zuhe[0].size();
		vector<double> bb = { b1, b2, b3, b4 };
		vector< vector<double> > A(len, vector<double>(len + 1));
		//ͨ����ϣ�����4Ԫһ�η��̵ľ���A
		for (int p = 0; p < zuhe.size(); p++)
		{
			for (int q = 0; q < zuhe[p].size(); q++)
			{
				for (int i = 0; i < (len + 1); i++)
				{
					if (i == len)
					{
						A[q][i] = bb[q];
					}
					else
					{
						A[q][i] = aij[zuhe[p][q] - 1][i];
					}
				}
			}
			vector<double> x4(m);
			vector<double> x(ng + ns, 0);
			x4 = gauss(A);
			if (youxiao(x4))
			{
				for (int i = 0; i < m; i++)
				{
					x[zuhe[p][i] - 1] = x4[i];
				}
				xBeforeSort.push_back(x);
			}
		}
		//�趨T��P������X1��X2������XN���ĺ���ֵG��������G��X1~XN��С�����������
		for (int i = 0; i < xBeforeSort.size(); i++)
		{
			double xave;
			xave = Xsum(xBeforeSort[i], ng);
			Git = GiT(Gif, Cip, Si, T);
			double ming = minG(xBeforeSort[i], Git, R, T, ng, ns, xave);
			gVal.push_back(ming);
			xvalg[ming] = xBeforeSort[i];
		}
		//��g��������,�õ�������x
		sort(gVal.begin(), gVal.end());
		for (int i = 0; i < gVal.size(); i++)
		{
			xAfterSort.push_back(xvalg[gVal[i]]);
		}
		//x1�� ~ xn��������˳����x1�� ~ xn����ѡ����ng+ns������������������xi�� :
		//��ӡ��������50��x
		for (int i = 0; i < xAfterSort.size(); i++)
		{
			for (auto num : xAfterSort[i])
			{
				cout << num << " ";
			}
			cout << endl;
		}
		cout << "*******************" << endl;

		int count = 0;
		xzero = xAfterSort[0];
		for (int i = 0; i < xAfterSort.size() && count < (ng+ns); i++)
		{
			if (fecture2(xAfterSort[i], count, m))
			{
				xfinal.push_back(xAfterSort[i]);
				xAfterSort.erase(xAfterSort.begin() + i, xAfterSort.begin() + i + 1);
				cout << "xAf.size" << xAfterSort.size() << endl;
				i = 0;
				count++;
			}
		}
		cout << "���յ�12��XiΪ��" << endl;
		for (int i = 0; i < xfinal.size(); i++)
		{
			cout << "x[" + to_string(i) + "]:  ";
			for (int j = 0; j <xfinal[0].size(); j++)
			{
				cout << xfinal[i][j] << " ";
			}
			cout << endl;
		}
		//b����
		vector<double> xopt = bSearch(xfinal, xzero, r, rp, R, T);
		cout << "Xopt:=[" << endl;
		for (double xo : xopt)
		{
			if (xo == xopt[xopt.size() - 1])
			{
				cout << xo;
			}
			else
			{
				cout << xo << ", ";
			}
		}
		cout << "]" << endl;
		cout << "������һ�ε�T,R,y���ÿո�ֿ�(����ctrl+z�˳�):" << endl;
	}
	return 0;
}

double minG(vector<double> x, vector<double> GiT, double R, double T, int ng, int ns, double Xsum)
{
	double result = 0;
	for (int i = 0; i < (ng + ns); i++)
	{
		if (i < ng)
		{
			if (x[i] != 0)
			{
				result = result + x[i] * (GiT[i] + R*T*log(x[i] / Xsum));
			}
		}
		else
		{
			result = result + x[i] * GiT[i];
		}
	}
	return result;
}

vector<double> GiT(vector<double> Gif, vector<double> Cip, vector<double> Si, double T)
{
	vector<double> result;
	double temp = 0;
	for (int i = 0; i < (ng + ns); i++)
	{
		temp = Gif[i] - (T - 298.15)*Si[i] + (T - 298)*Cip[i] - T*Cip[i] * (log(T / 298));
		result.push_back(temp);
	}
	return result;
}

double Xsum(vector<double> x, int ng)
{
	double xsum = 0;
	for (int i = 0; i< ng; i++)
	{
		xsum += x[i];
	}
	return xsum;
}

bool youxiao(vector<double> x)
{
	for (int i = 0; i<x.size(); i++) {
		if (x[i] < 0)
		{
			return false;
		}
	}
	return true;
}

bool fecture2(vector<double> x, int j, int m)
{
	int num = 0;
	if (x[j] <= 0)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < x.size(); i++)
		{
			if (x[i] > 0 && i != j)
			{
				num++;
			}
		}
		if (num > (m-1))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

vector<double> bSearch(vector<vector<double>> x, vector<double> x0, double r, double rp, double R, double T)
{
	while (r >= rp)
	{
		for (int i = 0; i < x.size(); i++)
		{
			vector<double> x1 = calux1(x0, x[i], r);
			if (minG(x1, Git, R, T, ng, ns, Xsum(x1, ng)) < minG(x0, Git, R, T, ng, ns, Xsum(x0, ng)))
			{
				x0 = x1;
			}
			else
			{
				vector<double> x2 = calux2(x0, x[i], r);
				for (double num2 : x2)
				{
					if (num2 < 0)
					{
						goto L1;//���˸�goto�����x2���Ƿ���X2<0�������������һ���ļ��㣬
					}
				}
				if (minG(x2, Git, R, T, ng, ns, Xsum(x2, ng)) < minG(x0, Git, R, T, ng, ns, Xsum(x0, ng)))
				{
					x0 = x2;
				}
L1:;
			}
		}
		r = r / 2;
	}
	return x0;
}
//����X1��ֵ
vector<double> calux1(vector<double> x_0, vector<double> x_1, double r)
{
	vector<double> x1;
	for (int i = 0; i < x_0.size(); i++)
	{
		double temp = (1 - r)*x_0[i] + r*x_1[i];
		x1.push_back(temp);
	}
	return x1;
}
//����X1��ֵ
vector<double> calux2(vector<double> x_0, vector<double> x_1, double r)
{
	vector<double> x2;
	for (int i = 0; i < x_0.size(); i++)
	{
		double temp = (1 + r)*x_0[i] - r*x_1[i];
		x2.push_back(temp);
	}
	return x2;
}
