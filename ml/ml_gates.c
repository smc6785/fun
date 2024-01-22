#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float sigmoid(float x)
{
    // man exp
    return 1.f / (1.f + expf(-x));
}
// OR gate
float train[][3] = {
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,0,1},
};
#define train_count (sizeof(train)/sizeof(train[0]))

float random_float(void)
{
    return (float) rand() / (float) RAND_MAX;
}

float cost(float w1, float w2)
{
#if 0
    // sigmoid demo
    for (float x = -10.f; x <= 10.f; x += 1.f)
    {
        printf("%f => %f\n", x, sigmoid(x));
    }
    return 0;
#endif
    float result = 0x0f;
    for (size_t i = 0; i < train_count; ++i)
    {
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoid(x1*w1 + x2*w2);
        float d = y - train[i][2];
        result += d*d;
        // printf("actual: %f, expected :%f\n",y,train[i][3]);
    }
    result /= train_count;
    return result;
}

int main()
{
    srand(0);
    // srand(time(NULL));
    float w1 = random_float();
    float w2 = random_float();

    // epsilon
    float eps = 1e-3;
    float rate = 1e-3;
    
    // finite difference, approximation of derivatives
    for (size_t i =0; i<1000; ++i)
    {
        float c = cost(w1, w2);
        printf("w1 =  %f, w2 = %f, c= %f \n",w1, w2, c);
        float dw1 = (cost(w1 + eps, w2) - c)/eps;
        float dw2 = (cost(w1, w2 + eps) - c)/eps;
        w1 -= rate*dw1;
        w2 -= rate*dw2;
    }
    return 0;
}

// activation function
// - sigmoid function
// - ReLu
