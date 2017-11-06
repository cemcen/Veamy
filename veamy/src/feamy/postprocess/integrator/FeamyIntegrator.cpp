#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <feamy/integration/integrables/IntegrableFunction.h>
#include <feamy/integration/AreaIntegrator.h>

FeamyIntegrator::FeamyIntegrator() {}

FeamyIntegrator::FeamyIntegrator(Computable *computable) {
    this->computable = computable;
}

double FeamyIntegrator::getIntegral(Triangle poly, std::vector<Point> points) {

    class IntegrableFunctionComputable: public IntegrableFunction<double>{
    private:
        Computable* computable;
    public:
        IntegrableFunctionComputable(Computable* c){
            this->computable = c;
        }

        inline double apply(Point p, int index){
            return this->computable->apply(p.getX(), p.getY(), index, Polygon());
        }
    };

    IntegrableFunctionComputable* computable = new IntegrableFunctionComputable(this->computable);
    double result;

    FeamyConfig* config = FeamyConfig::instance();
    AreaIntegrator::integrate(result, config->getNumberOfGaussPoints(), VeamyTriangle(poly), points, computable);

}

void FeamyIntegrator::setComputable(Computable *c) {
    this->computable = c;
}
