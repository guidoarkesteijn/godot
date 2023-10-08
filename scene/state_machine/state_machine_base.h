#pragma once

#ifndef STATE_MACHINE_BASE_H
#define STATE_MACHINE_BASE_H

#include "scene/main/node.h"

class StateMachineBase : public Node {
	GDCLASS(StateMachineBase, Node);

	protected:
		bool running = false;
		static void _bind_methods();

	public:
		void set_running(bool p_running);
		bool is_running() const;
};
#endif
