#include "TfIdfVector.h"
#include <vector>
#include <string>
#include <map>
#include <math.h>
#include <iostream>
#include <sstream> 
#include "../Preprocessing/Message.h"

using std::vector;
using std::string;
using std::map;
using std::stringstream;
using std::getline;

TfIdfVector::TfIdfVector() {
  // do nothing.
}

TfIdfVector::TfIdfVector(vector<Message> messages, int minFreq, int maxFreq) {
  minimumWordFrequency = minFreq;
  maximumWordFrequency = maxFreq;

  numMessages = messages.size();
  init_word_count_maps(messages);

  map<string, sparseVector> tfIdfVectors;

  for (auto wordCountMapsIterator = word_count_maps.begin(); wordCountMapsIterator != word_count_maps.end(); wordCountMapsIterator++) {
    sparseVector tfidfvec;

    string messageId = wordCountMapsIterator->first;
    map<string, int> currentWordCountMap = wordCountMapsIterator->second;

    int wordCount = 0;
    int counter = 0;

    for (auto wordIterator = word_frequencies.begin(); wordIterator != word_frequencies.end(); wordIterator++) {
      string currentWord = wordIterator->first;
      int wordDocumentFrequency = wordIterator->second;
      counter++;

      if (wordDocumentFrequency < minFreq || wordDocumentFrequency > maxFreq) {
        continue;
      }
      // std::cout << currentWord << std::endl;

      double val = 0.0;

      if (currentWordCountMap.find(currentWord) != currentWordCountMap.end()) {
        val = currentWordCountMap[currentWord];
        wordCount += val;
        tfidfvec[counter] = calculateTfIdf(val, 1, wordDocumentFrequency, numMessages);
      }
    }

    vectorLength = counter;

    for (auto tfidfIterator = tfidfvec.begin(); tfidfIterator != tfidfvec.end(); tfidfIterator++) {
      tfidfIterator->second = tfidfIterator->second / wordCount;
    }
    
    tfIdfVectors[messageId] = tfidfvec;
  }

  this->tfIdfVectors = tfIdfVectors;
}

TfIdfVector::TfIdfVector(const TfIdfVector & other) {
  this->numMessages = other.numMessages;
  this->vectorLength = other.vectorLength;
  this->word_count_maps = other.word_count_maps;
  this->word_frequencies = other.word_frequencies;
  this->tfIdfVectors = other.tfIdfVectors;
  this->minimumWordFrequency = other.minimumWordFrequency;
  this->maximumWordFrequency = other.maximumWordFrequency;
}

TfIdfVector& TfIdfVector::operator=(const TfIdfVector & other) {
  this->numMessages = other.numMessages;
  this->vectorLength = other.vectorLength;
  this->word_count_maps = other.word_count_maps;
  this->word_frequencies = other.word_frequencies;
  this->tfIdfVectors = other.tfIdfVectors;
  this->minimumWordFrequency = other.minimumWordFrequency;
  this->maximumWordFrequency = other.maximumWordFrequency;

  return *this;
}


map<string, sparseVector> TfIdfVector::getVectors() const {
  return tfIdfVectors;
}

unsigned TfIdfVector::getVectorLength() const  {
  return vectorLength;
}

string TfIdfVector::getMostSimilarMessageId(Message inputMessage) const {
  map<string, int> word_count_map = message_to_word_map(inputMessage);

  int counter = 0;
  int wordCount = 0;

  sparseVector tfidfvec;

  for (auto wordIterator = word_frequencies.begin(); wordIterator != word_frequencies.end(); wordIterator++) {
    string currentWord = wordIterator->first;
    int wordDocumentFrequency = wordIterator->second;
    counter++;

    if (wordDocumentFrequency < minimumWordFrequency || wordDocumentFrequency > maximumWordFrequency) {
      std::cout << currentWord << std::endl;
      continue;
    }

    double val = 0.0;

    if (word_count_map.find(currentWord) != word_count_map.end()) {
      val = word_count_map[currentWord];
      wordCount += val;
      tfidfvec[counter] = calculateTfIdf(val, 1, wordDocumentFrequency, numMessages);
    }
  }

  if (tfidfvec.size() == 0) {
    return "noMessageId";
  }
 
  for (auto tfidfIterator = tfidfvec.begin(); tfidfIterator != tfidfvec.end(); tfidfIterator++) {
    tfidfIterator->second = tfidfIterator->second / wordCount;
  }

  string mostSimilarId = "";
  double bestSimilarity = -1.0;

  for (auto tfidfIterator = tfIdfVectors.begin(); tfidfIterator != tfIdfVectors.end(); tfidfIterator++) {
    string messageId = tfidfIterator->first;
    sparseVector currentVect = tfidfIterator->second;
    double similarity = cosineSimilarity(tfidfvec, currentVect);
    if (similarity > bestSimilarity) {
      mostSimilarId = messageId;
      bestSimilarity = similarity;
    }
  }

  return mostSimilarId;
}

