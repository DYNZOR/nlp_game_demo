import numpy as np
from random import sample
import pickle

# Split data into train (70%), test (15%) and valid(15%) sets
def split_dataset(x, y, ratio = [0.7, 0.15, 0.15] ):
    # number of sequences
    data_len = len(x)
    lens = [ int(data_len*item) for item in ratio ]

    trainX, trainY = x[:lens[0]], y[:lens[0]]
    testX, testY = x[lens[0]:lens[0]+lens[1]], y[lens[0]:lens[0]+lens[1]]
    validX, validY = x[-lens[-1]:], y[-lens[-1]:]

    return (trainX,trainY), (testX,testY), (validX,validY)


# Generate batches of sequences
def batch_gen(x, y, batch_size):
    while True:
        for i in range(0, len(x), batch_size):
            if (i+1)*batch_size < len(x):
                yield x[i : (i+1)*batch_size ].T, y[i : (i+1)*batch_size ].T

# Generate random sample batches of sequences.
def rand_batch_gen(x, y, batch_size):
    while True:
        sample_idx = sample(list(np.arange(len(x))), batch_size)
        yield x[sample_idx].T, y[sample_idx].T

# Obtain the metadata
def get_metadata():
    with open('datasets/twitter/metadata.pkl', 'rb') as f:
        metadata = pickle.load(f)
    return metadata.get('idx2w'), metadata.get('w2idx'), metadata.get('limit')