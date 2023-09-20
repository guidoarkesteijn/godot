#pragma once

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "scene/main/node.h"

class StateMachine : public Node {
	GDCLASS(StateMachine, Node);

	private:
		NodePath start_state;
		NodePath current_state;

		void update();

		void activate();

		void switchState(NodePath path);

		static void _bind_methods();

	public:
		void _notification(int p_what);

		void set_start_state(const NodePath &path);
		NodePath get_start_state() const;

		StateMachine();
};
#endif
