#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <cassert>

#include "Menu.h"
#include "Button.h"
#include "utils.h"

// Constructor
Menu::Menu(sf::RenderWindow* window, Settings* settings)
{
	_settings = settings;
	_window = window;
	_isMenuInit = false;
	_isSubmenuInit = false;
	_wallpaper.setScale(static_cast<float>(_window->getSize().x), static_cast<float>(_window->getSize().y));
	_wallpaper.setScale(5.f, 5.f);
	addTexture(WALLPAPER_PATH);
	_wallpaper.setTexture(*_textures.back());
}

// Destructor
Menu::~Menu()
{
	for (Button* b : _buttons)
		delete b;

	_buttons.clear();
	_sprites.clear();
	_textures.clear();
	_texts.clear();
}

// Getters
float Menu::getCenterPositionX() const
{
	return (_window->getSize().x / 2.f);
}

float Menu::getCenterPositionY() const
{
	return (_window->getSize().y / 2.f);
}

// Setter
void Menu::setTextColor(int r, int g, int b, sf::Text& text)
{
	assert((r >= 0 && r <= 255) && (g >= 0 && g <= 255) && (b >= 0 && b <= 255));

	_textColor.r = r;
	_textColor.g = g;
	_textColor.b = b;

	text.setFillColor(_textColor);
}

void Menu::setAlignment(TextAlignment alignment)
{
	sf::FloatRect bounds = _texts.back().getLocalBounds();
	switch (alignment)
	{
	case AlignmentRight:
		_texts.back().setOrigin(bounds.left + bounds.width, bounds.top + bounds.height / 2.f);
		break;

	case AlignmentLeft:
		_texts.back().setOrigin(bounds.left, bounds.top + bounds.height / 2.f);
		break;

	case AlignmentCenter:
		_texts.back().setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
		break;

	default:
		break;
	}
}

