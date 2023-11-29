from scipy.optimize import curve_fit
import matplotlib.pyplot as plt
import numpy as np

def firstLetterUppercase(input_str):
    return input_str[0].upper() + input_str[1:] if input_str else input_str

def pretty_params(function, coefficients):
    formatted_str = ""

    if function == quadratic_function:
        formatted_str = f"{coefficients[0]:.2e}n² + {coefficients[1]:.2e}n + {coefficients[2]:.2e}"
    elif function == n_log_n_function:
        formatted_str = f"{coefficients[0]:.2e}n log(n) + {coefficients[1]:.2e}"
    elif function == linear_function:
        formatted_str = f"{coefficients[0]:.2e}n + {coefficients[1]:.2e}"
    elif function == n_squared_log_n_function:
        formatted_str = f"{coefficients[0]:.1e}n²log(n) + {coefficients[1]:.1e}n² + {coefficients[2]:.1e}n"
    else:
        formatted_str = 'Fitted Curve'

    return formatted_str

def fit_and_plot(observed_means, observed_stdev, fitting_function, algorithm, case):
    plt.style.use('default')
    plt.rcParams['font.family'] = 'serif'
    plt.rcParams['axes.facecolor'] = 'white'

    n_values = np.array([item[0] for item in observed_means])
    t_values = np.array([item[1] for item in observed_means])
    stdev_values = np.array([item[1] for item in observed_stdev])

    # Use curve_fit to fit the specified function to the data
    params, covariance = curve_fit(fitting_function, n_values, t_values)
    fitted_params = tuple(params)
    fit_curve = fitting_function(n_values, *fitted_params)

    # Flatten the arrays for compatibility with Matplotlib
    n_values_flat = n_values.flatten()
    t_values_flat = t_values.flatten()
    stdev_values_flat = stdev_values.flatten()

    # Plotting the original data and the fitted curve
    plt.errorbar(n_values_flat, t_values_flat, yerr=stdev_values_flat, fmt='o', color='blue', label='Observed data')
    plt.errorbar(n_values_flat, t_values_flat, yerr=stdev_values_flat, fmt='none', ecolor='gray', elinewidth=1, capsize=5)
    plt.plot(n_values_flat, fit_curve, linestyle='--', color='r',
             label=pretty_params(fitting_function, fitted_params))

    # Random is average
    if case == 'random':
        case = 'average'

    # Adding labels and title
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title(firstLetterUppercase(algorithm)
              + ', ' + case.capitalize() + ' Case,'
              + ' with Curve Fitting')
    # Show the legend
    plt.legend()

    # Save the plot to a file
    plt.savefig('tn_plotFit_'
                + algorithm.lower()
                + '_' + case
                + '.png',
                bbox_inches='tight')
    plt.close()

def fit_and_plot_combined(algorithms, res_mean_dict, res_sd_dict, fitting_functions):
    plt.style.use('default')
    plt.rcParams['font.family'] = 'serif'
    plt.rcParams['axes.facecolor'] = 'white'

    # Initialize an empty plot
    plt.figure()

    for algorithm in algorithms:
        n_values = np.array([item[0] for item in res_mean_dict[algorithm]])
        t_values = np.array([item[1] for item in res_mean_dict[algorithm]])
        stdev_values = np.array([item[1] for item in res_sd_dict[algorithm]])

        # Use curve_fit to fit the specified function to the data
        fitting_function = fitting_functions[algorithm]
        params, covariance = curve_fit(fitting_function, n_values, t_values)
        fitted_params = tuple(params)
        fit_curve = fitting_function(n_values, *fitted_params)

        # Flatten the arrays for compatibility with Matplotlib
        n_values_flat = n_values.flatten()
        t_values_flat = t_values.flatten()
        stdev_values_flat = stdev_values.flatten()

        # Plotting the original data and the fitted curve for each algorithm
        plt.errorbar(n_values_flat, t_values_flat, yerr=stdev_values_flat, fmt='o', label=f'{algorithm} - Observed data')
        plt.errorbar(n_values_flat, t_values_flat, yerr=stdev_values_flat, fmt='none', ecolor='gray', elinewidth=1, capsize=5)
        plt.plot(n_values_flat, fit_curve, linestyle='--', label=f'{algorithm} - {pretty_params(fitting_function, fitted_params)}')

    # Adding labels and title
    plt.xlabel('n')
    plt.ylabel('T(n)')
    plt.title(f'Combined Plot with Curve Fitting')

    # Show the legend
    plt.legend()

    # Save the plot to a file
    plt.savefig('tn_combined_plot.png', bbox_inches='tight')
    plt.close()

def quadratic_function(n, a, b, c):
    return a*n**2 + b*n + c

def n_log_n_function(n, a, b):
    return a*n*np.log(n) + b

def linear_function(n, a, b):
    return a * n + b

def n_squared_log_n_function(n, a, b, c):
    return (a * n**2 * np.log(n)) + (b * n**2) + (c * n)