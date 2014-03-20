// handle changes due to mouse motion, or keys
#ifndef Input_hpp
#define Input_hpp

class Input {
// public data
public:
    int mouseButton;            // which mouse button was pressed?
    int oldX, oldY;             // location of mouse at last event

// public methods
public:
    // initialize
    Input() : mouseButton(0), oldX(0), oldY(0) {}

    // handle mouse press / start of motion
    void mousePress(int button, int x, int y);

    // handle mouse drag
    void mouseDrag(int x, int y);

    // handle key press
    void keyPress(int key);

    // handle key release
    void keyRelease(int key);
};

extern Input g_input;                  // global UI object

#endif
