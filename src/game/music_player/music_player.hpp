#ifndef MUSIC_PLAYER_HPP_
#define MUSIC_PLAYER_HPP_

#include "model/temporary.hpp"
#include "engine/timer.hpp"
#include "engine/audio/sound.hpp"

#include "engine/scene.hpp"

#include "graphics/ui/panel.hpp"
#include "graphics/ui/label.hpp"
#include "graphics/ui/progressbar.hpp"

#include <pugixml.hpp>

struct MusicTrack {
	std::string name;
	std::string filepath;
	Music* music;
	
	MusicTrack(const std::string& name, const std::string& filepath);
	MusicTrack(const pugi::xml_node& node);
	
	bool operator==(const MusicTrack& mt) {
		return name == mt.name && filepath == mt.filepath;
	}
};

std::ostream& operator<<(std::ostream& o, const MusicTrack& p);

class Playlist : public CycleList<MusicTrack> {
public:
	Playlist();
	Playlist(const std::string& filepath);
	void load_from_file(const std::string& filepath);
	
	std::string name() const { return _name; }
	
private:
	std::string _name;
};

std::ostream& operator<<(std::ostream& o, const Playlist& p);

class MusicPlayer : public Temporary, public TimeEnabled, public Cycle<Music*> {
public:
	MusicPlayer();
	void load_playlist(Playlist* l);
	void load_directory(const std::string& filepath);
	
	// timeenabled
	void play();
	void pause();
	void unpause();
	void reset();
	
	// temporary
	void update();
	
	// cycle
	void next();
	void previous();
	Music* current();
	int cycleSize();

protected:
	Playlist* playlist;
	Music* current_song;

};

class MusicPlayerPanel : public Panel {
public:
	MusicPlayerPanel();
	MusicPlayerPanel(MusicPlayer* mp);
	
	void setMusicPlayer(MusicPlayer* mp);
	
	MusicPlayer* getMusicPlayer() {
		return mplayer;
	}
	
private:
	Label* name_label;
	ProgressBar* progress_bar;
	MusicPlayer* mplayer;
	
};

class MusicPlayerScene : public Scene {
public:
	MusicPlayerScene();
	
	void initialize();
	void terminate();
	void update();
	void handle_events(sf::Event&);
	
private:
	MusicPlayer* mplayer;
};

#endif // MUSIC_PLAYER_HPP_