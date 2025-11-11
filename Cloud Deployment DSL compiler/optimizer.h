#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "ast.h"

/* Apply optimizations in-place on deployment */
void optimize_deployment(Deployment *d);

#endif