void TfIdfVector::init_word_count_maps(vector<Message>& messages) {
  for (auto it = messages.begin(); it != messages.end(); it++) {
    map<string, int> word_count_map = message_to_word_map_init(*it);
    word_count_maps[it->getMessageId()] = word_count_map;
  }
}

map<string, int> TfIdfVector::message_to_word_map(Message& message) const {
  string content = message.getContent();
  vector<string> splitMessage = split(content, kDelimiter);
  message.setWordCount(splitMessage.size());

  map<string, int> word_count_map;

  for (const string & word : splitMessage) {
    if (word_count_map.find(word) != word_count_map.end()) {
      word_count_map[word] += 1;
    } else {
      word_count_map[word] = 1;
    }
  }

  return word_count_map;
}

map<string, int> TfIdfVector::message_to_word_map_init(Message& message) {
  string content = message.getContent();
  vector<string> splitMessage = split(content, kDelimiter);
  message.setWordCount(splitMessage.size());

  map<string, int> word_count_map;

  for (const string & word : splitMessage) {
    if (word_count_map.find(word) != word_count_map.end()) {
      word_count_map[word] += 1;
    } else {
      // first occurrence of word in document - need to add it to word_frequencies map
      if (word_frequencies.find(word) == word_frequencies.end()) {
        word_frequencies[word] = 1;
      } else {
        word_frequencies[word] += 1;
      }

      word_count_map[word] = 1;
    }
  }

  return word_count_map;
}

double TfIdfVector::cosineSimilarity(sparseVector vectorA, sparseVector vectorB) const {
  double dotProduct = 0.0;
  double magnitudeA = 0.0;
  double magnitudeB = 0.0;

  for (auto iteratorA = vectorA.begin(); iteratorA != vectorA.end(); iteratorA++) {
    int currentIdx = iteratorA->first;
    double currentValueA = iteratorA->second;
    // std::cout << "currentValueA: " << currentValueA << std::endl;
    if (vectorB.find(currentIdx) != vectorB.end()) {
      double currentValueB = vectorB[currentIdx];
      dotProduct += currentValueA * currentValueB;
    }
    magnitudeA += currentValueA * currentValueA;
  }

  for (auto iteratorB = vectorB.begin(); iteratorB != vectorB.end(); iteratorB++) {
    double currentValueB = iteratorB->second;
    magnitudeB += currentValueB * currentValueB;
    // std::cout << currentValueB << std::endl;
  }

  // std::cout << "MagnitudeA prior to sqrt: " << magnitudeA << std::endl;

  magnitudeA = sqrt(magnitudeA);
  magnitudeB = sqrt(magnitudeB);

  // std::cout << "MagnitudeA: " << magnitudeA << ", MagnitudeB: " << magnitudeB << ", dot prod: " << dotProduct << std::endl;

  double cosSimilarity = dotProduct / (magnitudeA * magnitudeB);

  return cosSimilarity;
}

// code from: https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
vector<string> TfIdfVector::split(const string toSplit, const char delim) const {
  vector<string> splitString;

  stringstream stream(toSplit);
  string intermediate;
      
  while(getline(stream, intermediate, delim)) {
    // just make everything lowercase
    transform(intermediate.begin(), intermediate.end(), intermediate.begin(), ::tolower);
    splitString.push_back(intermediate); 
  }

  return splitString;
}

double TfIdfVector::calculateTfIdf(int termCt, int documentWordCt, int documentCt, int numDocs) const {
  double termFreq = (double) termCt / (double) documentWordCt;
  double inverseDocumentFreq = 1 + log((double) numDocs / (double) documentCt);

  return termFreq * inverseDocumentFreq;
}