#include<vector>
#include<fstream>
#include<iostream>
double norm(std::vector<double> &start)
{
    double min = start[1] - start[0];
    double max = min;
    for(int i = 1; i < start.size() - 1; i++)
    {
        double delta = start[i+1] - start[i];
        if(delta > max)
        {
            max = delta;
        }
        else if(delta < min)
        {
            min = delta;
        }
    }
    return max - min;
}
void improve(std::vector<double> &start)
{
    std::vector<double> end = start;
    for(int i = 1; i < start.size() - 1; i++)
    {
        end[i] = (start[i+1] + start[i-1]) / 2;
    }
    start = end;
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
    while(norm(start) > 1e-3)
    {
        improve(start);
    }
    std::ofstream p("end.csv"); 
    std::ofstream diff("diff");
    for(int i = 0; i < size; i++)
    {
        p << start[i] << std::endl;
        diff << start[i] - (double)i / (size - 1) << std::endl;
    }
}

