#define BIN_SIZE 256
#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable
__kernel
void histogram_kernel(__global const uint* data,
 __local uchar* sharedArray,
 __global uint* binResultR,
 __global uint* binResultG,
 __global uint* binResultB)
{
 size_t localId = get_local_id(0);
 size_t globalId = get_global_id(0);
 size_t groupId = get_group_id(0);
 size_t groupSize = get_local_size(0);
 __local uchar* sharedArrayR = sharedArray;
 __local uchar* sharedArrayG = sharedArray +
 groupSize * BIN_SIZE;
 __local uchar* sharedArrayB = sharedArray + 2 * groupSize * BIN_SIZE;
 /* initialize shared array to zero */
 for(int i = 0; i < BIN_SIZE; ++i) {
  sharedArrayR[localId * BIN_SIZE + i] = 0;
  sharedArrayG[localId * BIN_SIZE + i] = 0;
  sharedArrayB[localId * BIN_SIZE + i] = 0;
 }
