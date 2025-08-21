#include "util.h"
#include "raylib.h"

void Util::RenderImage(Texture2D image, int x, int y, int width, int height, int rotation, int scale, unsigned char alpha) {
    DrawTexturePro(image, 
        // initial dimentions of the circle as a rectangle
        Rectangle{ 0.0f, 0.0f, (float)image.width, (float)image.height }, 
        // final position and dimentions of the image
        Rectangle{ (float)x, (float)y, (float)width*scale, (float)height*scale },
        // define the origin of the image to be the center
        Vector2{(float)width*scale/2, (float)height*scale/2}, 
        rotation, {255, 255, 255, alpha}
    );
}

void State2D::Set(int x, int y, int width, int height, float rot) {
    pose.x = x;
    pose.y = y;
    dims.width = width;
    dims.height = height;
    rotation = rot;
}

double sigmoid(double k) {
    return 1/(1 + pow(M_E, -k));
}