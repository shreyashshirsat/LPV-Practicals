# Binary Classification Using Deep Neural Network

## 0. Beginner Roadmap and Deep Learning Focus

If you are new to Deep Learning, understand this practical in this simple way:

- **Text data** cannot be directly understood by a neural network.
- So reviews are converted into numbers first.
- Each review becomes a vector showing which important words are present.
- The model learns patterns of words that usually appear in positive or negative reviews.
- **Binary classification** means there are only two possible outputs.
- Here output `0` means negative review and output `1` means positive review.
- **Sigmoid** gives a probability between 0 and 1.
- If probability is greater than 0.5, the model predicts positive.

Subject focus:

This practical is from **Deep Learning** because it uses a Deep Neural Network with Dense and Dropout layers. It is a **classification** problem because the model predicts a class label, not a continuous number. In the exam, first say: "This program classifies IMDB movie reviews as positive or negative using a Deep Neural Network."

## 0A. Core Theory: What, Why, How, and When

### What is Classification?

Classification is a supervised learning task where the model predicts a category or class.

In this practical, the categories are:

- Negative review.
- Positive review.

Because there are only two classes, this is called **binary classification**.

### What is Sentiment Analysis?

Sentiment analysis means finding the opinion or emotion in text. Here, the model reads a movie review and predicts whether the review is positive or negative.

Example:

```text
"The movie was excellent" -> positive
"The movie was boring" -> negative
```

### Why convert text into numbers?

Neural networks cannot understand raw English words directly. They only work with numbers. So text must be converted into numerical form before training.

In this code, each review is converted into a vector of size `10000`. Each position represents whether a particular word is present.

### What is a Deep Neural Network?

A Deep Neural Network is a model made of multiple layers. Each layer learns patterns from the previous layer.

For IMDB reviews:

- Early layers may learn simple word presence patterns.
- Later layers may learn stronger combinations of words that indicate positive or negative sentiment.

### Why use Dense layers?

Dense layers are fully connected layers. They are useful when the input is a fixed-size vector, like the 10,000-word vector used in this code.

### Why use Dropout?

Dropout helps prevent overfitting. Overfitting means the model memorizes training reviews instead of learning general sentiment patterns. Dropout randomly disables some neurons during training, forcing the model to learn more robust patterns.

### Why use Sigmoid?

Sigmoid is used in binary classification because it outputs a value between `0` and `1`.

Interpretation:

- Close to `0`: negative review.
- Close to `1`: positive review.
- Greater than `0.5`: predicted positive.
- Less than or equal to `0.5`: predicted negative.

### Why use Binary Crossentropy?

Binary crossentropy measures how wrong the predicted probability is for a two-class problem. It heavily penalizes confident wrong predictions.

### When do we use binary classification?

Use binary classification when there are two possible outputs, such as:

- Positive/negative review.
- Spam/not spam email.
- Disease/no disease.
- Pass/fail.
- Fraud/not fraud.

## 1. Which Practical This File Belongs To

This file belongs to the **Classification using Deep Neural Network** practical. Specifically, it implements the **Binary Classification using Deep Neural Networks** option using the IMDB movie review dataset.

Requirement check:

- Required option: Classify IMDB movie reviews as positive or negative.
- Actual code: Uses `keras.datasets.imdb`.
- Match status: **Matches the requirement**.

## 2. Aim of the Practical

To build a Deep Neural Network that classifies movie reviews as positive or negative based on the words present in the review text.

## 3. Dataset Used

The code uses the **IMDB movie review dataset** from Keras.

- Input: movie reviews represented as sequences of integer word indexes.
- Output: sentiment label.
- Label `0`: negative review.
- Label `1`: positive review.
- `num_words=10000`: only the top 10,000 most frequent words are used.

The purpose is to learn sentiment classification from text data.

## 4. Libraries Used

- `numpy`: Used for array operations and vectorization.
- `matplotlib.pyplot`: Used to plot accuracy and loss graphs.
- `keras.datasets.imdb`: Loads the IMDB dataset.
- `keras.models`: Provides the Sequential model API.
- `keras.layers`: Provides Dense and Dropout layers.
- `train_test_split`: Splits data into training and testing sets.
- `classification_report`: Shows precision, recall, F1-score, and support.
- `confusion_matrix`: Shows correct and incorrect classifications.
- `tensorflow`: Used for the EarlyStopping callback.

## 5. Complete Code Logic

