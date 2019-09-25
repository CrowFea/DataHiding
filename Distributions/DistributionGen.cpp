#include <iostream>
#include <fstream>
#include "Distribution.h"
using namespace std;

void menu(){
    system("cls");
    cout<<"================================"<<endl;
    cout<<"��ѡ���ܣ�"<<endl;
    cout<<"1.���ɸ�˹�ֲ�"<<endl;
    cout<<"2.������˹�ֲ�����"<<endl;
    cout<<"3.����ָ���ֲ�"<<endl;
    cout<<"4.����ָ���ֲ�����"<<endl;
    cout<<"5.���ɹ����˹�ֲ�"<<endl;
    cout<<"0.�˳�����"<<endl;
    cout<<"================================"<<endl;
}

void GaussTest(){
    system("cls");
    DistributionGen DisGen;
    int n;
    cout<<"���������ݹ�ģ�� ";
    cin>>n;
    vector<double> dis=DisGen.GaussDisGen(n);
    ofstream outfile;
    outfile.open("GaussDis.txt");
    for(int 0;i<dis.size();i++) outfile<<dis[i]<<" ";
    outfile<<endl;
    cout<<"������������ļ� GaussDis.txt"<<endl;
    while(1){
        cout<<"��1:�����ݴ�ӡ������̨"<<endl;
        cout<<"��0:�������˵�"<<endl;
        cin>>n;
        if(n==0)    return;
        if(n==1){
            for(int 0;i<dis.size();i++) cout<<dis[i]<<" ";
        }
        cout<<endl;
    }
    return;
}

void EXpTest(){
    system("cls");
    DistributionGen DisGen;
    int n;
    cout<<"���������ݹ�ģ�� ";
    cin>>n;
    double beta;
    cout<<"������ָ�������������Ĭ��Ϊ������ɣ�"
    vector<double> dis=DisGen.ExpDisGen(n);
    ofstream outfile;
    outfile.open("ExpDis.txt");
    for(int 0;i<dis.size();i++) outfile<<dis[i]<<" ";
    outfile<<endl;
    cout<<"������������ļ� ExpDis.txt"<<endl;
    while(1){
        cout<<"��1:�����ݴ�ӡ������̨"<<endl;
        cout<<"��0:�������˵�"<<endl;
        cin>>n;
        if(n==0)    return;
        if(n==1){
            for(int 0;i<dis.size();i++) cout<<dis[i]<<" ";
        }
        cout<<endl;
    }
    return;
}

int main()
{
    while(1){
        menu();
        int choice;
        cin>>choice;
        if(choice==0)   break;
        if(choice==1)   GaussTest();
        if(choice==2)   
    }
}
