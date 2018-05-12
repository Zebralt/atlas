#include "engine_program.hpp"

EngineProgram::EngineProgram(Engine* engine) : engine(engine) {}

/////////////////////////// ENGINE PROGRAM GRAPH ///////////////////////////////////////////////////////////

//EngineProgramGraphNode::EngineProgramGraphNode(Engine* engine) : EngineProgram(engine) {}
//EngineProgramGraphNode::EngineProgramGraphNode(EngineProgram* p, Engine* engine) : program(p), EngineProgram(engine) {}
//
//void EngineProgramGraphNode::set_program(EngineProgram* p) {
//	program = p;
//}
//
//void EngineProgramGraphNode::init() {
//	if (status && program && program->getStatus()) {
//		program->init();
//	}
//	else {
//		status = TERMINATED;
//	}
//}
//
//void EngineProgramGraphNode::setup() {
//	if (status && program && program->getStatus()) {
//		program->setup();
//	}
//	else {
//		status = TERMINATED;
//	}
//}
//
//void EngineProgramGraphNode::close() {
//	if (program) {
//		program->close();
//	}
//	status = TERMINATED;
//}
//
//void EngineProgramGraphNode::update() {
//	if (status && program && program->getStatus()) {
//		program->update();
//	}
//	else {
//		status = TERMINATED;
//	}
//}
//
//EngineProgramGraphNode::~EngineProgramGraphNode() {
//	if (program) delete program;
////	if (next) delete next;
//}
//
//EngineProgramGraph::EngineProgramGraph(Engine* engine) : EngineProgram(engine) {}
//EngineProgramGraph::EngineProgramGraph(EngineProgramGraphNode* n, Engine* engine) : node(n), EngineProgram(engine) {}
//
//void EngineProgramGraph::set_root(EngineProgramGraphNode* node) {
//	this->node = node;
//}
//
//void EngineProgramGraph::init() {
//	if (!status || !node) {
//		status = TERMINATED;
//	}
//	else {
//		
//	}
//}
//
//void EngineProgramGraph::setup() {
//	if (status && node && node->getStatus()) {
//		node->setup();
//	}
//	else {
//		status = TERMINATED;
//	}
//}
//
//void EngineProgramGraph::close() {
//	if (node) {
//		node->close();
//	}
//	status = TERMINATED;
//}
//
//void EngineProgramGraph::update() {
//	if (status && node && node->getStatus()) {
//		node->update();
//	}
//	else {
//		status = TERMINATED;
//	}
//}
//
//EngineProgramGraph::~EngineProgramGraph() {
//	if (node) delete node;
//}

////////////////////////////////////////////////////////////////////////

EngineProgramSequence::EngineProgramSequence(Engine* engine) : EngineProgram(engine) {}

EngineProgramSequence::~EngineProgramSequence() {
	for (auto ptr : programs) {
		if (ptr) delete ptr;
	}
}

void EngineProgramSequence::init() {
	if (programs.size() && index < programs.size()) {
		programs[index]->init();
	}
	else {
		status = TERMINATED;
	}
}

void EngineProgramSequence::setup() {
	if (programs.size() && index < programs.size()) {
		programs[index]->setup();
	}
	else {
		status = TERMINATED;
	}
}

void EngineProgramSequence::close() {
	if (programs.size() && index < programs.size()) {
		programs[index]->close();
	}
	else {
		status = TERMINATED;
	}
}

void EngineProgramSequence::update() {
	if (!programs.size() || index >= programs.size()) {
		status = TERMINATED;
	}
	else if (!programs[index] || !programs[index]->getStatus()) {
		if (programs[index]) {
			programs[index]->close();
		}
		index++;
		if (index < programs.size()) {
			programs[index]->init();
		}
	}
}