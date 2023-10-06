#pragma once

#include "scene/main/node.h"

class State : public Node {
	GDCLASS(State, Node);

	bool running = false;

protected:

	static void _bind_methods();

public:
	void enter();

	void update();

	Node* check();

	void exit();

	void set_running(bool p_running);
	bool is_running() const;
};
