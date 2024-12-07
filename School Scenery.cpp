#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <string>




// Variables for cloud positions
float cloud1X = 0.0f;
float cloud2X = -200.0f;
float cloud3X = -400.0f;
float cloud4X = -600.0f;

// Time delays for each cloud
int delay1 = 0;
int delay2 = 0;
int delay3 = 0;
int delay4 = 0;



void init() {
    glClearColor(0.1f, 0.5f, 1.0f, 1.0f); //background color
    gluOrtho2D(-900, 500, -500, 500);      // Set coordinate system
}



void drawText(const char* text, float x, float y, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text);
        text++;
    }
}

void drawBanner() {
    // Banner background
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.0f, 0.0f); // Red color for banner
    glVertex2f(-300, 150);
    glVertex2f(-20, 150);
    glVertex2f(-20, 200);
    glVertex2f(-300, 200);
    glEnd();

    // Text on the banner
    drawText("KYS High School", -240, 160, 1.0f, 1.0f, 1.0f); // White text
}


void drawCircle(float x, float y, float radius, float r, float g, float b) {
    int numSegments = 100;
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments;
        float dx = radius * cosf(angle);
        float dy = radius * sinf(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

void drawSun() {
    drawCircle(-250, 360, 60, 1.0f, 1.0f, 0.0f); // Yellow sun at top-right corner
}

// Draw clouds
void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 30, 1.0f, 1.0f, 1.0f);  // White color
    drawCircle(x + 25, y, 30, 1.0f, 1.0f, 1.0f);  // White color
    drawCircle(x + 12.5, y + 15, 35, 1.0f, 1.0f, 1.0f);  // White color

}

// Update clouds' position
void updateCloud(int value) {
    // Move each cloud separately with a delay
    if (value >= delay1) cloud1X += 1.0f;
    if (value >= delay2) cloud2X += 1.0f;
    if (value >= delay3) cloud3X += 1.0f;
    if (value >= delay4) cloud4X += 1.0f;

    // Reset clouds when they move off screen
    if (cloud1X > 800.0f) cloud1X = -250.0f;
    if (cloud2X > 800.0f) cloud2X = -400.0f;
    if (cloud3X > 800.0f) cloud3X = -600.0f;
    if (cloud4X > 800.0f) cloud4X = -800.0f;

    // Redraw and call the update again
    glutPostRedisplay();
    glutTimerFunc(16, updateCloud, value + 16); // Increment time
}


// Function to draw a big tree at the specified location
void drawTree(float x, float y) {
    // Draw tree trunk
    glColor3f(0.5f, 0.35f, 0.05f); // Brown color for trunk
    glBegin(GL_POLYGON);
    glVertex2f(x - 22, y);
    glVertex2f(x + 22, y);
    glVertex2f(x + 22, y + 170);
    glVertex2f(x - 22, y + 170);
    glEnd();

    // leaves overlapping green circles
    drawCircle(x, y + 190, 40, 0.0f, 0.6f, 0.0f); //for me(just understand the correct place)
    drawCircle(x - 30, y + 170, 40, 0.0f, 0.6f, 0.0f);
    drawCircle(x + 30, y + 170, 40, 0.0f, 0.6f, 0.0f);
    drawCircle(x - 20, y + 210, 40, 0.0f, 0.6f, 0.0f);
    drawCircle(x + 20, y + 210, 40, 0.0f, 0.6f, 0.0f);
}

// Variables for bird position and speed
float bird1X = -400.0f;// Starting position of the bird
float bird2X = -450.0f;// Starting position of the bird
float bird3X = -450.0f;// Starting position of the bird
float birdSpeed = 2.0f;  // Speed at which the bird moves

// Function to update bird's position
void updateBirdPosition(int value) {
    // Move the bird to the right
    bird1X += birdSpeed;
    bird2X += birdSpeed;
    bird3X += birdSpeed;

    // Reset bird's position when it goes off the screen
    if (bird1X > 800.0f) bird1X = -900.0f;
    if (bird2X > 800.0f) bird2X = -900.0f;
    if (bird3X > 800.0f) bird3X = -900.0f;

    // Redraw the scene
    glutPostRedisplay();

    // Call the update function every 16ms (60 FPS)
    glutTimerFunc(16, updateBirdPosition, value + 1);
}



