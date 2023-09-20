#pragma once

#include "scene/main/node.h"

class State : public Node {
	GDCLASS(State, Node);

public:
	void enter();

	void update();

	Node* check();

	void exit();
};
