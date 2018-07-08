#include "music_player.hpp"

#include "graphics/ui/button.hpp"
#include "tools/strmanip.hpp"

MusicTrack::MusicTrack(const std::string& name, const std::string& filepath) : name(name), filepath(filepath) {}
MusicTrack::MusicTrack(const pugi::xml_node& node) {
	
	filepath = node.attribute("href").value();
	if (node.attribute("name")) {
		name = node.attribute("name").value();
	}
	else {
		auto elems = split(filepath, '/');
		if (elems.size()) {
			name = elems[elems.size() - 1];
		}
		elems = split(name, '.');
		if (elems.size()) {
			elems.pop_back();
			name = join(elems, ".");
		}
	}
	
	Engine::load(ResourceType::MUSIC, name, filepath);
	music = Engine::get_music(name);
}

std::ostream& operator<<(std::ostream& o, const MusicTrack& p) {
	return o << p.name << " <" << p.filepath << ">";
}

Playlist::Playlist() {}
Playlist::Playlist(const std::string& filepath) {
	load_from_file(filepath);
}

void Playlist::load_from_file(const std::string& filepath) {
	XmlDocument xdoc;
	xdoc.load_from_file(filepath);
	
	auto nodes = xdoc.select_nodes("playlist/song");
	
	if (xdoc.first_child().attribute("name")) {
		_name = xdoc.first_child().attribute("name").value();
	}
	
	for (auto node : nodes) {
		add(MusicTrack(node.node()));
	}

}

std::ostream& operator<<(std::ostream& o, const Playlist& p) {
	o << "PLAYLIST: " << p.name() << std::endl;
	for (auto mt : p.allitems()) {
		o << "\t" << mt << std::endl;
	}
	return o << std::endl;
}

MusicPlayer::MusicPlayer() {}
void MusicPlayer::load_playlist(Playlist* l) {
	playlist = l;
}
void MusicPlayer::load_directory(const std::string& filepath) {
	
}

void MusicPlayer::play() {
	timer.play();
	if (current_song) current_song->play();
	
}
void MusicPlayer::pause() {
	timer.pause();
	if (current_song) current_song->pause();
}
void MusicPlayer::unpause() {
	timer.unpause();
	if (current_song) current_song->play();
}
void MusicPlayer::reset() {
	timer.reset();
	if (current_song) current_song->stop();
}

void MusicPlayer::next() {
	LOG("next");
	Cycle::next();
	current_song = current();
}
void MusicPlayer::previous() {
	LOG("previous");
	Cycle::previous();
	current_song = current();
}

int MusicPlayer::cycleSize() {
	return playlist ? playlist->size() : 0;
}

Music* MusicPlayer::current() {
	return playlist ? playlist->get(cursor).music : nullptr;
}

void MusicPlayer::update() {
	// check music progress
	// change song if music ended
	
}

MusicPlayerPanel::MusicPlayerPanel() {
	
	setSize(500, 400);
	setBackgroundColor(sf::Color(100, 100, 100));
	
	name_label = new Label();
	name_label->setSize(getSize().w, 100);
	
	progress_bar = new ProgressBar();
	progress_bar->setPosition(Vec2f(0, name_label->getPosition().y + name_label->getSize().h + 10));
	progress_bar->setSize(getSize().w, 10);
	
	auto button_panel = new Panel();
	button_panel->setSize(getSize().w, 50);
	button_panel->setPosition(Vec2f(0, progress_bar->getPosition().y + progress_bar->getSize().h + 10));
	
	auto play_button = new Button("Play");
	play_button->setSize(75, 30);
	play_button->set_action([=]() {
		mplayer->play();
	});
	
	auto pause_button = new Button("Pause");
	pause_button->setSize(75, 30);
	pause_button->setPosition(Vec2f(80, 0));
	pause_button->set_action([=]() {
		mplayer->pause();
	});
	
	auto next_button = new Button("Next");
	next_button->setSize(75, 30);
	next_button->setPosition(Vec2f(160, 0));
	next_button->set_action([=]() {
		mplayer->next();
	});
	
	auto previous_button = new Button("Previous");
	previous_button->setSize(75, 30);
	previous_button->setPosition(Vec2f(240, 0));
	previous_button->set_action([=]() {
		mplayer->previous();
	});
	
	button_panel->add(play_button);
	button_panel->add(pause_button);
	button_panel->add(next_button);
	button_panel->add(previous_button);
	
	add(name_label);
	add(progress_bar);
	add(button_panel);
	
	button_panel->setLayout(new RowLayout());
//	mplayer.load_playlist(new Playlist("tracks.xml"));

	Playlist p("tracks.xml");
	LOG(p);
}

MusicPlayerScene::MusicPlayerScene() : Scene() {}

void MusicPlayerScene::initialize() {
	auto main_item = new MusicPlayerPanel();
	Engine::register_widget(main_item);
}
void MusicPlayerScene::terminate() {}
void MusicPlayerScene::update() {
// update music player
// update song if over
// update progress bar
// update timer
}
void MusicPlayerScene::handle_events(sf::Event&) {}