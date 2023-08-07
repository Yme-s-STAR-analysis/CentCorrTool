#ifndef __CENT_UTIL_CONF__
#define __CENT_UTIL_CONF__

namespace cent_conf {
    
    const char* Name = "19p6"; // with this name, will be easy to find if we are using a correct parameter list
    const char* Mode = // uncomment current status, will help to know if we are using a correct parameter list as well
        // "TEST";
        // "PU";
        // "LUMI";
        // "VZ";
        "COMP";

    const int nTrg = 6;
    int trgList[nTrg] = {
        640001,
        640011,
        640021,
        640031,
        640041,
        640051,
    };

    // pile up arguments
    double beta_eta1_par[4] = {
        /*
            [kb - P][1][12 - A]
            P for k (slope) or b (constant)
            A for 1 (lower line) or 2 (higher line)
            k11, b11, k12, b12
        */
        -999, -999, -999, -999
    };
    double nTofMatch_par[4] = {
        /*
            [kb - P][2][12 - A]
            P for k (slope) or b (constant)
            A for 1 (lower line) or 2 (higher line)
            k21, b21, k22, b22
        */
        -999, -999, -999, -999
    };
    double TofMult_par[4] = {
        /*
            [kb - P][3][12 - A]
            P for k (slope) or b (constant)
            A for 1 (lower line) or 2 (higher line)
            k31, b31, k32, b32
        */
        -999, -999, -999, -999
    };

    // luminosity arguments
    double lumi_par[nTrg][2] = { // please follow the order of trigger id
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
        {0, 0},
    };

    // vz arguments
    double vz_par[nTrg][7] = { // please follow the order of trigger id
        {0., 0., 0., 0., 0., 0., 0.},
        {0., 0., 0., 0., 0., 0., 0.},
        {0., 0., 0., 0., 0., 0., 0.},
        {0., 0., 0., 0., 0., 0., 0.},
        {0., 0., 0., 0., 0., 0., 0.},
        {0., 0., 0., 0., 0., 0., 0.},
    };

} // namespace cent_conf


#endif