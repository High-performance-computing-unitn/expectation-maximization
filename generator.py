from numpy import random
import numpy as np
import pandas as pd

def gaussianGenerator(gaussiansNumber, dimensions):
    gaussians = []

    while(len(gaussians) < gaussiansNumber):

        mu = np.random.randint(-1e5, 1e5, dimensions)
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

    print("Which dataset? (s // m // l)")
    datasetSize = input()

    match datasetSize:
        case "s":
            samples = 200
        case "m":
            samples = 10000
        case "l":
            samples = 5000000
        case _:
            print("Invalid value")   

    for gaussian in gaussians:        
        pd.DataFrame(random.multivariate_normal( gaussian["mu"], gaussian["cov"], samples)).to_csv("data.csv", index=False, header=False, mode="a")

main()