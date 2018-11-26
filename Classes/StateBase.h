#pragma once

#ifndef _STATEBASE_H
#define _STATEBASE_H

using std::string;

class StateBase
{
public:
	virtual void Enter() = 0;

	virtual void Update() = 0;

	virtual void Exit() = 0;

	const string& GetStateID();

public:
	string StateId;
};



#endif