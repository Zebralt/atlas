#ifndef ENGINE_PROGRAM_HPP_
#define ENGINE_PROGRAM_HPP_

#include "../global.hpp"
#include "../model/temporary.hpp"
#include "../model/container.hpp"

#include <SFML/Graphics.hpp>

class Engine;

class EngineProgram : public Temporary {
public:
	EngineProgram(Engine* engine);
	
	virtual void init() {}
	virtual void setup() {}
	virtual void close() {}
	virtual void update() {}
	
	virtual void handle_events(sf::Event& event) {}
	
	virtual ~EngineProgram() {}
	
protected:
	Engine* engine = nullptr;
};

class EngineProgramSequence : public EngineProgram, public Container<EngineProgram*> {
public:
	EngineProgramSequence(Engine* engine);
	
	~EngineProgramSequence();
	void init();
	void setup();
	void close();
	void update();
	
private:
	std::vector<EngineProgram*> programs;
	int index = 0;
};

//class Game : public EngineProgram {
//	
//};
//
//class LogoShow : public EngineProgram {
//
//};

//class EngineProgramGraphNode : public EngineProgram {
//public:
//	EngineProgramGraphNode(Engine*);
//	EngineProgramGraphNode(EngineProgram*, Engine*);
//	~EngineProgramGraphNode();
//	void init();
//	void setup();
//	void close();
//	void update();
//	
//	void set_program(EngineProgram*);
//private:
//	EngineProgramGraphNode* next = nullptr;
//	EngineProgram* program = nullptr;
//};
//
//class EngineProgramGraph : public EngineProgram {
//public:
//	EngineProgramGraph(Engine*);
//	EngineProgramGraph(EngineProgramGraphNode*, Engine*);
//	~EngineProgramGraph();
//	void init();
//	void setup();
//	void close();
//	void update();
//	
//	void set_root(EngineProgramGraphNode*);
//		
//private:
//	EngineProgramGraphNode* node = nullptr;
//};


#endif // ENGINE_PROGRAM_HPP_