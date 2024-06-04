#include "a5.h"
#include <iostream>
#include <string>


void FeatureStatus::changeState(State* s) {
	state_ = s;
}

void State::changeState(FeatureStatus* f, State* s) {
    f->changeState(s);
}

void FeatureStatus::accept(){
	/*switch(id_){
		case CLASSDESIGN: id_=CODEUPATE; break;
		case CODEUPATE: id_=UNITTEST; break;
		case REDESIGNREQ: id_=CLASSDESIGN; break;
		case UNITTEST: id_=PULLREQUEST; break;
		case CODEFIXREQ: id_=CODEUPATE; break;
		case PULLREQUEST: id_=CHANGEACCEPTED; break;
		case CHANGEACCEPTED: break;
	}*/
	state_->accept(this);
}
void FeatureStatus::reject(){
	//switch(id_){
	//	case CLASSDESIGN: id_=CLASSDESIGN; break;
	//	case CODEUPATE: id_=REDESIGNREQ; break;
	//	case REDESIGNREQ: id_=CODEUPATE; break;
	//	case UNITTEST: id_=CODEFIXREQ; break;
	//	case CODEFIXREQ: id_=REDESIGNREQ; break;
	//	case PULLREQUEST: id_=CODEFIXREQ; break;
	//	case CHANGEACCEPTED: break;
	//}

	state_->reject(this);
}
void FeatureStatus::print(){
	/*if(id_==CLASSDESIGN){
		std::cout << theDesign_ << std::endl;
	}*/
	//if(id_==CODEUPATE || id_==UNITTEST){
	//	std::cout << theCode_ << std::endl;
	//	if(id_==UNITTEST){
	//		std::cout << comment_ << std::endl;
	//	}
	//}
	//if(id_==PULLREQUEST || id_==CODEFIXREQ || id_==REDESIGNREQ){
	//	if(id_==PULLREQUEST){
	//		std::cout << theCode_ << std::endl;
	//	}
	//	std::cout << comment_ << std::endl;
	//	if(id_==CODEFIXREQ){
	//		std::cout << theCode_ << std::endl;			
	//	}
	//	if(id_==REDESIGNREQ){
	//		std::cout << theDesign_ << std::endl;
	//	}
	//}
	//if(id_==CHANGEACCEPTED){
	//	std::cout << theDesign_ << std::endl;
	//	std::cout << theCode_ << std::endl;
	//	std::cout << comment_ << std::endl;
	//}
	state_->print(this);

}
std::string FeatureStatus::stateName() {
	//std::string name;
	//switch(id_){
	//	case CLASSDESIGN: name = "Class Design"; break;
	//	case CODEUPATE: name = "Code Update"; break;
	//	case REDESIGNREQ: name = "Redesign Requested"; break;
	//	case UNITTEST: name = "Unit Test"; break;
	//	case CODEFIXREQ: name = "Code Fix Requested"; break;
	//	case PULLREQUEST: name = "Pull Request"; break;
	//	case CHANGEACCEPTED: name = "Change Accepted"; break;
	//}
	return state_->stateName();
}

FeatureStatus::FeatureStatus(){
	id_= CLASSDESIGN;
	theCode_="";
	theDesign_="";
	comment_="";
	state_ = new StateCLASSDESIGN;
	
}
void FeatureStatus::update(const std::string& s){
	//switch(id_){
	//	case CLASSDESIGN: theDesign_ = s; break;
	//	case CODEUPATE: theCode_ = s; break;
	//	case REDESIGNREQ: comment_ = s; break;
	//	case UNITTEST: comment_ = comment_ + "\n" + s; break;
	//	case CODEFIXREQ: comment_= comment_ + " " + s; break;
	//	case PULLREQUEST: comment_ = s; break;
	//	case CHANGEACCEPTED: comment_ = "Change Accepted"; break;
	//}

	state_->update(s, this);
}

void StateCLASSDESIGN::print(FeatureStatus* f) {
    std::cout <<"-----------------------" << std::endl;
    std::cout << stateName() << std::endl;
	std::cout << f->theDesign_ << std::endl;
}



void StateCLASSDESIGN::update(const std::string& s, FeatureStatus* f) {
	f->theDesign_ = s;
}

void StateCLASSDESIGN::accept(FeatureStatus* f) {
    StateCODEUPATE* s = new StateCODEUPATE();
    f->changeState(s);
}

