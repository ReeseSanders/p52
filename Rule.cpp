#include "Rule.h"

void Rule::AddHeadPredicate(Predicate toAdd){
    headPredicate = toAdd;
}

void Rule::AddFollowingPred(Predicate toAdd){
    followingPred.push_back(toAdd);
}

std::string Rule::ToString(){
    std::string ruleString = headPredicate.ToString() + " :- ";
    for (unsigned int i = 0; i < followingPred.size(); i++){
        if (i != followingPred.size()-1) {
            ruleString += followingPred.at(i).ToString() + ",";
        } else {ruleString += followingPred.at(i).ToString() + ".";}
    }
    return ruleString;
}

std::vector<std::string> Rule::GetVecFollowPred(){
    std::vector<std::string> vecHead;
    for (auto i : followingPred) {
        vecHead.push_back(i.getHead());
    }
    return vecHead;
}

bool Rule::IsPredInHead(){
    bool isTrue = false;
    for (unsigned int i = 0; i < followingPred.size(); i++) {
        if (followingPred.at(i).getHead() == headPredicate.getHead()){
            isTrue = true;
        }
    }
    return isTrue;
}

bool Rule::IsPredInHeadOther(Predicate check){
    bool isTrue = false;
    for (unsigned int i = 0; i < followingPred.size(); i++) {
        if (followingPred.at(i).getHead() == check.getHead()){
            isTrue = true;
        }
    }
    return isTrue;
}