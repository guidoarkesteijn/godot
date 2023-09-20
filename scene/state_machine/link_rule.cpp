#include "link_rule.h"

bool LinkRule::is_valid() {
	bool ret = false;
	GDVIRTUAL_CALL(_is_valid, ret);
	return ret;
}

void LinkRule::activate() {
	GDVIRTUAL_CALL(_activate);
}

void LinkRule::deactivate() {
	GDVIRTUAL_CALL(_deactivate);
}

void LinkRule::_bind_methods() {
	GDVIRTUAL_BIND(_activate);
	GDVIRTUAL_BIND(_deactivate);
	GDVIRTUAL_BIND(_is_valid);
}
