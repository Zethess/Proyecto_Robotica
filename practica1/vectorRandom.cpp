#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
using namespace std;

static vector<int> rellenar(size_t tamano)
{
    static uniform_int_distribution<int> rango(numeric_limits<unsigned char>::min(), numeric_limits<unsigned char>::max());
    static default_random_engine generador;

    vector<int> v(tamano);
    generate(v.begin(), v.end(), [] {return rango(generador);});
    return v;
}

int main()
{
        vector<int> vector = rellenar(1000);
        
        sort(vector.begin(), vector.end(), [](const int & a, const int & b) -> bool
        {
        	return a < b;
        });

        for (auto i: vector)
        {
            cout << i << ",";
        }
        cout << "\n";
}
