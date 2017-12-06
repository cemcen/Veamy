#include <vector>
#include <delynoi/models/basic/Point.h>

namespace gauss_quadrature{
    void gauss_1d(int order, std::vector<double>& points, std::vector<double>& weights){
        if(order == 1){
            points.push_back(0.0);

            weights.push_back(2.0);
            return;
        }

        if(order == 2){
            points.push_back(-0.577350269189625764509148780502);
            points.push_back(0.577350269189625764509148780502);

            weights.push_back(1.0);
            weights.push_back(1.0);

            return;
        }

        if(order == 3){
            points.push_back(-0.774596669241483377035853079956);
            points.push_back(0.000000000000000);
            points.push_back(0.774596669241483377035853079956);

            weights.push_back(0.5555555555555555555555555555565);
            weights.push_back(0.8888888888888888888888888888889);
            weights.push_back(0.5555555555555555555555555555565);

            return;
        }

        if(order == 4){
            points.push_back(-0.861136311594052575223946488893);
            points.push_back(-0.339981043584856264802665759103);
            points.push_back(0.339981043584856264802665759103);
            points.push_back(0.861136311594052575223946488893);

            weights.push_back(0.347854845137453857373063949222);
            weights.push_back(0.652145154862546142626936050778);
            weights.push_back(0.652145154862546142626936050778);
            weights.push_back(0.347854845137453857373063949222);

            return;
        }

        if(order == 5){
            points.push_back(-0.906179845938663992797626878299);
            points.push_back(-0.538469310105683091036314420700);
            points.push_back(0.0);
            points.push_back(0.538469310105683091036314420700);
            points.push_back(0.906179845938663992797626878299);

            weights.push_back(0.236926885056189087514264040720);
            weights.push_back(0.478628670499366468041291514836);
            weights.push_back(0.568888888888888888888888888889);
            weights.push_back(0.478628670499366468041291514836);
            weights.push_back(0.236926885056189087514264040720);

            return;
        }

        if(order == 6){
            points.push_back(-0.932469514203152027812301554494);
            points.push_back(-0.661209386466264513661399595020);
            points.push_back(-0.238619186083196908630501721681);
            points.push_back(0.238619186083196908630501721681);
            points.push_back(0.661209386466264513661399595020);
            points.push_back(0.932469514203152027812301554494);

            weights.push_back(0.171324492379170345040296142173);
            weights.push_back(0.360761573048138607569833513838);
            weights.push_back(0.467913934572691047389870343990);
            weights.push_back(0.467913934572691047389870343990);
            weights.push_back(0.360761573048138607569833513838);
            weights.push_back(0.171324492379170345040296142173);

            return;
        }

        if(order == 7){
            points.push_back(-0.949107912342758524526189684048);
            points.push_back(-0.741531185599394439863864773281);
            points.push_back(-0.405845151377397166906606412077);
            points.push_back(0.0);
            points.push_back(0.405845151377397166906606412077);
            points.push_back(0.741531185599394439863864773281);
            points.push_back( 0.949107912342758524526189684048);

            weights.push_back(0.129484966168869693270611432679);
            weights.push_back(0.279705391489276667901467771424);
            weights.push_back(0.381830050505118944950369775489);
            weights.push_back(0.417959183673469387755102040816);
            weights.push_back(0.381830050505118944950369775489);
            weights.push_back(0.279705391489276667901467771424);
            weights.push_back(0.129484966168869693270611432679);

            return;
        }

        if(order == 8){
            points.push_back(-0.960289856497536231683560868569);
            points.push_back(-0.796666477413626739591553936476);
            points.push_back(-0.525532409916328985817739049189);
            points.push_back(-0.183434642495649804939476142360);
            points.push_back(0.183434642495649804939476142360);
            points.push_back(0.525532409916328985817739049189);
            points.push_back(0.796666477413626739591553936476);
            points.push_back(0.960289856497536231683560868569);

            weights.push_back(0.101228536290376259152531354310);
            weights.push_back(0.222381034453374470544355994426);
            weights.push_back(0.313706645877887287337962201987);
            weights.push_back(0.362683783378361982965150449277);
            weights.push_back(0.362683783378361982965150449277);
            weights.push_back(0.313706645877887287337962201987);
            weights.push_back(0.222381034453374470544355994426);
            weights.push_back(0.101228536290376259152531354310);

            return;
        }

        if(order == 9){
            points.push_back(-0.968160239507626089835576202904);
            points.push_back(-0.836031107326635794299429788070);
            points.push_back(-0.613371432700590397308702039341);
            points.push_back(-0.324253423403808929038538014643);
            points.push_back(0.0);
            points.push_back(0.324253423403808929038538014643);
            points.push_back(0.613371432700590397308702039341);
            points.push_back(0.836031107326635794299429788070);
            points.push_back(0.968160239507626089835576202904);

            weights.push_back(0.0812743883615744119718921581105);
            weights.push_back(0.180648160694857404058472031243);
            weights.push_back(0.260610696402935462318742869419);
            weights.push_back(0.312347077040002840068630406584);
            weights.push_back(0.330239355001259763164525069287);
            weights.push_back(0.312347077040002840068630406584);
            weights.push_back(0.260610696402935462318742869419);
            weights.push_back(0.180648160694857404058472031243);
            weights.push_back(0.0812743883615744119718921581105);

            return;
        }

        if(order == 10){
            points.push_back(-0.973906528517171720077964012084);
            points.push_back(-0.865063366688984510732096688423);
            points.push_back(-0.679409568299024406234327365115);
            points.push_back(-0.433395394129247290799265943166);
            points.push_back(-0.148874338981631210884826001130);
            points.push_back(0.148874338981631210884826001130);
            points.push_back(0.433395394129247290799265943166);
            points.push_back(0.679409568299024406234327365115);
            points.push_back(0.865063366688984510732096688423);
            points.push_back(0.973906528517171720077964012084);

            weights.push_back(0.0666713443086881375935688098933);
            weights.push_back(0.149451349150580593145776339658);
            weights.push_back(0.219086362515982043995534934228);
            weights.push_back(0.269266719309996355091226921569);
            weights.push_back(0.295524224714752870173892994651);
            weights.push_back(0.295524224714752870173892994651);
            weights.push_back(0.269266719309996355091226921569);
            weights.push_back(0.219086362515982043995534934228);
            weights.push_back(0.149451349150580593145776339658);
            weights.push_back(0.0666713443086881375935688098933);

            return;
        }
    }

