#include <fstream>
#include <cstdlib>
int main()
{
    int n = 80;
    double *arr = new double[n];
    arr[0] = 0.0;
    for(int i = 1; i < n - 1; i++)
    {
        arr[i] = (std::rand() % 1000000) / 1000000.0;
    }
    arr[n - 1] = 1.0;
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j+1])
            {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
    std::ofstream f("out.csv");
    for(int i = 0; i < n; i++)
    {
        f << arr[i] << std::endl;
    }
    delete[] arr;
}
