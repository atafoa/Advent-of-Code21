import numpy as np


def day25():
    s = open('input.txt').read()
    grid = np.array(
            [[1 if a == '>' else (2 if a == 'v' else 0) for a in l]
                for l in s.splitlines()], dtype=int)
    step = 0
    movingright = movingdown = True
    rowsmod1 = list(range(1, grid.shape[0])) + [0]
    colsmod1 = list(range(1, grid.shape[1])) + [0]
    while movingright or movingdown:
        newgrid = grid.copy()
        movingright = list(zip(*((grid == 1)
                & (grid[:, colsmod1] == 0)).nonzero()))
        for n, m in movingright:
            newgrid[n, m] = 0
            newgrid[n, (m + 1) % grid.shape[1]] = 1
        movingdown = list(zip(*((newgrid == 2)
                & (newgrid[rowsmod1, :] == 0)).nonzero()))
        for n, m in movingdown:
            newgrid[n, m] = 0
            newgrid[(n + 1) % grid.shape[0], m] = 2
        step += 1
        grid = newgrid
    
    return step

if __name__ == "__main__":
    print(day25())

