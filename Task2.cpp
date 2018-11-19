#include<vector>
#include<fstream>
#include<iostream>
#include<cmath>
#include<chrono>
const double pi = 3.1415926535;
double p(double x)
{
    return 0.1 + x; 
}
double F(double x)
{
    return (0.1*x + x*x*0.5) / 0.6;
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
    std::cout << "Enter number of requared iteration: ";
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
    while(method(start) > 1e-7)
    {
        iter += 1;
        if (iter == number)
        {
            for(int i = 0; i < size; i++)
            {
                f3 << (double)i / (size - 1) << "\t " << start[i] << "\t" << p(start[i]) << std::endl;
            }
        }
    }
    auto dt = std::chrono::steady_clock::now() - t0;
    std::ofstream f2("info.csv");
    f2 << "Amount of itearations: " << iter << std::endl;
    f2 << "Elapsed time: " << dt.count() / 1e6 << "ms" << std::endl;
    std::ofstream f1("end.csv");
    std::ofstream diff("diff");
    for(int i = 0; i < size; i++)
    {
        f1 << (double)i / (size - 1) << "\t" << start[i] << "\t" << p(start[i]) << std::endl;
        f2 << F((double)i / (size - 1)) - start[i] << std::endl;
    }
}
