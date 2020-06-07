#pragma once
#include <sfml/Graphics.hpp>
#include <thread>
#include <vector>
#include <array>
#include <functional>

namespace ge
{
#define ORIGIN vec2<int>{0,0}
#define VERSION "v.1.4.2"
#define GE ge

#pragma region PreDefs
#pragma endregion


#pragma region Vec2
	template<typename Type>
	struct vec2
	{
		Type x;
		Type y;

		/*
			Returns the sum vector.
			returns: vec2
			attrib: _vec2 vec2 
		*/
		vec2<Type> add(vec2 _vec2) 
		{
			return vec2{this->x + _vec2.x, this->y + _vec2.y};
		}

		vec2<Type> add(Type _factor)
		{
			return vec2{ this->x + _factor, this->y + _factor };
		}

		/*
			Returns the difference of vectors.
			returns: vec2
			attrib: _vec2 vec2
		*/
		vec2<Type> sub(vec2 _vec2)
		{
			return vec2{ this->x - _vec2.x, this->y - _vec2.y };
		}
		vec2<Type> sub(Type _factor)
		{
			return vec2{ this->x - _factor, this->y - _factor };
		}

		/*
			Returns the product of vectors.
			returns: vec2
			attrib: _vec2 vec2
		*/
		vec2<Type> mult(vec2 _vec2)
		{
			return vec2{ this->x * _vec2.x, this->y * _vec2.y };
		}
		vec2<Type> mult(Type _factor)
		{
			return vec2{ this->x * _factor, this->y * _factor };
		}

		/*
			Returns the quotient of vectors.
			returns: vec2
			attrib: _vec2 vec2
		*/
		vec2<Type> div(vec2 _vec2)
		{
			return vec2{ this->x / _vec2.x, this->y / _vec2.y };
		}
		vec2<Type> div(Type _factor)
		{
			return vec2{ this->x / _factor, this->y / _factor };
		}

		/*
			Compares Vectors.
			returns: bool
		*/
		bool equals(vec2 _vec2) 
		{
			return this->x == _vec2.x && this->y == _vec2.y;
		}

		/*
			Returns a copy of this vector.
			returns: vec2
		*/
		vec2<Type> copy() 
		{
			return vec2<Type>{this->x, this->y};
		}

		std::string to_string()
		{
			return std::to_string(this->x) + ", " + std::to_string(this->y);
		}

		vec2<int> to_int() 
		{
			return vec2<int>{int(this->x), int(this->y)};
		}

		vec2<float> to_float()
		{
			return vec2<float>{float(this->x), float(this->y)};
		}


		sf::Vector2f to_Vector2f() 
		{
			return sf::Vector2f(float(this->x), float(this->y));
		}

		sf::Vector2f to_Vector2i()
		{
			return sf::Vector2i(int(this->x), int(this->y));
		}

		static vec2<float> sfml_float_convert(sf::Vector2f _Vector2f)
		{
			return vec2<float>{_Vector2f.x, _Vector2f.y};
		}

		static vec2<int> sfml_int_convert(sf::Vector2i _Vector2i)
		{
			return vec2<int>{_Vector2i.x, _Vector2i.y};
		}
	};
#pragma endregion
#pragma region Rect
	template<typename Type>
	struct Rect
	{
		Type x;
		Type y;
		Type w;
		Type h;

		vec2<Type> getPos() { return vec2<Type>{x, y}; }
		vec2<Type> getSize() { return vec2<Type>{w, h}; }
	};
#pragma endregion
#pragma region ivec2 & fvec2 (Deprecated)
	//DEPRECATED
	struct ivec2
	{
		int x;
		int y;

		void add(ivec2 _vec)
		{
			this->x += _vec.x;
			this->y += _vec.y;
		}
	};

	//DEPRECATED
	struct fvec2
	{
		float x;
		float y;

