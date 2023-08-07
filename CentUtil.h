#ifndef __CENT_UTIL_HEADER__
#define __CENT_UTIL_HEADER__

/*
    Version: 2.0
    Author: yghuang
    Date: 07.08.2023
*/

#include <iostream>
#include "TF1.h"

class CentUtil {

    private:

        static const int MAX_TRG = 10; // the maximum of triggers
        int nTrg; // actual number of triggers, will be read from config file
        
        // pile up rejection parameters
        double k11, k12, b11, b12;
        double k21, k22, b21, b22;
        double k31, k32, b31, b32;
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
        void SetPileUpBetaEta1LowerPar(double k11, double b11) {
            this->k11 = k11;
            this->b11 = b11;
        }
        void SetPileUpBetaEta1UpperPar(double k12, double b12) {
            this->k12 = k12;
            this->b12 = b12;
        }
        void SetPileUpBetaEta1(double* arr) {
            k11 = arr[0];
            b11 = arr[1];
            k12 = arr[2];
            b12 = arr[3];
        }
        void SetPileUpNTofMatch(double* arr) {
            k21 = arr[0];
            b21 = arr[1];
            k22 = arr[2];
            b22 = arr[3];
        }
        void SetPileUpTofMult(double* arr) {
            k31 = arr[0];
            b31 = arr[1];
            k32 = arr[2];
            b32 = arr[3];
        }
        void SetPileUpNTofMatchLowerPar(double k21, double b21) {
            this->k21 = k21;
            this->b21 = b21;
        }
        void SetPileUpNTofMatchUpperPar(double k22, double b22) {
            this->k22 = k22;
            this->b22 = b22;
        }
        void SetPileUpTofMultLowerPar(double k31, double b31) {
            this->k31 = k31;
            this->b31 = b31;
        }
        void SetPileUpTofMultUpperPar(double k32, double b32) {
            this->k32 = k32;
            this->b32 = b32;
        }
        void SetPileUpParam(
            double k11, double b11, double k12, double b12,
            double k21, double b21, double k22, double b22,
            double k31, double b31, double k32, double b32
        ) {
            SetPileUpBetaEta1LowerPar(k11, b11);
            SetPileUpBetaEta1UpperPar(k12, b12);
            SetPileUpNTofMatchLowerPar(k21, b21);
            SetPileUpNTofMatchUpperPar(k22, b22);
            SetPileUpTofMultLowerPar(k31, b31);
            SetPileUpTofMultUpperPar(k32, b32);
        }

        // do pile up selection
        // here x is always RefMult3 and y depends on the name of function
        bool IsBetaEta1Bad(int x, int y) {
            return (k11 != -999 && x * k11 + b11 > y) || (k12 != -999 && x * k12 + b12 < y);
        }
        bool IsNTofMatchBad(int x, int y) {
            return (k21 != -999 && x * k21 + b21 > y) || (k22 != -999 && x * k22 + b22 < y);
        }
        bool IsTofMultBad(int x, int y) {
            return (k31 != -999 && x * k31 + b31 > y) || (k32 != -999 && x * k32 + b32 < y);
        }
        bool IsBetaEta1Good(int x, int y) { return !IsBetaEta1Bad(x, y); }
        bool IsNTofMatchGood(int x, int y) { return !IsNTofMatchBad(x, y); }
        bool IsTofMultGood(int x, int y) { return !IsTofMultBad(x, y); }

        bool IsPileUp(int ref3, int beta_eta1, int nTofMatch, int TofMult) {
            return IsBetaEta1Bad(ref3, beta_eta1) || IsNTofMatchBad(ref3, nTofMatch) || IsTofMultBad(ref3, TofMult);
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