// Event management
int Menu::isButtonPressed(const sf::Event& event)
{
	if (_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
		{
			if (_buttons[i]->isButtonPressed(event) != -1)
				return _buttons.at(i)->getAction();
		}

	return -1;
}

void Menu::isButtonHover(const sf::Event& event)
{
	if (_buttons.size() > 0)
		for (int i = 0; i < _buttons.size(); i++)
			_buttons[i]->isButtonHover(event);
}

int Menu::isAction()
{
	static sf::Cursor cursorArrow;
	if (!cursorArrow.loadFromSystem(sf::Cursor::Arrow))
		sendError(FileNotOpened);

	sf::Event event;
	while (_window->pollEvent(event))
	{
		int action;
		switch (event.type)
		{
		case sf::Event::Closed:
			return CloseOphidie;

		case sf::Event::KeyReleased:
			if (event.key.code == sf::Keyboard::Escape)
				return CloseOphidie;

		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			draw();
			action = isButtonPressed(event);
			_window->clear();
			if (action != -1)
				return action;

		case sf::Event::MouseMoved:
			_window->setMouseCursor(cursorArrow);
			isButtonHover(event);
			break;

		case sf::Event::Resized:
			_window->clear();
			_window->display();
			break;

		default:
			break;
		}
	}

	return -1;
}

// Music management
void Menu::playMusic(const std::string& soundFileName, float volume)
{
	if (!_musicBuffer.loadFromFile(MUSIC_DIR + soundFileName))
	{
		sendError(FileNotOpened);
		return;
	}

	_musicSound.setBuffer(_musicBuffer);
	_musicSound.setLoop(true);
	_musicSound.setVolume(volume);
	_musicSound.play();
}

void Menu::stopMusic()
{
	_musicSound.stop();
}

// Vectors management
void Menu::addButton(ButtonAction action, const std::string& text, ButtonStyle style, float scale, sf::Vector2f position)
{
	_buttons.push_back(new Button(_window, _settings, action, text, style, scale, position));
}

void Menu::addButton(ButtonAction action, const std::string& text, ButtonStyle style, float scale, sf::Vector2f position, bool* checked)
{
	_buttons.push_back(new Button(_window, _settings, action, text, style, scale, position, checked));
}

void Menu::addText(int fontSize, const std::string& text, sf::Vector2f position, TextAlignment alignment, int r, int g, int b)
{
	if (!_font.loadFromFile(FONT_PATH))
		sendError(FileNotOpened);

	_texts.push_back(sf::Text(text, _font, fontSize));

	_texts.back().setStyle(sf::Text::Regular);
	setTextColor(r, g, b, _texts.back());
	setAlignment(alignment);
	//_texts.back().setOrigin(_texts.back().getLocalBounds().width / 2.f, _texts.back().getLocalBounds().height / 2.f);
	_texts.back().setPosition(position);
	_texts.back().setLineSpacing(2.f);
}

void Menu::addTexture(const std::string& texture)
{
	_texture.loadFromFile(texture);
	_textures.push_back(new sf::Texture(_texture));
}

void Menu::addSprite(float scale, sf::Vector2f position, const std::string& texture)
{
	addTexture(texture);
	_sprites.push_back(new sf::Sprite(*_textures.back()));

	_sprites.back()->setScale(sf::Vector2f(scale, scale));
	_sprites.back()->setOrigin(_textures.back()->getSize().x / 2.f, _textures.back()->getSize().y / 2.f);
	_sprites.back()->setPosition(position);
}

void Menu::clearVectors()
{
	_buttons.clear();
	_sprites.clear();
	_texts.clear();
}

// Drawing management
void Menu::drawButtons()
{

	for (int i = 0; i < _buttons.size(); i++)
	{
		_buttons.at(i)->draw();
	}
}

void Menu::drawTexts()
{
	for (int i = 0; i < _texts.size(); i++)
	{
		drawText(_texts.at(i));
	}
}

void Menu::drawText(sf::Text text)
{
	_window->draw(text);
}

void Menu::drawSprites()
{
	for (int i = 0; i < _sprites.size(); i++)
	{
		drawSprite(_sprites.at(i));
	}
}

void Menu::drawSprite(sf::Sprite* sprite)
{
	_window->draw(*sprite);
}

void Menu::draw()
{
	_window->draw(_wallpaper);

	drawSprites();
	drawTexts();
	drawButtons();
}

// Menu initiation
void Menu::initHomeMenu()
{
	addButton(StartGame, "Play", BigButton, 0.5f, sf::Vector2f(getCenterPositionX(), 300.f));
	addButton(OpenHowToPlay, "How to play?", BigButton, 0.5f, sf::Vector2f(getCenterPositionX(), 450.f));
	addButton(OpenScoreboard, "Scoreboard", BigButton, 0.5f, sf::Vector2f(getCenterPositionX(), 600.f));
	addButton(OpenSettings, "Settings", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX() - 130.f, 750.f));
	addButton(CloseOphidie, "Quit", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX() + 130.f, 750.f));
	addText(12, "Credits: Jérémy Hébert, Vincent Gagnon, Félix-Antoine Lacroix & Nathan Bricault", sf::Vector2f(_window->getSize().y - 0.97 * _window->getSize().y, _window->getSize().y - 0.05 * _window->getSize().y), AlignmentLeft, 255, 255, 255);
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), 100.f), LOGO_PATH);
}

