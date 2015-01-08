#ifndef ButtonDebouncer_h
#define ButtonDebouncer_h

class ButtonDebouncer
{
private:
	int *Buttons;

public:
	ButtonDebouncer();
	~ButtonDebouncer();
	ButtonDebouncer(int *buttons);
};

#endif