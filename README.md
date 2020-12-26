# GEngine
Basic engine based on the SFML library for C++. The goal is to eventually adapt it to run on vanilla OpenGL, and seperate it from SFML.<br />
Currently on only works with Windows applications, but there will be work in the future to allow for multi-platform support.

# How to Use:
GEngine was built to be simple to use! Its very easy to get a window open, and to the size you desire.<br /><br />
<b>Step 1: </b> Link both GEngine and [SFML](https://www.sfml-dev.org/) in your IDE's linking system.<br />

---

<b>Step 2:</b> Import the GEngine & and SFML Graphics Header file:<br />
```c++
#include <{SFML Location}/Graphics.hpp>
#include <GEngine.h>
```
or 
```c++
#include <{SFML Location}/Graphics.hpp>
#include "GEngine.h"
```
Depending on your linking.<br />

---

<b>Step 3:</b> Create a new Class that overrides GEngines `Engine` class and override these methods:
```c++
class Game : public Engine
{
  void Setup() override {}
  void Update() override {}
  void Draw(sf::RenderWindow* window) override {}
}
```
---

<b>Step 4:</b> Make an instance of your new class in the main method and run these commands:
```c++
int main()
{
  Game game;
  bool window = game.CreateWindow(vec2<int>{640, 480}, false, "Untitled Game");
  if(window) game.GameLoop();
  
  return 0;
}
```
---

Compile and run your app, and you should now have a window on your screen!
