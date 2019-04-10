# CS 196 Project Proposal

## The idea - A chatbot that talks like you!

I want users to be able to give my tool a dataset containing their conversations with others (can be downloaded from Facebook or from iCloud). I then want my tool to train a model based on that given information, and produce a chatbot that they can interact with in the app's window.

## The plan

My app needs to:

1. Read conversation data inputted by user
2. Parse that into message pairs (other person's message, your response)
3. (Possibly) Convert words to word embeddings (word2vec)
4. Create and train tensorflow model using either bag of words or word embeddings

After these steps, the app also needs to display an interactive user interface for the chatbot where the user can type messages and get responses from the trained model.

## What I'll be using

* OpenFrameworks application (duh)
* Library not covered in class: Tensorflow [link](https://www.tensorflow.org/api_docs/cc)
* I came up with the idea on my own, but I looked it up and this has somewhat been done so here's the blog post I looked at [link](https://adeshpande3.github.io/How-I-Used-Deep-Learning-to-Train-a-Chatbot-to-Talk-Like-Me)