void Menu::initSettingsMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");
	addButton(CloseSubmenu, "Cancel Settings", LittleButton, 0.775f, sf::Vector2f(getCenterPositionX() + 200.f, 800.f));
	addButton(SaveSettings, "Save Settings", LittleButton, 0.775f, sf::Vector2f(getCenterPositionX() - 200.f, 800.f));

	addButton(DeafMode, "", CheckButton, 0.5f, sf::Vector2f(getCenterPositionX() + 200.f, getCenterPositionY() - 255.f), _settings->getDeafPointer());
	addButton(ArrowKey, "", CheckButton, 0.5f, sf::Vector2f(getCenterPositionX() + 200.f, getCenterPositionY() - 380.f), _settings->getArrowPointer());

	////addButton(SaveSettings, "Save Settings", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX() - 200.f, 800.f));
	//addButton(SaveSettings, "Save Settings", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX() - 200.f, 800.f));
	addText(20, "Arrow Keys", sf::Vector2f(getCenterPositionX() - 250.f, getCenterPositionY() - 380.f), AlignmentCenter, 255, 255, 255);
	addText(10, "This setting define if the game uses\n     the arrow keys or w,a,s,d", sf::Vector2f(getCenterPositionX() - 250.f, getCenterPositionY() - 360.f), AlignmentCenter, 255, 255, 255);
	addText(20, "Deaf Mode", sf::Vector2f(getCenterPositionX() - 250.f, getCenterPositionY() - 255.f), AlignmentCenter, 255, 255, 255);
	addText(10, "This setting turns off every sound", sf::Vector2f(getCenterPositionX() - 250.f, getCenterPositionY() - 235.f), AlignmentCenter, 255, 255, 255);
	addText(20, "Music", sf::Vector2f(getCenterPositionX() - 250.f, getCenterPositionY() - 130.f), AlignmentCenter, 255, 255, 255);
	addText(25, _settings->getDeaf() ? "MUTED" : std::to_string(static_cast<int>(_settings->getMusic())), sf::Vector2f(getCenterPositionX() + 200.f, getCenterPositionY() - 130.f), AlignmentCenter, 255, 255, 255);
	addText(20, "Sound", sf::Vector2f(getCenterPositionX() - 250.f, getCenterPositionY() - 5.f), AlignmentCenter, 255, 255, 255);
	addText(25, _settings->getDeaf() ? "MUTED" : std::to_string(static_cast<int>(_settings->getSound())), sf::Vector2f(getCenterPositionX() + 200.f, getCenterPositionY() - 5.f), AlignmentCenter, 255, 255, 255);
	addText(20, "Button's Sounds", sf::Vector2f(getCenterPositionX() - 250.f, getCenterPositionY() + 120.f), AlignmentCenter, 255, 255, 255);
	addText(25, _settings->getDeaf() ? "MUTED" : std::to_string(static_cast<int>(_settings->getMenu())), sf::Vector2f(getCenterPositionX() + 200.f, getCenterPositionY() + 120.f), AlignmentCenter, 255, 255, 255);

	if (!_settings->getDeaf())
		showVolumeButtons();
}

void Menu::initHowToPlayMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");
	addText(32, "How to play?", sf::Vector2f(getCenterPositionX(), _sprites.front()->getOrigin().y - _sprites.front()->getGlobalBounds().height / 2.f + 100.f), AlignmentCenter, 255, 255, 255);
	addButton(CloseSubmenu, "", NoButton, 0.5f, sf::Vector2f(getCenterPositionX(), _sprites.front()->getOrigin().y + _sprites.front()->getGlobalBounds().height / 2.f - 150.f));
	addText(20, "Control your snake using the arrow keys\nor WASD depending on your settings.\nYour goal is to eat as many eggs as possible,\nas each one makes your snake grow longer\nand increases your score.\n\nAvoid hitting the walls or your own body,\nas either will end the game instantly.\nThe longer your snake gets, the harder\nit is to maneuver, so plan your moves ahead.\n\nHigher difficulties increase the snake's\nspeed and introduce traps on the grid.\nTwo game modes also adds a hunger bar.\nLet it empty and it is game over!\nYour scores are saved to the scoreboard\nfor each game mode.", sf::Vector2f(getCenterPositionX(), getCenterPositionY() - 175.f), AlignmentCenter, 255, 255, 255);

	//TODO: Build it
}

void Menu::initStartMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");
	addButton(CloseSubmenu, "", YesButton, 0.5f, sf::Vector2f(getCenterPositionX(), 500.f));

	//TODO: Build it
}

