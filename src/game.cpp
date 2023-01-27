#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <loguru.cpp>

#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "game.hpp"
#include "config.hpp"

using namespace std;

Game* Game::instance;

void Game::update() {

}

void Game::render() {
	window->clear();
	// Debug Information
	if (debug_enabled) {
		ostringstream debug_string;
		debug_string << window->getSize().x << "x" << window->getSize().y << endl;
		debug_string << "fps: " << uint32_t(fps) << endl;
		debug_text.setString(debug_string.str());
		window->draw(debug_text);
	}

	window->display();
}

bool Game::handle_events() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window->close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		return true;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		debug_enabled = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		debug_enabled = false;

	// input on character
	return false;
}

void Game::run() {
	while (window->isOpen()) {
		// Begin timer to calculate FPS
		frame_start = chrono::high_resolution_clock::now();

		if (handle_events())
			break;

		update();
		render();

		// End FPS timer calculation
		frame_end = chrono::high_resolution_clock::now();

		// Calculate FPS
		fps = float(1e9) / float(chrono::duration_cast<chrono::nanoseconds>(frame_end - frame_start).count());
	}
}

void Game::initialize() {
	instance = new Game;

	// Setup random number generator
	mt19937::result_type seed = instance->device() ^ (
		(mt19937::result_type) chrono::duration_cast<chrono::seconds>
			(chrono::system_clock::now().time_since_epoch()).count() +

		(mt19937::result_type) chrono::duration_cast<chrono::microseconds>
			(chrono::high_resolution_clock::now().time_since_epoch()).count()
	);

	instance->rng = mt19937(seed);
	instance->load_resources();

	LOG_F(INFO, "hi");

	// Setup Window
	instance->video_mode = sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

	sf::RenderWindow root(instance->video_mode, instance->rand_title());
	instance->window = &root;
	instance->window->setFramerateLimit(120);
	instance->window->setVerticalSyncEnabled(true);

	// Debug Text	
	instance->debug_text = { "", instance->fonts[PRESS_START_2P] };
	instance->debug_text.setColor(sf::Color::White);

	if (instance->debug_enabled)
		LOG_F(INFO, "Debug enabled");

	// Paused Text
	instance->paused_text = { "PAUSED", instance->fonts[PRESS_START_2P] };
	instance->paused_text.setColor(sf::Color::White);
	instance->paused_text.setPosition({ (instance->window->getSize().x - 
		instance->paused_text.getGlobalBounds().width) / 2, 50 });

	// Run
	instance->run();
}

vector<string> Game::load_text_file(const string path) {
	ifstream file(path);

	vector<string> lines;
	string current_line;
	while (getline(file, current_line))
		lines.push_back(current_line);

	return lines;
}

string Game::rand_title() {
	uniform_int_distribution<mt19937::result_type> random_number_gen(0, titles.size());
	return ROOT_TITLE + ": " + (titles.empty() ? "" : titles[ random_number_gen(rng) ]);
}

void Game::load_resources() {
	// Titles
	titles = load_text_file(TITLES_DATABASE_PATH);
	LOG_F(INFO, "Loaded titles:");
	for (string& title: titles)
		LOG_F(INFO, "%s", title.data());

	// Fonts
	LOG_F(INFO, "Loading fonts...");
	for (uint8_t i = 0; i < fonts.size(); ++i) {
		fonts[i] = sf::Font();
		if (!fonts[i].loadFromFile(FONT_PATH_BASE + "/" + FONTS[i]))
			exit(EXIT_FAILURE);
		LOG_F(INFO, "Font: %s", FONTS[i].data());
	}

	// Load textures
	LOG_F(INFO, "Loading textures...");
	for (uint8_t i = 0; i < textures.size(); ++i) {
		textures[i] = sf::Texture();
		if (!textures[i].loadFromFile(TEXTURE_PATH_BASE + "/" + TEXTURES[i]))
			exit(EXIT_FAILURE);
		LOG_F(INFO, "Texture: %s", TEXTURES[i].data());
	}

	// Load music files
	LOG_F(INFO, "Loading music files...");
	for (uint8_t i = 0; i < music.size(); ++i) {
		// sf::Music root;
		// if (!root.openFromFile(MUSIC_PATH_BASE + "/" + MUSIC[i]))
		// 	exit(EXIT_FAILURE);
		// music[i] = &root;
		// LOG_F(INFO, "Music: %s", MUSIC[i].data());
	}

	LOG_F(INFO, "Loading sound files...");
	for (uint8_t i = 0; i < sounds.size(); ++i) {
		// sf::SoundBuffer buffer;
		// if (!buffer.loadFromFile(SOUND_PATH_BASE + "/" + SOUNDS[i]))
		// 	exit(EXIT_FAILURE);
		// sf::Sound sound(buffer);
		// sounds[i] = &sound;
		// LOG_F(INFO, "Sound: %s", SOUNDS[i].data());
	}
}