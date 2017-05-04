import nltk
from nltk.tag import StanfordNERTagger
from nltk.tokenize import word_tokenize
from datetime import datetime

def ProcessSentence(sentence, command_response):
        startTime = datetime.now()

        ##text = 'While in France, Christine Lagarde discussed short-term stimulus efforts in a recent interview with the Wall Street Journal.'
        sample = 'Bob collect the coins while shining';
        sample = 'move Bob to the house';

        sample = 'delete Bob';
        sample = 'create coins';

        sample = 'Bob collect the coins';
        sample = 'stop moving Bob'
        sample = 'rotate Bob';
        sample = 'move Bob to Paris'
        sample = 'short Bob go to Germany';

        sample = sentence.sentence

        tokenized_text = word_tokenize(sample)
        print(tokenized_text)

        ## NLTK Tagged sentence tokens 
        tagged_sentence = nltk.pos_tag(tokenized_text)
        print(tagged_sentence)

        # Change the path according to your system
        stanford_classifier = 'C:\\Users\\DYN\\AppData\Roaming\\nltk_data\\stanford\\stanford-ner-2016-10-31\\classifiers\\english.all.3class.distsim.crf.ser.gz'
        stanford_ner_path = 'C:\\Users\\DYN\\AppData\\Roaming\\nltk_data\\stanford\\stanford-ner-2016-10-31\\stanford-ner.jar'
        # Creating Tagger Object
        st = StanfordNERTagger(stanford_classifier, stanford_ner_path, encoding='utf-8')
        ## Stanford Tagged sentence tokens
        st_tagged_sentence = st.tag(tokenized_text)
        print(st_tagged_sentence)

        def get_continuous_chunks(tagged_sent):
            continuous_chunk = []
            current_chunk = []

            for token, tag in tagged_sent:
                if tag != "O":
                    current_chunk.append((token, tag))
                else:
                    if current_chunk: # if the current chunk is not empty
                        continuous_chunk.append(current_chunk)
                        current_chunk = []
            # Flush the final current_chunk into the continuous_chunk, if any.
            if current_chunk:
                continuous_chunk.append(current_chunk)
            return continuous_chunk

        named_entities = get_continuous_chunks(st_tagged_sentence)
        named_entities_str = [" ".join([token for token, tag in ne]) for ne in named_entities]
        named_entities_str_tag = [(" ".join([token for token, tag in ne]), ne[0][1]) for ne in named_entities]

        print (named_entities)
        print (named_entities_str)
        print (named_entities_str_tag)
        print ('\n')
        
        entity = named_entities_str[0]
        location = named_entities_str[1]
        present_actions = []
        actions = []
        characteristics = []


        ## Iterate over all word tags and extract 
        for item in tagged_sentence:
            if item[1] == 'NN': ## Noun, singular or mass
                actions.append(item[0])
            elif item[1] == 'VBP': ## Verb, non-3rd person singular present
                actions.append(item[0])
            elif item[1] == 'VB': ## Verb, base form
                actions.append(item[0])
            elif item[1] == 'VBG': ## Verb, gerund or present participle
                present_actions.append(item[0])
            elif item[1] == 'JJ': ## Adjective
                characteristics.append(item[0])

        print('Outputting... \n')
        print('Entity: ', entity)
        print('Location: ', location)
        print('Present actions: ', present_actions)
        print('Actions: ', actions)
        print('Characteristics', characteristics)

        command_response.sAction = actions[0]
        command_response.sLocation = location
        command_response.sPersonEntity1 = named_entities_str[0]

        
        ##command_response.sPresentAction = present_actions[0]
        ##command_response.sPersonEntity1 =

        bHasLocation = 0;

        if "Germany" in location:
            bHasLocation = 1
        elif "France" in location:
            bHasLocation = 1
        elif "England" in location:
            bHasLocation = 1
            
        print('Location count', bHasLocation)
                
        command_response.bHasLocation = bHasLocation;
        command_response.bCancelAction = 0;

        ## Time taken to execute the script
        print (datetime.now() - startTime)




