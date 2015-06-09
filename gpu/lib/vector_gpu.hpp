#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#include <exception>

typedef cl_double2 point;

#define TYPE_IN_USE double

typedef std::vector<TYPE_IN_USE> route;

std::ostream& operator<< ( std::ostream &out, const point& P)
// Body
{
 out << "(" << P.s0 << "," << P.s1 << ")";
 return out;
}

//  Create an OpenCL context on the first available platform using
//  either a GPU or CPU depending on what is available.
//
cl_context CreateContext()
// Body
{
    cl_int errNum;
    cl_uint numPlatforms;
    cl_platform_id firstPlatformId;
    cl_context context = NULL;

    // First, select an OpenCL platform to run on.  For this example, we
    // simply choose the first available platform.  Normally, you would
    // query for all available platforms and select the most appropriate one.
    errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
    if (errNum != CL_SUCCESS || numPlatforms <= 0)
    {
        std::cerr << "Failed to find any OpenCL platforms." << std::endl;
        return NULL;
    }

    // Next, create an OpenCL context on the platform.  Attempt to
    // create a GPU-based context, and if that fails, try to create
    // a CPU-based context.
    cl_context_properties contextProperties[] =
    {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)firstPlatformId,
        0
    };
    context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU, NULL, NULL, &errNum);
    if (errNum != CL_SUCCESS)
    {
        std::cout << "Could not create GPU context, trying CPU..." << std::endl;
        context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU,
                                          NULL, NULL, &errNum);
        if (errNum != CL_SUCCESS)
        {
            std::cerr << "Failed to create an OpenCL GPU or CPU context." << std::endl;
            return NULL;
        }
    }

    return context;
}

//  Create a command queue on the first device available on the
//  context
cl_command_queue CreateCommandQueue (
	cl_context context,
	cl_device_id *device
)
{
    cl_int errNum;
    cl_device_id *devices;
    cl_command_queue commandQueue = NULL;
    size_t deviceBufferSize = -1;

    // First get the size of the devices buffer
    errNum = clGetContextInfo (
		context,
		CL_CONTEXT_DEVICES,
		0,
		NULL,
		&deviceBufferSize);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Failed call to clGetContextInfo(...,GL_CONTEXT_DEVICES,...)";
        return NULL;
    }
    if (deviceBufferSize <= 0)
    {
        std::cerr << "No devices available.";
        return NULL;
    }

    // Allocate memory for the devices buffer
    devices = new cl_device_id[deviceBufferSize / sizeof(cl_device_id)];
    errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, deviceBufferSize, devices, NULL);
    if (errNum != CL_SUCCESS)
    {
        delete [] devices;
        std::cerr << "Failed to get device IDs";
        return NULL;
    }

    // In this example, we just choose the first available device.  In a
    // real program, you would likely use all available devices or choose
    // the highest performance device based on OpenCL device queries
    commandQueue = clCreateCommandQueue(context, devices[0], 0, NULL);
    if (commandQueue == NULL)
    {
        delete [] devices;
        std::cerr << "Failed to create commandQueue for device 0";
        return NULL;
    }

    *device = devices[0];
    delete [] devices;
    return commandQueue;
}

//  Create an OpenCL program from the kernel source file
cl_program CreateProgram (
	cl_context context,
	cl_device_id device,
	const char* fileName
)
{
    cl_int errNum;
    cl_program program;

    std::ifstream kernelFile(fileName, std::ios::in);
    if (!kernelFile.is_open())
    {
        std::cerr << "Failed to open file for reading: " 
				  << fileName << std::endl;
        return NULL;
    }

    std::ostringstream oss;
    oss << kernelFile.rdbuf();

    const char *srcStr = oss.str().c_str();
    program = clCreateProgramWithSource ( 
		context,
		1,
		(const char**) &srcStr,
		NULL,
		NULL);
    if (program == NULL)
    {
        std::cerr << "Failed to create CL program from source." << std::endl;
        return NULL;
    }

    errNum = clBuildProgram(program, 0, NULL, OCLFLAGS, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        // Determine the reason for the error
        char buildLog[16384];
        clGetProgramBuildInfo (
			program,
			device,
			CL_PROGRAM_BUILD_LOG,
            sizeof(buildLog),
			buildLog,
			NULL);

        std::cerr << "Error in kernel: " << std::endl;
        std::cerr << buildLog;
        clReleaseProgram(program);
        return NULL;
    }

    return program;
}

//  Create memory objects used as the arguments to the kernel
//  The kernel takes three arguments: result (output), a (input),
//  and b (input)
bool CreateMemObjects (
	cl_context context,
	cl_mem* memObjects,
	TYPE_IN_USE* T,
	TYPE_IN_USE* M,
	int ARRAY_SIZE
)
{
	
		memObjects[0] = clCreateBuffer (
			context, 
   		 	CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
   		 	sizeof(TYPE_IN_USE) * ARRAY_SIZE,
			T,
			NULL);
		memObjects[1] = clCreateBuffer (
			context, 
   		 	CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
   		 	sizeof(TYPE_IN_USE) * ARRAY_SIZE,
			M,
			NULL);
		memObjects[2] = clCreateBuffer (
			context, 
   		 	CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
   		 	sizeof(TYPE_IN_USE) * ARRAY_SIZE,
			NULL,
			NULL);


		if ( memObjects[0] == NULL || memObjects[1] == NULL || memObjects[2] == NULL)
		{
        	std::cerr << "Error creating memory objects." << std::endl;
       		return false;
		}


	return true;
}

