#ifndef LINEAR_ELASTIC_SOLVER
#define LINEAR_ELASTIC_SOLVER

#include <deal.II/base/symmetric_tensor.h>
#include "solverBase.h"
#include "linearMaterial.h"

namespace IFEM
{
  using namespace dealii;
  using namespace std;

  /*! \brief Solver for linear elastic materials
  *
  * Currently dynamics is not implemented.
  * Reference: http://www.dealii.org/8.5.0/doxygen/deal.II/step_8.html
  */
  template<int dim>
  class LinearElasticSolver : public SolverBase<dim>
  {
  public:
    LinearElasticSolver(int order = 1): SolverBase<dim>(order) {};
    /*
    * Assemble the system matrix and system rhs at the same time.
    */
    void assemble();
    void evaluateStressStrain();
    void setMaterial(Material<dim>*) override;
  };

#include "linearElasticSolver.tpp"
}

#endif
