import nltk

from nltk.corpus import stopwords
from nltk.tokenize import PunktSentenceTokenizer

'''
POS TAG LIST

CC | Coordinating conjunction |
CD | Cardinal number |
DT | Determiner |
EX | Existential there |
FW | Foreign word |
IN | Preposition or subordinating conjunction |
JJ | Adjective |
JJR | Adjective, comparative |
JJS | Adjective, superlative |
LS | List item marker |
MD | Modal |
NN | Noun, singular or mass |
NNS | Noun, plural |
NNP | Proper noun, singular |
NNPS | Proper noun, plural |
PDT | Predeterminer |
POS | Possessive ending |
PRP | Personal pronoun |
PRP$ | Possessive pronoun |
RB | Adverb |
RBR | Adverb, comparative |
RBS | Adverb, superlative |
RP | Particle |
SYM | Symbol |
TO | to |
UH | Interjection |
VB | Verb, base form |
VBD | Verb, past tense |
VBG | Verb, gerund or present participle |
VBN | Verb, past participle |
VBP | Verb, non-3rd person singular present |
VBZ | Verb, 3rd person singular present |
WDT | Wh-determiner |
WP | Wh-pronoun |
WP$ | Possessive wh-pronoun |
WRB | Wh-adverb |
'''

import nltk
import pprint
from nltk.tree import Tree


sample = 'Bob collect the coins';
sample = 'Bob collect the coins while shining';
sample = 'move Bob to the house';

sample = 'delete Bob';
sample = 'create coins';

sample = 'move green short Bob to the house'
sample = 'short Bob move to  the coins';
sample = 'hello Bob'
sample = 'stop moving Bob'
sample = 'rotate Bob';


##sentences = PunktSentenceTokenizer(sample_text)
##tokenized_sentences = custom_stnc_tokenizer.tokenize(sample_text)
tokenized_sentences = nltk.sent_tokenize(sample)
print('Tokenized Sentences...')
print(tokenized_sentences)

tokenized_words = [nltk.word_tokenize(sentence) for sentence in tokenized_sentences]
##tokenized_words = nltk.word_tokenize(tokenized_sentences)
print('Tokenized Words...')
print(tokenized_words[0])

##
##stop_words = set(stopwords.words("english"))
##filtered_sentence = []
##
##for w in tokenized_words:
##    if w not in stop_words:
##        filtered_sentence.append(w)
##print('Filtered sentence...')
##print(filtered_sentence)

tagged_sentences = [nltk.pos_tag(sentence) for sentence in tokenized_words]
print('Tagged Words...')
print(tagged_sentences[0])

named_entities = [nltk.ne_chunk(tagged_stnc) for tagged_stnc in tagged_sentences]
print('Named Entities...')
print(named_entities)

def get_continuous_chunks(chunked):
    prev = None
    continuous_chunk = []
    current_chunk = []
    for i in chunked:
             if type(i) == Tree:
                     current_chunk.append(" ".join([token for token, pos in i.leaves()]))
             elif current_chunk:
                     named_entity = " ".join(current_chunk)
                     if named_entity not in continuous_chunk:
                             continuous_chunk.append(named_entity)
                             current_chunk = []
             else:
                     continue
    return continuous_chunk
print(get_continuous_chunks(named_entities))


##chunkGram = r"""NE: {<RB.?>*<VB.?>*<JJ>*<NNP>+<NN>?}"""
####chunkGram = "NP: {<DT>?<JJ>*<NN>}"
##
##chunkParser = nltk.RegexpParser(chunkGram)
#### DO PROPER CHUNKING IN ORDER TO
#### GROUP ENTITIES WITH RELATED NOUNS/ADJECTIVES/ETC...
##
##chunkedSentence = chunkParser.parse(tagged_sentences[0])
##print('Chunked Sentence...')
##print(chunkedSentence)
##chunkedSentence.draw()


