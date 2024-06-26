#include "progress_bar.h"

void ProgressBar::update()
{
    if (curr_pass >= num_passes)
    {
        std::cout << "Done.";
    }
    else
    {
        std::cout << "[";
        curr_pass += 1;
        progress = double(curr_pass) / num_passes;
        int pos = barWidth * progress;
        for (int i = 0; i < barWidth; ++i)
        {
            if (i < pos)
                std::cout << "=";
            else if (i == pos)
                std::cout << ">";
            else
                std::cout << " ";
        }
        std::cout << "] " << int(progress * 100.0) << " %\r";
        std::cout.flush();
    }
}
