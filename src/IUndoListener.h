#pragma once

class IUndoListener {
public:
	virtual void notify() = 0;
	virtual ~IUndoListener() {}
};
