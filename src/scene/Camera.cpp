#include "Camera.h"

Camera::Camera(int width, int height)
    :window_width(width), window_height(height)
{

    // set the projection matrix that accounts for the aspect ratio of the window
    aspect_ratio = (float)window_width / (float)window_height;

    //user set value to control the height of the world. 2.0f lets the top and bottom be at 1.0 and -1.0.
    world_height = 2.0f;
    world_width = world_height * aspect_ratio;

    printf("World height: %f  World Width: %f\n", world_height, world_width);

    left_window_bound = -window_width * 0.5f;
    right_window_bound = window_width * 0.5f;
    top_window_bound = window_height * 0.5f;
    bottom_window_bound = -window_height * 0.5f;

    //using this projection means that the left wall and right wall are at +/- aspect
    projection = glm::ortho(left_window_bound, right_window_bound, bottom_window_bound, top_window_bound);

}
