#ifndef PIPELINE_HPP_
#define PIPELINE_HPP_

#include "model/container.hpp"
#include "tools/xml_document.hpp"

#include <iostream>
#include <vector>
#include <map>

// namespace atlas_engine {

enum ParameterType {
	Integer, Float, String
};

std::string getTypeName(const ParameterType& pt);

/**
	\brief This class embodies a unit of a pipeline. When parsing the
	xml file for a pipeline unit, once the PU has been identified by name,
	the PU can specify its parameters by name and by type (although you will
	have to convert those yourself, as they are all strings by default. You
	can use pugixml's xml_attribute class conversion methods.) with the 
	`parameters` method. The parser will see if parsed parameters are correct,
	and will send their values to the PU with `set_parameters`.
	You can take a look at class TestsPipelineUnit for an example of 
	implementation.
*/
template <typename T>
class PipelineUnit {
public:
	PipelineUnit() {}
	virtual T run(T t) = 0;
	

	///	\brief Returns the list of parameters for the PU.	
	virtual std::map<std::string, ParameterType> parameters() const {
		return std::map<std::string, ParameterType>();
	};
	
	/// \brief Used by the parser to send the parameters' values to the PU.
	virtual void set_parameters(std::map<std::string, pugi::xml_attribute>& parameters) {
		for (auto it = parameters.begin(); it != parameters.end(); ++it) {
			// do your thing
		}
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& o, const PipelineUnit<T>& p) {
	
	o << "PipelineUnit(";
	
	auto params = p.parameters();
	
	for (auto it = params.begin(); it != params.end(); ++it) {
		if (it != params.begin()) {
			o << ", ";
		}
		o << it->first << " " << getTypeName(it->second);
	}
	
	return o << ")"; 
}

/**
	\brief A mediocre but working (maybe) way of passing variables of different
	types through the pipeline.
*/
class PipelineBuffer {
public:
	PipelineBuffer();
	
	void* get(const std::string& name) { return items.find(name) != items.end() ? items[name] : nullptr; }
	void set(const std::string& name, void* value) { items[name] = value; }
	
private:
	std::map<std::string, void*> items;
};

/**
	\brief A pipeline consists of a chain of processing elements arranged 
	so that the output of each element is the input of the next. This output
	is stored in the pipeline object, and can be initialzed beforehand. Once
	this is done, you can run the pipeline with `Pipeline::run()`. This will
	run units one after the other. You can retrieve the final data with after
	that.
	A pipeline is described in a XML file with the following format :
	    
	    ```<xml>
		<pipeline>
			<unit name="unit_name" [param=value ...] />
			...
		</pipeline>```
	
	Pipeline units are identified by name. You need to provide the method
	`identifyPipelineUnit` with the pipeline unit class to instantiate for 
	each possible name. You can also pass parameters to pipeline units with
	additional xml node attributes. 
*/
template <typename T>
class Pipeline : public Container<PipelineUnit<T>*> {
public:
	Pipeline() {}
	
	virtual ~Pipeline() {
		for (auto unit : this->items) {
			if (unit) delete unit;		
		}
	}
	
	/// \brief Run the pipeline. You should initialize the data
	/// before using this method.
	virtual void run() = 0;
	
	/// \brief Returns the pipeline data object.
	T data() { return _data; }
	
	void setData(T t) { _data = t; }
	
	/// \brief As there is no other way, you need to be able to figure out
	/// which pipeline units to use depending on the name contained by the 
	/// unit node in the xml file. Thus you must specify (with if statements,
	/// for example) which name correponds to which pipeline unit class you 
	/// have custom created.
	virtual PipelineUnit<T>* identifyPipelineUnit(const std::string& name) = 0;
	
protected:
	T _data;
	PipelineUnit<T>* current_unit;
};

template <typename T>
std::ostream& operator<<(std::ostream& o, const Pipeline<T>& p) {
	
	o << "Pipeline {" << std::endl;
	for (auto unit : p.allitems()) {
		o << "\t" << *unit << std::endl;
	}
	return o << "}";
}

/////////////// ^ ABSTRACTION //////
/////////////// v IMPLEMENTATION ///

/**
	\brief An implementation of the Pipeline pattern for the engine.
	Allows to easily modify the engine process without recompiling everything.
*/
class EnginePipeline : public Pipeline<int> {
public:
	EnginePipeline();
	EnginePipeline(const std::string& name) {
		load_from_file(name);
	}
	
	 void run() {
//		for (auto unit : this->items) {
//			_data = unit->run(_data);
//		}
		for (int i=0; i<size(); i++) {
			_data = get(i)->run(_data);
		}
	}
	
	void load_from_file(const std::string& name);
	virtual PipelineUnit<int>* identifyPipelineUnit(const std::string& name);
	
	
private:
	XmlDocument xml_doc;
};

#include "test/test.hpp"
#include "engine.hpp"

/**
	\brief A pipeline unit executing the tests located in `\test`.
	You can specify the output location parameter in the xml file.
*/
class TestsPipelineUnit : public PipelineUnit<int> {
public:
	TestsPipelineUnit() {}
	
	int run(int) {
		run_tests(test_output);
		return 0; 
	}
	
	std::map<std::string, ParameterType> parameters() const {
		std::map<std::string, ParameterType> params;
		params["output"] = ParameterType::String;
		return params;
	}
	
	void set_parameters(std::map<std::string, pugi::xml_attribute>& parameters) {
		test_output = parameters["output"].value();
	}
	
private:
	std::string test_output;
};

#include "game/snake_game/snake_game.hpp"

/**
	\brief A pipeline unit to start the snake game.
*/
class SnakeGamePipelineUnit : public PipelineUnit<int> {
public:
	SnakeGamePipelineUnit(){}
	
	int run(int) {
		Engine::init();
		Engine::load_scene(new SnakeGameScene(10, 10));
		Engine::run();
		return Engine::get_status();
	}
};

#include "engine/scene.hpp"
class LogoScenePipelineUnit : public PipelineUnit<int> {
public:
	LogoScenePipelineUnit(){}
	
	int run(int) {
		Engine::init();
		Engine::load_scene(new EngineLogoScene());
		Engine::run();
		return Engine::get_status();
	}
};

#include "game/show_cards/show_cards.hpp"
class ShowCardsScenePipelineUnit : public PipelineUnit<int> {
public:
	ShowCardsScenePipelineUnit(){}
	
	int run(int) {
		Engine::init();
		Engine::load_scene(new ShowCardsScene());
		Engine::run();
		return Engine::get_status();
	}
};

#include "game/music_player/music_player.hpp"
class MusicPlayerScenePipelineUnit : public PipelineUnit<int> {
public:
	MusicPlayerScenePipelineUnit(){}
	
	int run(int) {
		Engine::init();
		Engine::load_scene(new MusicPlayerScene());
		Engine::run();
		return Engine::get_status();
	}
};

//}

#endif // PIPELINE_HPP_