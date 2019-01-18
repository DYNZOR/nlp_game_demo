import nltk
import itertools
import numpy as np
import pickle

EN_WHITELIST = '0123456789abcdefghijklmnopqrstuvwxyz '  # Whitelist of characters
EN_BLACKLIST = '!"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~\'' # Blacklist of characters

# Twitter chat dataset
FILENAME = 'data/twitter_en.txt'

# Sequence word size limits
limit = {
    'maxq': 20,
    'minq': 0,
    'maxa': 20,
    'mina': 3
}

UNK = 'unk' # Unknown word token
VOCAB_SIZE = 6000 # Vocabulary size

# Opens a .txt file and returns an array of lines.
def read_lines(filename):
    return open(filename,encoding='utf-8').read().split('\n')[:-1]

# Strips a single line of all characters in the whitelist
def filter_line(line, whitelist):
    return ''.join([ch for ch in line if ch in whitelist])\


# Returns tuple of words and counts and dictionaries for indexes to words, and words to indexes.
def index_(tokenized_sentences, vocab_size):

    # Obtain the frequency of each word in the dataset.
    freq_dist = nltk.FreqDist(itertools.chain(*tokenized_sentences))

    # Return the most frequently occurring words with a limit of the size of the vocabulary.
    vocab = freq_dist.most_common(vocab_size)
    # index2word
    index2word = ['_'] + [UNK] + [x[0] for x in vocab]
    # word2index
    word2index = dict([(w, i) for i, w in enumerate(index2word)])
    return index2word, word2index, freq_dist


# Filters sequences by length
def filter_data(sequences):
    # Filtered questions and answers
    filtered_q, filtered_a = [], []
    raw_data_len = len(sequences) // 2

    for i in range(0, len(sequences), 2):
        qlen, alen = len(sequences[i].split(' ')), len(sequences[i + 1].split(' '))
        if qlen >= limit['minq'] and qlen <= limit['maxq']:
            if alen >= limit['mina'] and alen <= limit['maxa']:
                filtered_q.append(sequences[i])
                filtered_a.append(sequences[i + 1])

    # print the fraction of the original data, filtered
    filt_data_len = len(filtered_q)
    filtered = int((raw_data_len - filt_data_len) * 100 / raw_data_len)
    print(str(filtered) + '% filtered from original data')

    return filtered_q, filtered_a

# Create zero padded index arrays for each sequence
def zero_pad(qtokenized, atokenized, w2idx):
    # num of rows
    data_len = len(qtokenized)

    # numpy arrays to store indices
    idx_q = np.zeros([data_len, limit['maxq']], dtype=np.int32)
    idx_a = np.zeros([data_len, limit['maxa']], dtype=np.int32)

    for i in range(data_len):
        q_indices = pad_seq(qtokenized[i], w2idx, limit['maxq'])
        a_indices = pad_seq(atokenized[i], w2idx, limit['maxa'])

        # Add index array
        idx_q[i] = np.array(q_indices)
        idx_a[i] = np.array(a_indices)

    return idx_q, idx_a

# Obtain the index array for the given sequence.
def pad_seq(seq, lookup, maxlen):
    # Empty array
    indices = []
    #
    for word in seq:
        if word in lookup:
            indices.append(lookup[word])
        else:
            indices.append(lookup[UNK])
    return indices + [0] * (maxlen - len(seq))

# Pre-process dataset and outputs to disk
def process_data():
    print('\n>> Read lines from file')
    # Read lines in from dataset .txt file
    lines = read_lines(filename=FILENAME)

    # Change to lines to lower case
    lines = [line.lower() for line in lines]

    print('\n:: Sample of unfiltered lines...')
    print(lines[121:125])

    # Filter out unnecessary characters
    lines = [filter_line(line, EN_WHITELIST) for line in lines]
    print('\n:: Sample of filtered lines...')
    print(lines[121:125])

    # Filter out too long or too short question and answer sequences
    print('\n>> Filtering long and short sequences...')
    qlines, alines = filter_data(lines)
    print('\nq : {0} ; a : {1}'.format(qlines[60], alines[60]))
    print('\nq : {0} ; a : {1}'.format(qlines[61], alines[61]))

    # convert list of [lines of text] into list of [list of words ]
    print('\n>> Segment lines into words')
    qtokenized = [wordlist.split(' ') for wordlist in qlines]
    atokenized = [wordlist.split(' ') for wordlist in alines]

    # indexing -> idx2w, w2idx
    print('\n >> Index words')
    idx2w, w2idx, freq_dist = index_(qtokenized + atokenized, vocab_size=VOCAB_SIZE)

    print('\n >> Zero Padding')
    idx_q, idx_a = zero_pad(qtokenized, atokenized, w2idx)

    print('\n >> Save numpy arrays to disk')
    # save them
    np.save('idx_q.npy', idx_q)
    np.save('idx_a.npy', idx_a)

    # Save dictionaries, limits and word frequencies as metadata
    metadata = {
        'w2idx': w2idx,
        'idx2w': idx2w,
        'limit': limit,
        'freq_dist': freq_dist
    }

    # Use pickle to output metadata to disk
    with open('metadata.pkl', 'wb') as f:
        pickle.dump(metadata, f)

# To be called externally to retrieve the pre-processed pickled dataset + numpy index arrays
def load_data(PATH=''):

    # read data dictionaries
    with open(PATH + 'metadata.pkl', 'rb') as f:
        metadata = pickle.load(f)

    # read numpy word index arrays
    idx_q = np.load(PATH + 'idx_q.npy')
    idx_a = np.load(PATH + 'idx_a.npy')
    return metadata, idx_q, idx_a

if __name__ == '__main__':
    process_data()