#include "state_machine.h"
#include "state.h"
#include "scene/scene_string_names.h"

StateMachine::StateMachine() {
}

void StateMachine::set_running(bool p_running) {
	running = p_running;
}

bool StateMachine::is_running() const {
	return running;
}

void StateMachine::_notification(int p_what) {
	if (Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			set_process_internal(true);
		} break;
		case NOTIFICATION_EXIT_TREE: {
			set_process_internal(false);
		} break;
		case NOTIFICATION_READY: {
			activate();
		} break;
		case NOTIFICATION_INTERNAL_PROCESS: {
			update();
		} break;
	}
}

void StateMachine::update() {
	if (current_state.is_empty()) {
		return;
	}

	Node* node = get_node_or_null(current_state);
	State* current = Object::cast_to<State>(node);

	if (current) {
		current->update();

		Node* destination = current->check();
		if (destination) {
			switchState(get_path_to(destination));
		}
	}
};

void StateMachine::activate() {
	running = true;

	if (!start_state.is_empty()) {
		switchState(start_state);
		return;
	}

	TypedArray<Node> nodes = get_children();

	for (int i = 0; i < nodes.size(); i++) {
		Object *child = nodes[i];
		State *state = Object::cast_to<State>(child);

		if (state != nullptr) {
			if (current_state.is_empty() && state->is_inside_tree()) {
				switchState(state->get_path());
			}
		}
	}
}

void StateMachine::deactivate() {
	running = false;
}

void StateMachine::switchState(NodePath path) {
	Node *node = get_node_or_null(current_state);
	State *state = Object::cast_to<State>(node);
	if (state) {
		state->exit();

		emit_signal(SNAME("state_exited"), state);
	}

	current_state = path;

	Node *newNode = get_node_or_null(current_state);
	State *newState = Object::cast_to<State>(newNode);

	if (newState) {
		newState->enter();

		emit_signal(SNAME("state_entered"), newState);
	}

	emit_signal(SNAME("state_switched"), state, newState);
}

void StateMachine::set_start_state(const NodePath &node) {
	start_state = node;
}

NodePath StateMachine::get_start_state() const {
	return start_state;
}

PackedStringArray StateMachine::get_configuration_warnings() const {
	PackedStringArray warnings = Node::get_configuration_warnings();

	if (get_child_count() == 0) {
		warnings.push_back("No States added as child to this StateMachine. Make sure at least one State node is the child of this node.");
	}

	if (start_state.is_empty()) {
		warnings.push_back(RTR("A valid NodePath must be set in the \"Start State\" property, otherwise the first State will be used."));
	}

	return warnings;
};

void StateMachine::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_start_state", "node"), &StateMachine::set_start_state);
	ClassDB::bind_method(D_METHOD("get_start_state"), &StateMachine::get_start_state);

	ClassDB::bind_method(D_METHOD("set_running", "running"), &StateMachine::set_running);
	ClassDB::bind_method(D_METHOD("is_running"), &StateMachine::is_running);

	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "start_state", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "State"), "set_start_state", "get_start_state");

	ADD_SIGNAL(MethodInfo("state_exited", PropertyInfo(Variant::OBJECT, "state", PROPERTY_HINT_TYPE_STRING, "State")));
	ADD_SIGNAL(MethodInfo("state_entered", PropertyInfo(Variant::OBJECT, "state", PROPERTY_HINT_TYPE_STRING, "State")));
	ADD_SIGNAL(MethodInfo("state_switched", PropertyInfo(Variant::OBJECT, "state", PROPERTY_HINT_TYPE_STRING, "State")));
}
