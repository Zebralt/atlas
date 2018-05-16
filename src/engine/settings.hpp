#ifndef settings_hpp__
#define settings_hpp__

#include <fstream>
#include <map>
#include "../pugixml/pugixml.hpp"

//typedef std::variant<int, double, std::string> setting_variant;
typedef pugi::xml_attribute setting_variant;

class Settings {
	public:
		Settings();
		Settings(const std::string& filepath);
		void load_from_file(const std::string& filepath);
		setting_variant get(const std::string& name);
	private:
		pugi::xml_document xml_data;
};

/*
class XSettings {
	
public:
	Settings();
	Settings(const std::string& filepath);
	
	bool exists(const std::string& key);
	std::string get(const std::string& name);
	bool append(const std::string& name, const std::string& value);
	
	std::map<std::string, std::string> get_category(const std::string& name);
	
	// open and close the file
	bool loadFromFile(const std::string& filepath);
	bool saveToFile(const std::string& filepath);
	
	// these assume the file is open, and do not close it once their job is done
	// you need to define a syntax
	// For example :
	// [Category]
	// key=value
	
	virtual bool load_from_file(std::ifstream& file);
	virtual bool load_from_file(const std::string& filepath);
	virtual bool save_to_file(std::ofstream& file);
	
	void setName(const std::string& name);
	std::string name();
	
	// add 's' categories/attributes to this settings
	bool extend(const Settings& s);
	
private:
	// default: the name of the file ?
	std::string m_name;
	std::map<std::string, std::map<std::string, std::string>> attributes;
	
	
};


class DefaultSettings : public Settings {
public:
	DefaultSettings() : Settings("default_settings") {
		insert("display", "resolution.width", "1920");
		insert("resolution.height", "1080");
		insert("framerate_limit", "60");
	}
};

// Example of keymap settings

class KeymapSettings : public Settings {
public:
	KeymapSettings() : Settings("Keymap") {
		insert("keyboard", "jump", "spacebar");
		insert("keyboard", "up", "up");
		insert("keyboard", "sprint", "maj");
	}
};

class Event {

};
*/
//class EventNexus {
//	
//	void fireEvent();
//	
//};
//
//class Frame {
//	
//	std::vector<std::string> registered_events;
//	
//	void registerEvent(const std::string& eventName);
//	void unregisterEvent(const std::string& eventName);
//	virtual void onEvent(const Event& event) = 0;
//};

#endif // settings_hpp__