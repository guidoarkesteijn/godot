#pragma once

#include "scene/main/node.h"
#include "core/object/gdvirtual.gen.inc"

class StateAction : public Node {
	GDCLASS(StateAction, Node);

	private:
		static void _bind_methods();

	public:
		void activate();
		GDVIRTUAL0(_activate);

		void update();
		GDVIRTUAL0(_update);

		void deactivate();
		GDVIRTUAL0(_deactivate);
};
