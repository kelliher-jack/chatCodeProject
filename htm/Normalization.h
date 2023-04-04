#pragma once
#include "Utils.h"

struct bNormParams {
  fValue ConnectionStrength;
  fValue ConnectedPermanence;
};

nValue binaryNorm(nValue input, bNormParams *params);
nValue linearNorm(nValue input, bNormParams *params);
