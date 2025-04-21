#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <OpenCL/opencl.h>

// OpenCL kernel code
const char *kernelSource = 
"__kernel void hello(__global char *output) {\n"
"    __constant const char *hello = \"Hello, World!\\n\";\n"
"    int gid = get_global_id(0);\n"
"    if (gid < 14) output[gid] = hello[gid];\n"
"}\n";

int main() {
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_mem output_buffer;
    cl_uint num_platforms;
    cl_int ret;

    // Get platform and device
    ret = clGetPlatformIDs(1, &platform_id, &num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);

    // Create OpenCL context
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

    // Create command queue
    queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffer
    size_t buffer_size = 14; // Length of "Hello, World!\n"
    output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
                                 buffer_size * sizeof(char), NULL, &ret);

    // Create program from kernel source
    program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, &ret);

    // Build program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create kernel
    kernel = clCreateKernel(program, "hello", &ret);

    // Set kernel argument
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &output_buffer);

    // Execute kernel
    size_t global_work_size = 14;
    ret = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, 
                               &global_work_size, NULL, 0, NULL, NULL);

    // Read result
    char *output = (char*)malloc(buffer_size * sizeof(char));
    ret = clEnqueueReadBuffer(queue, output_buffer, CL_TRUE, 0, 
                            buffer_size * sizeof(char), output, 0, NULL, NULL);

    // Print result
    printf("%s\n", output);

    // Cleanup
    ret = clFlush(queue);
    ret = clFinish(queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(output_buffer);
    ret = clReleaseCommandQueue(queue);
    ret = clReleaseContext(context);
    free(output);

    return 0;
}
