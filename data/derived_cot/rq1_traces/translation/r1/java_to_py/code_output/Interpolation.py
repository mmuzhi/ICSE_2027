def interpolate1d(x, y, xInterp):
    yInterp = []
    for xi in xInterp:
        for i in range(len(x) - 1):
            if x[i] <= xi <= x[i + 1]:
                yi_val = y[i] + (y[i + 1] - y[i]) * (xi - x[i]) / (x[i + 1] - x[i])
                yInterp.append(yi_val)
                break
    return yInterp

def interpolate2d(x, y, z, xInterp, yInterp):
    zInterp = []
    for k in range(len(xInterp)):
        xi = xInterp[k]
        yi_val = yInterp[k]
        for i in range(len(x) - 1):
            if x[i] <= xi <= x[i + 1]:
                for j in range(len(y) - 1):
                    if y[j] <= yi_val <= y[j + 1]:
                        z00 = z[i][j]
                        z01 = z[i][j + 1]
                        z10 = z[i + 1][j]
                        z11 = z[i + 1][j + 1]
                        numerator = (z00 * (x[i + 1] - xi) * (y[j + 1] - yi_val) +
                                     z10 * (xi - x[i]) * (y[j + 1] - yi_val) +
                                     z01 * (x[i + 1] - xi) * (yi_val - y[j]) +
                                     z11 * (xi - x[i]) * (yi_val - y[j]))
                        denominator = (x[i + 1] - x[i]) * (y[j + 1] - y[j])
                        zi = numerator / denominator
                        zInterp.append(zi)
                        break
                break
    return zInterp