#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

class ProgressBar
{
public:
    int barWidth;
    float progress = 0;
    int curr_pass = 0;
    int num_passes;

    ProgressBar(int b, int n) : barWidth(b), num_passes(n){};
    void update();
};