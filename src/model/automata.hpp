#ifndef automata_hpp_
#define automata_hpp_

//#include "global.h""

#include <vector>

// generic Automata-AutomataNode classes
// you may need to redefine the 'RelationData' type operator ==
// a relation should either be another node or something that you define
// relationdata being the value of the transition : for a regex, a char 'a' for instance

// this automata is not necessarily deterministic, and it will retrieve by default
// the first relation with the corresponding relationData

template <typename RelationData, typename Relation> struct AutomataNode {
	
	std::vector<std::pair<RelationData, Relation*>> relations;
	
	std::vector<Relation*> getRelationsFromData(RelationData rd) {
		std::vector<Relation*> rs;
		for (auto& pair : relations) {
			if (rd == pair.first) {
				rs.push_back(pair.second);
			}
		}
		
		return rs;
	}
	
	Relation* addRelation(RelationData rdata, Relation* r) {
//		relations.push_back(std::pair<RelationData, Relation*>(rdata, r));
		relations.push_back(std::make_pair(rdata, r));
		return r;
	}
	
	AutomataNode() {
		
	}
	
	~AutomataNode() {
		for (auto& pair : relations) {
			if (pair.second && pair.first != '_') 
				delete pair.second;
		}
	}
	
};

template <typename AutomataNode> struct Automata {
	AutomataNode* start;
	
	void setStart(AutomataNode* an) {
		start = an;
	}	
	
	~Automata() {
		delete start;
	}
};




#endif // automata_hpp_