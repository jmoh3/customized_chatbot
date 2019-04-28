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

TfIdfVector::TfIdfVector(vector<Message> messages, int minFreq, int maxFreq) {
  int numMessages = messages.size();
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

      double val = 0.0;

      if (currentWordCountMap.find(currentWord) != currentWordCountMap.end()) {
        val = currentWordCountMap[currentWord];
        wordCount += val;
        tfidfvec[counter] = calculateTfIdf(val, 1, wordDocumentFrequency, numMessages);
      }
    }

    vectorLength = counter;

    for (int i = 0; i < tfidfvec.size(); i++) {
      tfidfvec[i] = tfidfvec[i] / wordCount;
    }
    
    tfIdfVectors[messageId] = tfidfvec;
  }

  this->tfIdfVectors = tfIdfVectors;
}

map<string, sparseVector> TfIdfVector::getVectors() const {
  return tfIdfVectors;
}

unsigned TfIdfVector::getVectorLength() const  {
  return vectorLength;
}

void TfIdfVector::init_word_count_maps(vector<Message>& messages) {
  for (auto it = messages.begin(); it != messages.end(); it++) {
    map<string, int> word_count_map = message_to_word_map(*it);
    word_count_maps[it->getMessageId()] = word_count_map;
  }
}

map<string, int> TfIdfVector::message_to_word_map(Message& message) {
  string content = message.getContent();
  vector<string> splitMessage = split(content, cDelimiter);
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
    if (vectorB.find(currentIdx) != vectorB.end()) {
      double currentValueB = vectorB[currentIdx];
      dotProduct += currentValueA * currentValueB;
    }
    magnitudeA += currentValueA * currentValueA;
  }

  for (auto iteratorB = vectorB.begin(); iteratorB != vectorB.end(); iteratorB++) {
    double currentValueB = iteratorB->second;
    magnitudeB += currentValueB * currentValueB;
  }

  magnitudeA = sqrt(magnitudeA);
  magnitudeB = sqrt(magnitudeB);

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

double TfIdfVector::calculateTfIdf(int termCt, int documentWordCt, int documentCt, int numDocs) {
  double termFreq = (double) termCt / (double) documentWordCt;
  double inverseDocumentFreq = 1 + log((double) numDocs / (double) documentCt);

  return termFreq * inverseDocumentFreq;
}