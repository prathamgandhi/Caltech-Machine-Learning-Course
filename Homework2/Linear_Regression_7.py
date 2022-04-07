import numpy as np


def generate_line():
    x1, y1 = 2 * np.random.uniform() - 1, 2 * np.random.uniform() - 1
    x2, y2 = 2 * np.random.uniform() - 1, 2 * np.random.uniform() - 1
    a = y1 - y2
    b = x2 - x1
    c = ((x1 * y2) - (y1 * x2))
    return np.array([a, b, c])


def main():
    N = 10
    k_total = 0
    for _ in range(1000):
        line = generate_line()
        X = np.random.random((N, 3))
        X[:, :2] = X[:, :2, ] * 2-1
        X[:, 2] = 1
        Y = np.sign(X@line)
        w = np.linalg.solve(X.T@X, X.T@Y)
        k = 0
        while(True):
            flag = True
            for i in range(len(X)):
                if np.sign(X[i]@w) != Y[i]:
                    w = w + Y[i]*X[i]
                    flag = False
                    break
            if flag:
                break
            k += 1
        k_total += k

    print(f'The average iteartions is  {k_total/1000}')
    # The answer comes close to 5 on average which is closest to 1, option A


if __name__ == '__main__':
    main()
