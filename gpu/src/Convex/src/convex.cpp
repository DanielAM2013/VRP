#include <base.hpp>

// Get a list of points and calculate mean point
// argv[1] kernel_binary
// argv[2] kernel name
// argv[3] points file
int main(int argc, char** argv) {
  // Create contex
  cl_context context = NULL;
  cl_uint num_platforms;
  cl_platform_id first_platform_id;
  cl_int status = clGetPlatformIDs(1, &first_platform_id, &num_platforms);
  if (status != CL_SUCCESS || num_platforms <= 0) {
    std::cerr << "Failed to find OpenCL platforms" << std::endl;
    return -1;
  }

  cl_context_properties context_properties[] = {
      CL_CONTEXT_PLATFORM, (cl_context_properties)first_platform_id, 0};

  context = clCreateContextFromType(context_properties, CL_DEVICE_TYPE_GPU,
                                    NULL, NULL, &status);
  if (status != CL_SUCCESS) {
    std::cerr << "Could not create GPU context" << std::endl;
    return -1;
  }

  // Create Command Queue
  size_t device_buffer_size = -1;
  status = clGetContextInfo(context, CL_CONTEXT_DEVICES, 0, NULL,
                            &device_buffer_size);

  if (status != CL_SUCCESS) {
    std::cerr << "Failed call to clGetContextInfo" << std::endl;
    return -1;
  }
  if (device_buffer_size <= 0) {
    std::cerr << "No devices available." << std::endl;
    return -1;
  }

  cl_device_id device = 0;
  cl_device_id* devices =
      new cl_device_id[device_buffer_size / sizeof(cl_device_id)];
  status = clGetContextInfo(context, CL_CONTEXT_DEVICES, device_buffer_size,
                            devices, NULL);
  if (status != CL_SUCCESS) {
    delete[] devices;
    std::cerr << "Failed to get device IDS" << std::endl;
    return -1;
  }

  cl_command_queue command_queue = NULL;
  command_queue = clCreateCommandQueue(context, devices[0], 0, NULL);
  if (command_queue == NULL) {
    delete[] devices;
    std::cerr << "Failed to create command queue for device 0" << std::endl;
    clReleaseContext(context);
    return -1;
  }

  device = devices[0];
  delete[] devices;

  // Create Program
  FILE* fp = fopen(argv[1], "rb");
  if (fp == NULL) {
    return -1;
  }

  fseek(fp, 0, SEEK_END);
  size_t binary_size = ftell(fp);
  rewind(fp);

  unsigned char* program_binary = new unsigned char[binary_size];
  fread(program_binary, 1, binary_size, fp);
  fclose(fp);

  cl_int binary_status;
  status = 0;
  cl_program program = clCreateProgramWithBinary(
      context, 1, &device, &binary_size, (const unsigned char**)&program_binary,
      &binary_status, &status);
  delete[] program_binary;
  if (status != CL_SUCCESS) {
    std::cerr << "Error loading program binary." << std::endl;
    return -1;
  }
  if (binary_status != CL_SUCCESS) {
    std::cerr << "Invalid binary for device" << std::endl;
    return -1;
  }
  if (program == NULL) {
    std::cerr << "Failed to create program" << std::endl;
    clReleaseContext(context);
    clReleaseCommandQueue(command_queue);
    return -1;
  }

  status = clBuildProgram(program, 0, NULL, OCLFLAGS, NULL, NULL);
  if (status != CL_SUCCESS) {
    unsigned size_log = 16384;
    char build_log[size_log];
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, size_log,
                          build_log, NULL);
    std::cerr << "Error in program: " << std::endl;
    std::cerr << build_log << std::endl;
    clReleaseProgram(program);
    return -1;
  }

  // Create kernel
  cl_kernel kernel = 0;
  kernel = clCreateKernel(program, (char*)argv[2], NULL);
  if (kernel == NULL) {
    std::cerr << "Failed to create kernel" << std::endl;
    clReleaseContext(context);
    clReleaseCommandQueue(command_queue);
    clReleaseProgram(program);
    return -1;
  }

  // Create memory Object
  route R(read_route(argv[3]));
  uint SIZE = R.size();

  uint B[SIZE];
  point mean;
  mean.s0 = 0;
  mean.s1 = 0;

  for (uint i = 0; i < SIZE; i++) {
    mean = mean + R[i];
  }
  mean = mean / ((double)SIZE);

  std::vector<cl_mem> Buffers;

  Buffers.push_back(clCreateBuffer(context,
                                   CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                   sizeof(point) * SIZE, &R[0], NULL));
  Buffers.push_back(clCreateBuffer(context,
                                   CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                   sizeof(point), &mean, NULL));
  Buffers.push_back(clCreateBuffer(context, CL_MEM_READ_WRITE,
                                   sizeof(uint) * SIZE, NULL, NULL));
  Buffers.push_back(clCreateBuffer(context,
                                   CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                   sizeof(uint), &SIZE, NULL));

  for (uint i = 0; i < Buffers.size(); i++) {
    if (Buffers[i] == NULL) {
      std::cerr << "Error creating memory objects" << std::endl;
      clReleaseContext(context);
      clReleaseCommandQueue(command_queue);
      clReleaseProgram(program);
      for (uint j = 0; j < Buffers.size(); j++) {
        if (Buffers[j] != NULL) {
          clReleaseMemObject(Buffers[j]);
        }
      }
      return -1;
    }
  }

  // Set Arguments
  status = CL_SUCCESS;
  for (uint i = 0; i < Buffers.size(); i++) {
    status |= clSetKernelArg(kernel, i, sizeof(cl_mem), &Buffers[i]);
  }

  if (status != CL_SUCCESS) {
    std::cerr << "Error setting kernel arguments" << std::endl;
    clReleaseContext(context);
    clReleaseCommandQueue(command_queue);
    clReleaseProgram(program);
    for (uint j = 0; j < Buffers.size(); j++) {
      if (Buffers[j] != NULL) {
        clReleaseMemObject(Buffers[j]);
      }
    }
    return -1;
  }

  size_t global_work_size[1] = {SIZE};
  size_t local_work_size[1] = {1};

  status =
      clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size,
                             local_work_size, 0, NULL, NULL);

  // Error Enqueue
  if (status != CL_SUCCESS) {
    std::cerr << "Error queuing kernel for execution." << std::endl;
    clReleaseContext(context);
    clReleaseCommandQueue(command_queue);
    clReleaseProgram(program);
    for (uint j = 0; j < Buffers.size(); j++) {
      if (Buffers[j] != NULL) {
        clReleaseMemObject(Buffers[j]);
      }
    }
    return -1;
  }

  // Read Buffer output
  status = clEnqueueReadBuffer(command_queue, Buffers[2], CL_TRUE, 0,
                               SIZE * sizeof(uint), &B[0], 0, NULL, NULL);
  status |= clEnqueueReadBuffer(command_queue, Buffers[1], CL_TRUE, 0,
                                sizeof(point), &mean, 0, NULL, NULL);

  if (status != CL_SUCCESS) {
    std::cerr << "Failed to read buffer" << std::endl;
    clReleaseContext(context);
    clReleaseCommandQueue(command_queue);
    clReleaseProgram(program);
    for (uint j = 0; j < Buffers.size(); j++) {
      if (Buffers[j] != NULL) {
        clReleaseMemObject(Buffers[j]);
      }
    }
    return -1;
  }

  for (uint i = 0; i < SIZE; i++) {
    std::cout << R[i] << "| " << B[i] << std::endl;
  }

  route test;
  for ( uint aux=B[0], i=B[B[0]]; aux != i; i=B[i] ) {
   test.push_back(R[i]);
   std::cout << R[i] << " ";
  }
  test.push_back(R[B[0]]);
  std::cout << R[B[0]] << std::endl;
 
  std::cout << mean << std::endl;

  clReleaseContext(context);
  clReleaseCommandQueue(command_queue);
  clReleaseProgram(program);
  for (uint j = 0; j < Buffers.size(); j++) {
    if (Buffers[j] != NULL) {
      clReleaseMemObject(Buffers[j]);
    }
  }
  return 0;
}