		void add(fvec2 _vec)
		{
			this->x += _vec.x;
			this->y += _vec.y;
		}
	};
#pragma endregion
#pragma region Color
	class Color 
	{
	public:
		unsigned int r;
		unsigned int g;
		unsigned int b;
		unsigned int a;
	public:
		Color()
		{
			r = 0;
			g = 0;
			b = 0;
			a = 255;
		}
		Color(unsigned int _greyscale) 
		{
			if (_greyscale > 255)
				throw "Color value outside of range!";
			r = _greyscale;
			g = _greyscale;
			b = _greyscale;
			a = 255;
		}
		Color(unsigned int _r, unsigned int _g, unsigned int _b) 
		{
			if (_r > 255 || _g > 255 || _b > 255) 
				throw "Color value outside of range!";

			r = _r;
			g = _g;
			b = _b;
			a = 255;
		}
		Color(unsigned int _r, unsigned int _g, unsigned int _b, unsigned int _a)
		{
			if (_r > 255 || _g > 255 || _b > 255 || _a > 255)
				throw "Color value outside of range!";

			r = _r;
			g = _g;
			b = _b;
			a = _a;
		}
		sf::Color convertToSfmlColor() 
		{
			return sf::Color(r, g, b, a);
		}
		static Color convertFromSfmlColor(sf::Color _color)
		{
			return Color(_color.r, _color.g, _color.b, _color.a);
		}
	};
#pragma endregion
#pragma region HSLColor

	class HSLColor
	{
	public:
		HSLColor()
		{
			h = 0; s = 1.0; l = 0;
		}
		HSLColor(float _h)
		{
			if (_h < 0 || _h > 360)
				throw "Color Values out of range";
			h = _h; s = 1.0; l = 0.5;
		}
		HSLColor(float _h, float _s, float _l)
		{
			if (_s < 0 || _s > 1 || _l < 0 || _l > 1)
				throw "Color Values out of range";
			h = _h; s = _s; l = _l;
		}

	public:
		float h;
		float s;
		float l;
	};
#pragma endregion
#pragma region Timer
	class Timer 
	{
	public:
		Timer(unsigned int _time, bool _start = true)
		{
			ElapsedTime = 0;
			PauseTime = 0;
			Time = _time;
			TimerOn = _start;
		}

		//Returns a bool representing
		//if the timer has passed its 
		//alloted time. Evoking this
		//method will reset the timer.
		bool check() 
		{
			if(isCompleted())
			{
				reset();
				return true;
			}
			return false;
		}

		//Returns a bool representing
		//if the timer has passed its 
		//alloted time. Evoking this
		//method will not reset the timer.
		bool isCompleted() 
		{
			if (getTimeLeft() == 0 && TimerOn) 
			{
				return true;
			}
			return false;
		}

		unsigned int getElapsedTime() 
		{
			update();
			return ElapsedTime;
		}

		unsigned int getTimeLeft()
		{
			int timeLeft;

			timeLeft = Time - ElapsedTime;

			return  timeLeft > 0 ? timeLeft : 0;
		}

		void update() 
		{
			int timePassed = Clock.getElapsedTime().asMilliseconds() - ElapsedTime - PauseTime;

			if (TimerOn) ElapsedTime += timePassed;
			else PauseTime += timePassed;
		}

		void reset() 
		{
			ElapsedTime = 0;
			PauseTime = 0;
			Clock.restart();
		}

		bool stop() 
		{
			if(TimerOn)
			{
				TimerOn = false;
				return true;
			}

			return false;
		}

		bool start() 
		{
			if (!TimerOn) 
			{
				TimerOn = true;
				return true;
			}

			return false;
		}

		void setTime(unsigned int _newTime) 
		{
			Time = _newTime;
		}

	public:
		unsigned int Time;
		unsigned int ElapsedTime;
		unsigned int PauseTime;

		bool TimerOn;

		sf::Clock Clock;
	};
#pragma endregion
#pragma region Keyboard(KBD)
	class KBD 
	{
	public:
		enum Key
		{
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,ZERO,
			LEFT, RIGHT, UP, DOWN,
			F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,
			SPACE, LEFT_CONTROL, RIGHT_CONTROL, LEFT_ALT, RIGHT_ALT, LEFT_SHIFT, RIGHT_SHIFT, ESCAPE,
			TILDE,
		};
		
		bool isKeyClicked(Key _key) 
		{
			return downKeys[_key];
		}
		bool isKeyClicked(int _keyCode)
		{
			return downKeys[_keyCode];
		}

