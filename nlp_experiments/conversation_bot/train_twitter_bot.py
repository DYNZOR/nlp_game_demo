from datasets.twitter import twitter_data_process
import data_utils
import seq2seq_wrapper

# Load pre-processed data, i.e metadata, question and answer numpy id arrays
metadata, index_array_questions, index_array_answers = twitter_data_process.load_data(PATH='datasets/twitter/')

# Split dataset into training, validation and test sets.
(trainX, trainY), (testX, testY), (validX, validY) = data_utils.split_dataset(index_array_questions, index_array_answers)

#  Length of sequences
xsequence_length = trainX.shape[-1]
ysequence_length = trainY.shape[-1]

# Sequence batch size
batch_size = 32

xvocab_size = len(metadata['idx2w'])
yvocab_size = xvocab_size

# Dimensionality of feature/thought vector?
emb_dim = 1024


# Initialising the Seq2Seq model
model = seq2seq_wrapper.Seq2Seq(xseq_len=xsequence_length,
                               yseq_len=ysequence_length,
                               xvocab_size=xvocab_size,
                               yvocab_size=yvocab_size,
                               ckpt_path='ckpt/twitter/',
                               emb_dim=emb_dim,
                               num_layers=3
                               )

# Generate random training and validation batches of 32 sequences
train_batch_gen = data_utils.rand_batch_gen(trainX, trainY, batch_size)
val_batch_gen = data_utils.rand_batch_gen(validX, validY, batch_size)

# Restores trained model from pickle checkpoint
session = model.restore_last_session()
# Trains the model and saves progress to pickle checkpoint
session = model.train(train_batch_gen, val_batch_gen,session)

# ONLY FOR INITIAL MODEL TRAINING TO GENERATE NEW CHECKPOINT
#session = model.train(train_batch_gen, val_batch_gen)