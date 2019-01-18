from nltk.stem import WordNetLemmatizer


lemmatizer = WordNetLemmatizer()

print(lemmatizer.lemmatize("worst", pos="a"))
print(lemmatizer.lemmatize("better", pos="a"))
print(lemmatizer.lemmatize("Remove", pos="n"))
print(lemmatizer.lemmatize("Delete", pos="n"))
print(lemmatizer.lemmatize("move", pos="a"))
print(lemmatizer.lemmatize("move", pos="a"))
print(lemmatizer.lemmatize("move", pos="a"))
print(lemmatizer.lemmatize("move", pos="a"))
print(lemmatizer.lemmatize("move", pos="a"))
