#ifndef __CENT_UTIL_CONFXXX__
#define __CENT_UTIL_CONFXXX__

// These parameters are using BES-II 19.6 GeV U-runs as template.
// Need to change with your own.

namespace cent_conf {
    
    static const char* Name = "19p6-U"; // with this name, will be easy to find if we are using a correct parameter list
    static const char* Mode = // uncomment current status, will help to know if we are using a correct parameter list as well
        // "TEST";
        // "PU";
        // "LUMI";
        // "VZ";
        "COMP";

    static const int nTrg = 6;
    static int trgList[nTrg] = {
        640001,
        640011,
        640021,
        640031,
        640041,
        640051,
    };

    // pile up arguments
    static double beta_eta1_par[4] = {
        /*
            [kb - P][1][12 - A]
            P for k (slope) or b (constant)
            A for 1 (lower line) or 2 (higher line)
            k11, b11, k12, b12
        */
        0.47975, -11.21695, -999, -999
    };
    static double nTofMatch_par[4] = {
        /*
            [kb - P][2][12 - A]
            P for k (slope) or b (constant)
            A for 1 (lower line) or 2 (higher line)
            k21, b21, k22, b22
        */
        0.2645, -7.64716, -999, -999
    };
    static double TofMult_par[4] = {
        /*
            [kb - P][3][12 - A]
            P for k (slope) or b (constant)
            A for 1 (lower line) or 2 (higher line)
            k31, b31, k32, b32
        */
        1.38858, -24.58453, 1.84384, 192.93884
    };

    // luminosity arguments
    static double lumi_par[nTrg][2] = { // please follow the order of trigger id
        {0.00406336, 197.364},
        {0.000512621, 197.968}, 
        {-0.000218194, 198.159},
        {0.00166, 197.782},
        {0.00158331, 197.544},
        {-6.51105e-05, 197.931},
    };

    // vz arguments
    static double vz_par[nTrg][7] = { // please follow the order of trigger id
        {600.949	,0.0296317	,0.00294569	,-4.7635e-05	,-2.62036e-06	,7.92971e-09	,4.02049e-10	},
        {603.67	    ,0.0296317	,0.00294569	,-4.7635e-05	,-2.62036e-06	,7.92971e-09	,4.02049e-10	},
        {605.535	,0.0296317	,0.00294569	,-4.7635e-05	,-2.62036e-06	,7.92971e-09	,4.02049e-10	},
        {599.584	,0.0296317	,0.00294569	,-4.7635e-05	,-2.62036e-06	,7.92971e-09	,4.02049e-10	},
        {599.626	,0.0296317	,0.00294569	,-4.7635e-05	,-2.62036e-06	,7.92971e-09	,4.02049e-10	},
        {600.939	,0.0296317	,0.00294569	,-4.7635e-05	,-2.62036e-06	,7.92971e-09	,4.02049e-10	},
    };
      
    // centrality split with RefMult3
    static int cent_edge[9] = { // here fill in the centrality bin edge 
        497, 417, 291, 197, 129, 79, 46, 24, 12
    };

} // namespace cent_conf


#endif