void Menu::initScoreboardMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");
	addButton(CloseSubmenu, "", NoButton, 0.5f, sf::Vector2f(getCenterPositionX(), getCenterPositionY() * 2 - 150.f));
	addButton(GoToNext, "Next", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX() + 250, getCenterPositionY() * 2 - 150.f));
	addButton(GoToPrevious, "Previous", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX() - 250, getCenterPositionY() * 2 - 150.f));

	addButton(GoToNormalSCR, "Normal", LittleButton, 0.45f, sf::Vector2f(getCenterPositionX() - 330, 120.f));
	addButton(GoToSurvivalSCR, "Survival", LittleButton, 0.45f, sf::Vector2f(getCenterPositionX() - 111, 120.f));
	addButton(GoToDeathTrapSCR, "DeathTrap", LittleButton, 0.45f, sf::Vector2f(getCenterPositionX() + 111, 120.f));
	addButton(GoToSurviveHellSCR, "Hell", LittleButton, 0.45f, sf::Vector2f(getCenterPositionX() + 330, 120.f));

	addText(32, _currentDifficulty, sf::Vector2f(getCenterPositionX(), 230.f), AlignmentCenter, 255, 255, 255);

	for (int i = 0; i < NUMBER_OF_SCORES; i++)
		addText(32, _currentScores[i], sf::Vector2f(getCenterPositionX(), 280.f + (42.0f * i)), AlignmentCenter, 255, 255, 255);
}

void Menu::initPauseMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");
	addButton(QuitGame, "Quit", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX(), 250.f));
	addButton(Resume, "Resume", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX(), 500.f));
	addButton(OpenSettings, "Settings", LittleButton, 0.5f, sf::Vector2f(getCenterPositionX(), 750.f));
	addText(32, "Pause", sf::Vector2f(getCenterPositionX(), _sprites.front()->getOrigin().y - _sprites.front()->getGlobalBounds().height / 2.f + 150.f), AlignmentCenter, 255, 255, 255);
}

void Menu::initGameOverMenu()
{
	addSprite(1.f, sf::Vector2f(getCenterPositionX(), getCenterPositionY()), "assets/menu/menuBackground.png");
	addText(64, "Game Over", sf::Vector2f(getCenterPositionX(), getCenterPositionY() - 350.f), AlignmentCenter, 255, 255, 255);
	addButton(OpenHomeMenu, "Go back to home menu", BigButton, 0.5f, sf::Vector2f(getCenterPositionX(), getCenterPositionY() - 150.f));
	addButton(StartGameNow, "Restart a game now", BigButton, 0.5f, sf::Vector2f(getCenterPositionX(), getCenterPositionY() + 150.f));
}

// Menu loading
bool Menu::loadHomeMenu()
{
	_isMenuInit = false;
	_isSubmenuInit = false;
	playMusic("menuMusic.wav", _settings->getMusic());

	while (true)
	{
		if (_isMenuInit == false)
		{
			initHomeMenu();
			_isMenuInit = true;
		}

		_window->clear();
		draw();
		_window->display();

		switch (isAction())
		{
		case StartGame:
			clearVectors();

			if (_isSubmenuInit == false)
			{
				initStartMenu();
				_isSubmenuInit = true;
			}

			while (loadStartMenu())
				;
			_isSubmenuInit = false;
			clearVectors();

			stopMusic();
		case StartGameNow:
			return true;

		case CloseOphidie:
			stopMusic();
			return false;

		case OpenHowToPlay:
			clearVectors();

			if (_isSubmenuInit == false)
			{
				initHowToPlayMenu();
				_isSubmenuInit = true;
			}

			_isMenuInit = false;

			while (loadHowToPlayMenu())
				;

			_isSubmenuInit = false;
			clearVectors();
			break;

		case OpenScoreboard:
			clearVectors();

			if (_isSubmenuInit == false)
			{
				initScoreboardMenu();
				_isSubmenuInit = true;
			}

			_isMenuInit = false;

			while (loadScoreboardMenu())
				;

			_isSubmenuInit = false;
			clearVectors();
			break;

		case OpenSettings:
			clearVectors();

			if (_isSubmenuInit == false)
			{
				initSettingsMenu();
				_isSubmenuInit = true;
			}

			_isMenuInit = false;

			while (loadSettingsMenu())
				;

			_isSubmenuInit = false;
			clearVectors();
			break;

		default:
		case -1:
			break;
		}
	}
}

