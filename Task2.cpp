#include<vector>
#include<fstream>
#include<iostream>
#include<cmath>
#include<chrono>
const double pi = 3.1415926535;
double p(double x)
{
    return std::exp(x);
}
double F_bad(double x)
{
    return std::exp(x);
}
double F(double x)
{
    return (F_bad(x) - F_bad(0.0)) / (F_bad(1.0) - F_bad(0.0));
}

double method(std::vector<double> &start)
{
    std::vector<double> end = start;
    double norm = 0.0;
    for(int i = 1; i < start.size() - 1; i++)
    {
        double p_left = p(start[i - 1]);
        double p_right = p(start[i + 1]);
        end[i] = (p_left * start[i - 1] + p_right * start[i + 1]) / (p_left + p_right);
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
    int number;
    std::cout << "Enter number of required iteration: ";
    std::cin >> number;    
    std::vector<double> start;
    std::ifstream f("out.csv");
    double num;
    while(f >> num)
    {
        start.push_back(num);
    }
    int size = start.size();
    int iter = 0;
    auto t0 = std::chrono::steady_clock::now();
    std::ofstream f3("intermediate_iteration.csv");
    double norm;
    std::vector<double> intermediate;
    while((norm = method(start)) > 1e-6)
    {
        iter += 1;
        if (iter == number)
        {
            intermediate = start;
        }
        std::cout << norm << "\r";
    }
    auto dt = std::chrono::steady_clock::now() - t0;
    std::ofstream out("exp.csv");
    out << "Amount of itearations: " << iter << std::endl;
    out << "Elapsed time: " << dt.count() / 1e6 << "ms" << std::endl;
    for(int i = 0; i < size; i++)
    {
        out << (double)i / (size - 1) << "\t";
        out << F((double)i / (size - 1)) << "\t";
        out << start[i] << "\t";
        out << p(start[i])<< "\t";
        out << intermediate[i] << "\t";
        out << p(intermediate[i]) << "\t";
        out << std::endl;
    }
}