void drawFlyingBird(float x, float y, float size) {
    // Body of the bird
    glColor3f(0.3f, 0.3f, 0.3f);  // Dark grey color for the body
    glBegin(GL_POLYGON);
    glVertex2f(x, y);                  // Left side of body
    glVertex2f(x + size * 0.5f, y);    // Right side of body
    glVertex2f(x + size * 0.5f, y - size * 0.2f); // Bottom right
    glVertex2f(x, y - size * 0.2f);    // Bottom left
    glEnd();

    // Head of the bird
    glColor3f(0.3f, 0.3f, 0.3f);  // Same color as the body
    glBegin(GL_POLYGON);
    glVertex2f(x + size * 0.45f, y + size * 0.1f); // Top right of head
    glVertex2f(x + size * 0.6f, y);                // Beak position
    glVertex2f(x + size * 0.45f, y - size * 0.1f); // Bottom right of head
    glEnd();

    // Beak of the bird
    glColor3f(1.0f, 0.5f, 0.0f);  // Orange color for beak
    glBegin(GL_TRIANGLES);
    glVertex2f(x + size * 0.5f, y); // Start of beak
    glVertex2f(x + size * 0.6f, y + size * 0.05f); // Beak tip top
    glVertex2f(x + size * 0.6f, y - size * 0.05f); // Beak tip bottom
    glEnd();

    // Left Wing (upwards for flying effect)
    glColor3f(0.2f, 0.2f, 0.2f);  // Darker color for wings
    glBegin(GL_TRIANGLES);
    glVertex2f(x + size * 0.1f, y);                   // Attachment to body
    glVertex2f(x - size * 0.4f, y + size * 0.8f);     // Left wing tip (upward)
    glVertex2f(x, y);                                 // Near body tip
    glEnd();

    // Right Wing (upwards for flying effect)
    glColor3f(0.2f, 0.2f, 0.2f);  // Darker color for wings
    glBegin(GL_TRIANGLES);
    glVertex2f(x + size * 0.1f, y);                    // Attachment to body
    glVertex2f(x + size * 0.6f, y + size * 0.8f);      // Right wing tip (upward)
    glVertex2f(x + size * 0.4f, y);                    // Near body tip
    glEnd();

    // Tail of the bird
    glColor3f(0.2f, 0.2f, 0.2f);  // Darker color for tail
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y - size * 0.1f);        // Bottom of body
    glVertex2f(x - size * 0.3f, y - size * 0.3f); // Bottom tip of tail
    glVertex2f(x - size * 0.1f, y - size * 0.1f); // Top of tail
    glEnd();
}


