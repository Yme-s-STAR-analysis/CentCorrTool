#ifndef __CENT_UTIL_CONFXXX__
#define __CENT_UTIL_CONFXXX__

// These parameters are using BES-II 17.3 GeV as template.
// Need to change with your own.

namespace cent_conf {
    
    static const char* Name = "17p3"; // with this name, will be easy to find if we are using a correct parameter list
    static const char* Mode = // uncomment current status, will help to know if we are using a correct parameter list as well
        // "TEST";
        // "PU";
        // "LUMI";
        "VZ";
        // "COMP";

    static const int nTrg = 1;
    static int trgList[nTrg] = {
        870010
    };

    // pile up arguments
    static double nTofMatch_upper_pars[4] = {
        /*
            3th order polynomial parameters.
        */
        50.8123, 3.48025, 0.0109673, -5.92909e-05
    };
    static double nTofMatch_lower_pars[4] = {
        /*
            3th order polynomial parameters.
        */
        -13.546, 1.39532, 0.0122539, -3.23417e-05
    };
    static double beta_eta1_upper_pars[4] = {
        /*
            3th order polynomial parameters.
        */
        37.9077, 1.85666, 0.00370279, -1.01181e-05
    };
    static double beta_eta1_lower_pars[4] = {
        /*
            3th order polynomial parameters.
        */
        -13.3618, 1.15569, 0.00222227, -3.21415e-06
    };

    // luminosity arguments
    static double lumi_par[nTrg][2] = { // please follow the order of trigger id
        {0, 0},
    };

    // vz arguments
    static double vz_par[nTrg][7] = { // please follow the order of trigger id
        // the old one is below:
        // {591.52	,0.0021783	,-0.00115482	,5.69411e-06	,-2.26069e-07	,-1.09632e-09	,2.42791e-11},
        // just for comparson if needed
        {591.522	,0.00279258	,-0.00124635	,4.9085e-06	,-1.49937e-07	,-8.14843e-10	,6.30363e-12},
    };
      
    // centrality split with RefMult3
    static int cent_edge[9] = { // here fill in the centrality bin edge 
        492, 413, 288, 196, 128, 79, 46, 24, 12
    };

} // namespace cent_conf


#endif
