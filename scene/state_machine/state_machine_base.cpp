#include "state_machine_base.h"

void StateMachineBase::set_running(bool p_running) {
	running = p_running;
}

bool StateMachineBase::is_running() const {
	return running;
}

void StateMachineBase::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_running", "running"), &StateMachineBase::set_running);
	ClassDB::bind_method(D_METHOD("is_running"), &StateMachineBase::is_running);
}
