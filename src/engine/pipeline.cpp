#include "pipeline.hpp"

// namespace atlas_engine {

std::string getTypeName(const ParameterType& pt) {
	return std::vector<std::string>({"INTEGER", "FLOAT", "STRING"})[pt];
}

EnginePipeline::EnginePipeline() : Pipeline<int>() {}

void EnginePipeline::load_from_file(const std::string& filepath) {
	xml_doc.load_from_file(filepath);
	
	auto unit_nodes = xml_doc.select_nodes("pipeline/unit");
	
	for (auto& node : unit_nodes) {
		
		PipelineUnit<int>* unit = nullptr;
			
		for (auto& param : node.node().attributes()) {
			
			if (std::string(param.name()) == "name") {
				unit = identifyPipelineUnit(param.value());
			}
			else {					
				if (!unit) break;

				auto parameter_names = unit->parameters();
				std::map<std::string, pugi::xml_attribute> parameter_values;
				
				if (parameter_names.find(std::string(param.name())) != parameter_names.end()) {
					parameter_values[std::string(param.name())] = param;
				}
				else {
					LOG("In pipeline unit, unknown parameter : " << std::string(param.name()));
				}
				
				unit->set_parameters(parameter_values);
			}
		}
		
		if (unit) add(unit);
	}
}


PipelineUnit<int>* EnginePipeline::identifyPipelineUnit(const std::string& name) {
	
	if (name == "tests") {
//		LOG("Issued Tests PU");
		return new TestsPipelineUnit();
	}
	if (name == "default_scene") {
//		LOG("Issued default PU");
		return new LogoScenePipelineUnit();
	}
	if (name == "show_cards") {
//		LOG("Issued ShowCards PU");
		return new ShowCardsScenePipelineUnit();
	}
	if (name == "snake_game") {
//		LOG("Issued SnakeGame PU");
		return new SnakeGamePipelineUnit();
	}
	if (name == "music_player") {
		return new MusicPlayerScenePipelineUnit();
	}
	
	return nullptr;
}

// } // namespace atlas_engine
