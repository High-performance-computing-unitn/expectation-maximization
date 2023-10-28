from numpy import random
import numpy as np
import pandas as pd

f = open("Data generator/GaussiansInformations.txt", "a")

def gaussianGenerator(gaussiansNumber, dimensions):
    gaussians = []

    while(len(gaussians) < gaussiansNumber):

        mu = np.random.randint(-1e5, 1e5, dimensions)
        A = np.random.rand(dimensions, dimensions)
        cov = np.dot(A, A.transpose())

        f.write("new gaussian \n Mu: " + str(mu) + "\n Cov: " + str(cov) + "\n\n")

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
            path = "Data generator/smallDataset.csv"
        case "m":
            samples = 10000
            path = "Data generator/mediumDataset.csv"
        case "l":
            samples = 5000000
            path = "Data generator/bigDataset.csv"
        case _:
            print("Invalid value")   

    for gaussian in gaussians:        
        pd.DataFrame(random.multivariate_normal(gaussian["mu"], gaussian["cov"], samples)).to_csv(path, index=False, header=False, mode="a")

main()
f.close()