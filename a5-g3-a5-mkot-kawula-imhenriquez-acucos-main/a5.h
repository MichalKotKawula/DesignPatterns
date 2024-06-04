#ifndef A5_H
#define A5_H

#include <string>

enum StateID {CLASSDESIGN,CODEUPATE,REDESIGNREQ,UNITTEST,
					CODEFIXREQ,PULLREQUEST,CHANGEACCEPTED};


class State;
class FeatureStatus{
	friend class StateCLASSDESIGN;
	friend class StateCODEUPATE;
	friend class StateREDESIGNREQ;
	friend class StateUNITTEST;
	friend class StateCODEFIXREQ;
	friend class StatePULLREQUEST;
	friend class StateCHANGEACCEPTED;
	friend class State;
	StateID id_;  //enumerated type for the state, easier to check this than string
	std::string theCode_;
	std::string comment_;
	std::string theDesign_;
	State* state_;
	void changeState(State* s);
public:
	FeatureStatus();
	std::string stateName();
	void print();
	void update(const std::string& s);
	void accept();
	void reject();
};



class State {
	FeatureStatus* feature;
public:
	void changeState(FeatureStatus* f, State* s);
	virtual std::string stateName() = 0;
	virtual void print(FeatureStatus* feature) = 0;
	virtual void update(const std::string& s, FeatureStatus* feature) = 0;
	virtual void accept(FeatureStatus* feature) {}
	virtual void reject(FeatureStatus* feature) {}
protected:
	void changeState(State* s);
};



class StateCLASSDESIGN : public State {
public:
	virtual void print(FeatureStatus* feature);
	virtual void update(const std::string& s, FeatureStatus* feature);
	virtual void accept(FeatureStatus* feature);
	virtual std::string stateName(){return "Class Design";}
};

class StateCODEUPATE : public State {
public:
	virtual void print(FeatureStatus* feature);
	virtual void update(const std::string& s, FeatureStatus* feature);
	virtual void accept(FeatureStatus* feature);
	virtual void reject(FeatureStatus* feature);
	virtual std::string stateName(){return "Code Update";}
};

class StateREDESIGNREQ : public State {
public:
	virtual void print(FeatureStatus* feature);
	virtual void update(const std::string& s, FeatureStatus* feature);
	virtual void accept(FeatureStatus* feature);
	virtual void reject(FeatureStatus* feature);
	virtual std::string stateName(){return "Redesign Requested";}
};

class StateUNITTEST : public State {
public:
	virtual void print(FeatureStatus* feature);
	virtual void update(const std::string& s, FeatureStatus* feature);
	virtual void accept(FeatureStatus* feature);
	virtual void reject(FeatureStatus* feature);
	virtual std::string stateName(){return "Unit Test";}
};

class StateCODEFIXREQ : public State {
public:
	virtual void print(FeatureStatus* feature);
	virtual void update(const std::string& s, FeatureStatus* feature);
	virtual void accept(FeatureStatus* feature);
	virtual void reject(FeatureStatus* feature);
	virtual std::string stateName(){return "Code Fix Requested";}
};

class StatePULLREQUEST : public State {
public:
	virtual void print(FeatureStatus* feature);
	virtual void update(const std::string& s, FeatureStatus* feature);
	virtual void accept(FeatureStatus* feature);
	virtual void reject(FeatureStatus* feature);
	virtual std::string stateName(){return "Pull Request";}
};

class StateCHANGEACCEPTED : public State {
public:
	virtual void print(FeatureStatus* feature);
	virtual void update(const std::string& s, FeatureStatus* feature);
	virtual void reject(FeatureStatus* feature);
	virtual std::string stateName(){return "Change Accepted";}
};


#endif