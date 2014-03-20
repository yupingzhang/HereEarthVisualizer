// handle view changes
#ifndef View_hpp
#define View_hpp

#include "Vec.hpp"

class View {
// public data
public:
    int width, height;          // window dimensions

    int updateTime;             // time (in ms) of last update

    Vec<2> position;       
    float direction;            // current motion direction (in radians)
    float speed;         // speed and acceleration in motion direction
    float rotSpeed;  
    // head rotation
    float pan, tilt;
    float scale;
    float scale_accelerate;
    
// public methods
public:
    // create with initial window size and orbit location
    View();

    // reset view to default position
    void reset();

    // set up new window viewport of width x height
    void viewport(int width, int height);

    // set view using current position and direction
    void view() const;

    // update based on elapsed time in ms
    void update();
};

extern View g_view;                // global view object
extern const float c_speed;
extern const float c_rotation;     // rotation radians per ms

#endif