bool Menu::loadSettingsMenu()
{
	_window->clear();
	draw();
	_window->display();

	switch (isAction())
	{
	case CloseSubmenu:
		_settings->readFile();
		_musicSound.setVolume(_settings->getMusic());
		return false;

	case SaveSettings:
		_settings->saveSettings();
		return false;

	case ArrowKey:
		_settings->setArrow(_settings->getArrow() ? false : true);
		break;

	case DeafMode:
		_settings->setDeaf(_settings->getDeaf() ? false : true);

		_musicSound.setVolume(_settings->getMusic());
		if (_settings->getDeaf())
			hideVolumeButtons();
		else
			showVolumeButtons();

		break;
	case IncreaseMusic:
		if (_settings->getMusic() != 100.f)
			_settings->setMusic(_settings->getMusic() + 1.f > 100.f ? 100.f : _settings->getMusic() + 1.f);
		break;

	case BigIncreaseMusic:
		if (_settings->getMusic() != 100.f)
			_settings->setMusic(_settings->getMusic() + 10.f > 100.f ? 100.f : _settings->getMusic() + 10.f);
		break;

	case DecreaseMusic:
		if (_settings->getMusic() != 0.0f)
			_settings->setMusic(_settings->getMusic() - 1.f < 0.0f ? 0.0f : _settings->getMusic() - 1.f);
		break;

	case BigDecreaseMusic:
		if (_settings->getMusic() != 0.0f)
			_settings->setMusic(_settings->getMusic() - 10.f < 0.0f ? 0.0f : _settings->getMusic() - 10.f);
		break;
	
	case IncreaseSound:
		if (_settings->getSound() != 100.f)
			_settings->setSound(_settings->getSound() + 1.f > 100.f ? 100.f : _settings->getSound() + 1.f);
		break;

	case BigIncreaseSound:
		if (_settings->getSound() != 100.f)
			_settings->setSound(_settings->getSound() + 10.f > 100.f ? 100.f : _settings->getSound() + 10.f);
		break;

	case DecreaseSound:
		if (_settings->getSound() != 0.0f)
			_settings->setSound(_settings->getSound() - 1.f < 0.0f ? 0.0f : _settings->getSound() - 1.f);
		break;

	case BigDecreaseSound:
		if (_settings->getSound() != 0.0f)
			_settings->setSound(_settings->getSound() - 10.f < 0.0f ? 0.0f : _settings->getSound() - 10.f);

		break;

	case IncreaseMenu:
		if (_settings->getMenu() != 100.f)
			_settings->setMenuVolume(_settings->getMenu() + 1.f > 100.f ? 100.f : _settings->getMenu() + 1.f);

		break;

	case BigIncreaseMenu:
		if (_settings->getMenu() != 100.f)
			_settings->setMenuVolume(_settings->getMenu() + 10.f > 100.f ? 100.f : _settings->getMenu() + 10.f);

		break;

	case DecreaseMenu:
		if (_settings->getMenu() != 0.0f)
			_settings->setMenuVolume(_settings->getMenu() - 1.f < 0.0f ? 0.0f : _settings->getMenu() - 1.f);

		break;

	case BigDecreaseMenu:
		if (_settings->getMenu() != 0.0f)
			_settings->setMenuVolume(_settings->getMenu() - 10.f < 0.0f ? 0.0f : _settings->getMenu() - 10.f);

		break;

	default:
		return true;

	}

	_texts.at(5).setString(_settings->getDeaf() ? "MUTED" : std::to_string(static_cast<int>(_settings->getMusic())) == "100" ? "MAX" : std::to_string(static_cast<int>(_settings->getMusic())) == "0"     ? "MIN" : std::to_string(static_cast<int>(_settings->getMusic())));
	_texts.at(7).setString(_settings->getDeaf() ? "MUTED" : std::to_string(static_cast<int>(_settings->getSound())) == "100" ? "MAX" : std::to_string(static_cast<int>(_settings->getSound())) == "0" ? "MIN" : std::to_string(static_cast<int>(_settings->getSound())));
	_texts.at(9).setString(_settings->getDeaf() ? "MUTED" : std::to_string(static_cast<int>(_settings->getMenu())) == "100" ? "MAX" : std::to_string(static_cast<int>(_settings->getMenu())) == "0"     ? "MIN" : std::to_string(static_cast<int>(_settings->getMenu())));
	
	return true;
}

