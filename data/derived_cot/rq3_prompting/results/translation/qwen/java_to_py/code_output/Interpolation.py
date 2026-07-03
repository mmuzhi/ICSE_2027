def interpolate1d(x, y, xInterp):
    yInterp = []
    for xi in xInterp:
        for i in range(len(x) - 1):
            if x[i] <= xi <= x[i+1]:
                yi = y[i] + (y[i+1] - y[i]) * (xi - x[i]) / (x[i+1] - x[i])
                yInterp.append(yi)
                break
    return yInterp

def interpolate2d(x, y, z, xInterp, yInterp):
    zInterp = []
    for xi, yi in zip(xInterp, yInterp):
        found = False
        for i in range(len(x) - 1):
            if x[i] <= xi <= x[i+1]:
                for j in range(len(y) - 1):
                    if y[j] <= yi <= y[j+1]:
                        z00 = z[i][j]
                        z01 = z[i][j+1]
                        z10 = z[i+1][j]
                        z11 = z[i+1][j+1]
                        numerator = (z00 * (x[i+1] - xi) * (y[j+1] - yi) +
                                    z10 * (xi - x[i]) * (y[j+1] - yi) +
                                    z01 * (x[i+1] - xi) * (yi - y[j]) +
                                    z11 * (xi - x[i]) * (yi - y[j]))
                        denominator = (x[i+1] - x[i]) * (y[j+1] - y[j])
                        zi = numerator / denominator
                        zInterp.append(zi)
                        found = True
                        break
                if found:
                    break
    return zInterp