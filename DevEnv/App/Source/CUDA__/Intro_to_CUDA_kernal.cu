// My Header files
#include"cuda_functions.h"

// C & C++ std files.
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<memory.h>
#include<ctime>


// CUDA headers
#include<cuda_runtime.h>
#include<cuda/cmath>
#include <device_launch_parameters.h>


// CUDA Kernel function 

__global__ void Vector_Addition(float* A, float* B, float* C, int VectorLenght)
{
	// calculate which element this thread is responsible for computing
	int Work_index = threadIdx.x + blockDim.x * blockIdx.x;

	if (Work_index < VectorLenght)
	{
		// Perform computation
		C[Work_index] = A[Work_index] + B[Work_index];
	}
};

void initArray(float* A, int length)
{
    std::srand(std::time({}));
    for (int i = 0; i < length; i++)
    {
        A[i] = rand() / (float)RAND_MAX;
    }
}

void serialVecAdd(float* A, float* B, float* C, int length)
{
    for (int i = 0; i < length; i++)
    {
        C[i] = A[i] + B[i];
    }
}

bool vectorApproximatelyEqual(float* A, float* B, int length, float epsilon = 0.00001)
{
    for (int i = 0; i < length; i++)
    {
        if (fabs(A[i] - B[i]) > epsilon)
        {
            printf("Index %d mismatch: %f != %f", i, A[i], B[i]);
            return false;
        }
    }
    return true;
}

// Allocation of memory by 2 methods either by Unified Memory Or Explicit Memory management 

// Unified Memory 
 
void Unified_Memory_Example(int UM_Vector_Lenght)
{
    // Pointers to memory vectors
    float* A = nullptr;
    float* B = nullptr;
    float* C = nullptr;
    float* comparisonResult = (float*)malloc(UM_Vector_Lenght * sizeof(float));

    // Use unified memory to allocate buffers
    cudaMallocManaged(&A, UM_Vector_Lenght * sizeof(float));
    cudaMallocManaged(&B, UM_Vector_Lenght * sizeof(float));
    cudaMallocManaged(&C, UM_Vector_Lenght * sizeof(float));

    // Initialize vectors on the host
    initArray(A, UM_Vector_Lenght);
    initArray(B, UM_Vector_Lenght);

    // Launch the kernel. Unified memory will make sure A, B, and C are
    // accessible to the GPU
    int threads = 256;
    int blocks = cuda::ceil_div(UM_Vector_Lenght, threads);
    
    Vector_Addition << <blocks, threads >> > (A, B, C, UM_Vector_Lenght);
    // Wait for the kernel to complete execution
    cudaDeviceSynchronize();

    // Perform computation serially on CPU for comparison
    serialVecAdd(A, B, comparisonResult, UM_Vector_Lenght);

    // Confirm that CPU and GPU got the same answer
    if (vectorApproximatelyEqual(C, comparisonResult, UM_Vector_Lenght))
    {
        printf("Unified Memory: CPU and GPU answers match\n");
    }
    else
    {
        printf("Unified Memory: Error - CPU and GPU answers do not match\n");
    }

    // Clean Up
    cudaFree(A);
    cudaFree(B);
    cudaFree(C);
    free(comparisonResult);

};

// Explicit Memory management 

void Explicit_Memory_Example(int EM_Vector_lenght)
{
    float* A = nullptr;
    float* B = nullptr;
    float* C = nullptr;
    float* comparisonResult = (float*)malloc(EM_Vector_lenght * sizeof(float));

    // Pointers for device memory
    float* devA = nullptr;
    float* devB = nullptr;
    float* devC = nullptr;

    //Allocate Host Memory using cudaMallocHost API. This is best practice
    // when buffers will be used for copies between CPU and GPU memory
    cudaMallocHost(&A, EM_Vector_lenght * sizeof(float));
    cudaMallocHost(&B, EM_Vector_lenght * sizeof(float));
    cudaMallocHost(&C, EM_Vector_lenght * sizeof(float));

    // Initialize vectors on the host
    initArray(A, EM_Vector_lenght);
    initArray(B, EM_Vector_lenght);

    // start-allocate-and-copy
    // Allocate memory on the GPU
    cudaMalloc(&devA, EM_Vector_lenght * sizeof(float));
    cudaMalloc(&devB, EM_Vector_lenght * sizeof(float));
    cudaMalloc(&devC, EM_Vector_lenght * sizeof(float));

    // Copy data to the GPU
    cudaMemcpy(devA, A, EM_Vector_lenght * sizeof(float), cudaMemcpyDefault);
    cudaMemcpy(devB, B, EM_Vector_lenght * sizeof(float), cudaMemcpyDefault);
    cudaMemset(devC, 0, EM_Vector_lenght * sizeof(float));
    // end-allocate-and-copy

    // Launch the kernel
    int threads = 256;
    int blocks = cuda::ceil_div(EM_Vector_lenght, threads);

    Vector_Addition<< <blocks, threads >> > (devA, devB, devC, EM_Vector_lenght);
    // wait for kernel execution to complete
    cudaDeviceSynchronize();

    // Copy results back to host
    cudaMemcpy(C, devC, EM_Vector_lenght * sizeof(float), cudaMemcpyDefault);

    // Perform computation serially on CPU for comparison
    serialVecAdd(A, B, comparisonResult, EM_Vector_lenght);

    // Confirm that CPU and GPU got the same answer
    if (vectorApproximatelyEqual(C, comparisonResult, EM_Vector_lenght))
    {
        printf("Explicit Memory: CPU and GPU answers match\n");
    }
    else
    {
        printf("Explicit Memory: Error - CPU and GPU answers to not match\n");
    }

    // clean up
    cudaFree(devA);
    cudaFree(devB);
    cudaFree(devC);
    cudaFreeHost(A);
    cudaFreeHost(B);
    cudaFreeHost(C);
    free(comparisonResult);
};


// My Own Code

using namespace std;

__CUDA_INTRO__ void Intro(int Vector_lenght)
{
    Unified_Memory_Example(Vector_lenght);

    Explicit_Memory_Example(Vector_lenght);
};
