#ifndef LINEAR_MATERIAL
#define LINEAR_MATERIAL

#include <deal.II/base/symmetric_tensor.h>
#include "material.h"

namespace IFEM
{
  using namespace dealii;
  using namespace std;

  template<int dim>
  class LinearMaterial : public Material<dim>
  {
  public:
    LinearMaterial<dim>(double lameFirst, double lameSecond, double rho = 1.0) :
      Material<dim>(lameFirst, lameSecond, rho) {}
    SymmetricTensor<4, dim> getElasticityTensor() const;
  };

  template<int dim>
  SymmetricTensor<4, dim> LinearMaterial<dim>::getElasticityTensor() const
  {
    if (!this->initialized)
    {
      throw std::runtime_error("Material is not initialized!");
    }
    SymmetricTensor<4, dim> elasticity;
    for (unsigned int i = 0; i < dim; ++i)
    {
      for (unsigned int j = 0; j < dim; ++j)
      {
        for (unsigned int k = 0; k < dim; ++k)
        {
          for (unsigned int l = 0; l < dim; ++l)
          {
            elasticity[i][j][k][l] = (i==k && j==l ? this->mu : 0.0)
              + (i==l && j==k ? this->mu : 0.0) + (i==j && k==l ? this->lambda : 0.0);
          }
        }
      }
    }
    return elasticity;
  }
}

#endif