The program loads the IMDB dataset, combines the original training and testing data, converts each review into a one-hot encoded vector of size 10,000, splits the data again into 80% training and 20% testing, builds a dense neural network, trains it, evaluates accuracy, prints classification metrics, plots accuracy/loss graphs, and displays sample predictions.

## 6. Step-by-Step Code Explanation

`imdb.load_data(num_words=10000)`

Loads IMDB reviews. Each review is already converted into a list of word indexes. Only the top 10,000 words are kept.

`data = np.concatenate((X_train, X_test), axis=0)`

Combines original train and test reviews into one dataset.

`labels = np.concatenate((y_train, y_test), axis=0)`

Combines original train and test labels.

`def vectorize(sequences, dimension=10000):`

Defines a function to convert review sequences into fixed-size vectors.

`results = np.zeros((len(sequences), dimension))`

Creates a matrix where each row represents one review and each column represents one word.

`results[i, sequence] = 1`

Marks word indexes present in a review as `1`. This is one-hot multi-hot vectorization.

`labels = np.array(labels).astype("float32")`

Converts labels to float format because neural network training uses numerical tensors.

`train_test_split(data, labels, test_size=0.2, random_state=42)`

Splits data into 80% training and 20% testing. `random_state=42` makes the split reproducible.

`models.Sequential([...])`

Creates a layer-by-layer neural network model.

`Dense(50, activation="relu", input_shape=(10000,))`

First hidden layer. It accepts a 10,000-dimensional review vector and learns 50 features.

`Dropout(0.3)`

Randomly disables 30% neurons during training to reduce overfitting.

`Dense(50, activation="relu")`

Second hidden layer for deeper feature learning.

`Dropout(0.2)`

Again reduces overfitting.

`Dense(50, activation="relu")`

Third hidden layer.

`Dense(1, activation="sigmoid")`

Output layer. It gives probability between 0 and 1 for positive sentiment.

`model.compile(...)`

Configures optimizer, loss, and metrics.

`EarlyStopping(monitor='loss', patience=3)`

Stops training if training loss does not improve for 3 epochs.

`model.fit(...)`

Trains the model using training data and validates it on test data.

`model.evaluate(X_test, y_test)`

Calculates test loss and test accuracy.

`model.predict(X_test) > 0.5`

Converts predicted probabilities into class labels. More than 0.5 means positive.

## 7. Data Preprocessing

Preprocessing steps:

- Reviews are loaded as integer sequences.
- Original train and test data are combined.
- Reviews are vectorized into 10,000-dimensional binary vectors.
- Labels are converted to `float32`.
- Data is split into training and testing sets.

Important concept:

This code does not use word embeddings or tokenization manually because Keras IMDB already provides tokenized integer sequences.

## 8. Model Architecture

Architecture:

```text
Input: 10000 features
Dense: 50 neurons, ReLU
Dropout: 0.3
Dense: 50 neurons, ReLU
Dropout: 0.2
Dense: 50 neurons, ReLU
Output: 1 neuron, Sigmoid
```

Layer explanation:

- Input has 10,000 values because each review is represented by the top 10,000 words.
- Dense layers learn combinations of word presence.
- ReLU helps learn non-linear patterns.
- Dropout reduces overfitting.
- Sigmoid is used because output has two classes.

## 9. Compilation

The model is compiled with:

- Optimizer: `adam`
- Loss: `binary_crossentropy`
- Metric: `accuracy`

Why Adam:

- It is efficient and commonly used for deep learning.

Why binary crossentropy:

- It is the correct loss function for binary classification.

Why accuracy:

- Accuracy tells the percentage of correctly classified reviews.

## 10. Training Process

Training settings:

- `epochs=2`: model sees the training data 2 times.
- `batch_size=500`: 500 reviews are processed before one weight update.
- `validation_data=(X_test, y_test)`: test data is used to monitor validation accuracy and loss.
- `callbacks=[callback]`: early stopping is used.

During training:

1. The model predicts sentiment probabilities.
2. Binary crossentropy loss is calculated.
3. Backpropagation updates weights.
4. Accuracy and validation accuracy are recorded.

## 11. Evaluation and Prediction

The model is evaluated using:

```python
loss, accuracy = model.evaluate(X_test, y_test)
```

Predictions are made using:

```python
y_pred = (model.predict(X_test) > 0.5).astype("int32")
```

If predicted probability is greater than `0.5`, the review is classified as positive. Otherwise, it is classified as negative.