void StateCODEUPATE::print(FeatureStatus* f) {
    std::cout <<"-----------------------" << std::endl;
    std::cout << stateName() << std::endl;
    std::cout << f->theCode_ << std::endl;
}

void StateCODEUPATE::update(const std::string& s, FeatureStatus* f) {
    f->theCode_ = s;
}

void StateCODEUPATE::accept(FeatureStatus* f) {
    StateUNITTEST *s = new StateUNITTEST();
    f->changeState(s);
}

void StateCODEUPATE::reject(FeatureStatus* f) {
    StateREDESIGNREQ *s = new StateREDESIGNREQ();
    f->changeState(s);
}

void StateREDESIGNREQ::accept(FeatureStatus* f) {
    StateCLASSDESIGN *s = new StateCLASSDESIGN();
    f->changeState(s);
}

void StateREDESIGNREQ::reject(FeatureStatus* f) {
    StateCODEUPATE *s = new StateCODEUPATE();
    f->changeState(s);
}

void StateREDESIGNREQ::print(FeatureStatus* f) {
    std::cout <<"-----------------------" << std::endl;
    std::cout << stateName() << std::endl;
    std::cout << f->comment_ << std::endl;
    std::cout << f->theDesign_ << std::endl;
}

void StateREDESIGNREQ::update(const std::string& s, FeatureStatus* f) {
    f->comment_ = s;
}

void StateUNITTEST::print(FeatureStatus* f) {
    std::cout <<"-----------------------" << std::endl;
    std::cout << stateName() << std::endl;
    std::cout << f->theCode_ << std::endl;
    std::cout << f->comment_ << std::endl;
}

void StateUNITTEST::update(const std::string& s, FeatureStatus* f) {
    f->comment_ = f->comment_ + "\n" + s;
}

void StateUNITTEST::accept(FeatureStatus* f) {
    StatePULLREQUEST *s = new StatePULLREQUEST();
    f->changeState(s);
}

void StateUNITTEST::reject(FeatureStatus* f) {
    StateCODEFIXREQ *s = new StateCODEFIXREQ();
    f->changeState(s);
}


void StateCODEFIXREQ::print(FeatureStatus* f) {
    std::cout <<"-----------------------" << std::endl;
    std::cout << stateName() << std::endl;
    std::cout << f->comment_ << std::endl;
    std::cout << f->theCode_ << std::endl;
}

void StateCODEFIXREQ::update(const std::string& s, FeatureStatus* f) {
    f->comment_ = f->comment_ + " " + s;
}

void StateCODEFIXREQ::accept(FeatureStatus* f) {
    StateCODEUPATE *s = new StateCODEUPATE();
    f->changeState(s);
}

void StateCODEFIXREQ::reject(FeatureStatus* f) {
    StateREDESIGNREQ *s = new StateREDESIGNREQ();
    f->changeState(s);
}


void StatePULLREQUEST::print(FeatureStatus* f) {
    std::cout <<"-----------------------" << std::endl;
    std::cout << stateName() << std::endl;
    std::cout << f->theCode_ << std::endl;
    std::cout << f->comment_ << std::endl;
}

void StatePULLREQUEST::update(const std::string& s, FeatureStatus* f) {
    f->comment_ = s;
}

void StatePULLREQUEST::accept(FeatureStatus* f) {
    StateCHANGEACCEPTED *s = new StateCHANGEACCEPTED();
    f->changeState(s);
}

void StatePULLREQUEST::reject(FeatureStatus* f) {
    StateCODEFIXREQ *s = new StateCODEFIXREQ();
    f->changeState(s);
}

void StateCHANGEACCEPTED::print(FeatureStatus* f) {
    std::cout <<"-----------------------" << std::endl;
    std::cout << stateName() << std::endl;
    std::cout << f->theDesign_ << std::endl;
    std::cout << f->theCode_ << std::endl;
    std::cout << f->comment_ << std::endl;
}

void StateCHANGEACCEPTED::update(const std::string& s, FeatureStatus* f) {
    f->comment_ = "Change Accepted";
}

void StateCHANGEACCEPTED::reject(FeatureStatus* f) {
    StateCODEUPATE *s = new StateCODEUPATE();
    f->changeState(s);
}
