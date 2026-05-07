#pragma once

const std::string BUTTON_SOUND_PATH = "assets/soundEffects/"; //TODO: Déplacer dans const
const std::string FONT_PATH = "assets/fonts/PressStart2P.ttf"; //TODO: Déplacer dans const
const std::string BUTTON_TEXTURE_PATH = "assets/buttons/"; //TODO: Déplacer dans const
const int FONT_SIZE = 20; //TODO: Déplacer dans const
const int BUTTON_VOLUME = 25; //DELETE: Retirer post-merge

enum ButtonStyle
{
	bigButton,
	mediumButton,
	littleButton,
	yesButton,
	noButton,

	nbStyle // Number of style
};

enum ButtonAction
{
	startGame,
	closeOphidie,
	openSettings,
	openHTP,
	openScoreboard,
	goToNormalSCR,
	goToSurvivalSCR,
	goToDeathTrapSCR,
	goToSurviveHellSCR,

	nbAction // Number of action
};

class Button
{
private:
	// Button declarations
	int _action;
	bool _buttonPressed;

	// Interface declarations
	sf::Sprite _button;
	sf::Texture _texture, _pressedTexture;
	sf::Vector2f _scale, _position;

	// Text declarations
	sf::Text _text;
	sf::Font _font;
	sf::Color _textColor;
	void calculateTextPosition();

	// Sound declarations
	sf::SoundBuffer _soundEffectBuffer;
	sf::Sound _soundEffect;

public:
	// Constructors
	Button();
	Button(const int action, const std::string text, const int buttonStyle, const float scale, const sf::Vector2f position);

	// Destructor
	~Button();

	// Getter
	int getAction() const;

	// Setters
	void setTextColor(int r, int g, int b);
	void setButtonTexture(const int buttonStyle);

	// Event management
	void updateButton(sf::RenderWindow& window);
	void playButtonSound(sf::SoundBuffer& soundEffectBuffer, sf::Sound& soundEffect, std::string soundPath);
	int isButtonPressed(sf::Event event, sf::RenderWindow& window);
	void isButtonHover(sf::Event event, sf::RenderWindow& window);

	// Drawing management
	void draw(sf::RenderWindow& window);
};