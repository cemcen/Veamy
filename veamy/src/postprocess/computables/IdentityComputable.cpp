#include <veamy/postprocess/computables/IdentityComputable.h>
#include <delynoi/models/polygon/Polygon.h>

double IdentityComputable::apply(double x, double y, int index, Polygon container) {
    return 1;
}
