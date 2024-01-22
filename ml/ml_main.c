#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

float cost(float w)
{
    float result = 0x0f;
    for (size_t i = 0; i < train_count; ++i)
    {
        float x = train[i][0];
        float y = x*w;
        float d = y - train[i][1];
        result += d*d;
        //printf("actual: %f, expected :%f\n",y,train[i][1]);
    }
    result /= train_count;
    return result;
}

int main()
{
    srand(0);
    //srand(time(NULL));
    float w = random_float();

    //epsilon
    float eps = 1e-3;
    float rate = 1e-3;
    
    // finite difference, approximation of derivatives
    printf("result %f\n",cost(w));
    for (size_t i = 0; i < 500; ++i)
    {
        float dcost = (cost(w + eps) - cost(w))/eps;
        w -= rate*dcost;
        printf("result %f\n",cost(w+eps));
    }
    printf("w %f\n", w);
    return 0;
}
