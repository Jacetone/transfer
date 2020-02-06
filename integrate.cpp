#include <stdio.h>
#include <thread>
#include <vector>
#include <iostream>
#include <cmath>

float f(float x){ //Definite Integral to be evaluated
	//float defInt = 1/(1+x*x);
	return x == 0 ? 1 : sin(x)/x;
}

/*float integrate(float a, float b, int n){//, int n_threads){ //Trapezoidal Rule of Integration
	float integral, sum = 0;
	float x[n+1], y[n+1];
	float h = (b - a)/n; //Obtain subinterval length
	for(int i = 1; i <= n+1; i++){
		x[i] = a + i * h; //Evaluate both x0->xn and y0->yn
		y[i] = f(x[i]);
	}
	for(int i = 1; i < n; i++){
		sum += h*y[i]; //Evaluate h*(y1+...+yn-1)
	}
	integral = h/2.0 * (y[0] + y[n]) + sum;
	return integral;
}*/

void integrate2(double start, double sub_length, int n, double &sum){
	double current = start;
	for(int i = 0; i < n; i++){
		sum += f(current);
		current += sub_length;
	}
}

//void spawnThread(double current, double sub_length, int ops_PT){
	
//}

int main(int argc, char* argv[]){
	if(argc > 5) throw ("Please enter 4 arguments.");
	
	int n = atoi(argv[3]), n_threads = atoi(argv[4]);
	double a = atof(argv[1]), b = atof(argv[2]);
	double sub_length = (b - a)/n;
	double current = a;
	int opsPerThread = n/n_threads, remainingOps = n % n_threads;
	const unsigned int num_cpus = std::thread::hardware_concurrency(); // The total number of CPUs on the system. Will be 24 for OpenHPC. 
	std::vector<std::thread> threads;
	double *sums = new double[n_threads];
	for (int i = 0; i < n_threads; ++i)
	{	
		int extra_op = remainingOps > 0;
    		std::thread temp(integrate2, current, sub_length, opsPerThread+extra_op, std::ref(sums[i])); //Or pthread
    		threads.push_back(std::move(temp));
		current += sub_length*(opsPerThread+extra_op);
		remainingOps -= extra_op;
		
    		cpu_set_t cpuset;
    		CPU_ZERO(&cpuset);
    		CPU_SET( (i % num_cpus ), &cpuset);

     		int rc = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpuset);
     		if (rc != 0){
	    		std::cerr << "Error setting affinity" << '\n';
    		}
	}
	double totalSum = 0;
	for(int i = 0; i < n_threads; i++) {
		threads[i].join();
		totalSum += sums[i];
	}
	double integral = (b - a) * totalSum / n;
	std::cout << integral << std::endl;
	delete[] sums;
}
