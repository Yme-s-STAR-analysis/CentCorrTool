#include "Conf.h"
#include "CentUtil.h"

CentUtil::CentUtil() {
    k11 = k12 = b11 = b12 = 0;
    k21 = k22 = b21 = b22 = 0;
    k31 = k32 = b31 = b32 = 0;
    for (int i=0; i<MAX_TRG; i++) {
        kLumi[i] = 0;
        bLumi[i] = 0;
    }
    funcVz = new TF1("funcVz", "pol6", -70, 70);
    for (int i=0; i<9; i++) {
        centSplitEdge[i] = 0;
    }
    doPileUp = doLumi = doVz = true;
    doSplit = false;
}

void CentUtil::ReadParams() {
    nTrg = cent_conf::nTrg; 
    std::cout << "[LOG] - ReadParams: The parameter list is named as [" << cent_conf::Name << "] version [" << cent_conf::Mode << "]." << std::endl;
    std::cout << "[LOG] - ReadParams: Number of triggers: " << nTrg << ", list: ";
    for (int i=0; i<nTrg; i++) {
        std::cout << cent_conf::trgList[i] << "\t";
    }
    std::cout << std::endl;

    SetPileUpBetaEta1(cent_conf::beta_eta1_par);
    SetPileUpNTofMatch(cent_conf::nTofMatch_par);
    SetPileUpTofMult(cent_conf::TofMult_par);

    for (int i=0; i<nTrg; i++) {
        SetLumiParam(cent_conf::trgList[i], cent_conf::lumi_par[i][0], cent_conf::lumi_par[i][1]);
    }

    for (int i=0; i<nTrg; i++) {
        SetVzParam(cent_conf::trgList[i], &cent_conf::vz_par[i][0]);
    }
}

int CentUtil::ConvertTrg(int trg) {
    for (int i=0; i<nTrg; i++) {
        if (trg == cent_conf::trgList[i]) { 
            return i;
        }
    }
    return -1;
}

int CentUtil::LumiCorrection(int trg, int ref3, int zdcx) {
    // trg means converted trgid
    // like: 0 for 610001, 0 is trg and 610001 is trgid 
    double f = zdcx * kLumi[trg] + bLumi[trg];
    double factor = f == 0 ? 0.0 : bLumi[trg] / f;
    return (int)(factor * ref3);
}

int CentUtil::VzCorrection(int trg, int ref3, double vz) {
    double factor = parVz[trg][0] / funcVz->Eval(vz);
    return (int)(factor * ref3);
}

int CentUtil::GetRefMult3Corr(int ref3, int beta_eta1, int nTofMatch, int TofMult, double zdcx, double vz, int trgid) {
    int trg = ConvertTrg(trgid);
    if (trg >= nTrg || trg < 0) {
        return -1;
    }
    if (fabs(vz) > 70.0) {
        return -1;
    }
    if (doPileUp && IsPileUp(ref3, beta_eta1, nTofMatch, TofMult)) {
        return -1;
    }
    if (doLumi) {
        ref3 = LumiCorrection(trg, ref3, zdcx);
    }
    if (doVz) {
        ref3 = VzCorrection(trg, ref3, vz);
    }
    return ref3;

}

int CentUtil::GetCentrality9(int ref3) {
    if (!doSplit) {
        std::cout << "[WARNING] - GetCentrality9: Centrality bin edge not set yet." << std::endl;
        return -1;
    }
    for (int i=0; i<9; i++) {
        if (ref3 > centSplitEdge[i]) {
            return i;
        }
    }
    return -1;
}