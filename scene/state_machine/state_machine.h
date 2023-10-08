#pragma once

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "state_machine_base.h"
#include "scene/main/node.h"

class StateMachine : public StateMachineBase {
	GDCLASS(StateMachine, StateMachineBase);

	private:
		NodePath start_state;
		NodePath current_state;

		void switchState(NodePath path);

	protected:
		void update();

		void activate();
		void deactivate();

		static void _bind_methods();

	public:
		void _notification(int p_what);

		void set_start_state(const NodePath &path);
		NodePath get_start_state() const;

		PackedStringArray get_configuration_warnings() const override;
};

#endif
