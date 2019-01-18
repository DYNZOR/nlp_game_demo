import nltk
import random
from nltk.corpus import movie_reviews

documents = [(list(movie_reviews.words(fileid)), category)
             for category in movie_reviews.categories()
             for fileid in movie_reviews.fileids(category)]

##documents = []
##for category in movie_reviews.categories():
##    for fileid in movie_reviews.fileids(category):
##        documents.append(list(movie_reviews.words(fileid)), category)

random.shuffle(documents)
#print(documents[1])

all_words = []

## Insert every word into list 
for word in movie_reviews.words():
    all_words.append(word.lower())

## All words in the corpus ordered by highest frequency
all_words = nltk.FreqDist(all_words)

##word_features = list(all_words.keys()) [:3000]
word_features = []
for i in all_words.most_common(3000):
    word_features.append(i[0])

def find_features(document):
    words = set(document)
    features = {}
    for w in word_features:
        features[w] = (w in words)

    return features

#print( (find_features(movie_reviews.words('neg/cv000_29416.txt'))))

featuresets = [(find_features(rev), category) for (rev, category) in documents]

# Split training and testing data 
training_set = featuresets[:1900]
testing_set = featuresets[1900:]

# Naive Bayes Algorithm = Posterior - prior occurences x likelyhood / evidence
classifier = nltk.NaiveBayesClassifier.train(training_set)
print("Naive Bayes Algorithm Accuracy: ", (nltk.classify.accuracy(classifier, testing_set))*100)
classifier.show_most_informative_features(15)

