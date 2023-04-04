#include "Normalization.h"

// Synaptic normalization functions

nValue binaryNorm(nValue input, bNormParams *params)
{
  if(params->ConnectionStrength < params->ConnectedPermanence) {
    return 0;
  }
  if(input >= 1) {
    return 1;
  }
  if(input <= -1) {
    return -1;
  }
  return 0;
}

nValue linearNorm(nValue input, bNormParams *params)
{
  if(params->ConnectionStrength < params->ConnectedPermanence) {
    return 0;
  } else {
    if(input > 0) {
      return (nValue)((fValue)input*(params->ConnectionStrength)+0.5f);
    } else {
      return (nValue)((fValue)input*(params->ConnectionStrength)-0.5f);
    }
  }
}
