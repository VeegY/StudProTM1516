//#include "../src/assemblyLGS.cpp"
#include "../src/include/assemblefem.hpp"

#include "../src/include/slicedvector.hpp"
#include "../src/include/bicgstabsolver.hpp"
#include "../src/include/distellpackmatrix.hpp"

//#include "../src/include/vtkwriter.hpp"
//#include "../src/include/discretizer.hpp"

#include <iostream>

int main()
{
    double h(1.0);
    int nx(3), ny(4), nz(5);

    Icarus::DistEllpackMatrix<double> matrix(nx*ny*nz);

    Icarus::SlicedVector<double> rhs(nx*ny*nz);
    rhs.clear();

    Icarus::SlicedVector<double> sol(nx*ny*nz);
    sol.clear();

    Icarus::assembleFem assembler(h, nx, ny, nz);
    assembler.assemble(matrix, rhs);
    matrix.print_local_data(std::cout);

	Icarus::BiCgStabSolver<Icarus::DistEllpackMatrix<double>> solver(matrix, rhs);
    //solver.solve(sol);
    sol.print_local_data(std::cout);

    return 0;
}
