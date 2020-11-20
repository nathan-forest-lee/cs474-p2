
// [0] is X derivative and [1] is Y derivative

// const double prewittX[3][3] = {{0, 0.111, 0.222}, {0, 0.111, 0.222}, {0, 0.111, 0.222}};
// const double prewittY[3][3] = {{0, 0, 0}, {0.111, 0.111, 0.111}, {0.222, 0.222, 0.222}};

// const int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
// const int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// const int laplacian[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};







const int prewittX[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
const int prewittY[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};

const int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
const int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

const int laplacian[3][3] = {{0, 1, 0}, {1, -4, 1}, {0, 1, 0}};