		bool isKeyHeld(Key _key) 
		{
			return heldKeys[_key];
		}
		bool isKeyHeld(int _keyCode)
		{
			return heldKeys[_keyCode];
		}

		void update() 
		{
			for (int k = 0; k < downKeys.size(); k++) 
			{
				heldKeys[k] = false;

				if (downKeys[k])
				{
					downKeys[k] = false;
					downKeyBlocks[k] = true;
				}

				switch (k)
				{
				case Key::A:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) heldKeys[k] = true;
					break;
				case Key::B:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) heldKeys[k] = true;
					break;
				case Key::C:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) heldKeys[k] = true;
					break;
				case Key::D:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) heldKeys[k] = true;
					break;
				case Key::E:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) heldKeys[k] = true;
					break;
				case Key::F:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) heldKeys[k] = true;
					break;
				case Key::G:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) heldKeys[k] = true;
					break;
				case Key::H:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) heldKeys[k] = true;
					break;
				case Key::I:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) heldKeys[k] = true;
					break;
				case Key::J:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) heldKeys[k] = true;
					break;
				case Key::K:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) heldKeys[k] = true;
					break;
				case Key::L:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) heldKeys[k] = true;
					break;
				case Key::M:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) heldKeys[k] = true;
					break;
				case Key::N:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) heldKeys[k] = true;
					break;
				case Key::O:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) heldKeys[k] = true;
					break;
				case Key::P:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) heldKeys[k] = true;
					break;
				case Key::Q:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) heldKeys[k] = true;
					break;
				case Key::R:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) heldKeys[k] = true;
					break;
				case Key::S:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) heldKeys[k] = true;
					break;
				case Key::T:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) heldKeys[k] = true;
					break;
				case Key::U:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) heldKeys[k] = true;
					break;
				case Key::V:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) heldKeys[k] = true;
					break;
				case Key::W:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) heldKeys[k] = true;
					break;
				case Key::X:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) heldKeys[k] = true;
					break;
				case Key::Y:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) heldKeys[k] = true;
					break;
				case Key::Z:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) heldKeys[k] = true;
					break;
				case Key::ONE:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) heldKeys[k] = true;
					break;
				case Key::TWO:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) heldKeys[k] = true;
					break;
				case Key::THREE:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) heldKeys[k] = true;
					break;
				case Key::FOUR:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) heldKeys[k] = true;
					break;
				case Key::FIVE:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) heldKeys[k] = true;
					break;
				case Key::SIX:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) heldKeys[k] = true;
					break;
				case Key::SEVEN:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) heldKeys[k] = true;
					break;
				case Key::EIGHT:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) heldKeys[k] = true;
					break;
				case Key::NINE:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) heldKeys[k] = true;
					break;
				case Key::ZERO:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) heldKeys[k] = true;
					break;
				case Key::LEFT:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) heldKeys[k] = true;
					break;
				case Key::RIGHT:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) heldKeys[k] = true;
					break;
				case Key::UP:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) heldKeys[k] = true;
					break;
				case Key::DOWN:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) heldKeys[k] = true;
					break;
				case Key::F1:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) heldKeys[k] = true;
					break;
				case Key::F2:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) heldKeys[k] = true;
					break;
				case Key::F3:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) heldKeys[k] = true;
					break;
				case Key::F4:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) heldKeys[k] = true;
					break;
				case Key::F5:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) heldKeys[k] = true;
					break;
				case Key::F6:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) heldKeys[k] = true;
					break;
				case Key::F7:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)) heldKeys[k] = true;
					break;
				case Key::F8:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)) heldKeys[k] = true;
					break;
				case Key::F9:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) heldKeys[k] = true;
					break;
				case Key::F10:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) heldKeys[k] = true;
					break;
				case Key::F11:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) heldKeys[k] = true;
					break;
				case Key::F12:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) heldKeys[k] = true;
					break;
				case Key::LEFT_CONTROL:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) heldKeys[k] = true;
					break;
				case Key::RIGHT_CONTROL:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) heldKeys[k] = true;
					break;
				case Key::LEFT_ALT:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) heldKeys[k] = true;
					break;
				case Key::RIGHT_ALT:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) heldKeys[k] = true;
					break;
				case Key::LEFT_SHIFT:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) heldKeys[k] = true;
					break;
				case Key::RIGHT_SHIFT:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) heldKeys[k] = true;
					break;
				case Key::ESCAPE:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) heldKeys[k] = true;
					break;
				case Key::TILDE:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde)) heldKeys[k] = true;
					break;
				case Key::SPACE:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) heldKeys[k] = true;
					break;
				default:
					break;
				}

				if(heldKeys[k])
				{
					if (!downKeyBlocks[k])
						downKeys[k] = true;
				}
				else downKeyBlocks[k] = false;
			}

		}

	private:

	private:
		std::array<bool, 100> downKeys;
		std::array<bool, 100> downKeyBlocks;
		std::array<bool, 100> heldKeys;

	};
