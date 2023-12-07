from numpy import random
import numpy as np
import pandas as pd

def gaussianGenerator(gaussiansNumber, dimensions):
    gaussians = []

    while(len(gaussians) < gaussiansNumber):

        mu = np.random.randint(-10000, 10000, dimensions)
        A = np.random.rand(dimensions, dimensions)
        cov = np.dot(A, A.transpose())

        gaussians.append({"mu": mu, "cov": cov})

    return gaussians

def main():

    print("How many gaussians? ")
    gaussiansNumber = int(input())

    print("How many dimensions? ")
    dimensions = int(input())

    gaussians = gaussianGenerator(gaussiansNumber, dimensions)

    print("How many samples per gaussian? ")
    samples = input()

    N = int(samples) * gaussiansNumber

    path = "./N" + str(N) + "_K" + str(gaussiansNumber) + "_D" + str(dimensions) + ".csv"

    for gaussian in gaussians:        
        pd.DataFrame(random.multivariate_normal(gaussian["mu"], gaussian["cov"], int(samples))).to_csv(path, index=False, header=False, mode="a")

main()