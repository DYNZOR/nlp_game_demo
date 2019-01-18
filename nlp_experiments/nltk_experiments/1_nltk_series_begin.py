from nltk.tokenize import sent_tokenize, word_tokenize

# TOKENIZING - WORD TOKENIZER.... SENTENCE TOKENIZERS
# LEXICON AND CORPORAS
# CORPORA - body of text. ex: medical journals, speeches
# LEXICON - words and their meanings

example_text = "Hello Mr. Smith, how are you doing today? The weather is great and Python is starting to seem awesome."

##print(sent_tokenize(example_text))
##print(word_tokenize(example_text))

for i in word_tokenize(example_text):
    print(i)
