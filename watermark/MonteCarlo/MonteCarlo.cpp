#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "DistributionGen.h"
using namespace std;

#define GN 100000
#define a 1.8

void menu() {
	system("cls");
	cout << "================================" << endl;
	cout << "��ѡ���ܣ�" << endl;
	cout << "1.���ɸ�˹�ֲ�" << endl;
	cout << "2.������˹�ֲ�����" << endl;
	cout << "3.����ָ���ֲ�" << endl;
	cout << "4.����ָ���ֲ�����" << endl;
	cout << "5.���ɹ����˹�ֲ�" << endl;
	cout << "0.�˳�����" << endl;
	cout << "================================" << endl;
}

void GaussTest() {
	system("cls");
	DistributionGen DisGen;
	int n;
	cout << "���������ݹ�ģ�� ";
	cin >> n;
	vector<double> dis = DisGen.GaussDisGen(n);
	ofstream outfile;
	outfile.open("GaussDis.txt");
	for (int i = 0; i < n; i++) outfile << dis[i] << " ";
	outfile << endl;
	cout << "������������ļ� GaussDis.txt" << endl;
	while (1) {
		cout << "��1:�����ݴ�ӡ������̨" << endl;
		cout << "��0:�������˵�" << endl;
		cin >> n;
		if (n == 0)    return;
		if (n == 1) {
			int count = 0;
			for (unsigned int i = 0; i < dis.size(); i++) {
				cout << setw(12) << dis[i];
				++count;
				if (count == 10) {
					count = 0;
					cout << endl;
				}
			}
		}
		cout << endl;
	}
	return;
}

void GaussAnalyzeTest() {
	system("cls");
	DistributionGen DisGen;
	vector<double> dis;
	ifstream infile;
	infile.open("GaussDis.txt");
	if (!infile) {
		cout << "�������ɸ�˹�ֲ�" << endl;
		while (1) {
			cout << "��0:�������˵�" << endl;
			int n;
			cin >> n;
			if (n == 0)    return;
			cout << endl;
		}
		return;
	}
	for (int i = 0; i < 10000; i++) {
		double temp;
		infile >> temp;
		dis.push_back(temp);
	}
	cout << "�Ѷ����ļ� GaussDis.txt" << endl;
	DisGen.AnalyzGaussDis(dis);
	int n;
	while (1) {
		cout << "��0:�������˵�" << endl;
		cin >> n;
		if (n == 0)    return;
		cout << endl;
	}
	return;
}

void ExpTest() {
	system("cls");
	DistributionGen DisGen;
	int n;
	cout << "���������ݹ�ģ�� ";
	cin >> n;
	double beta;
	cout << "������ָ�������������Ĭ��Ϊ������ɣ�";
	cin >> beta;
	vector<double> dis = DisGen.ExpDisGen(n, beta);
	ofstream outfile;
	outfile.open("ExpDis.txt");
	for (unsigned int i = 0; i < dis.size(); i++) outfile << dis[i] << " ";
	outfile << endl;
	cout << "������������ļ� ExpDis.txt" << endl;
	while (1) {
		cout << "��1:�����ݴ�ӡ������̨" << endl;
		cout << "��0:�������˵�" << endl;
		cin >> n;
		if (n == 0)    return;
		if (n == 1) {
			int count = 0;
			for (unsigned int i = 0; i < dis.size(); i++) {
				cout << setw(12) << dis[i];
				++count;
				if (count == 10) {
					count = 0;
					cout << endl;
				}
			}
		}
		cout << endl;
	}
	return;
}

void ExpAnalyzeTest() {
	system("cls");
	DistributionGen DisGen;
	vector<double> dis;
	ifstream infile;
	infile.open("ExpDis.txt");
	if (!infile) {
		cout << "��������ָ���ֲ�" << endl;
		while (1) {
			cout << "��0:�������˵�" << endl;
			int n;
			cin >> n;
			if (n == 0)    return;
			cout << endl;
		}
		return;
	}
	for (int i = 0; i < 10000; i++) {
		double temp;
		infile >> temp;
		dis.push_back(temp);
	}
	cout << "�Ѷ����ļ� ExpDis.txt" << endl;
	DisGen.AnalyzeExpDis(dis);
	int n;
	while (1) {
		cout << "��0:�������˵�" << endl;
		cin >> n;
		if (n == 0)    return;
		cout << endl;
	}
	return;
}

vector<double> GGDTest(int n) {
	system("cls");
	DistributionGen DisGen;
	double beta = 1.0;
	vector<double> dis = DisGen.GGDDisGen(n, beta);
	//ofstream outfile;
	//outfile.open("GGDDis.txt");
	//for (unsigned int i = 0; i < dis.size(); i++) outfile << dis[i] << " ";
	//outfile << endl;
	//cout << "������������ļ� GGDDis.txt" << endl;
	return dis;
}

void Randomize(vector<int>& w) {
	for (int i = 0; i < w.size(); ++i) {

		swap(w[i], w[Randint(i)]);
	}
}

double getPm() {

}



int main()
{
	vector<int> w(N,1);
	for (int i = 500; i < N; ++i)	w[i] = -1;
	Randomize(w);
	double ls = 0;
	
	for (int i = 0; i < GN; ++i) {
		vector<double> dis = GGDTest(1000);
		for (int j = 0; j < 1000; ++j) {
			ls += (dis[j] + a * w[j])*w[j] / N;
		}
		cout << i << endl;
	}
	ls /= GN;
	cout << ls << endl;
	return 0;
}