//  Cleanup any created OpenCL resources
void Cleanup (
	cl_context context,
	cl_command_queue commandQueue,
	cl_program program,
	cl_kernel kernel,
	std::vector<cl_mem> memObjects
)
{
    for (int i = 0; i < memObjects.size(); i++)
    {
        if ( memObjects[i] != NULL)
            clReleaseMemObject(memObjects[i]);
    }
    if (commandQueue != 0)
        clReleaseCommandQueue(commandQueue);

    if (kernel != NULL)
        clReleaseKernel(kernel);

    if (program != NULL)
        clReleaseProgram(program);

    if (context != NULL)
        clReleaseContext(context);
}

//  Attempt to create the program object from a cached binary.  Note that
//  on first run this will fail because the binary has not yet been created.
cl_program CreateProgramFromBinary (
	cl_context context,
	cl_device_id device,
 	const char* fileName
)
{
    FILE *fp = fopen(fileName, "rb");
    if (fp == NULL)
    {
        return NULL;
    }

    // Determine the size of the binary
    size_t binarySize;
    fseek(fp, 0, SEEK_END);
    binarySize = ftell(fp);
    rewind(fp);

    unsigned char *programBinary = new unsigned char[binarySize];
    fread(programBinary, 1, binarySize, fp);
    fclose(fp);

    cl_int errNum = 0;
    cl_program program;
    cl_int binaryStatus;

    program = clCreateProgramWithBinary (
		context,
        1,
        &device,
        &binarySize,
        (const unsigned char**)&programBinary,
        &binaryStatus,
        &errNum);
    delete [] programBinary;
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error loading program binary." << std::endl;
        return NULL;
    }
    if (binaryStatus != CL_SUCCESS)
    {
        std::cerr << "Invalid binary for device" << std::endl;
        return NULL;
    }

    errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if (errNum != CL_SUCCESS)
    {
        // Determine the reason for the error
        char buildLog[16384];
        clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
                              sizeof(buildLog), buildLog, NULL);

        std::cerr << "Error in program: " << std::endl;
        std::cerr << buildLog << std::endl;
        clReleaseProgram(program);
        return NULL;
    }

    return program;
}

bool SaveProgramBinary (
	cl_program program,
	cl_device_id device,
	const char* fileName
)
{
    cl_uint numDevices = 0;
    cl_int errNum;

    // 1 - Query for number of devices attached to program
    errNum = clGetProgramInfo (
		program,
		CL_PROGRAM_NUM_DEVICES,
		sizeof(cl_uint),
		&numDevices,
		NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error querying for number of devices." << std::endl;
        return false;
    }

    // 2 - Get all of the Device IDs
    cl_device_id *devices = new cl_device_id[numDevices];
    errNum = clGetProgramInfo (
		program,
		CL_PROGRAM_DEVICES,
		sizeof(cl_device_id) * numDevices,
		devices,
		NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error querying for devices." << std::endl;
        delete [] devices;
        return false;
    }

    // 3 - Determine the size of each program binary
    size_t *programBinarySizes = new size_t [numDevices];
    errNum = clGetProgramInfo (
		program,
		CL_PROGRAM_BINARY_SIZES,
		sizeof(size_t) * numDevices,
		programBinarySizes,
		NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error querying for program binary sizes." << std::endl;
        delete [] devices;
        delete [] programBinarySizes;
        return false;
    }

    unsigned char **programBinaries = new unsigned char*[numDevices];
    for (cl_uint i = 0; i < numDevices; i++)
    {
        programBinaries[i] = new unsigned char[programBinarySizes[i]];
    }

    // 4 - Get all of the program binaries
    errNum = clGetProgramInfo (
		program,
		CL_PROGRAM_BINARIES,
		sizeof(unsigned char*) * numDevices,
		programBinaries,
		NULL);
    if (errNum != CL_SUCCESS)
    {
        std::cerr << "Error querying for program binaries" << std::endl;

        delete [] devices;
        delete [] programBinarySizes;
        for (cl_uint i = 0; i < numDevices; i++)
        {
            delete [] programBinaries[i];
        }
        delete [] programBinaries;
        return false;
    }

    // 5 - Finally store the binaries for the device requested out to disk for future reading.
    for (cl_uint i = 0; i < numDevices; i++)
    {
        // Store the binary just for the device requested.  In a scenario where
        // multiple devices were being used you would save all of the binaries out here.
        if (devices[i] == device)
        {
            FILE *fp = fopen(fileName, "wb");
            fwrite(programBinaries[i], 1, programBinarySizes[i], fp);
            fclose(fp);
            break;
        }
    }

    // Cleanup
    delete [] devices;
    delete [] programBinarySizes;
    for (cl_uint i = 0; i < numDevices; i++)
    {
        delete [] programBinaries[i];
    }
    delete [] programBinaries;
    return true;
}

route read_route ( char* file )
{

	std::ifstream points ( file, std::ios::in );

	route Aux;
	TYPE_IN_USE aux;
	while ( points >> aux ) {
		Aux.push_back(aux);
	}

	return Aux;
}
