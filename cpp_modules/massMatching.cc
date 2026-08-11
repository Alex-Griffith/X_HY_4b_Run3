#include <TMath.h>
#include <stdio.h>
#include <iostream>
#include <TRandom.h>
#include <string>
#include "TIMBER/Framework/include/common.h"

int getRand01(){
    //randomly returns 0 or 1
    static long seed = 1;
    seed++;
    TRandom randGen = TRandom(seed);
    int rand = randGen.Binomial(1,0.5);
    return rand;   
}


Int_t idxCloserToHiggsMass(Float_t m0, Float_t m1);
Int_t higgsMassMatching(Float_t m0, Float_t m1);
Int_t higgsMassMatchingAlternative(Float_t m0, Float_t m1);
Float_t regMassSyst(Float_t m, std::string syst);
Int_t higgsMassMatchingRegMass(Float_t m0, Float_t m1, std::string syst);
Int_t FindIdxJHRegMass(RVec<float> regMass, std::string syst, Float_t low, Float_t high, Float_t target = 125.0);

Int_t idxCloserToHiggsMass(Float_t m0, Float_t m1){
//returns index of the jet closer in mass to Higgs jet mass (125)
	Float_t diff0 = TMath::Abs(m0-125.0);
	Float_t diff1 = TMath::Abs(m1-125.0);
	if(diff0<=diff1){
		return 0;
	}
	else{
		return 1;
	}
}

Int_t higgsMassMatching(Float_t m0, Float_t m1){
//returns index of the Higgs jet
//criterion is that it falls into 110-140 GeV mass window
//if both are in the window, choose randomly
	int HcandidateFlag0 = 0;
	int HcandidateFlag1 = 0;

	if(m0 > 110 && m0 < 140 ){
		HcandidateFlag0 = 1;
	}
	if(m1 > 110 && m1 < 140 ){
		HcandidateFlag1 = 1;
	}
	if(HcandidateFlag0==1 && HcandidateFlag1!=1){
		return 0;
	}
	if(HcandidateFlag1==1 && HcandidateFlag0!=1){
		return 1;
	}
	if(HcandidateFlag0==1 && HcandidateFlag1==1){
		int res = getRand01();
		return res;
	}
	return -1;
}


Int_t higgsMassMatchingAlternative(Float_t m0, Float_t m1){
//returns index of the Higgs jet
//criterion is that it falls into 110-140 GeV mass window
//if both are in the window, choose one closer to 125
	int HcandidateFlag0 = 0;
	int HcandidateFlag1 = 0;

	if(m0 > 110 && m0 < 140 ){
		HcandidateFlag0 = 1;
	}
	if(m1 > 110 && m1 < 140 ){
		HcandidateFlag1 = 1;
	}
	if(HcandidateFlag0==1 && HcandidateFlag1!=1){
		return 0;
	}
	if(HcandidateFlag1==1 && HcandidateFlag0!=1){
		return 1;
	}
	if(HcandidateFlag0==1 && HcandidateFlag1==1){
		int res = idxCloserToHiggsMass(m0,m1);
		return res;
	}
	return -1;
}

Float_t regMassSyst(Float_t m, std::string syst){
	// Flat +/-5% template prior for the GloParT X2p regressed mass.
	if(syst == "JMS__up"){
		return 1.05 * m;
	}
	if(syst == "JMS__down"){
		return 0.95 * m;
	}
	if(syst == "JMR__up"){
		return 125.0 + 1.05 * (m - 125.0);
	}
	if(syst == "JMR__down"){
		return 125.0 + 0.95 * (m - 125.0);
	}
	return m;
}

Int_t higgsMassMatchingRegMass(Float_t m0, Float_t m1, std::string syst){
	return higgsMassMatching(regMassSyst(m0, syst), regMassSyst(m1, syst));
}

Int_t FindIdxJHRegMass(RVec<float> regMass, std::string syst, Float_t low, Float_t high, Float_t target){
	Int_t bestIdx = -1;
	Float_t bestDiff = 10000.0;
	for(unsigned int i = 0; i < regMass.size(); i++){
		Float_t mass = regMassSyst(regMass.at(i), syst);
		Float_t diff = TMath::Abs(mass - target);
		if(diff < bestDiff){
			bestIdx = i;
			bestDiff = diff;
		}
	}
	if(bestIdx < 0){
		return -1;
	}
	Float_t bestMass = regMassSyst(regMass.at(bestIdx), syst);
	return (bestMass > low && bestMass < high) ? bestIdx : -1;
}
