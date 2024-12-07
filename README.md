
# OpenGL Landscape Scene

This project is a graphical representation of a landscape created using OpenGL in C++. 
The program includes various elements like a school building, sun, clouds, trees, birds, and a river.

## Features

- **School Building:** A two-story building with windows, doors, and rooftops.
- **Sun:** A yellow circular sun positioned at the top-right corner.
- **Clouds:** White fluffy clouds made from overlapping circles.
- **Trees:** Realistic trees with trunks and leafy canopies.
- **Birds:** Flying birds with detailed body parts, including wings, tails, and beaks.
- **River:** A flowing river with ripples for a natural effect.
- **Flag:** A green flag with a red circle at its center, representing a country's flag.
- **Grass and Boundaries:** Ground elements to add realism.

## Prerequisites

- **GLUT Library:** Ensure you have the OpenGL Utility Toolkit (GLUT) installed on your system.
- **C++ Compiler:** Use a compiler that supports OpenGL (e.g., GCC).

## How to Compile and Run

1. Save the code to a file named `landscape.cpp`.
2. Open a terminal or command prompt.
3. Compile the code using the following command (adjust paths as needed):
   ```bash
   g++ landscape.cpp -o landscape -lGL -lGLU -lglut
   ```
4. Run the program:
   ```bash
   ./landscape
   ```

## Controls

- No interactive controls are implemented in this version. The scene is static and automatically rendered.

## File Structure

- **Main Functions:**
  - `drawText`: Displays text on the screen.
  - `drawCircle`: Draws a filled circle with a specified color and position.
  - `drawSun`: Creates the sun.
  - `drawCloud`: Creates fluffy clouds.
  - `drawTree`: Creates realistic trees.
  - `drawFlyingBird`: Draws flying birds with detailed parts.
  - `drawFlag`: Draws a flag with a stick.
  - `river`: Draws the flowing river with ripples.
  - `display`: Main rendering function for the entire scene.

## Preview
<img src="https://github.com/user-attachments/assets/c6e03e61-ceb2-4637-8515-68836a9464b5" alt="Door Control System" width="600px">




## License

This project is open-source and available for educational and non-commercial use.

---

