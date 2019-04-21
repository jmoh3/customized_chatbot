# Development

## A slight change of plans

Originally, I had decided to use the Tensorflow library to make this chatbot. After more research, I found that the approach that I intended to use was beyond the scope of this very limited C++ library and that I'd essentially have to implement very complicated neural network structures from scratch. I will come back to this if I have time, but until then, I've decided to use a much simpler approach.

Instead of using a Seq-to-Seq model, I'm going to start with an approach that doesn't involve any learning whatsoever. My app will still take in a bunch of messages (in JSON format) that the user can download from their Facebook account. I plan on using the FastJSON library to process these message into objects that contain the content of the message, the sender, and a unique message ID.

I may use word embeddings later, but at the moment, I plan to use a Bag-Of-Words approach. This means that each document will be reduced into a vector where each component corresponds to the number of times a certain word appears in that document. The vectors for all the documents will be uniform, with the same words corresponding to the same components. 

Beyond the raw word counts, I will also apply the Term-Frequency-Inverse-Document-Frequency (TfIdf) transformation to account for words that appear extremely frequently in documents (think stopwords like "and", "but", "or", which I will not be removing unless I have time) or appear very rarely in documents (ex: typos). This ensures that very frequently seen words aren't given a high weight, and that messages that contain many words aren't given too high of a weight, either.

To measure similarity between messages, I will use cosine similarity (dot product of 2 vectors divided by the product of their magnitudes).

The input to the model will be a message from the user. The model will find the most similar message to that input from a list of the messages from other users, and return the response to that message.

When I finish with this approach, and with the chat UI, I will consider using word embeddings or other more learning based approaches.
