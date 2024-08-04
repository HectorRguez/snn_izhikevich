# Imports
import sys
import pandas as pd
import numpy as np

VALUES_PER_ROW = 15

# Read data file
data = pd.read_csv(str(sys.argv[1]), header=None)
data = np.array(data)
in_out_data = data[:,0:-1]
labels = data[:,-1]
n_parameters = in_out_data.shape[1]
n_data = in_out_data.shape[0]

# Write file
with open('data.c', 'w') as file:
    file.write('#include "data.h"\n')

    # DATA
    file.write('float data[] = {\n\t')
    values_per_row = 0
    idx = 0
    for row in in_out_data:
        for value in row:
            file.write(str(value))
            idx += 1
            values_per_row += 1
            if(idx != in_out_data.size):
                file.write((', '))
                if(values_per_row == VALUES_PER_ROW):
                    file.write('\n\t')
                    values_per_row = 0
    file.write('};\n')

    # N_PARAMETERS
    file.write('const int n_parameters = ')
    file.write(str(n_parameters))
    file.write(';\n')

    # N_LABELS
    values_per_row = 0
    idx = 0
    file.write('int labels[] = {\n\t')
    for label in labels:
        file.write(str(int(label)))
        idx += 1
        values_per_row += 1
        if(idx != labels.size):
                file.write((', '))
                if(values_per_row == VALUES_PER_ROW):
                    file.write('\n\t')
                    values_per_row = 0
    file.write('};\n')

    # N_DATA
    file.write('const int n_data = ')
    file.write(str(n_data))
    file.write(';\n')    