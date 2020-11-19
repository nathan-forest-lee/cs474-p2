
// [0] is X derivative and [1] is Y derivative

const int prewitt[2] = {{{{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}}},
                        {{{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}}}};

static const int sobel[2] = {{{{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}}},
                             {{{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}}}};

static const int laplacian = {{{0, 1, 0}, {1, -4, 1}, {0, 1, 0}}};
