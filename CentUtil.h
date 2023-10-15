#ifndef __CENT_UTIL_HEADER__
#define __CENT_UTIL_HEADER__

/*
    Version: 3.0
    Author: yghuang
    Date: 06.10.2023
*/

#include <iostream>
#include "TF1.h"

class CentUtil {

    private:

        static const int MAX_TRG = 10; // the maximum of triggers
        int nTrg; // actual number of triggers, will be read from config file
        
        // pile up rejection parameters
        // ---- old version : straight lines -----
        // double k11, k12, b11, b12;
        // double k21, k22, b21, b22;
        // double k31, k32, b31, b32;

        // ---- 3.0 new method parameters ------
        double nTofMatchLowerPars[3];
        double nTofMatchUpperPars[3];
        double betaEta1LowerPars[3];
        double betaEta1UpperPars[3];
        TF1* nTofMatchUpperPoly3;
        TF1* nTofMatchLowerPoly3;
        TF1* betaEta1UpperPoly3;
        TF1* betaEta1LowerPoly3;
        bool doPileUp;

        // luminosity correction parameters
        double kLumi[MAX_TRG];
        double bLumi[MAX_TRG];
        bool doLumi;

        // vz correction parameters
        double parVz[MAX_TRG][7]; // 6-order poly + constant
        TF1* funcVz;
        bool doVz;

        // centrality split with bin edge
        double centSplitEdge[9];
        bool doSplit;

    public:
        CentUtil();
        ~CentUtil(){}

        // -------------------------------------------------------------------
        int ConvertTrg(int trg);
        void ReadParams();
        void SetDoPileUp(bool do_) {
            doPileUp = do_;
            if (do_) {
                std::cout << "[LOG] - SetDoPileUp: " << "ON." <<std::endl;
            } else {
                std::cout << "[LOG] - SetDoPileUp: " << "OFF." <<std::endl;
            }
        }
        void SetDoLumi(bool do_) {
            doLumi = do_;
            if (do_) {
                std::cout << "[LOG] - SetDoLumi: " << "ON." <<std::endl;
            } else {
                std::cout << "[LOG] - SetDoLumi: " << "OFF." <<std::endl;
            }
        }
        void SetDoVz(bool do_) {
            doVz = do_;
            if (do_) {
                std::cout << "[LOG] - SetDoVz: " << "ON." <<std::endl;
            } else {
                std::cout << "[LOG] - SetDoVz: " << "OFF." <<std::endl;
            }

        }
        
        // -------------------------------------------------------------------
        // - pile up settings
        // helper functions
        void SetPileUpNTofMatchLowerParam(double p0, double p1, double p2, double p3) {
            nTofMatchLowerPars[0] = p0;
            nTofMatchLowerPars[1] = p1;
            nTofMatchLowerPars[2] = p2;
            nTofMatchLowerPars[3] = p3;
            nTofMatchLowerPoly3->SetParameters(nTofMatchLowerPars);
        }

        void SetPileUpNTofMatchLowerParam(double *p) {
            nTofMatchLowerPoly3->SetParameters(p);
        }

        void SetPileUpNTofMatchUpperParam(double p0, double p1, double p2, double p3) {
            nTofMatchUpperPars[0] = p0;
            nTofMatchUpperPars[1] = p1;
            nTofMatchUpperPars[2] = p2;
            nTofMatchUpperPars[3] = p3;
            nTofMatchUpperPoly3->SetParameters(nTofMatchUpperPars);
        }

        void SetPileUpNTofMatchUpperParam(double *p) {
            nTofMatchUpperPoly3->SetParameters(p);
        }

        void SetPileUpbetaEta1LowerParam(double p0, double p1, double p2, double p3) {
            betaEta1LowerPars[0] = p0;
            betaEta1LowerPars[1] = p1;
            betaEta1LowerPars[2] = p2;
            betaEta1LowerPars[3] = p3;
            betaEta1LowerPoly3->SetParameters(betaEta1LowerPars);
        }

        void SetPileUpBetaEta1LowerParam(double *p) {
            betaEta1LowerPoly3->SetParameters(p);
        }

        void SetPileUpbetaEta1UpperParam(double p0, double p1, double p2, double p3) {
            betaEta1UpperPars[0] = p0;
            betaEta1UpperPars[1] = p1;
            betaEta1UpperPars[2] = p2;
            betaEta1UpperPars[3] = p3;
            betaEta1UpperPoly3->SetParameters(betaEta1UpperPars);
        }

        void SetPileUpBetaEta1UpperParam(double *p) {
            betaEta1UpperPoly3->SetParameters(p);
        }

        bool IsBetaEta1PileUp(int ref3, int beta_eta1);
        bool IsNTofMatchPileUp(int ref3, int nTofMatch);

        bool IsPileUp(int ref3, int beta_eta1, int nTofMatch) {
            return IsBetaEta1PileUp(ref3, beta_eta1) || IsNTofMatchPileUp(ref3, nTofMatch);
        }

        bool IsNotPileUp(int ref3, int beta_eta1, int nTofMatch) {
            return !IsPileUp(ref3, beta_eta1, nTofMatch);
        }

        // -------------------------------------------------------------------
        // - luminosity settings
        void SetLumiParam(int trgid, double k, double b) {
            int trg = ConvertTrg(trgid);
            if (trg != -1) {
                kLumi[trg] = k;
                bLumi[trg] = b;
            }
        }
        int LumiCorrection(int trg, int ref3, int zdcx);

        // -------------------------------------------------------------------
        // - vz settings
        void SetVzParam(int trgid, double p0, double p1, double p2, double p3, double p4, double p5, double p6) {
            int trg = ConvertTrg(trgid);
            parVz[trg][0] = p0;
            parVz[trg][1] = p1;
            parVz[trg][2] = p2;
            parVz[trg][3] = p3;
            parVz[trg][4] = p4;
            parVz[trg][5] = p5;
            parVz[trg][6] = p6;
            funcVz->SetParameters(&parVz[trg][0]);
        }

        void SetVzParam(int trgid, double* p) {
            int trg = ConvertTrg(trgid);
            parVz[trg][0] = *(p+0);
            parVz[trg][1] = *(p+1);
            parVz[trg][2] = *(p+2);
            parVz[trg][3] = *(p+3);
            parVz[trg][4] = *(p+4);
            parVz[trg][5] = *(p+5);
            parVz[trg][6] = *(p+6);
            funcVz->SetParameters(&parVz[trg][0]);
        }

        int VzCorrection(int trg, int ref3, double vz);

        // -------------------------------------------------------------------
        // - do correction
        int GetRefMult3Corr(int ref3, int beta_eta1, int nTofMatch, int TofMult, double zdcx, double vz, int trgid);

        // -------------------------------------------------------------------
        // - centrality split functions
        void SetCentEdge(int e0, int e1, int e2, int e3, int e4, int e5, int e6, int e7, int e8) {
            centSplitEdge[0] = e0;
            centSplitEdge[1] = e1;
            centSplitEdge[2] = e2;
            centSplitEdge[3] = e3;
            centSplitEdge[4] = e4;
            centSplitEdge[5] = e5;
            centSplitEdge[6] = e6;
            centSplitEdge[7] = e7;
            centSplitEdge[8] = e8;
            doSplit = true;
            std::cout << "[LOG] - Centrality bin edge specified.\n";
        }

        void SetCentEdge(int* arr) {
            for (int i=0; i<9; i++) {
                centSplitEdge[i] = *(arr+i);
            }
            doSplit = true;
            std::cout << "[LOG] - Centrality bin edge specified.\n";
        }

        int GetCentrality9(int ref3);

};

#endif