void drawFlag(float x, float y) {
    // Adjusted stick dimensions
    float stickWidth = 15; // Increased width
    float stickHeight = 450; // Increased height

    // Adjusted flag dimensions
    float flagWidth = 150; // Increased width
    float flagHeight = 90; // Increased height

    // Draw the flag stick
    glColor3f(0.6f, 0.3f, 0.0f); // Brown color for the stick
    glBegin(GL_POLYGON);
    glVertex2f(x, y);
    glVertex2f(x + stickWidth, y);
    glVertex2f(x + stickWidth, y + stickHeight);
    glVertex2f(x, y + stickHeight);
    glEnd();

    // Draw the flag
    glColor3f(0.0f, 0.5f, 0.0f); // Green color for the flag
    glBegin(GL_POLYGON);
    glVertex2f(x + stickWidth, y + stickHeight);
    glVertex2f(x + stickWidth + flagWidth, y + stickHeight);
    glVertex2f(x + stickWidth + flagWidth, y + stickHeight - flagHeight);
    glVertex2f(x + stickWidth, y + stickHeight - flagHeight);
    glEnd();

    // Add a circle in the flag (optional, for decoration)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    float cx = x + stickWidth + flagWidth / 2; // Center of the flag
    float cy = y + stickHeight - flagHeight / 2; // Center of the flag
    float r = 0.2f * flagHeight; // Circle radius proportional to flag height
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 100; i++) {
        float angle = 2 * M_PI * i / 100;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

void drawSmallTree(float x, float y) {
    // Draw tree trunk with longer height
    glColor3f(0.55f, 0.27f, 0.07f); // Brown color for trunk
    glBegin(GL_POLYGON);
    glVertex2f(x - 5, y);          // Bottom-left of the trunk
    glVertex2f(x + 5, y);          // Bottom-right of the trunk
    glVertex2f(x + 5, y + 40);     // Top-right of the trunk (longer trunk)
    glVertex2f(x - 5, y + 40);     // Top-left of the trunk
    glEnd();

    // Draw tree leaves as overlapping circles
    drawCircle(x, y + 50, 15, 0.0f, 0.6f, 0.0f);   // Bottom circle of leaves
    drawCircle(x - 10, y + 60, 15, 0.0f, 0.6f, 0.0f); // Left circle of leaves
    drawCircle(x + 10, y + 60, 15, 0.0f, 0.6f, 0.0f); // Right circle of leaves
    drawCircle(x, y + 70, 15, 0.0f, 0.6f, 0.0f);   // Top circle of leaves
}




void river() {

    drawSmallTree(-550, 65);
    drawSmallTree(-650, 45);
    drawSmallTree(-750, 25);

    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.4f, 0.8f);
    glVertex2f(-350, 30);
    glVertex2f(-900, -450);
    glVertex2f(-900, -50);
    glVertex2f(-350, 100);
    glEnd();




    // Ripples
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.6f, 1.0f);

    // Ripple 1
    glVertex2f(-400, 90);
    glVertex2f(-420, 30);

    // Ripple 2
    glVertex2f(-420, 70);
    glVertex2f(-435, 30);

    //Ripple 3
    glVertex2f(-490, 50);
    glVertex2f(-510, 5);

    //Ripple 3
    glVertex2f(-510, 50);
    glVertex2f(-530, 5);

    glEnd();

    //river grass
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(-900, 0);
    glVertex2f(-900, -50);
    glVertex2f(-350, 100);
    glVertex2f(-350, 115);
    glEnd();



}