#pragma endregion
#pragma region Textured2D
	class Textured2D 
	{
	public:
		Textured2D(vec2<float> _pos, vec2<float> _size, std::string _texturePath, vec2<int> _texCoords = vec2<int>{0,0})
		{
			Pos = _pos;
			Size = _size;

			TexCoords = _texCoords;
		
			TexturePath = _texturePath;
			Texture = sf::Texture();
			Texture.loadFromFile(TexturePath);
		}

		void Resize(vec2<float> _size) 
		{
			Size = _size;
		}

		sf::VertexArray getVertexArray() 
		{
			sf::VertexArray vArray = sf::VertexArray(sf::Quads, 4);

			vArray[0].position = sf::Vector2f(Pos.x, Pos.y);
			vArray[1].position = sf::Vector2f(Pos.x + Size.x, Pos.y);
			vArray[2].position = sf::Vector2f(Pos.x + Size.x, Pos.y + Size.y);
			vArray[3].position = sf::Vector2f(Pos.x, Pos.y + Size.y);

			vArray[0].texCoords = sf::Vector2f(TexCoords.x, TexCoords.y);
			vArray[1].texCoords = sf::Vector2f(TexCoords.x + Size.x, TexCoords.y);
			vArray[2].texCoords = sf::Vector2f(TexCoords.x + Size.x, TexCoords.y + Size.y);
			vArray[3].texCoords = sf::Vector2f(TexCoords.x, TexCoords.y + Size.y);

			return vArray;
		}

		void Move(vec2<float> _pos) 
		{
			Pos = _pos;
		}

		virtual void Update()
		{
		}

		virtual void Draw(sf::RenderWindow* window)
		{
			window->draw(getVertexArray(), &Texture);
		}

	public:
		vec2<float> Size;
		vec2<float> Pos;

		std::string TexturePath;
		sf::Texture Texture;
		vec2<int> TexCoords;
	};
#pragma endregion
#pragma region Basic2D
	class Basic2D
	{
	public:
		Basic2D() 
		{
			Pos = ORIGIN.to_float();
			Size = ORIGIN.to_float();

			Color = GE::Color();
		}
		//DEPRECATED
		Basic2D(vec2<float> _pos, vec2<float> _size, sf::Color _color)
		{
			Pos = _pos;
			Size = _size;

			Color = Color::convertFromSfmlColor(_color);
		}

		Basic2D(vec2<float> _pos, vec2<float> _size, Color _color)
		{
			Pos = _pos;
			Size = _size;

			Color = _color;
		}

		void Resize(vec2<float> _size) 
		{
			Size = _size;
		}

		void Move(vec2<float> _pos) 
		{
			Pos = _pos;
		}

		virtual void Update(){}

		virtual void Draw(sf::RenderWindow* window)
		{
			window->draw(getVertexArray());
		}

		sf::VertexArray getVertexArray() 
		{
			sf::VertexArray vertexArray;
			vertexArray.setPrimitiveType(sf::Quads);
			vertexArray.resize(4);

			vertexArray[0].position = sf::Vector2f(Pos.x,			Pos.y);
			vertexArray[1].position = sf::Vector2f(Pos.x + Size.x,	Pos.y);
			vertexArray[2].position = sf::Vector2f(Pos.x + Size.x,	Pos.y + Size.y);
			vertexArray[3].position = sf::Vector2f(Pos.x,			Pos.y + Size.y);

			vertexArray[0].color = Color.convertToSfmlColor();
			vertexArray[1].color = Color.convertToSfmlColor();
			vertexArray[2].color = Color.convertToSfmlColor();
			vertexArray[3].color = Color.convertToSfmlColor();

			return vertexArray;
		}

	public:
		vec2<float> Size;
		vec2<float> Pos;

		Color Color;
	};
