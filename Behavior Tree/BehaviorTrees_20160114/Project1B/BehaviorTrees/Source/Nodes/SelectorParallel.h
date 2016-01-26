DEFINE_SELECTOR_NODE(SelectorParallel, "Runs all children in parallel until any of them",
	MEMBER_VAR(vector<int>, activeChildren)
	MEMBER_VAR(vector<int>, childStatuses)
	MEMBER_VAR(bool, initialized)
)