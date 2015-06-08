#include <vector_gpu.hpp>

#define ARRAY_SIZE 10

int main(int argc, char** argv)
{
    cl_context context = 0;
    cl_command_queue commandQueue = 0;
    cl_program program = 0;
    cl_device_id device = 0;
    cl_kernel kernel = 0;
    cl_mem memObjects[3] = { 0, 0, 0 };
    cl_int errNum;

    // Create an OpenCL context on first available platform
    context = CreateContext();
    if (context == NULL)
    {
        std::cerr << "Failed to create OpenCL context." << std::endl;
        return 1;
    }
    // Create a command-queue on the first device available
    // on the created context
    commandQueue = CreateCommandQueue(context, &device);
    if (commandQueue == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    std::cout << "Attempting to create program from binary..." << std::endl;
    program = CreateProgramFromBinary(context, device, KERNEL_BIN);
    if (program == NULL)
    {
        std::cout << "Binary not loaded, create from source..." << std::endl;
        program = CreateProgram(context, device, (char*) argv[1]);
        if (program == NULL)
        {
            Cleanup(context, commandQueue, program, kernel, memObjects);
            return 1;
        }

        std::cout << "Save program binary for future run..." << std::endl;
        if (SaveProgramBinary(program, device, KERNEL_BIN) == false)
        {
            std::cerr << "Failed to write program binary" << std::endl;
            Cleanup(context, commandQueue, program, kernel, memObjects);
            return 1;
        }
    }
    else
    {
        std::cout << "Read program from binary." << std::endl;
    }

/*
    // Create OpenCL program from HelloWorld.cl kernel source
    program = CreateProgram(context, device, (char*) argv[1]);
    if (program == NULL)
    {
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

*/
    // Create OpenCL kernel
    kernel = clCreateKernel(program, (char*) argv[2], NULL);
    if (kernel == NULL)
    {
        std::cerr << "Failed to create kernel" << std::endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Create memory objects that will be used as arguments to
    // kernel.  First create host memory arrays that will be
    // used to store the arguments to the kernel
    route result(ARRAY_SIZE);
    route a(ARRAY_SIZE);
    route b(ARRAY_SIZE);
    for (double i = 0.; i < ARRAY_SIZE; i++)
    {
        a[i].s0=i; a[i].s1=i+0.1;
        b[i].s0=0.1*i; b[i].s1=i*i;
    }

//	route R(read_route(argv[3]));

    if (!CreateMemObjects(context, memObjects, &a[0], &b[0],ARRAY_SIZE))
    {
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Set the kernel arguments (result, a, b)
    errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
    errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);
    errNum |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &memObjects[2]);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error setting kernel arguments." << std::endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    size_t globalWorkSize[1] = { ARRAY_SIZE };
    size_t localWorkSize[1] = { 1 };

    // Queue the kernel up for execution across the array
    errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
globalWorkSize, localWorkSize, 0, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error queuing kernel for execution." << std::endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Read the output buffer back to the Host
    errNum = clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE, 0, ARRAY_SIZE * sizeof(point), &result[0], 0, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error reading result buffer." << std::endl;
        Cleanup(context, commandQueue, program, kernel, memObjects);
        return 1;
    }

    // Output the result buffer
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        std::cout << a[i] << " " <<  b[i] << " " << result[i] << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Executed program succesfully." << std::endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);

    return 0;
}
