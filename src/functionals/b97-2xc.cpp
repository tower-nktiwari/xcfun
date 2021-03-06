#include "functional.hpp"
#include "constants.hpp"
#include "b97x.hpp"
#include "b97c.hpp"


template<class num>
static num b97_2x_en(const densvars<num> &d)
{
    return b97x::energy_b97x_ab(b97x::Gamma,b97x::c_b97_2,d.a_43,d.gaa)
    + b97x::energy_b97x_ab(b97x::Gamma,b97x::c_b97_2, d.b_43,d.gbb);
}

template<class num>
static num b97_2c_en(const densvars<num> &d)
{
    num e_LSDA_a, e_LSDA_b, tmp;
    tmp = b97c::energy_b97c_par(b97c::Gamma_par, b97c::c_b97_2[1] ,
                                d.a,d.a_43, d.gaa, e_LSDA_a) +
    b97c::energy_b97c_par(b97c::Gamma_par, b97c::c_b97_2[1] , d.b,  d.b_43, d.gbb, e_LSDA_b);
    
    return tmp + b97c::energy_b97c_antipar(b97c::Gamma_antipar,
                                           b97c::c_b97_2[0], d, e_LSDA_a, e_LSDA_b);
}


FUNCTIONAL(XC_B97_2X) = {
  "B97-2 exchange",
  "Hybrid exchange-correlation functional determined from\n"
  "thermochemical data and ab initio potentials\n"
  "P.J.Wilson,T-J-Bradley,D.J.Tozer; J.Chem.Phys.; 115, 9233, (2001)\n"
  "Implemented by Sarah Reimann ",
  XC_DENSITY | XC_GRADIENT,
  ENERGY_FUNCTION(b97_2x_en) };


FUNCTIONAL(XC_B97_2C) = {
  "B97-2 correlation",
  "Hybrid exchange-correlation functional determined from\n"
  "thermochemical data and ab initio potentials\n"
  "P.J.Wilson,T-J-Bradley,D.J.Tozer; J.Chem.Phys.; 115, 9233, (2001)\n"
  "Implemented by Sarah Reimann ",
  XC_DENSITY | XC_GRADIENT,
  ENERGY_FUNCTION(b97_2c_en) };
