## 🧮 Custom Scientific Calculator

A feature-rich calculator with support for:

- Constants (π, e, g)
- Trig functions (sin, asin, sinh, etc.)
- Implicit multiplication
- Power/root logic (`^0.5`, `^(1/3)`)
- Error handling (syntax + math errors)

### ⚠️ Notes
- Not 100% bug-free — edge cases may cause unexpected results.
- Works as expected with correct mathematical input (e.g., using parentheses).
- Built with C++ and Raylib.

### 🚀 Why I Built This
A personal challenge to explore parsing, evaluation, and GUI design.


### Important
- 1 Needs a compiler with C++17 support 
- 2 Needs CMake to build the project
- 3 If you are using MSVS delete from line 41 to 53
- 4 needs Raylib installed on the system or in lib/ folder of the CMakwLists.txt




### How to build on Window(Using CMake)
- 1 Open CMD in the project directory
- 2 mkdir build
- 3 cmake .. -G "Ninja" (or your Perfereded generator)
- 4 "Ninja" (or tyoe your Perfereded generator name)
- 5 go to the bin folder and open Calculator.exe






