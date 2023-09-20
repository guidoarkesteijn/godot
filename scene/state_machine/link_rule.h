#pragma once

#include "scene/main/node.h"
#include "core/object/gdvirtual.gen.inc"

class LinkRule : public Node {
	GDCLASS(LinkRule, Node);

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
