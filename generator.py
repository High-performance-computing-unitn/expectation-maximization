from numpy import random
import matplotlib.pyplot as plt

f = open("data.txt", "a")

def randomFiller(dimensions):
    mu = [0] * dimensions #Mean of the N-dimensional distribution of length N
    cov = [[0 for _ in range(dimensions)] for _ in range(dimensions)] #Covariance matrix of the distribution. It must be symmetric and positive-semidefinite for proper sampling. Size NxN
   
    for i in range(dimensions):
        mu[i] = (round(random.uniform(0, 1000), 2))
        for j in range(dimensions):
            cov[i][j] = mu[i]/10

    return (mu, cov)

def gaussianGenerator(gaussiansNumber, dimensions):
    gaussians = []

    while(len(gaussians) < gaussiansNumber):

        (mu, cov) = randomFiller(dimensions)

        gaussian = {"mu": mu, "cov": cov}
        gaussians.append(gaussian)

    #print(gaussians)
    return gaussians


def pointGenerator(dimensions, mu, cov):
    points = random.multivariate_normal(mu, cov, (dimensions, dimensions, dimensions))
    #points = random.normal(mu, sigma, (dataset["samples"], dataset["dimensions"]))
    for point in points:
        for p in point:
            f.write(str(point) + " ")
        f.write("\n")
    return points

def main():

    print("How many gaussians? ")
    gaussiansNumber = input()

    print("How many dimensions? ")
    dimensions = input()

    gaussians = gaussianGenerator(int(gaussiansNumber), int(dimensions))

    print("Which dataset? (s // m // l)")
    datasetSize = input()

    for gaussian in gaussians:
        pointGenerator(int(dimensions), gaussian["mu"], gaussian["cov"])

main()
f.close()

"""   match datasetSize:
        case "s":
            dataset = {"samples": 200, "dimensions": 1}
        case "m":
            dataset = {"samples": 2000, "dimensions": 10}
        case "l":
            dataset = {"samples": 1000000, "dimensions": 100}
        case _:
            print("Invalid value")     """