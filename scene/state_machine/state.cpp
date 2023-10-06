#include "state.h"
#include "state_action.h"
#include "state_link.h"

void State::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_running", "running"), &State::set_running);
	ClassDB::bind_method(D_METHOD("is_running"), &State::is_running);
}

void State::enter() {
	set_running(true);

	TypedArray<Node> nodes = get_children();

	for (int i = 0; i < nodes.size(); i++) {
		Object *child = nodes[i];
		StateAction *action = Object::cast_to<StateAction>(child);

		if (action) {
			action->activate();
			continue;
		}

		StateLink *link = Object::cast_to<StateLink>(child);

		if (link) {
			link->activate();
			continue;
		}
	}
}

void State::update(){
	TypedArray<Node> nodes = get_children();

	for (int i = 0; i < nodes.size(); i++) {
		Object *child = nodes[i];
		StateAction *action = Object::cast_to<StateAction>(child);

		if (action) {
			action->update();
		}
	}
};

Node* State::check() {
	TypedArray<Node> nodes = get_children();

	for (int i = 0; i < nodes.size(); i++) {
		Object *child = nodes[i];
		StateLink *link = Object::cast_to<StateLink>(child);

		if (link) {
			bool valid = link->is_valid();
			if (valid) {
				return link->get_destination_node();
			}
		}
	}

	return nullptr;
}

void State::exit() {
	set_running(false);

	TypedArray<Node> nodes = get_children();

	for (int i = 0; i < nodes.size(); i++) {
		Object *child = nodes[i];
		StateAction *action = Object::cast_to<StateAction>(child);

		if (action) {
			action->deactivate();
			continue;
		}

		StateLink *link = Object::cast_to<StateLink>(child);

		if (link) {
			link->deactivate();
			continue;
		}
	}
}
void State::set_running(bool p_running){
	running = p_running;
}
bool State::is_running() const {
	return running;
};
