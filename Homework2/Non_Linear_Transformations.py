import numpy as np
from numpy.random import default_rng


N = 1000


def func(arr):
    return np.sign((arr[:, 1] ** 2) + (arr[:, 2] ** 2) - 0.6)


def transform(X):
    return np.array([1, X[1], X[2], X[1] * X[2], X[1] ** 2, X[2] ** 2])


def prob_8():
    Einavg_total = 0
    for _ in range(1000):
        X = np.random.uniform(-1, 1, (N, 3))
        X[:, 0] = 1
        Y = func(X)
        rng = default_rng()
        indices = rng.choice(N, int(0.1 * N), replace=False)
        for index in indices:
            Y[index] *= -1
        w = np.linalg.solve(X.T@X, X.T@Y)
        Einavg = np.sum(np.sign(X@w) != Y)/N
        Einavg_total += Einavg
    print(f'The total average of the insample error is {Einavg_total/1000}')
    # It comes out to be really close to 0.5


def prob_9():
    ans = np.zeros(6)
    for _ in range(10):
        X = np.random.uniform(-1, 1, (N, 3))
        X[:, 0] = 1
        Y = func(X)
        rng = default_rng()
        indices = rng.choice(N, int(0.1 * N), replace=False)
        for index in indices:
            Y[index] *= -1
        Z = np.apply_along_axis(transform, 1, X)
        '''
        Z = np.zeros((X.shape[0], 6))
        Z[:, 0] = 1.0
        Z[:, 1] = X[:, 1]
        Z[:, 2] = X[:, 2]
        Z[:, 3] = X[:, 1] * X[:, 2]
        Z[:, 4] = X[:, 1]**2
        Z[:, 5] = X[:, 2]**2
        '''
        w = np.linalg.solve(Z.T@Z, Z.T@Y)
        ans += w
    return ans/10


def prob_10():
    EoutTotal = 0
    for _ in range(1000):
        X = np.random.uniform(-1, 1, (N, 3))
        X[:, 0] = 1
        Y = func(X)
        rng = default_rng()
        indices = rng.choice(N, int(0.1 * N), replace=False)
        for index in indices:
            Y[index] *= -1
        Z = np.apply_along_axis(transform, 1, X)
        w = np.linalg.solve(Z.T@Z, Z.T@Y)
        X_test = np.random.uniform(-1, 1, (N, 3))
        X_test[:, 0] = 1
        Y_test = func(X_test)
        rng = default_rng()
        indices = rng.choice(N, int(0.1 * N), replace=False)
        for index in indices:
            Y_test[index] *= -1
        Z_test = np.apply_along_axis(transform, 1, X_test)
        EoutTotal += np.sum(np.sign(Z_test@w) != Y_test)/N
    print(f"EoutAverage = {EoutTotal/1000}")
    # The answer obtained is 0.13 which is closest to option b - 0.1


if __name__ == '__main__':
    prob_10()
