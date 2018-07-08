#ifndef object_hpp__
#define object_hpp__

// namespace atlas_engine {

/// IDENTIFICATION CODES :
enum ID_CODE {
	ON_HOVER = 0b10000,
	ON_CLICK = 0b01000,
	CONTAINER = 0b100,
	WIDGET = 0b10
};

/**
	\author Zebralt
	\brief This class has been created for the sake
	of easily determining an object's class. Notably
	when parsing for objects that possess mouseover and
	mouseclick related behaviors.
*/
class Object {
public:
    Object() {}
    virtual int hash_code() { return 0; }
};

// } // namespace atlas_engine

#endif // object_hpp__
