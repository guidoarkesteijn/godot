#pragma once

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "scene/main/node.h"

class StateMachine : public Node {
	GDCLASS(StateMachine, Node);

	bool running = false;

	private:
		NodePath start_state;
		NodePath current_state;

		void update();

		void activate();
		void deactivate();

		void switchState(NodePath path);

		static void _bind_methods();

	public:
		void _notification(int p_what);

		void set_start_state(const NodePath &path);
		NodePath get_start_state() const;

		PackedStringArray get_configuration_warnings() const override;

		StateMachine();

		void set_running(bool p_running);
		bool is_running() const;
};
#endif
