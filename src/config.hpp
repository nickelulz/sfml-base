#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>

#include "game.hpp"

using namespace std;

/*
 * Configuration Variables
 */

constexpr uint64_t DEFAULT_WINDOW_WIDTH = 1200;
constexpr uint64_t DEFAULT_WINDOW_HEIGHT = 800;

const string ROOT_TITLE = "TSA Game";
const string TITLES_DATABASE_PATH = "./res/titles.txt";

const string GAME_ICON_PATH = "./res/icon.png";
const string PRESS_START_2P_PATH = "./res/fonts/PressStart2P-Regular.ttf";

/*
 * ASSETS
 */

// Textures
constexpr uint8_t NUM_TEXTURES = 1;
const string TEXTURE_PATH_BASE = "./res/textures";
const string TEXTURES[NUM_TEXTURES] = {
	"map.png"
};

enum TextureName {
	TEX_MAP
};

// Music
constexpr uint8_t NUM_MUSIC = 1;
const string MUSIC_PATH_BASE = "./res/audio/music";
const string MUSIC[NUM_MUSIC] = {
	"puzzle.mp3"
};

enum MusicName {
	MP3_PUZZLE
};

// Sounds
constexpr uint8_t NUM_SOUNDS = 0;
const string SOUND_PATH_BASE = "./res/audio/sounds";
const string SOUNDS[NUM_SOUNDS] = {

};

// Fonts
constexpr uint8_t NUM_FONTS = 1;
const string FONT_PATH_BASE = "./res/fonts";
const string FONTS[NUM_FONTS] = {
    "PressStart2P-Regular.ttf"
};

enum FontName {
    PRESS_START_2P
};

#endif