void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    river();

    drawSun();

    drawCloud(cloud1X, 450);
    drawCloud(cloud2X, 400);
    drawCloud(cloud3X, 350);
    drawCloud(cloud4X, 300);

    // BIRD
    drawFlyingBird(bird1X, 400, 55);
    drawFlyingBird(bird2X, 420, 55);
    drawFlyingBird(bird3X, 380, 55);






    //Grass
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.8f, 0.2f);
    glVertex2d(-200, 0);
    glVertex2d(-350, 0);
    glVertex2d(-900, -450);
    glVertex2d(-900, -500);
    glVertex2d(500, -500);
    glVertex2d(500, -150);
    glVertex2d(250, -150);
    glVertex2d(0, 0);
    glVertex2d(-130, 0);
    glEnd();


    //boundary line
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-350, 0);
    glVertex2f(-350, 30);
    glVertex2f(-900, -200);
    glVertex2f(-900, -450);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(-350, 30);
    glVertex2f(-900, -200);
    glVertex2f(-900, -210);
    glVertex2f(-350, 20);
    glEnd();




    //end line

    //school building roof
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.7f, 1.0f); //rooftop color
    glVertex2d(500, 150);
    glVertex2d(500, 300);
    glVertex2d(0, 300);
    glVertex2d(250, 150);
    glEnd();
    //floor wall-1 up
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.25f, 0.0f);
    glVertex2d(0, 300);
    glVertex2d(0, 150);
    glVertex2d(250, 0);
    glVertex2d(250, 150);
    glEnd();
    //wall-2 up
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.25f, 0.0f);
    glVertex2d(250, 150);
    glVertex2d(250, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 150);
    glEnd();
    //devider
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2d(0, 160);
    glVertex2d(0, 150);
    glVertex2d(250, 0);
    glVertex2d(250, 10);
    glEnd();
    //devider -2
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2d(250, 10);
    glVertex2d(250, 0);
    glVertex2d(500, 0);
    glVertex2d(500, 10);
    glEnd();

    //floor-wall-2
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.25f, 0.0f);
    glVertex2d(0, 150);
    glVertex2d(0, 0);
    glVertex2d(250, -150);
    glVertex2d(250, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.25f, 0.0f);
    glVertex2d(250, 0);
    glVertex2d(250, -150);
    glVertex2d(500, -150);
    glVertex2d(500, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2d(0, 10);
    glVertex2d(0, 0);
    glVertex2d(250, -150);
    glVertex2d(250, -140);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);//pillar color
    glVertex2d(250, -140);
    glVertex2d(250, -150);
    glVertex2d(500, -150);
    glVertex2d(500, -140);
    glEnd();
    //pillar from right side
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2d(245, 152);
    glVertex2d(245, -145);
    glVertex2d(250, -150);
    glVertex2d(250, 150);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2d(10, 300);
    glVertex2d(0, 300);
    glVertex2d(0, 0);
    glVertex2d(10, 0);
    glEnd();
    //2nd Building
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.25f, 0.0f);
    glVertex2d(0, 150);
    glVertex2d(-350, 150);
    glVertex2d(-350, 0);
    glVertex2d(0, 0);
    glEnd();
    //pillar
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2d(-350, 150);
    glVertex2d(-350, 0);
    glVertex2d(-340, 0);
    glVertex2d(-340, 150);
    glEnd();
    //Rooftop
    glBegin(GL_POLYGON);
    glColor3f(0.9f, 0.7f, 1.0f);
    glVertex2d(-350, 150);
    glVertex2d(0, 150);
    glVertex2d(0, 220);
    glEnd();
    //door
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(-130, 0);
    glVertex2d(-200, 0);
    glVertex2d(-200, 90);
    glVertex2d(-130, 90);
    glEnd();
    //windows
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(-230, 100);
    glVertex2d(-320, 100);
    glVertex2d(-320, 40);
    glVertex2d(-230, 40);
    glEnd();
    //windows
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(-100, 40);
    glVertex2d(-100, 100);
    glVertex2d(-20, 100);
    glVertex2d(-20, 40);
    glEnd();
    //windows-2ndfloor baka
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(30, 250);
    glVertex2d(30, 170);
    glVertex2d(90, 130);
    glVertex2d(90, 210);
    glEnd();
    //windows-2nd floor baka
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(120, 200);
    glVertex2d(120, 120);
    glVertex2d(200, 70);
    glVertex2d(200, 150);
    glEnd();
    //windows 1st floor baka
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(20, 100);
    glVertex2d(20, 20);
    glVertex2d(100, -30);
    glVertex2d(100, 50);
    glEnd();
    //windows-2 1stfloor baka
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(130, 40);
    glVertex2d(130, -40);
    glVertex2d(220, -100);
    glVertex2d(220, -10);
    glEnd();
    //soja-wall up window
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(265, 120);
    glVertex2d(265, 30);
    glVertex2d(365, 30);
    glVertex2d(365, 120);
    glEnd();
    //soja-wall up window
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(390, 120);
    glVertex2d(390, 30);
    glVertex2d(480, 30);
    glVertex2d(480, 120);
    glEnd();
    //soja wall down window
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(265, -30);
    glVertex2d(265, -120);
    glVertex2d(365, -120);
    glVertex2d(365, -30);
    glEnd();
    //soja wall down window
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 1.0f, 1.0f);
    glVertex2d(390, -120);
    glVertex2d(390, -30);
    glVertex2d(480, -30);
    glVertex2d(480, -120);
    glEnd();
    //Road from School
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.2f, 0.1f);
    glVertex2d(-200, 0);
    glVertex2d(-300, -80);
    glVertex2d(-100, -280);
    glVertex2d(100, -290);
    glVertex2d(-180, -80);
    glVertex2d(-130, 0);
    glEnd();
    //road
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.2f, 0.1f);
    glVertex2d(-100, -280);
    glVertex2d(-400, -500);
    glVertex2d(-100, -500);
    glVertex2d(100, -290);
    glEnd();



    //tree

    drawTree(-120, -280);




    //Field
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2d(115, -280);
    glVertex2d(-95, -500);
    glVertex2d(500, -500);
    glVertex2d(500, -420);
    glEnd();

    // Boundary lines
    glColor3f(1.0f, 1.0f, 1.0f); // White color for lines
    glBegin(GL_LINE_LOOP);
    glVertex2d(115, -280);
    glVertex2d(500, -420);
    glVertex2d(500, -500);
    glVertex2d(-95, -500);
    glEnd();

    // Center line
    glBegin(GL_LINES);
    glVertex2d(300, -348);
    glVertex2d(210, -500);
    glEnd();

    // Center circle
    drawCircle(210, -500, 30, 1.0f, 1.0f, 1.0f);

    //left goalbox
    glBegin(GL_LINE_LOOP);
    glVertex2d(2, -400);
    glVertex2d(-77, -480);
    glVertex2d(20, -500);
    glVertex2d(80, -430);
    glEnd();




    //boy
    //Head

    drawCircle(-200, -300, 20, 1.0f, 0.8f, 0.6f);

    // Body
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-210, -320);
    glVertex2f(-190, -320);
    glVertex2f(-190, -380);
    glVertex2f(-210, -380);
    glEnd();

    // Legs
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-210, -380);
    glVertex2f(-215, -410);
    glVertex2f(-190, -380);
    glVertex2f(-185, -410);
    glEnd();

    // Arms
    glBegin(GL_LINES);
    glVertex2f(-210, -340);
    glVertex2f(-230, -355);
    glVertex2f(-190, -340);
    glVertex2f(-170, -355);
    glEnd();


    //girl
    //Head
    drawCircle(-140, -300, 20, 1.0f, 0.8f, 0.6f);

    // Body
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-150, -320);
    glVertex2f(-130, -320);
    glVertex2f(-125, -380);
    glVertex2f(-155, -380);
    glEnd();

    // Legs
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-150, -380);
    glVertex2f(-155, -410);
    glVertex2f(-130, -380);
    glVertex2f(-115, -410);
    glEnd();

    // Arms
    glBegin(GL_LINES);
    glVertex2f(-150, -340);
    glVertex2f(-170, -355);
    glVertex2f(-130, -340);
    glVertex2f(-110, -355);
    glEnd();



    //Shahid Minar

    //left row
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-850, -310);
    glVertex2f(-850, -410);
    glVertex2f(-795, -365);
    glVertex2f(-795, -265);
    glEnd();



    //add a box just like background
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-835, -318);
    glVertex2f(-835, -400);
    glVertex2f(-810, -380);
    glVertex2f(-810, -298);
    glEnd();

    //left row increasing
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-765, -210);
    glVertex2f(-765, -338);
    glVertex2f(-710, -295);
    glVertex2f(-710, -165);
    glEnd();



    //left row background
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-750, -215);
    glVertex2f(-750, -328);
    glVertex2f(-725, -308);
    glVertex2f(-725, -195);
    glEnd();


    drawCircle(-650, -150, 38, 0.8f, 0.1f, 0.1f);

    //middle row

     //1st box

    //creating base line
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-675, -97);
    glVertex2f(-675, -268);

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-650, -15);
    glVertex2f(-675, -97);

    glVertex2f(-590, 33);
    glVertex2f(-650, -15);

    glVertex2f(-590, 33);
    glVertex2f(-620, -70);

    glVertex2f(-620, -70);
    glVertex2f(-620, -250);
    glEnd();

    //1st box
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-675, -97);
    glVertex2f(-675, -268);
    glVertex2f(-670, -260);
    glVertex2f(-670, -90);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-650, -15);
    glVertex2f(-675, -97);
    glVertex2f(-668, -90);
    glVertex2f(-645, -13);
    glEnd();

    //2nd box
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-625, -70);
    glVertex2f(-625, -250);
    glVertex2f(-620, -250);
    glVertex2f(-620, -70);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-595, 28);
    glVertex2f(-625, -70);
    glVertex2f(-620, -70);
    glVertex2f(-590, 33);
    glEnd();

    //up box
    glBegin(GL_POLYGON);
    glVertex2f(-650, -15);
    glVertex2f(-653, -25);
    glVertex2f(-595, 25);
    glVertex2f(-590, 33);
    glEnd();

    //middle line

    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-620, 10);
    glVertex2f(-645, -80);

    glVertex2f(-645, -250);
    glVertex2f(-645, -80);
    glEnd();

    //right pillar
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-590, -75);
    glVertex2f(-590, -200);
    glVertex2f(-535, -150);
    glVertex2f(-535, -30);
    glEnd();


    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-575, -85);
    glVertex2f(-575, -200);
    glVertex2f(-550, -180);
    glVertex2f(-550, -62);
    glEnd();

    //right pillar
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-505, -35);
    glVertex2f(-505, -130);
    glVertex2f(-450, -90);
    glVertex2f(-450, 8);
    glEnd();
    //right pillar bg
    glBegin(GL_POLYGON);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-490, -40);
    glVertex2f(-490, -120);
    glVertex2f(-465, -100);
    glVertex2f(-465, -22);
    glEnd();


    //stairs

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.4f, 0.2f);
    glVertex2f(-350, 0);
    glVertex2f(-900, -450);
    glVertex2f(-900, -470);
    glVertex2f(-330, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-330, 0);
    glVertex2f(-900, -470);
    glVertex2f(-900, -475);
    glVertex2f(-325, 0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.4f, 0.2f);
    glVertex2f(-325, 0);
    glVertex2f(-900, -475);
    glVertex2f(-900, -500);
    glVertex2f(-300, 0);
    glEnd();

    //tree-beside shahid minar

    drawTree(-370, -60);

    // Add the banner
    drawBanner();

    // Draw flag
    drawFlag(-870, -500);


    // Grass beside road

    glColor3f(0.0f, 0.5f, 0.0f); // Green color for grass blades
    glBegin(GL_LINES);
    glVertex2f(-280, -360);
    glVertex2f(-280, -415);

    glVertex2f(-280, -415);
    glVertex2f(-290, -365);

    glVertex2f(-280, -415);
    glVertex2f(-270, -365);

    glVertex2f(-280, -415);
    glVertex2f(-300, -365);

    glVertex2f(-280, -415);
    glVertex2f(-260, -365);

    glVertex2f(-280, -415);
    glVertex2f(-250, -365);

    glVertex2f(-280, -415);
    glVertex2f(-300, -365);
    //more grass
    glVertex2f(-395, -430);
    glVertex2f(-395, -500);

    glVertex2f(-375, -435);
    glVertex2f(-395, -500);

    glVertex2f(-415, -435);
    glVertex2f(-395, -500);

    glVertex2f(-355, -435);
    glVertex2f(-395, -500);

    glVertex2f(-435, -435);
    glVertex2f(-395, -500);

    //third grass

    glVertex2f(10, -200);
    glVertex2f(10, -130);

    glVertex2f(10, -200);
    glVertex2f(25, -135);

    glVertex2f(10, -200);
    glVertex2f(-5, -135);

    glVertex2f(10, -200);
    glVertex2f(-20, -140);

    glVertex2f(10, -200);
    glVertex2f(40, -140);

    //grass 4

    glVertex2f(-300, -80);
    glVertex2f(-300, -25);

    glVertex2f(-300, -80);
    glVertex2f(-285, -30);

    glVertex2f(-300, -80);
    glVertex2f(-315, -30);

    glVertex2f(-300, -80);
    glVertex2f(-330, -35);

    glVertex2f(-300, -80);
    glVertex2f(-270, -35);

    glEnd();





    glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1300, 700);
    glutCreateWindow("School Scenery");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(33, updateCloud, 0); // Cloud animation
    glutTimerFunc(16, updateBirdPosition, 0);  // Update bird position every 16ms (60 FPS)

    glutMainLoop();
    return 0;
}
