from pybrain.auxiliary import kmeans as pybrain_kmeans

def multiply(a,b):
    print "Will compute", a, "times", b
    c = 0
    for i in range(0, a):
        c = c + b
    return c

def mlkmeans(a,b):
    # Where a is an array of values and b is the number of clusters
    # return pybrain_kmeans.kmeanspp(a, b)
    return 0

