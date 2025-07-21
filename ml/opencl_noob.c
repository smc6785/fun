#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif
// gcc -framework OpenCL helloworld.c 
// OpenCL kernel code with corrected address space
const char *kernelSource = 
"__kernel void hello(__global char *output) {\n"
"    __constant const char *hello = \"Hello, World!\\n\";\n"  // Added __constant
"    int gid = get_global_id(0);\n"
"    if (gid < 14) output[gid] = hello[gid];\n"
"}\n";

void checkError(cl_int err, const char *operation) {
    if (err != CL_SUCCESS) {
        fprintf(stderr, "Error during %s: %d\n", operation, err);
        exit(1);
    }
}

int main() {
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_mem output_buffer;
    cl_uint num_platforms;
    cl_int err;

    // Get platform and device
    err = clGetPlatformIDs(1, &platform_id, &num_platforms);
    checkError(err, "clGetPlatformIDs");
    if (num_platforms == 0) {
        printf("No OpenCL platforms found\n");
        return 1;
    }

    err = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
    checkError(err, "clGetDeviceIDs");

    // Create OpenCL context
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &err);
    checkError(err, "clCreateContext");

    // Create command queue
    queue = clCreateCommandQueue(context, device_id, 0, &err);
    checkError(err, "clCreateCommandQueue");

    // Create memory buffer
    size_t buffer_size = 14; // Length of "Hello, World!\n"
    output_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, 
                                 buffer_size * sizeof(char), NULL, &err);
    checkError(err, "clCreateBuffer");

    // Create program from kernel source
    program = clCreateProgramWithSource(context, 1, &kernelSource, NULL, &err);
    checkError(err, "clCreateProgramWithSource");

    // Build program
    err = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
    if (err != CL_SUCCESS) {
        size_t log_size;
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
        char *log = (char *)malloc(log_size);
        clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
        fprintf(stderr, "Build error: %s\n", log);
        free(log);
        exit(1);
    }

    // Create kernel
    kernel = clCreateKernel(program, "hello", &err);
    checkError(err, "clCreateKernel");

    // Set kernel argument
    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), &output_buffer);
    checkError(err, "clSetKernelArg");

    // Execute kernel
    size_t global_work_size = 14;
    err = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, 
                               &global_work_size, NULL, 0, NULL, NULL);
    checkError(err, "clEnqueueNDRangeKernel");

    // Read result
    char *output = (char*)malloc(buffer_size * sizeof(char));
    err = clEnqueueReadBuffer(queue, output_buffer, CL_TRUE, 0, 
                            buffer_size * sizeof(char), output, 0, NULL, NULL);
    checkError(err, "clEnqueueReadBuffer");

    // Print result
    printf("%s", output);

    // Cleanup
    clFlush(queue);
    clFinish(queue);
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseMemObject(output_buffer);
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    free(output);

    return 0;
}
