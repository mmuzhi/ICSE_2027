#include <vector>
#include <cmath>

class Interpolation {
public:
    static std::vector<double> interpolate_1d(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& x_interp) {
        std::vector<double> y_interp;
        for (double xi : x_interp) {
            bool found = false;
            for (int i = 0; i < x.size() - 1; ++i) {
                if (x[i] <= xi && xi <= x[i+1]) {
                    double yi = y[i] + (y[i+1] - y[i]) * (xi - x[i]) / (x[i+1] - x[i]);
                    y_interp.push_back(yi);
                    found = true;
                    break;
                }
            }
            if (!found) {
                y_interp.push_back(std::numeric_limits<double>::NaN());
            }
        }
        return y_interp;
    }

    static std::vector<double> interpolate_2d(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::vector<double>>& z, const std::vector<double>& x_interp, const std::vector<double>& y_interp) {
        std::vector<double> z_interp;
        for (size_t i = 0; i < x_interp.size(); ++i) {
            double xi = x_interp[i];
            double yi = y_interp[i];
            bool found_x = false;
            bool found_y = false;

            for (int idx = 0; idx < x.size() - 1; ++idx) {
                if (x[idx] <= xi && xi <= x[idx+1]) {
                    found_x = true;
                    for (int jdx = 0; jdx < y.size() - 1; ++jdx) {
                        if (y[jdx] <= yi && yi <= y[jdx+1]) {
                            found_y = true;
                            double z00 = z[idx][jdx];
                            double z01 = z[idx][jdx+1];
                            double z10 = z[idx+1][jdx];
                            double z11 = z[idx+1][jdx+1];
                            double denom = (x[idx+1] - x[idx]) * (y[jdx+1] - y[jdx]);
                            double zi = (z00 * (x[idx+1] - xi) * (y[jdx+1] - yi) +
                                        z10 * (xi - x[idx]) * (y[jdx+1] - yi) +
                                        z01 * (x[idx+1] - xi) * (yi - y[jdx]) +
                                        z11 * (xi - x[idx]) * (yi - y[jdx])) / denom;
                            z_interp.push_back(zi);
                            break;
                        }
                    }
                    if (found_y) break;
                }
            }
            if (!found_x || !found_y) {
                z_interp.push_back(std::numeric_limits<double>::NaN());
            }
        }
        return z_interp;
    }
};