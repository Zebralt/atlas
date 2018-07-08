#ifndef SLIDING_WINDOW_HPP_
#define SLIDING_WINDOW_HPP_

template <typename T>
class SlidingWindow {
public:
	SlidingWindow(std::vector<T>& elems, int windowSize = 3) : elems(elems), windowSize(windowSize) {}
	void setCursor(int i) { cursor = i; }
	
	bool hasPrevious(int index = -1) {
		return index >= 0 ? index - windowSize/2 >= 0 : cursor - windowSize/2 >= 0;
	}
	bool hasNext(int index = -1) {
		return index >= 0 ? index + windowSize/2 < elems.size() : cursor + windowSize/2 < elems.size();
	}
	T previous(int index = -1) {
		return hasPrevious(index) ? elems[(index >= 0 ? index : cursor) - windowSize/2] : T();
	}
	T next(int index = -1);
	T get(int index = -1);
	
private:
	std::vector<T>& elems;
	int windowSize = 0;
	int cursor = 0;
};

#endif // SLIDING_WINDOW_HPP_