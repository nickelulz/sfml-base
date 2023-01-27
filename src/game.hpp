#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cstdint>
#include <random> 
#include <chrono>
#include <string>

#include "config.hpp"

using namespace std;

class Game {
public:
	static Game* instance;
	static void initialize();

private:
	void update();
	void render();
	bool handle_events();
	void run();

private:
	vector<string> load_text_file(const string path);
	void load_resources();

	vector<string> titles;
	string rand_title();

	random_device device;
	mt19937 rng;

public:
	/*
	 * ASSETS
	 */
	array<unique_ptr<sf::Music>, NUM_MUSIC>  music;
	array<unique_ptr<sf::Sound>, NUM_SOUNDS> sounds;
	array<sf::Texture, NUM_TEXTURES>  	textures;
	array<sf::Font, NUM_FONTS> 			fonts;

	sf::VideoMode video_mode;
	sf::RenderWindow* window;
	bool debug_enabled, paused;

	sf::Text debug_text, paused_text;

	// FPS Timers
	chrono::high_resolution_clock::time_point frame_start, frame_end;
	float fps;
};

#endif
