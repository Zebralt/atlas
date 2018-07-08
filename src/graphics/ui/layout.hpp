#ifndef LAYOUT_HPP_
#define LAYOUT_HPP_

class Panel;

/**
    \author Zebralt
    \brief A class used to layout elements in a panel.
    Similar to the Java implementation.
*/
class Layout {
public:
    Layout() {}
    Layout(Panel* t) { target = t;}
    
    /// \brief Main method to redefine for a new layout.
    /// To be called after constructor.
    virtual void layoutTarget() = 0;
    void setTarget(Panel *p) { target = p;}

protected:
    Panel* target;
    unsigned int margin = 1;
};

class ColumnLayout : public Layout {
public:
    ColumnLayout() : Layout() {}
    ColumnLayout(Panel* t) : Layout(t) {}
    void layoutTarget();
};

class RowLayout : public Layout {
public:
	RowLayout() : Layout() {}
	RowLayout(Panel* t) : Layout(t) {}
	void layoutTarget();
};

enum class BorderLayoutLocation {
	NORTH, SOUTH, EAST, WEST, CENTER
};

class BorderLayout : public Layout {
public:
	BorderLayout() : Layout() {}
	BorderLayout(Panel* t) : Layout(t) {}
	void layoutTarget();
};

class GridLayout : public Layout {
public:
    GridLayout(int r, int c) : rows(r), cols(c), Layout() {}
    GridLayout(Panel* t, int r, int c) : rows(r), cols(c), Layout(t) {}
    void layoutTarget();
    
protected:
    int rows,cols;
    bool orientation = true; // left to right / f=top to bot
};

#endif