#pragma endregion
#pragma region Button

	class Button 
	{	
	public:
		Button(Rect<float> _rect, Color _color)
		{
			ButtonObj = Basic2D(_rect.getPos(), _rect.getSize(), _color);
			ButtonRect = _rect;
			Color = _color;
		}
		Button(vec2<float> _pos, vec2<float> _size, Color _color) 
		{
			ButtonObj = Basic2D(_pos, _size, _color);
			ButtonRect = Rect<float>{ _pos.x, _pos.y, _size.x, _size.y};
			Color = _color;
		}

		bool isHovered(vec2<float> _pointerPos) 
		{
			if (_pointerPos.x >= ButtonRect.x && _pointerPos.x <= ButtonRect.x + ButtonRect.w)
				if (_pointerPos.y >= ButtonRect.y && _pointerPos.y <= ButtonRect.y + ButtonRect.h)
					return true;
			return false;
		}

		bool isClicked(vec2<float> _pointerPos, sf::Mouse::Button _button) 
		{
			if (isHovered(_pointerPos) && sf::Mouse::isButtonPressed(_button)) 
				return true;
			return false;
		}

		Rect<float> getRect() 
		{
			return ButtonRect;
		}

		void Draw(sf::RenderWindow* window)
		{
			ButtonObj.Draw(window);
		}

		//====== Move() =======
		void Move(float _x, float _y)
		{
			ButtonRect.x = _x;
			ButtonRect.y = _y;
			update();
		}
		void Move(vec2<float> _pos)
		{
			ButtonRect.x = _pos.x;
			ButtonRect.y = _pos.y;
			update();
		}
		//====== Size() =======
		void Resize(float _x, float _y)
		{
			ButtonRect.w = _x;
			ButtonRect.h = _y;
			update();
		}
		void Resize(vec2<float> _size) 
		{
			ButtonRect.w = _size.x;
			ButtonRect.h = _size.y;
			update();
		}

		//===== Recolor ======
		void Recolor(Color _color) 
		{
			Color = _color;
			update();
		}

	private:
		void update()
		{
			ButtonObj = Basic2D(ButtonRect.getPos(), ButtonRect.getSize(), Color);
		}
	private:
		Basic2D ButtonObj;
		Rect<float> ButtonRect;
		Color Color;
	public:
	};

#pragma endregion
#pragma region Engine
	class Engine 
	{
	public:
		Engine() 
		{
			WindowSize = vec2<float>{100,100};
			window = nullptr;

			BGColor = sf::Color::Black;

			evnt = sf::Event();

			FrameTime = 0;

			kbd = KBD();

			blockESCtoQuit = false;
		}

		void setBGColor(Color _color) 
		{
			BGColor = _color.convertToSfmlColor();
		}

		void Quit() 
		{
			window->close();
		}

		//DEPRECATED
		void setBGColor(sf::Color _color)
		{
			BGColor = _color;
		}

		void setBlockESCToQuit(bool _newValue) 
		{
			blockESCtoQuit = _newValue;
		}

		bool CreateWindow(ivec2 _size, bool _fullscreen = false, std::string _title = "Default")
		{
			WindowSize = vec2<float>{ float(_size.x), float(_size.y) };
			if (_fullscreen)
			{
				window = new sf::RenderWindow(sf::VideoMode(WindowSize.x, WindowSize.y), _title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen);
			}
			else
			{
				window = new sf::RenderWindow(sf::VideoMode(WindowSize.x, WindowSize.y), _title, sf::Style::Close | sf::Style::Titlebar);
			}

			return true;
		}

		bool CreateWindow(vec2<int> _size, bool _fullscreen = false, std::string _title = "Default")
		{
			WindowSize = _size.to_float();
			if (_fullscreen) 
			{
				window = new sf::RenderWindow(sf::VideoMode(WindowSize.x, WindowSize.y), _title, sf::Style::Close | sf::Style::Titlebar | sf::Style::Fullscreen);
			}
			else 
			{
				window = new sf::RenderWindow(sf::VideoMode(WindowSize.x, WindowSize.y), _title, sf::Style::Close | sf::Style::Titlebar);
			}

			return true;
		}

		void Start() 
		{
			std::thread t = std::thread(&Engine::GameLoop, this);

			t.join();
		}

		void GameLoop() 
		{
			Preload();
			Setup();

			while (window->isOpen())
			{
				FrameTime = FrameTimeClock.getElapsedTime().asSeconds();
				FrameTimeClock.restart();

				while (window->pollEvent(evnt)) {
					EventUpdate();
					switch (evnt.type)
					{
					case sf::Event::Closed:
						window->close();
						break;
					}
				}

				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && !blockESCtoQuit)
				{
					window->close();
				}

				kbd.update();

				Update();

				window->clear(BGColor);

				Draw(window);

				window->display();
			}
		}
		virtual void Preload() {}
		virtual void Setup() {}
		virtual void Draw(sf::RenderWindow* window) {}
		virtual void Update() {}
		virtual void EventUpdate() {}

	protected:
		vec2<float> WindowSize;
		sf::RenderWindow* window;

		sf::Color BGColor;

		sf::Event evnt;

		float FrameTime;
		sf::Clock FrameTimeClock;

		sf::Clock GameClock;

		KBD kbd;

		bool blockESCtoQuit;
	};
