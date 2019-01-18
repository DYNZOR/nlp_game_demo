from nltk.corpus import wordnet

syns = wordnet.synsets("program")

#synset
print(syns[0])

# A word from the 1st synset
print(syns[0].lemmas()[0].name())

# Definition
print(syns[0].definition())

# Examples
print(syns[0].examples())

# Retrieve all synonyms and antonyms of the word "good"
synonyms = []
antonyms = []

for syn in wordnet.synsets("good"):
    for l in syn.lemmas():
        ##print("l:", l )
        synonyms.append(l.name())
        if l.antonyms():
            antonyms.append(l.antonyms()[0].name())

print(set(synonyms))
print(set(antonyms))

# Semantic similarity 
word1 = wordnet.synset("ship.n.01")
word2 = wordnet.synset("boat.n.01")
print(word1.wup_similarity(word2))

word1 = wordnet.synset("ship.n.01")
word2 = wordnet.synset("car.n.01")

print(word1.wup_similarity(word2))
word1 = wordnet.synset("ship.n.01")
word2 = wordnet.synset("cactus.n.01")
print(word1.wup_similarity(word2))