void Menu::showVolumeButtons()
{
	addButton(IncreaseMusic, ">", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 300.f, getCenterPositionY() - 130.f));
	addButton(BigIncreaseMusic, ">>", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 400.f, getCenterPositionY() - 130.f));
	addButton(DecreaseMusic, "<", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 100.f, getCenterPositionY() - 130.f));
	addButton(BigDecreaseMusic, "<<", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 0.0f, getCenterPositionY() - 130.f));

	addButton(IncreaseSound, ">", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 300.f, getCenterPositionY() - 5.f));
	addButton(BigIncreaseSound, ">>", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 400.f, getCenterPositionY() - 5.f));
	addButton(DecreaseSound, "<", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 100.f, getCenterPositionY() - 5.f));
	addButton(BigDecreaseSound, "<<", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 0.0f, getCenterPositionY() - 5.f));

	addButton(IncreaseMenu, ">", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 300.f, getCenterPositionY() + 120.f));
	addButton(BigIncreaseMenu, ">>", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 400.f, getCenterPositionY() + 120.f));
	addButton(DecreaseMenu, "<", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 100.f, getCenterPositionY() + 120.f));
	addButton(BigDecreaseMenu, "<<", YesButton, 0.5f, sf::Vector2f(getCenterPositionX() + 0.0f, getCenterPositionY() + 120.f));
}

void Menu::hideVolumeButtons()
{
	for (int i = 0; i < 12; i++)
		_buttons.erase(_buttons.end() - 1);
}

bool Menu::loadHowToPlayMenu()
{
	_window->clear();
	draw();
	_window->display();

	switch (isAction())
	{
	case CloseSubmenu:
		return false;
	default:
		return true;
	}

	// TODO: Build it
}

bool Menu::loadStartMenu()
{
	_window->clear();
	draw();
	_window->display();

	switch (isAction())
	{
	case CloseSubmenu:
		return false;
	default:
		return true;
	}

	// TODO: Build it
}

bool Menu::loadScoreboardMenu()
{
	Scoreboard scoreboard;
	scoreboard.loadData();
	while (true)
	{
		_window->clear();
		draw();
		_window->display();

		switch (isAction())
		{
		case CloseSubmenu:
			return false;
		case GoToNext:
			_scoreboardMenuNavigation.x++;
			if (_scoreboardMenuNavigation.x > Hardcore)
				_scoreboardMenuNavigation.x = Baby;
			break;

		case GoToPrevious:
			_scoreboardMenuNavigation.x--;
			if (_scoreboardMenuNavigation.x < Baby)
				_scoreboardMenuNavigation.x = Hardcore;
			break;

		case GoToNormalSCR:
			_scoreboardMenuNavigation.y = Normal;
			break;

		case GoToSurvivalSCR:
			_scoreboardMenuNavigation.y = Survival;
			break;

		case GoToDeathTrapSCR:
			_scoreboardMenuNavigation.y = DeathTrap;
			break;

		case GoToSurviveHellSCR:
			_scoreboardMenuNavigation.y = SurviveHell;
			break;

		default:
			return true;
		}

		_currentDifficulty = DIFFICULTY_PATH[_scoreboardMenuNavigation.x];
		for (int i = 0; i < NUMBER_OF_SCORES; i++)
			_currentScores[i] = scoreboard.getScoreAt(_scoreboardMenuNavigation.y, _scoreboardMenuNavigation.x, i);
		clearVectors();
		initScoreboardMenu();
	}
}

bool Menu::loadPauseMenu()
{
	_window->clear();
	draw();
	_window->display();

	while (true)
	{
		switch (isAction())
		{
		case QuitGame:
			return true;

		case Resume:
			return false;

		case OpenSettings:
			clearVectors();

			if (_isSubmenuInit == false)
			{
				initSettingsMenu();
				_isSubmenuInit = true;
			}

			while (loadSettingsMenu())
				;

			_isSubmenuInit = false;
			clearVectors();
			break;
		default:
			break;
		}
	}
}

bool Menu::loadGameOverMenu()
{
	_window->clear();
	clearVectors();
	initGameOverMenu();
	draw();
	_window->display();

	while (true)
		switch (isAction())
		{
		case StartGameNow:
			return true;

		case OpenHomeMenu:
			return false;

		default:
			break;
		}
}
