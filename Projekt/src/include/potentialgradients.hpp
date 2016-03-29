#ifndef __POTENTIALGRADIENTS_HPP_
#define __POTENTIALGRADIENTS_HPP_

#include <vector>
#include "fullvector.hpp"
#include "assemblefem.hpp"
#include "mpihandler.hpp"

namespace Icarus
{
    template<typename Scalar>
    void getInnerPotentialGradients (const FullVector<Scalar>& potential, const size_t nx, const size_t ny, const size_t nz, double h, std::vector<char> discpoints,
                                     FullVector<Scalar>& xComp, FullVector<Scalar>& yComp, FullVector<Scalar>& zComp);

    template<typename Scalar>
    void getCellMidpointGradientsFEM (const FullVector<Scalar>& potential, const size_t nx, const size_t ny, const size_t nz, std::vector<char> discpoints,
                                     FullVector<Scalar>& xComp, FullVector<Scalar>& yComp, FullVector<Scalar>& zComp);
}

#endif // __POTENTIALGRADIENTS_HPP_
