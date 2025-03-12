#include <vector>
using namespace std;
class Gauss {
private:
    vector<vector<double>> augmentedMatrix;
    vector<double> sol;
    int n;
    int m;

public:
    void readMatrix();
    void eliminate();
    void backSubstitute();
    void printSolution();
};