## 12. Output Explanation

Expected output:

- Training accuracy and validation accuracy.
- Test accuracy.
- Classification report.
- Confusion matrix.
- Accuracy vs Epoch graph.
- Loss vs Epoch graph.
- Sample actual and predicted labels.

Classification report contains:

- Precision: how many predicted positives were actually positive.
- Recall: how many actual positives were correctly found.
- F1-score: balance between precision and recall.
- Support: number of samples in each class.

Confusion matrix shows:

- True negatives.
- False positives.
- False negatives.
- True positives.

## 13. Why This Practical Is Important

This practical is important because sentiment analysis is widely used in review analysis, social media monitoring, recommendation systems, customer feedback analysis, and opinion mining.

## 14. Common Viva Questions and Answers

1. What type of classification is this?
   Answer: Binary classification.

2. What are the two classes?
   Answer: Positive review and negative review.

3. Which dataset is used?
   Answer: IMDB movie review dataset.

4. What does `num_words=10000` mean?
   Answer: Only the top 10,000 most frequent words are used.

5. What is vectorization?
   Answer: Converting text data into numerical vectors.

6. Why do we vectorize reviews?
   Answer: Neural networks cannot directly process raw text.

7. What is the input shape?
   Answer: `(10000,)`.

8. Why is sigmoid used in the output layer?
   Answer: It gives probability between 0 and 1 for binary classification.

9. Why is binary crossentropy used?
   Answer: It is suitable for two-class classification.

10. What does label 1 mean?
    Answer: Positive review.

11. What does label 0 mean?
    Answer: Negative review.

12. What is Dropout?
    Answer: A regularization technique that randomly disables neurons during training.

13. Why is ReLU used?
    Answer: It introduces non-linearity and helps learn complex patterns.

14. What is Adam optimizer?
    Answer: An adaptive optimizer used to update weights efficiently.

15. What is EarlyStopping?
    Answer: A callback that stops training when loss stops improving.

16. What is a confusion matrix?
    Answer: A table showing correct and incorrect predictions for each class.

17. What is precision?
    Answer: Correct positive predictions divided by all positive predictions.

18. What is recall?
    Answer: Correct positive predictions divided by actual positives.

19. Why is threshold 0.5 used?
    Answer: Sigmoid output above 0.5 is treated as class 1, below or equal to 0.5 as class 0.

20. What is overfitting?
    Answer: When the model performs well on training data but poorly on unseen data.

21. How does Dropout reduce overfitting?
    Answer: It prevents the model from depending too much on specific neurons.

22. Does this code match the given practical?
    Answer: Yes, it matches the IMDB binary classification option.

## 15. Examiner-Style Short Explanation

This program performs binary sentiment classification on the IMDB movie review dataset. The reviews are loaded as integer word sequences and converted into 10,000-dimensional binary vectors. A deep neural network with Dense and Dropout layers is trained using ReLU activations in hidden layers and sigmoid activation in the output layer. The model is compiled with Adam optimizer and binary crossentropy loss. After training, the model is evaluated using test accuracy, classification report, confusion matrix, and accuracy/loss graphs.

## 16. Important Points to Remember

- This is binary classification.
- Dataset is IMDB.
- Input reviews are vectorized into 10,000 features.
- Output is 0 or 1.
- Sigmoid is used for binary output.
- Binary crossentropy is the correct loss.
- Dropout prevents overfitting.
- `0.5` threshold converts probability into class.
- Confusion matrix shows prediction mistakes.

## 17. Possible Errors and Fixes

- Error: `ModuleNotFoundError: No module named 'tensorflow'`
  Fix: Install TensorFlow.

- Error: IMDB dataset download fails.
  Fix: Check internet connection.

- Error: Memory issue due to 10,000-dimensional vectors.
  Fix: Reduce `num_words` to 5000 or use smaller batch size.

- Error: Plot window does not open.
  Fix: Use Jupyter notebook or save plots with `plt.savefig()`.

- Error: `int(y_pred[i])` warning because prediction is an array.
  Fix: Use `int(y_pred[i][0])`.

## 18. Code Improvements

- Monitor `val_loss` in EarlyStopping instead of training `loss`.
- Increase epochs, for example 10 or 20, and let early stopping decide.
- Do not combine original train and test data if strict evaluation is required.
- Use validation split separately and keep test data only for final testing.
- Use embedding layers for more advanced text classification.
- Print model summary using `model.summary()`.
