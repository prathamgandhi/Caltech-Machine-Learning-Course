import numpy as np


def generate_line():
    x1 = 2 * np.random.uniform() - 1
    y1 = 2 * np.random.uniform() - 1
    x2 = 2 * np.random.uniform() - 1
    y2 = 2 * np.random.uniform() - 1
    a = y1 - y2
    b = x2 - x1
    c = ((x1 * y2) - (y1 * x2))
    return np.array([a, b, c])


def main():
    N = 100
    EinTotal = 0
    EoutTotal = 0
    for v in range(1000):
        line = generate_line()
        X = np.random.random((N, 3))
        X[:, :2] = X[:, :2, ] * 2-1
        X[:, 2] = 1
        Y = np.sign(X@line)
        w = np.linalg.solve(X.T@X, X.T@Y)
        Einavg = np.sum(np.sign(X@w) != Y)/N
        EinTotal += Einavg
        OutSample = np.random.random((1000, 3))
        OutSample[:, :2] = OutSample[:, :2] * 2 - 1
        OutSample[:, 2] = 1
        Y_out = np.sign(OutSample@line)
        Eoutavg = np.sum(np.sign(OutSample@w) != Y_out)/1000
        EoutTotal += Eoutavg
    print(f'Ein average = {EinTotal/1000}')
    print(f'Eout average = {EoutTotal/1000}')


if __name__ == '__main__':
    main()
