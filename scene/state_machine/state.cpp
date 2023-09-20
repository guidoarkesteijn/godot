#include "state.h"
#include "state_action.h"
#include "state_link.h"

void State::enter() {
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
};
