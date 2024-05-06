#ifndef NN_H_
#define NN_H_

#include <stddef.h>

#ifndef NN_MALLOC
#include <stdlib.h>
#define NN_MALLOC malloc
#endif //NN_MALLOC

#ifndef NN_ASSERT
#include <assert.h>
#define NN_ASSERT assert
#endif //NN_ASSERT

// float d[] = {0, 1, 0, 1};
// Mat m = { .rows = 2, cols = 2, .es = d };

typedef struct{
    size_t rows;
    size_t cols;
    float *es;
} Mat;

Mat mat_alloc(size_t rows, size_t cols);
void mat_dot(Mat dst, Mat a, Mat b);
void mat_sum(Mat dst, Mat a);
void mat_print(Mat m);

#endif // NN_H_

#ifdef NN_IMPLEMENTATION

Mat mat_alloc(size_t rows, size_t cols)
{
    Mat m;
    m.rows = rows;
    m.cols = cols;
    m.es = NN_MALLOC(sizeof(*m.es)*rows*cols);
    NN_ASSERT(m.es != NULL);
    return m;
}
void mat_dot(Mat dst, Mat a, Mat b)
{
    (void) dst;
    (void) a;
    (void) b;
}

void mat_sum(Mat dst, Mat a)
{
    (void) dst;
    (void) a;
}
void mat_print(Mat m)
{
   for()
   {
       for()
       {

       }
   }
}
#endif // NN_IMPLEMENTATION
