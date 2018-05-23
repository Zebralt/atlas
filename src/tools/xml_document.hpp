#ifndef XML_DOCUMENT_HPP_
#define XML_DOCUMENT_HPP_

#include <iostream>
#include <pugixml.hpp>

/**
	\brief Wrapper for pugixml.
*/
class XmlDocument : public pugi::xml_document {
public:
	XmlDocument();
	XmlDocument(const std::string& filepath);
	
	void load_from_file(const std::string& filepath);
	
	int geti(const std::string& name);
	std::string gets(const std::string& name);
	bool has(const std::string& name);
};

XmlDocument parse_xml(const std::string& filepath);

#endif