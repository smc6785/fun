#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// artifician neurons
// x1, x2, x3, ..., b(bias)
// w1, w2, w3, ...
// y = x1*w1 + x2*w2 + x3*w3 + ... + b

float train[][2] = {
    {0,0},
    {1,2},
    {2,4},
    {3,6},
    {4,8},
};
#define train_count (sizeof(train)/sizeof(train[0]))

float random_float(void)
{
    return (float) rand() / (float) RAND_MAX;
}

float cost(float w, float b)
{
    float result = 0x0f;
    for (size_t i = 0; i < train_count; ++i)
    {
        float x = train[i][0];
        float y = x*w + b;
        float d = y - train[i][1];
        result += d*d;
        // printf("actual: %f, expected :%f\n",y,train[i][1]);
    }
    result /= train_count;
    return result;
}

int main()
{
    srand(0);
    // srand(time(NULL));
    float w = random_float();
    float b = random_float();

    // epsilon
    float eps = 1e-3;
    float rate = 1e-3;
    
    // finite difference, approximation of derivatives
    printf("result %f\n",cost(w, b));
    for (size_t i = 0; i < 500; ++i)
    {
        float dw = (cost(w + eps, b) - cost(w, b))/eps;
        float db = (cost(w,b + eps) - cost(w, b))/eps;
        w -= rate*dw;
        b -= rate*db;
        printf("cost %f, w = %f, b = %f\n",cost(w,b), w, b);
    }
    printf("w %f\n", w);
    printf("b %f\n", b);
    return 0;
}
