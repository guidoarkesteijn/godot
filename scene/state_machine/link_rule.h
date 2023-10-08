#pragma once

#include "state_link.h"
#include "scene/main/node.h"
#include "core/object/gdvirtual.gen.inc"
#include "state_machine_base.h"

class LinkRule : public StateMachineBase {
	GDCLASS(LinkRule, StateMachineBase);

private:
	static void _bind_methods();

public:
	GDVIRTUAL0(_activate);
	void activate();

	GDVIRTUAL0(_deactivate);
	void deactivate();

	GDVIRTUAL0RC(bool, _is_valid);
	bool is_valid();
};