    void gauss_triangle(int order, std::vector<Point>& points, std::vector<double>& weights){
        if(order == 1){
            points.push_back(Point(0.33333333333333,0.33333333333333));

            weights.push_back(1.00000000000000);

            return;
        }

        if(order == 2){
            points.push_back(Point(0.16666666666667,0.16666666666667));
            points.push_back(Point(0.16666666666667,0.66666666666667));
            points.push_back(Point(0.66666666666667,0.16666666666667));

            weights.push_back(0.33333333333333);
            weights.push_back(0.33333333333333);
            weights.push_back(0.33333333333333);

            return;
        }

        if(order == 3){
            points.push_back(Point(0.33333333333333,0.33333333333333));
            points.push_back(Point(0.20000000000000,0.20000000000000));
            points.push_back(Point(0.20000000000000,0.60000000000000));
            points.push_back(Point(0.60000000000000,0.20000000000000));

            weights.push_back(-0.56250000000000);
            weights.push_back(0.52083333333333);
            weights.push_back(0.52083333333333);
            weights.push_back(0.52083333333333);

            return;
        }

        if(order == 4){
            points.push_back(Point(0.44594849091597,0.44594849091597));
            points.push_back(Point(0.44594849091597,0.10810301816807));
            points.push_back(Point(0.10810301816807,0.44594849091597));
            points.push_back(Point(0.09157621350977,0.09157621350977));
            points.push_back(Point(0.09157621350977,0.81684757298046));
            points.push_back(Point(0.81684757298046,0.09157621350977));

            weights.push_back(0.22338158967801);
            weights.push_back(0.22338158967801);
            weights.push_back(0.22338158967801);
            weights.push_back(0.10995174365532);
            weights.push_back(0.10995174365532);
            weights.push_back(0.10995174365532);

            return;
        }

        if(order == 5){
            points.push_back(Point(0.33333333333333,0.33333333333333));
            points.push_back(Point(0.47014206410511,0.47014206410511));
            points.push_back(Point(0.47014206410511,0.05971587178977));
            points.push_back(Point(0.05971587178977,0.47014206410511));
            points.push_back(Point(0.10128650732346,0.10128650732346));
            points.push_back(Point(0.10128650732346,0.79742698535309));
            points.push_back(Point(0.79742698535309,0.10128650732346));

            weights.push_back(0.22500000000000);
            weights.push_back(0.13239415278851);
            weights.push_back(0.13239415278851);
            weights.push_back(0.13239415278851);
            weights.push_back(0.12593918054483);
            weights.push_back(0.12593918054483);
            weights.push_back(0.12593918054483);

            return;
        }

        if(order == 6){
            points.push_back(Point(0.24928674517091,0.24928674517091));
            points.push_back(Point(0.24928674517091,0.50142650965818));
            points.push_back(Point(0.50142650965818,0.24928674517091));
            points.push_back(Point(0.06308901449150,0.06308901449150));
            points.push_back(Point(0.06308901449150,0.87382197101700));
            points.push_back(Point(0.87382197101700,0.06308901449150));
            points.push_back(Point(0.31035245103378,0.63650249912140));
            points.push_back(Point(0.63650249912140,0.05314504984482));
            points.push_back(Point(0.05314504984482,0.31035245103378));
            points.push_back(Point(0.63650249912140,0.31035245103378));
            points.push_back(Point(0.31035245103378,0.05314504984482));
            points.push_back(Point(0.05314504984482,0.63650249912140));

            weights.push_back(0.11678627572638);
            weights.push_back(0.11678627572638);
            weights.push_back(0.11678627572638);
            weights.push_back(0.05084490637021);
            weights.push_back(0.05084490637021);
            weights.push_back(0.05084490637021);
            weights.push_back(0.08285107561837);
            weights.push_back(0.08285107561837);
            weights.push_back(0.08285107561837);
            weights.push_back(0.08285107561837);
            weights.push_back(0.08285107561837);
            weights.push_back(0.08285107561837);

            return;
        }

        if(order == 7){
            points.push_back(Point(0.33333333333333,0.33333333333333));
            points.push_back(Point(0.26034596607904,0.26034596607904));
            points.push_back(Point(0.26034596607904,0.47930806784192));
            points.push_back(Point(0.47930806784192,0.26034596607904));
            points.push_back(Point(0.06513010290222,0.06513010290222));
            points.push_back(Point(0.06513010290222,0.86973979419557));
            points.push_back(Point(0.86973979419557,0.06513010290222));
            points.push_back(Point(0.31286549600487,0.63844418856981));
            points.push_back(Point(0.63844418856981,0.04869031542532));
            points.push_back(Point(0.04869031542532,0.31286549600487));
            points.push_back(Point(0.63844418856981,0.31286549600487));
            points.push_back(Point(0.31286549600487,0.04869031542532));
            points.push_back(Point(0.04869031542532,0.63844418856981));

            weights.push_back(-0.14957004446768);
            weights.push_back(0.17561525743321);
            weights.push_back(0.17561525743321);
            weights.push_back(0.17561525743321);
            weights.push_back(0.05334723560884);
            weights.push_back(0.05334723560884);
            weights.push_back(0.05334723560884);
            weights.push_back(0.07711376089026);
            weights.push_back(0.07711376089026);
            weights.push_back(0.07711376089026);
            weights.push_back(0.07711376089026);
            weights.push_back(0.07711376089026);
            weights.push_back(0.07711376089026);

            return;
        }

        if(order == 8){
            points.push_back(Point(0.33333333333333,0.33333333333333));
            points.push_back(Point(0.45929258829272,0.45929258829272));
            points.push_back(Point(0.45929258829272,0.08141482341455));
            points.push_back(Point(0.08141482341455,0.45929258829272));
            points.push_back(Point(0.17056930775176,0.17056930775176));
            points.push_back(Point(0.17056930775176,0.65886138449648));
            points.push_back(Point(0.65886138449648,0.17056930775176));
            points.push_back(Point(0.05054722831703,0.05054722831703));
            points.push_back(Point(0.05054722831703,0.89890554336594));
            points.push_back(Point(0.89890554336594,0.05054722831703));
            points.push_back(Point(0.26311282963464,0.72849239295540));
            points.push_back(Point(0.72849239295540,0.00839477740996));
            points.push_back(Point(0.00839477740996,0.26311282963464));
            points.push_back(Point(0.72849239295540,0.26311282963464));
            points.push_back(Point(0.26311282963464,0.00839477740996));
            points.push_back(Point(0.00839477740996,0.72849239295540));

            weights.push_back(0.14431560767779);
            weights.push_back(0.09509163426728);
            weights.push_back(0.09509163426728);
            weights.push_back(0.09509163426728);
            weights.push_back(0.10321737053472);
            weights.push_back(0.10321737053472);
            weights.push_back(0.10321737053472);
            weights.push_back(0.03245849762320);
            weights.push_back(0.03245849762320);
            weights.push_back(0.03245849762320);
            weights.push_back(0.03245849762320);
            weights.push_back(0.02723031417443);
            weights.push_back(0.02723031417443);
            weights.push_back(0.02723031417443);
            weights.push_back(0.02723031417443);
            weights.push_back(0.02723031417443);
            weights.push_back(0.02723031417443);

            return;
        }
    }
}

