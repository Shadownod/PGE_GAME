#ifndef _STATEBASE_H
#define _STATEBASE_H

#include <string>
using std::string;



class StateBase
{

public:
	StateBase();
	StateBase(const string &stateID);
	~StateBase();


	virtual void Enter() = 0;

	virtual void Update() = 0;

	virtual void Exit() = 0;

	const string& GetStateID()
	{
		return StateId;
	};

	string StateId;

};

#endif