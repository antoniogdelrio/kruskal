import subprocess
import resource
import sys
import os
import statistics
import matplotlib.pyplot as plt

# Parameters
algorithms = [
        'optimized',
        'unoptmized']
res_mean = {algorithm: [] for algorithm in algorithms}
res_sd = {algorithm: [] for algorithm in algorithms}

def compile():
    cmd = "gcc -O0 kruskal.c -o kruskal"
    subprocess.run(cmd.split())

def set_stack_limit(new_gb_limit=10.0):
    new_bytes_limit = int(new_gb_limit * 1024 * 1024 * 1024)  # Convert GB to bytes
    resource.setrlimit(
            resource.RLIMIT_STACK,
            (new_bytes_limit, resource.RLIM_INFINITY))

    current_stack_limit_bytes, _ = resource.getrlimit(resource.RLIMIT_STACK)
    current_stack_limit_gb = current_stack_limit_bytes / (1024 * 1024 * 1024)
    print(f"Stack size limit: {current_stack_limit_gb} GB")

def grab(iterations, algorithm):
    print(algorithm
          + "\t n=" + str(iterations), end='\t')
    cmd = "./bin/kruskal " + str(iterations) + " " + algorithm
    output = subprocess.run(cmd.split(), 
                            capture_output=True, text=True).stdout
    output = output.split(', ')[1:-1]
    output = [float(string) for string in output]
    mean = statistics.mean(output)
    sd = statistics.stdev(output)
    print('T(n)={:.4f}\tSD={:.4f}'.format(mean, sd))
    return mean, sd

def get_iters():
    iterations = 200
    step=int(iterations/10)
    return iterations, step

def main():
    compile()
    set_stack_limit(10.0)

    for algorithm in algorithms:
        iterations, step = get_iters()
        for n in range(step, iterations, step):
            mean, sd = grab(n, algorithm)
            res_mean[algorithm].append((n, mean))
            res_sd[algorithm].append((n, sd))

if __name__ == "__main__":
    main()
