#ifndef CLICKABLE_HPP_
#define CLICKABLE_HPP_


class Clickable {
	
public:
	Clickable() {}
	virtual void onClick() = 0;
	virtual ~Clickable() {}
};

#endif // CLICKABLE_HPP_
