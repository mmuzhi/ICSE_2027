#include <vector>

class Interpolation {
public:
    static std::vector<double> interpolate_1d(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& x_interp) {
        std::vector<double> y_interp;
        for (double xi : x_interp) {
            for (int i = 0; i < x.size() - 1; ++i) {
                if (x[i] <= xi && xi <= x[i+1]) {
                    double dx = x[i+1] - x[i];
                    double dy = y[i+1] - y[i];
                    double t = (xi - x[i]) / dx;
                    double yi_val = y[i] + dy * t;
                    y_interp.push_back(yi_val);
                    break;
                }
            }
        }
        return y_interp;
    }

    static std::vector<double> interpolate_2d(const std::vector<double>& x, const std::vector<double>& y, const std::vector<std::vector<double>>& z,
                                              const std::vector<double>& x_interp, const std::vector<double>& y_interp) {
        std::vector<double> z_interp;
        for (int idx = 0; idx < x_interp.size(); ++idx) {
            double xi = x_interp[idx];
            double yi = y_interp[idx];
            for (int i = 0; i < x.size() - 1; ++i) {
                if (x[i] <= xi && xi <= x[i+1]) {
                    for (int j = 0; j < y.size() - 1; ++j) {
                        if (y[j] <= yi && yi <= y[j+1]) {
                            double dx = x[i+1] - x[i];
                            double dy = y[j+1] - y[j];
                            double z00 = z[i][j];
                            double z01 = z[i][j+1];
                            double z10 = z[i+1][j];
                            double z11 = z[i+1][j+1];
                            double w00 = (x[i+1] - xi) * (y[j+1] - yi);
                            double w10 = (xi - x[i]) * (y[j+1] - yi);
                            double w01 = (x[i+1] - xi) * (yi - y[j]);
                            double w11 = (xi - x[i]) * (yi - y[j]);
                            double zi_val = (z00 * w00 + z10 * w10 + z01 * w01 + z11 * w11) / (dx * dy);
                            z_interp.push_back(zi_val);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        return z_interp;
    }
};