#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
	Component();
	~Component();

	virtual void Initialize() = 0;
	virtual void Destroy();
};

#endif // !COMPONENT_H