#pragma endregion

#pragma region Helper Functions

	float map(float value, float x1, float y1, float x2, float y2)
	{
		return (value - x1) / (y1 - x1) * (y2 - x2) + x2;
	}

	//***DEPRECATED***
	bool KeyIsDown(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}

	HSLColor RGBtoHSL(Color _color) 
	{
		float r = map(_color.r, 0,255, 0, 1);
		float g = map(_color.g, 0, 255, 0, 1);
		float b = map(_color.b, 0, 255, 0, 1);

		float Xmax = fmax(r, g);
		Xmax = fmax(Xmax, b);
		float V = Xmax;

		float Xmin = fmin(r, g);
		Xmin = fmin(Xmin, b);

		float C = Xmax - Xmin;

		//Lightness
		float l = (Xmax + Xmin) / 2;

		//Hue
		float h;
		bool x = false;
		if (C == 0) { h = 0; x = true; }
		if (V == r) { h = 60 * (0 + ((g - b) / C)); x = true; }
		if (V == g) { h = 60 * (2 + ((b - r) / C)); x = true; }
		if (V == b) { h = 60 * (4 + ((r - g) / C)); x = true; }
		if (Xmax = Xmin) { h = 0; }
		if (x == false) { h = 0; }

		//Saturation
		float s;
		if	 (V == 0) { s = 0; }
		else { s = C / (1 - fabs(2 * V - C - 1)); }
		if (s > 1)
			s = 1.0f;

		return HSLColor(h, s, l);
	}

	Color HSLtoRGB(HSLColor _color) 
	{
		float h = _color.h;
		float s = _color.s;
		float l = _color.l;

		float C = (1 - fabs(2 * l - 1)) * s;
		float h2 = h / 60.0;
		float X = C * (1 - fabs((fmod(h2, 2)) - 1));
		int h2i = ceil(h2);

		float r1, g1, b1;
		if (h2i == 1) { r1 = C; g1 = X; b1 = 0; }
		else if (h2i == 2) { r1 = X; g1 = C; b1 = 0; }
		else if (h2i == 3) { r1 = 0; g1 = C; b1 = X; }
		else if (h2i == 4) { r1 = 0; g1 = X; b1 = C; }
		else if (h2i == 5) { r1 = X; g1 = 0; b1 = C; }
		else if (h2i == 6) { r1 = C; g1 = 0; b1 = X; }
		else { r1 = 0; g1 = 0; b1 = 0; }

		float m = l - (C / 2);
		float r = int(map(r1 + m, 0, 1, 0, 255));
		float g = int(map(g1 + m, 0, 1, 0, 255));
		float b = int(map(b1 + m, 0, 1, 0, 255));
		return Color(r, g, b);
	}

#pragma endregion

}