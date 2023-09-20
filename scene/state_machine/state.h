#pragma once

#include "scene/main/node.h"

class State : public Node {
	GDCLASS(State, Node);

public:
	void enter();

	void update();

	NodePath check();

	void exit();
};
