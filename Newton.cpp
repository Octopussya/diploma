#include<vector>
#include<fstream>
#include<iostream>
#include<cmath>

const double pi = 3.1415926535;
double p(double x)
{
    return pi * std::sin(pi * x)/2;
}
double delta(int i, std::vector<double> &v)
{
    int L = v.size() - 1;
    if(i == 0)
    {
        return 1/ L / (v[1] - v[0]);
    }
    else if(i == L)
    {
        return 1/ L / (v[L] - v[L-1]);
    }
    return 2 / L / (v[i+1] - v[i-1]);
}
double f(int i, std::vector<double> &v)
{
    return p(v[i]) - delta(i,v);
}
double df(int i, std::vector<double> &v)
{
    return (f(i+1,v) - f(i-1,v)) / (v[i+1] - v[i-1]);
}
double newton(std::vector<double> &start)
{
    std::vector<double> end = start;
    double norm = 0.0;
    for(int i = 1; i < start.size() - 1; i++)
    {
        end[i] = start[i]  - f(i,start) / df(i,start);
        double diff = std::abs(end[i] - start[i]);
        if(diff > norm)
        {
            norm = diff;
        }
    }
    start = end;
    return norm;
}

int main()
{
    std::vector<double> start;
    std::ifstream f("out.csv");
    double num;
    while(f >> num)
    {
        start.push_back(num);
    }
    int size = start.size();
    int iter = 0;
    while(newton(start) > 1e-6)
    {
        iter += 1;
    }
    std::cout << iter << std::endl;
    std::ofstream p("end.csv");
    std::ofstream diff("diff");
    for(int i = 0; i < size; i++)
    {
        p << start[i] << std::endl;
    }

}
                   
