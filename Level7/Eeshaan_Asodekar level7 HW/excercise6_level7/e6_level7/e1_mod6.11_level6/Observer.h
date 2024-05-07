#pragma once

#include <memory>

class Subject;

class Observer
{
public:
	virtual void Update(Subject* subject) = 0;
};

