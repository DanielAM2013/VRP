#include <vector_gpu.hpp>

int main(int argc, char** argv) {
  cl_context context = 0;
  cl_command_queue commandQueue = 0;
  cl_program program = 0;
  cl_device_id device = 0;
  cl_kernel kernel = 0;
  std::vector<cl_mem> memObjects;
  cl_int errNum;

  // Create an OpenCL context on first available platform
  context = CreateContext();
  if (context == NULL) {
    std::cerr << "Failed to create OpenCL context." << std::endl;
    return 1;
  }
  // Create a command-queue on the first device available
  // on the created context
  commandQueue = CreateCommandQueue(context, &device);
  if (commandQueue == NULL) {
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
  }

  program = CreateProgramFromBinary(context, device, (char*)argv[1]);
  if (program == NULL) {
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
  }

  // Create OpenCL kernel
  kernel = clCreateKernel(program, (char*)argv[2], NULL);
  if (kernel == NULL) {
    std::cerr << "Failed to create kernel" << std::endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
  }

  // Create memory objects that will be used as arguments to
  // kernel.  First create host memory arrays that will be
  // used to store the arguments to the kernel

  route R(read_route(argv[3]));
  int ARRAY_SIZE = R.size();

  int k = 3;
  route test(ARRAY_SIZE);
  route result(ARRAY_SIZE);
  std::vector<int> index(ARRAY_SIZE);
  double aux = 0;
  for (double i = 0.; i < ARRAY_SIZE; i++) {
    test[i] = R[i];
    aux += test[i];
  }
  aux /= k;

  memObjects.push_back(
      clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                     sizeof(TYPE_IN_USE) * ARRAY_SIZE, &test[0], NULL));
  memObjects.push_back(clCreateBuffer(context,
                                      CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                      sizeof(TYPE_IN_USE), &aux, NULL));
  memObjects.push_back(clCreateBuffer(context, CL_MEM_READ_WRITE,
                                      sizeof(TYPE_IN_USE) * ARRAY_SIZE, NULL,
                                      NULL));
  memObjects.push_back(clCreateBuffer(context,
                                      CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                      sizeof(uint), &ARRAY_SIZE, NULL));
  memObjects.push_back(clCreateBuffer(context, CL_MEM_READ_WRITE,
                                      sizeof(int) * ARRAY_SIZE, NULL, NULL));

  for (uint i = 0; i < memObjects.size(); i++)
    if (memObjects[i] == NULL) {
      Cleanup(context, commandQueue, program, kernel, memObjects);
      std::cerr << "Error creating memory objects." << std::endl;
      return false;
    }

  // Set the kernel arguments (result, a, b)
  errNum = CL_SUCCESS;
  for (uint i = 0; i < memObjects.size(); i++)
    errNum |= clSetKernelArg(kernel, i, sizeof(cl_mem), &memObjects[i]);

  if (errNum != CL_SUCCESS) {
    std::cerr << "Error setting kernel arguments." << std::endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
  }

  size_t globalWorkSize[1] = {ARRAY_SIZE};
  size_t localWorkSize[1] = {1};

  // Queue the kernel up for execution across the array
  errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalWorkSize,
                                  localWorkSize, 0, NULL, NULL);
  // error
  if (errNum != CL_SUCCESS) {
    std::cerr << "Error queuing kernel for execution." << std::endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
  }

  // Read the output buffer back to the Host
  errNum = clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE, 0,
                               ARRAY_SIZE * sizeof(TYPE_IN_USE), &result[0], 0,
                               NULL, NULL);
  errNum |=
      clEnqueueReadBuffer(commandQueue, memObjects[4], CL_TRUE, 0,
                          ARRAY_SIZE * sizeof(int), &index[0], 0, NULL, NULL);
  // error
  if (errNum != CL_SUCCESS) {
    std::cerr << "Error reading result buffer." << std::endl;
    Cleanup(context, commandQueue, program, kernel, memObjects);
    return 1;
  }

  // Output the result buffer
  for (int i = 0; i < ARRAY_SIZE; i++) {
    std::cout << test[i] << " " << result[i] << " " << index[i] << " " << i
              << std::endl;
  }

  Cleanup(context, commandQueue, program, kernel, memObjects);
  return 0;
}
