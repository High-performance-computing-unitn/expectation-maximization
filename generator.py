from numpy import random
import matplotlib.pyplot as plt

f = open("data.txt", "a")

def gaussianGenerator(gaussiansNumber):
    gaussians = []

    while(len(gaussians) < int(gaussiansNumber)):

        mu = round(random.uniform(-1000, 1000), 2)
        gaussian = {"mu": mu, "sigma": mu/10}
        gaussians.append(gaussian)

    print(gaussians)
    return gaussians


def pointGenerator(dataset, mu, sigma):
    points = random.normal(mu, sigma, (dataset["samples"], dataset["dimensions"]))
    for point in points:
        for p in point:
            f.write(str(p) + " ")
        f.write("\n")
    return points

def main():

    print("How many gaussians? ")
    gaussiansNumber = input()

    gaussians = gaussianGenerator(gaussiansNumber)

    print("Which dataset? (s // m // l)")
    datasetSize = input()

    match datasetSize:
        case "s":
            dataset = {"samples": 200, "dimensions": 1}
        case "m":
            dataset = {"samples": 2000, "dimensions": 10}
        case "l":
            dataset = {"samples": 1000000, "dimensions": 100}
        case _:
            print("Invalid value")    


    for gaussian in gaussians:
        #data = pointGenerator(gaussian["mu"], gaussian["sigma"])
        pointGenerator(dataset, gaussian["mu"], gaussian["sigma"])
        #plt.hist(data, 30)
        #plt.show()

main()
f.close()