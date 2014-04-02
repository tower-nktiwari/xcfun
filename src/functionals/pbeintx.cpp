#include "functional.hpp"
#include "pw9xx.hpp"

template<class num>
static num pbeint_enhancement(const num &na, const num &gaa)
{
  using pw91_like_x_internal::S2;
  const parameter mupbe = 0.21951;
  const parameter muge = 0.123456790123;
  const parameter kappa = 0.804;
  const parameter alpha = 0.197;
  num st2 = S2(na,gaa);
  num mu = muge + (mupbe-muge)*alpha*st2/(1+alpha*st2);
  num t1 = 1 + mu*st2/kappa;
  return 1 + kappa - kappa/t1;
}


template<class num>
static num energy_pbeintx(const num &na, const num &gaa)
{
  const parameter c = pow(81/(4*M_PI),1.0/3.0)/2;
  num na43 = pow(na,4.0/3.0);
  num lda = -c*na43;
  num pbeintx = lda * pbeint_enhancement(na,gaa);
  return pbeintx;
}


template<class num>
static num energy(const densvars<num> &d)
{
  return energy_pbeintx(d.a,d.gaa) + energy_pbeintx(d.b,d.gbb);
}


FUNCTIONAL(XC_PBEINTX) = {
  "PBEint Exchange Functional",
  "PBEint Exchange Functional\n"
  "E. Fabiano, L.A. Constantin, F. Della Sala,\n"
  "      Phys. Rev. B. 82, 113104 (2010).\n"
  "Implemented by Eduardo Fabiano\n",
  XC_DENSITY | XC_GRADIENT,
  ENERGY_FUNCTION(energy)
};

