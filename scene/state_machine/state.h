#pragma once

#include "state_machine_base.h"
#include "state_machine.h"
#include "scene/main/node.h"

class State : public StateMachineBase {
	GDCLASS(State, StateMachineBase);

protected:

	static void _bind_methods();

public:
	void enter();

	void update();

	Node* check();

	PackedStringArray get_configuration_warnings() const override;

	void exit();
};
