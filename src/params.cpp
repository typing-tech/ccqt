#include "params.h"

void get_diff(Parameters &params, bool *output_diff[MESSAGES_LEN]) {
  for (unsigned i = 0; i < MESSAGES_LEN; i++)
    (*output_diff)[i] = params.parameters[i] != params.parameters_modified[i];
}
