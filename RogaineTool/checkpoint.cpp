#include "checkpoint.h"

checkpoint::checkpoint(int id, double x, double y): checkpointID(id), x(x), y(y) {value = (checkpointID/10)*10;}