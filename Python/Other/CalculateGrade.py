def mean(values):
    return sum(values)*1.0/len(values)

def standev (values):
    length = len(values)
    m = mean(values)
    total_sum = 0
    for i in range(length):
        total_sum += (values[i]-m)**2
    under_root = total_sum*1.0/length
    return under_root**0.5

##x = [1, 2, 4, 1, 2, 42, 12]
##stan_dev = standev(x)
##print(stan_dev)
