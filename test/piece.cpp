#include <array>
#include <cstdio>

enum Direction : unsigned int 
{
    LEFT, RIGHT, DOWN
};

void testMove(Direction dir, std::array<std::array<int, 2>, 4> (&coordinates))
{
    switch (dir) {
        case LEFT:
            for (auto &row : coordinates)
                row[0]--;
            break;
        case RIGHT:
            for (auto &row : coordinates)
                row[0]++;
            break;
        case DOWN:
            for (auto &row : coordinates)
                row[1]--;
            break;
        default:
            printf("defaulted, array unchanged");
            break;
    }
}

void print2DArray(std::array<std::array<int, 2>, 4> array) {
    for (auto row : array) {
        printf("{%d, %d}, ", row[0], row[1]);
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    std::array<std::array<int, 2>, 4> coordinates = { {{0, 0}, {0, 1}, {0, 2}, {0, 3}} };

    // Expected: {{-1, 0}, {-1, 1}, {-1, 2}, {-1, 3}}
    testMove(LEFT, coordinates);
    print2DArray(coordinates);

    std::array<std::array<int, 2>, 4> coordinates2 = { {{0, 0}, {0, 1}, {0, 2}, {0, 3}} };

    // Expected: {{1, 0}, {1, 1}, {1, 2}, {1, 3}}
    testMove(RIGHT, coordinates2);
    print2DArray(coordinates2);

    std::array<std::array<int, 2>, 4> coordinates3 = { {{0, 0}, {0, 1}, {0, 2}, {0, 3}} };

    // Expected: {{0, -1}, {0, 0}, {0, 1}, {0, 2}}
    testMove(DOWN, coordinates3);
    print2DArray(coordinates3);
}
