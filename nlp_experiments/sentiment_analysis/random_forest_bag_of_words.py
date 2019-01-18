# -*- coding: utf-8 -*-
"""
Created on Fri May 6 14:33:10 2017
@author: Dinis
"""
import sys
import csv
import pandas as pd       
import numpy as np
import re 

from bs4 import BeautifulSoup
from nltk.corpus import stopwords

from sklearn.feature_extraction.text import CountVectorizer
from sklearn.ensemble import RandomForestClassifier

# This function pre-processes a raw training movie review 
def review_to_words(raw_review):
    
    # removing HTML markup from reviews 
    review = BeautifulSoup(raw_review, "html5lib").get_text()
    
    # using regular expressions to remove punctuation and numbers from reviews
    letters_only_review = re.sub("[^a-zA-Z]",
                             " ",
                             review)
    
    # convert to lowercase and split into word tokens 
    lower_case_review = letters_only_review.lower()
    words = lower_case_review.split()
    
    # a set of stop words to search for 
    stops = set(stopwords.words("english"))
    
    # remove stop words 
    meaningful_words = [w for w in words if not w in stops]
    
    # return a string of words 
    return( " ".join(meaningful_words))



# read in labelled train and test datasets
print('Reading train and test sets...')
train = pd.read_csv("labeledTrainData.tsv", header=0, \
                    delimiter="\t", quoting=3)

test = pd.read_csv("testData.tsv", header=0, \
                    delimiter="\t", quoting=3)

# Initialise the vectorizer to convert sentences into feature vectors
vectorizer = CountVectorizer(analyzer = "word", 
                             tokenizer= None,
                             preprocessor = None,
                             stop_words = None,
                             max_features = 5000)

print('Number of train and test reviews...')
# Obtain total number of reviews 
num_train_reviews = train["review"].size
num_test_reviews = train["review"].size

# Empty list to hold clean training reviews 
clean_train_reviews = []
clean_test_reviews = []

print('Cleaning train and test reviews...')
# Loop over all training and test reviews and preprocess them
for i in range(0, num_train_reviews):
    clean_train_reviews.append(review_to_words(train["review"][i]))

for i in range(0, num_test_reviews):
    clean_test_reviews.append(review_to_words(test["review"][i]))

# Fits the training data and then transforms it into feature vectors
train_data_features = vectorizer.fit_transform(clean_train_reviews)
# Convert features into Numpy array 
train_data_features = train_data_features.toarray()

# Transforms testing data into feature vectors
test_data_features = vectorizer.transform(clean_test_reviews)
# Convert features into Numpy array 
test_data_features = test_data_features.toarray()

# Features/Words in the vocabulary 
vocab = vectorizer.get_feature_names()

# Sum up counts of each vocab word 
dist = np.sum(train_data_features, axis=0)

# Initialise random forest classifier with 100 trees 
forest = RandomForestClassifier(n_estimators = 100)

# Fit forest to the training set, uses bag of words as features and 
# sentiment labels as target variables. 
forest = forest.fit(train_data_features, train["sentiment"])

# Use the random forest to predict the test set 
result = forest.predict(test_data_features)

# Copy the results to a pandas dataframe with an "review" column and
# a predicted "sentiment" column
output = pd.DataFrame( data={ "review":clean_test_reviews, "sentiment":result} )

writer = csv.writer(sys.stdout, delimiter="|", quoting=3, quotechar='')

# Use pandas to write the comma-separated output file
output.to_csv( "model_test_results.csv", index=False, quoting=3 )





