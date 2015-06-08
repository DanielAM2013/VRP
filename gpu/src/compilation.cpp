#include <vector_gpu.hpp>

int main ( int argc, char** argv)
{
    cl_context context = 0;
    cl_command_queue commandQueue = 0;
    cl_program program = 0;
    cl_device_id device = 0;
    cl_kernel kernel = 0;
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
        return 1;
    }

    program = CreateProgram(context, device, (char*) argv[1]);
    if (program == NULL)
    {
        return 1;
    }

    if (SaveProgramBinary(program, device,(char*) argv[2]) == false)
    {
        std::cerr << "Failed to write program binary" << std::endl;
        return 1;
	}

    return 0;
}
