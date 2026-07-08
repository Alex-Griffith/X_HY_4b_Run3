#include <TMath.h>
#include <stdio.h>
#include <iostream>
#include <TRandom.h>
#include <string>
#include <random>
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
Float_t regMassSyst(Float_t m, std::string year, std::string syst);
Int_t higgsMassMatchingRegMass(Float_t m0, Float_t m1, std::string year, std::string syst);
Int_t FindIdxJHRegMass(RVec<float> regMass, std::string year, std::string syst, Float_t low, Float_t high, Float_t target = 125.0);

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


Float_t regMassSyst(Float_t m, std::string year, std::string syst){
	// Default regressed mass branch: FatJet_globalParT3_massCorrGeneric.
	// Other candidate branches: FatJet_globalParT2_massVis, FatJet_globalParT3_massCorrX2p.
	Float_t jms_central = 1.0;
	Float_t jms_up = 1.0;
	Float_t jms_down = 1.0;
	Float_t jmr_central = 1.0;
	Float_t jmr_up = 1.0;
	Float_t jmr_down = 1.0;

	if(year == "2022" || year == "2022EE"){
		jms_central = 1.008;
		jms_up = 1.012;
		jms_down = 1.005;
		jmr_central = 1.144;
		jmr_up = 1.190;
		jmr_down = 1.098;
	}
	else if(year == "2023" || year == "2023BPix"){
		jms_central = 0.974;
		jms_up = 0.978;
		jms_down = 0.969;
		jmr_central = 1.089;
		jmr_up = 1.152;
		jmr_down = 1.025;
	}
	else if(year == "2024"){
		jms_up = 1.05;
		jms_down = 0.95;
		jmr_up = 1.05;
		jmr_down = 0.95;
	}

	if(syst == "JMS__up"){
		return m * (jms_up / jms_central);
	}
	if(syst == "JMS__down"){
		return m * (jms_down / jms_central);
	}
	if(syst == "JMR__up"){
		return 125.0 + (m - 125.0) * (jmr_up / jmr_central);
	}
	if(syst == "JMR__down"){
		return 125.0 + (m - 125.0) * (jmr_down / jmr_central);
	}
	return m;
}

Int_t higgsMassMatchingRegMass(Float_t m0, Float_t m1, std::string year, std::string syst){
	return higgsMassMatching(regMassSyst(m0, year, syst), regMassSyst(m1, year, syst));
}

Int_t FindIdxJHRegMass(RVec<float> regMass, std::string year, std::string syst, Float_t low, Float_t high, Float_t target){
	RVec<int> validIdxs = {};
	for(int i = 0; i < regMass.size(); i++){
		Float_t m = regMassSyst(regMass.at(i), year, syst);
		if(m >= low && m <= high){
			validIdxs.push_back(i);
		}
	}
	if(validIdxs.size() == 0){
		return -1;
	}
	if(validIdxs.size() == 1){
		return validIdxs.at(0);
	}

	Float_t bestDiff = TMath::Abs(regMassSyst(regMass.at(validIdxs.at(0)), year, syst) - target);
	RVec<int> bestIdxs = {validIdxs.at(0)};
	for(int i = 1; i < validIdxs.size(); i++){
		Int_t idx = validIdxs.at(i);
		Float_t diff = TMath::Abs(regMassSyst(regMass.at(idx), year, syst) - target);
		if(diff < bestDiff){
			bestDiff = diff;
			bestIdxs = {idx};
		}
		else if(diff == bestDiff){
			bestIdxs.push_back(idx);
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, bestIdxs.size() - 1);
	return bestIdxs.at(dist(gen));
}
