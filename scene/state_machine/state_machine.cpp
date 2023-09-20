#include "state_machine.h"
#include "state.h"

StateMachine::StateMachine() {
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

void StateMachine::switchState(NodePath path) {
	Node *node = get_node_or_null(current_state);
	State *state = Object::cast_to<State>(node);
	if (state) {
		state->exit();
	}

	current_state = path;

	Node *newNode = get_node_or_null(current_state);
	State *newState = Object::cast_to<State>(newNode);

	if (newState) {
		newState->enter();
	}
}

void StateMachine::set_start_state(const NodePath &node) {
	start_state = node;
}

NodePath StateMachine::get_start_state() const {
	return start_state;
};

void StateMachine::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_start_state", "node"), &StateMachine::set_start_state);
	ClassDB::bind_method(D_METHOD("get_start_state"), &StateMachine::get_start_state);

	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "start_state", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "State"), "set_start_state", "get_start_state");
}
