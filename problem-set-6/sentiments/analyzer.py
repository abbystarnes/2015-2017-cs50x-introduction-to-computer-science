import nltk
from nltk.tokenize import TweetTokenizer


class Analyzer():
    """Implements sentiment analysis."""
    
    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        # load positive & negative words into memory
        def loadWords(dictionary, file):
            dictionary = open(file, 'r').read()
            self.cleanArr = dictionary.strip()
            self.positivesArr = self.cleanArr.splitlines()
            self.posArray = []
            for self.posWord in self.positivesArr:
                if self.posWord.startswith(';'):
                    del self.posWord
                elif self.posWord == '':
                    del self.posWord
                else:
                    self.posArray.append(self.posWord)
            dictionary = self.posArray 
            return dictionary
            
        self.positives = loadWords(positives, 'positive-words.txt')
        self.negatives = loadWords(negatives, 'negative-words.txt')
        # print(self.positives, self.negatives)
        

    def analyze(self, text):
        self.score = 0
        self.tokenizer = TweetTokenizer()
        """Analyze text for sentiment, returning its score."""
        self.text = text
        self.lines = self.text.splitlines()
        for line in self.lines:
            tokens = self.tokenizer.tokenize(line)
            for token in tokens:
                token = token.lower()
                # print(token)
                if token in self.positives:
                    self.score +=1
                elif token in self.negatives:
                    self.score -=1
                else: 
                    self.score +=0
        return self.score
 

