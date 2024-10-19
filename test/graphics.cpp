#include <array>
#include <cstdio>

void renderFrame(std::array<std::array<char, 5>, 5> &board)
{
    int y_pos = 0;

    for (auto row : board)
    {
        int x_pos = 0;
        for (auto col : row)
        { 
            x_pos++;
            printf("x: %d\n", x_pos);
            printf("element at x: %c\n", col);
        }
        y_pos++;
        printf("y: %d\n", y_pos);
    }
}

int main(int argc, char** argv)
{
    std::array<std::array<char, 5>, 5> testArray = {{
        {'#', '#', '#', '#', '#'},
        {'#', 'o', 'o', 'p', '#'},
        {'#', 's', 'i', 'e', '#'},
        {'#', '#', '#', '#', '#'},
        {'#', '#', '#', '#', '#'},
    }};

    renderFrame(testArray);
}
