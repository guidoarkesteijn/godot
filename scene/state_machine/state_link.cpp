#include "state_link.h"
#include "link_rule.h"

void StateLink::activate() {
	TypedArray<Node> nodes = get_children();

	for (int i = 0; i < nodes.size(); i++) {
		Object *child = nodes[i];
		LinkRule *rule = Object::cast_to<LinkRule>(child);

		if (rule) {
			rule->activate();
			continue;
		}
	}
}

bool StateLink::is_valid() {
	TypedArray<Node> nodes = get_children();

	for (int i = 0; i < nodes.size(); i++) {
		Object *child = nodes[i];
		LinkRule *rule = Object::cast_to<LinkRule>(child);

		if (rule && !rule->is_valid()) {
			return false;
		}
	}
	return true;
}

void StateLink::deactivate() {
	TypedArray<Node> nodes = get_children();

	for (int i = 0; i < nodes.size(); i++) {
		Object *child = nodes[i];
		LinkRule *rule = Object::cast_to<LinkRule>(child);

		if (rule) {
			rule->deactivate();
			continue;
		}
	}
}

void StateLink::set_destination_state(const NodePath &path) {
	destination = path;
}

NodePath StateLink::get_destination_state() const {
	return destination;
}

void StateLink::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_destination_state", "node"), &StateLink::set_destination_state);
	ClassDB::bind_method(D_METHOD("get_destination_state"), &StateLink::get_destination_state);

	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "destination", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "State"), "set_destination_state", "get_destination_state");
}
