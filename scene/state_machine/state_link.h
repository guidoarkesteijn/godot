#pragma once

#include "state_machine_base.h"
#include "state.h"
#include "scene/main/node.h"

class StateLink : public StateMachineBase {
	GDCLASS(StateLink, StateMachineBase);

	private:
		static void _bind_methods();

	public:
		NodePath destination;

		bool is_valid();

		void activate();

		void deactivate();

		Node* get_destination_node();

		void set_destination_state(const NodePath &path);
		NodePath get_destination_state() const;
};
