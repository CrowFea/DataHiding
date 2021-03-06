#pragma once

#include<random>
#include<time.h>
#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

#define PI 3.14159265358979323846
#define N 10000
class DistributionGen{
private:
//内部接口
    double RandGen();
    int RandGenint();
    double GaussGen();
    double ExpGen(double beta);
    double GammaGen(double alpha,double beta);
    bool BonGen();
    double GGDGen(double c);
public:
//外部接口
    vector<double> GaussDisGen(int n);
	vector<double> ExpDisGen(int n, double beta);
    vector<double> GammaDisGen(int n,double alpha,double beta);
	vector<bool> BonDisGen(int n);
	vector<double> GGDDisGen(int n, double c);
    void AnalyzGaussDis(vector<double> GaussDis);
    void AnalyzeExpDis(vector<double> ExpDis);
};

//生成两个0-1之间的随机数，MT实现
double DistributionGen::RandGen(){
    std::random_device rd;  //获取随机数种子
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_real_distribution<double> dis(0.0, 1.0);
	int count = 0;
    double res=dis(gen);
	while (count<1000) {
		res = dis(gen);
		++count;
	}
    return res;
}

//生成两个0-1之间的随机数，MT实现
int DistributionGen::RandGenint(){
    std::random_device rd;  //获取随机数种子
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<int> dis(0,10000);
    
    int res=dis(gen);
    return res;
}

//生成符合高斯分布的数据 Box-Muller
double DistributionGen::GaussGen(){
    double U1,U2;
	U1 = RandGen();
	U2 = RandGen();
	while ((-2)*log(U1)*sin(2 * PI*U2)<0){
		U1 = RandGen();
		U2 = RandGen();
	}
    double Z=sqrt((-2)*log(U1)*sin(2*PI*U2));
    return Z;
}

//生成指数分布Z
double DistributionGen::ExpGen(double beita){
    double pV=RandGen();
    double Z = (-1.0/beita)*log(1-pV);
    //cout<<Z<<endl;
    return Z;
}

//生成伽玛分布Z
double DistributionGen::GammaGen(double alpha,double lambda){
    double u, v;
    double x, y;
    double b, c;
    double w, z;
    bool accept = false;
    
    if (alpha > 1.0){
        b = alpha - 1;
        c = 3*alpha-0.75;
        do {
            u = RandGen();
            v = RandGen();
            
            w = u*(1-u);
            y = sqrt(c/w)*(u-0.5);
            x = b+y;
            if (x>=0) {
                z = 64*w*w*w*v*v;
                double zz = 1-2*y*y/x;
                if (z-zz<1e-10){
                    accept = true;
                }
                else{
                    accept = false;
                }
                //accept=(z=1-2*y*y/x);
                //accept=(z==(1-2*y*y/x));
                if (!accept){
                    double logz = log(z);
                    double zzz = 2 * (b*log(x/b)-y);
                    if (logz-zzz<1e-10){
                        accept = true;
                    }
                    else{
                        accept = false;
                    }
                    //accept=(log(z)==2 * (b*log(x/b)-y));
                }
            }
        } while(!accept);
        return lambda*x;
    }
    else if (alpha == 1.0){
        return lambda * ExpGen(RandGen());
    }
    else if (alpha < 1.0){
        double dv = 0.0;
        double b=(exp(1.0)+alpha)/exp(1.0);
        do{
            double u1=RandGen();
            double p=b*RandGen();
            double y;
            if(p>1){
                y=-log((b-p)/alpha);
                if(u1<pow(y,alpha-1)){
                    dv=y;
                    break;
                }
            }else{
                y=pow(p,1/alpha);
                if(u1<exp(-y)){
                    dv=y;
                    break;
                }
            }
        }while(1);
        return dv*lambda;
    }
    return -1;
}

//生成伯努利分布Z
bool DistributionGen::BonGen(){
    double prob=0.5;
    default_random_engine generator;
    bernoulli_distribution b(prob);
    bool Z=0;
    for(int i=0;i<RandGenint();++i){
        Z=b(generator);
    }
    return Z;
}

//生成广义高斯分布Z
double DistributionGen::GGDGen(double c){
    bool w=BonGen();
    double E=GammaGen(RandGen(),RandGen());
    double Z;
    if(w==1)    Z=pow(E,c);
    else    Z=-1*pow(E,c);
    return Z;
}

//生成高斯分布数据
vector<double>  DistributionGen::GaussDisGen(int n){
    vector<double> res(n);
    for(int i=0;i<n;++i){
        res[i]=GaussGen();
    }
    return res;
}

//生成指数分布数据
vector<double>  DistributionGen::ExpDisGen(int n,double beta){
    vector<double> res(n);
    for(int i=0;i<n;++i){
        res[i]=ExpGen(beta);
    }
    return res;
}

//生成伽玛分布数据
vector<double>  DistributionGen::GammaDisGen(int n,double alpha,double beta){
    vector<double> res(n);
    for(int i=0;i<n;++i){
        res[i]=GammaGen(alpha,beta);
    }
    return res;
}

//生成伯努利分布数据
vector<bool>   DistributionGen::BonDisGen(int n){
    vector<bool> res(n);
    for(int i=0;i<n;++i){
        res[i]=BonGen();
    }
    return res;
}

//生成伽玛分布数据
vector<double>   DistributionGen::GGDDisGen(int n,double c){
    vector<double> res(n);
    for(int i=0;i<n;++i){
        res[i]=GGDGen(c);
    }
    return res;
}

//似然估计高斯分布的参数
void DistributionGen::AnalyzGaussDis(vector<double> gauss){
    double miu=0,sigma=0;
    for(int i=0;i<N;++i){
        miu+=gauss[i];
    }
    miu/=N;
    for(int i=0;i<N;++i){
        sigma+=(gauss[i]-miu)*(gauss[i]-miu);
    }
    sigma/=N;
    sigma=sqrt(sigma);
    cout<<"该高斯分布的参数为："<<endl<<"u: "<<miu<<endl<<"sigma: "<<sigma<<endl;
    return;
}

void DistributionGen::AnalyzeExpDis(vector<double> exp){
	double beita,pV;
	beita = 0;
	for (unsigned int i = 0; i < exp.size(); ++i) {
		pV = RandGen();
		beita += (-1.0 / exp[i])*log(1 - pV);
	}
	beita /= exp.size();
	cout << "该指数分布的参数为：" << endl << "c: " << beita << endl;
	return;
}


int Randint(int i) {
	std::random_device rd;  //获取随机数种子
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

	uniform_int_distribution<int> dis(i, N - 1);

	int res = dis(gen);

	return res;
}