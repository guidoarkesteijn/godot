#include "state_action.h"

void StateAction::activate() {
	GDVIRTUAL_CALL(_activate);
}

void StateAction::update() {
	GDVIRTUAL_CALL(_update);
}

void StateAction::deactivate() {
	GDVIRTUAL_CALL(_deactivate);
}

void StateAction::_bind_methods() {
	GDVIRTUAL_BIND(_activate);
	GDVIRTUAL_BIND(_update);
	GDVIRTUAL_BIND(_deactivate);
}
