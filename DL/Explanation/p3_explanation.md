# Multiclass Classification Using Deep Neural Network

## 0. Beginner Roadmap and Deep Learning Focus

If you are new to Deep Learning, understand this practical in this simple way:

- An image is stored as pixel values.
- A 28 x 28 image has 784 pixels.
- The code converts each image into a list of 784 numbers.
- The neural network learns which pixel patterns look like digit 0, 1, 2, and so on.
- **Multiclass classification** means more than two possible output classes.
- Here there are 10 classes: digits 0 to 9.
- **Softmax** gives probability for each class.
- The class with the highest probability becomes the final prediction.

Subject focus:

This practical is from **Deep Learning** because it uses a multi-layer neural network to classify images. It is not a CNN because the image is flattened and passed into Dense layers. In the exam, first say: "This program performs multiclass image classification using a Deep Neural Network."

## 0A. Core Theory: What, Why, How, and When

### What is Multiclass Classification?

Multiclass classification means the model chooses one class from more than two possible classes.

In this practical, the classes are digits:

```text
0, 1, 2, 3, 4, 5, 6, 7, 8, 9
```

So the model must decide which digit is shown in the image.

### What is MNIST?

MNIST is a famous beginner dataset of handwritten digit images. Each image is grayscale and has size 28 x 28 pixels.

The computer sees an image as numbers. Each pixel has a value:

- `0` means black.
- `255` means white.
- Values between them are shades of gray.

### Why flatten the image?

Dense neural networks expect input as a one-dimensional vector. A 28 x 28 image is therefore converted into:

```text
28 * 28 = 784 values
```

This allows the Dense network to accept the image as input.

### What is one-hot encoding?

One-hot encoding converts a class number into a vector.

Example:

```text
Digit 3 -> [0, 0, 0, 1, 0, 0, 0, 0, 0, 0]
```

It is used because the output layer has 10 neurons, one for each class.

### Why use Softmax?

Softmax is used for multiclass classification. It converts output values into probabilities whose total is 1.

Example:

```text
Digit 0: 0.01
Digit 1: 0.02
Digit 2: 0.03
Digit 3: 0.90
...
```

The model predicts the class with the highest probability.

### Why use Categorical Crossentropy?

Categorical crossentropy is used when:

- There are multiple classes.
- Labels are one-hot encoded.
- The output layer uses softmax.

It measures how different the predicted probability distribution is from the correct one-hot label.

### How does image classification work in this DNN?

1. Pixel values are given as input.
2. Hidden layers learn patterns from pixels.
3. Dropout reduces memorization.
4. Final softmax layer gives probabilities for 10 digits.
5. Highest probability becomes prediction.

### When do we use multiclass classification?

Use multiclass classification when there are more than two categories, such as:

- Digit recognition.
- Letter recognition.
- Animal classification.
- Clothing category prediction.
- Disease type classification.

## 1. Which Practical This File Belongs To

This file belongs to the **Multiclass Classification using Deep Neural Network** category because it classifies images into one of 10 possible classes using a fully connected neural network.

Requirement check:

- Required option: OCR Letter Recognition dataset, or IMDB binary classification.
- Actual code: Uses MNIST handwritten digit dataset.
- Match status: **Partially matches as a multiclass DNN**, but it does **not** use the required OCR Letter Recognition dataset.

This file is still useful for viva because MNIST is also an OCR-style classification dataset, but it recognizes digits `0-9`, not letters `A-Z`.

## 2. Aim of the Practical

To build a deep neural network that classifies handwritten digit images into 10 classes from 0 to 9 using the MNIST dataset.

## 3. Dataset Used

The code uses the **MNIST handwritten digit dataset**.

- Loaded using `tensorflow.keras.datasets.mnist`.
- Training images: 60,000.
- Testing images: 10,000.
- Image size: 28 x 28 pixels.
- Image type: grayscale.
- Input: handwritten digit image.
- Output: digit class from `0` to `9`.

Purpose:

The model learns to recognize handwritten digits from pixel values.

Exam note:

The listed practical mentions OCR Letter Recognition dataset. MNIST is digit recognition, so if the examiner strictly asks for letter recognition, this file should be modified to use the UCI Letter Recognition dataset with 26 output classes.

## 4. Libraries Used

- `numpy`: Used for one-hot encoding and numerical operations.
- `matplotlib.pyplot`: Used for plotting accuracy, loss, and confusion matrix figure.
- `Sequential`: Creates a layer-by-layer Keras model.
- `Dense`: Fully connected neural network layer.
- `Dropout`: Reduces overfitting.
- `RMSprop`: Optimizer used to update model weights.
- `mnist`: Loads the MNIST dataset.
- `EarlyStopping`: Stops training when validation loss stops improving.
- `ModelCheckpoint`: Saves the best model.
- `classification_report`: Prints precision, recall, F1-score, and support.
- `confusion_matrix`: Creates a table of actual vs predicted classes.
- `seaborn`: Used to draw a heatmap for the confusion matrix.

## 5. Complete Code Logic

The program loads MNIST digit images, reshapes each 28 x 28 image into a flat vector of 784 values, normalizes pixel values between 0 and 1, one-hot encodes the labels, builds a deep dense neural network, trains it using RMSprop optimizer and categorical crossentropy loss, evaluates it on test data, prints classification results, displays a confusion matrix, plots accuracy/loss graphs, and prints sample predictions.

## 6. Step-by-Step Code Explanation

`(x_train, y_train), (x_test, y_test) = mnist.load_data()`

Loads MNIST training and testing data.

`x_train.reshape(60000, 784)`

Converts each 28 x 28 image into a 1D vector of 784 pixel values.

`astype('float32') / 255`

Converts pixel values to float and normalizes them from range `0-255` to `0-1`.

`y_test_labels = y_test.copy()`

Saves original test labels before one-hot encoding. This is needed later for classification report and confusion matrix.

`y_train = np.eye(10)[y_train]`

Converts labels into one-hot encoded vectors. Example: label `3` becomes `[0,0,0,1,0,0,0,0,0,0]`.

`model = Sequential([...])`

Creates the neural network.

`Dense(512, activation='relu', input_shape=(784,))`

First hidden layer with 512 neurons. It accepts the flattened image.

`Dropout(0.3)`

Randomly disables 30% of neurons during training to reduce overfitting.

`Dense(256, activation='relu')`

Second hidden layer with 256 neurons.

`Dropout(0.3)`

Another dropout layer.

`Dense(128, activation='relu')`

Third hidden layer with 128 neurons.

`Dense(10, activation='softmax')`

Output layer with 10 neurons, one for each digit class. Softmax gives probability distribution across 10 classes.

`loss='categorical_crossentropy'`

Used because this is multiclass classification with one-hot encoded labels.

`optimizer=RMSprop(learning_rate=0.001)`

Updates model weights using RMSprop.

`EarlyStopping(monitor='val_loss', patience=3, restore_best_weights=True)`

Stops training if validation loss does not improve for 3 epochs and restores the best weights.

`ModelCheckpoint("best_model.h5", save_best_only=True)`

Saves the best model during training.

`model.fit(...)`

Trains the model for up to 30 epochs.

`np.argmax(model.predict(x_test), axis=1)`

Converts softmax probabilities into predicted class labels.

## 7. Data Preprocessing

Preprocessing steps:

- Reshaping images from 28 x 28 to 784.
- Converting pixel values to `float32`.
- Normalizing pixels by dividing by 255.
- Saving original labels for evaluation.
- One-hot encoding labels into 10-dimensional vectors.

Why flattening is needed:

Dense layers need 1D input, so each 2D image is converted into a 1D vector.

Why normalization is needed:

Neural networks train better when input values are small and in a similar range.

Why one-hot encoding is needed:

The output layer has 10 neurons and uses categorical crossentropy, so labels must also be in 10-class vector form.

## 8. Model Architecture

Architecture:

```text
Input: 784 pixels
Dense: 512 neurons, ReLU
Dropout: 0.3
Dense: 256 neurons, ReLU
Dropout: 0.3
Dense: 128 neurons, ReLU
Output: 10 neurons, Softmax
```

Layer explanation:

- Input has 784 values because 28 x 28 = 784.
- Dense 512 learns high-level combinations of pixels.
- Dropout prevents memorization.
- Dense 256 and Dense 128 learn deeper patterns.
- Output has 10 neurons because there are 10 digit classes.
- Softmax is used because exactly one class must be selected from many classes.

## 9. Compilation

Compilation settings:

- Loss: `categorical_crossentropy`
- Optimizer: `RMSprop`
- Metric: `accuracy`

Why categorical crossentropy:

- It is used for multiclass classification when labels are one-hot encoded.

Why RMSprop:

- RMSprop adapts learning during training and works well for neural networks.

Why accuracy:

- Accuracy measures how many images are classified correctly.

## 10. Training Process

Training settings:

- `batch_size=128`
- `epochs=30`
- `validation_data=(x_test, y_test)`
- callbacks: EarlyStopping and ModelCheckpoint

During training:

1. Images are passed through Dense layers.
2. Softmax produces probabilities for digits 0 to 9.
3. Categorical crossentropy calculates error.
4. Backpropagation updates weights.
5. Validation loss is monitored.
6. Best model is saved.

The model may stop before 30 epochs if validation loss does not improve.

## 11. Evaluation and Prediction

Evaluation:

```python
loss, accuracy = model.evaluate(x_test, y_test)
```

Prediction:

```python
y_pred = np.argmax(model.predict(x_test), axis=1)
```

`model.predict()` returns probabilities. `np.argmax()` selects the class with the highest probability.

## 12. Output Explanation

Expected output:

- Test accuracy.
- Classification report for digits 0 to 9.
- Confusion matrix heatmap.
- Accuracy vs Epoch graph.
- Loss vs Epoch graph.
- Five sample predictions.

How to interpret:

- High accuracy means most digits are correctly classified.
- Confusion matrix shows which digits are confused with each other.
- Accuracy graph should increase.
- Loss graph should decrease.
- If validation accuracy is much lower than training accuracy, overfitting may be happening.

## 13. Why This Practical Is Important

This practical shows how deep neural networks classify images into multiple categories. It is useful for OCR, digit recognition, form reading, postal code recognition, and document automation.

## 14. Common Viva Questions and Answers

1. What type of problem is this?
   Answer: Multiclass classification.

2. Which dataset is used?
   Answer: MNIST handwritten digit dataset.

3. Does this match the OCR Letter Recognition requirement?
   Answer: Partially. It is OCR-like multiclass classification, but it uses digit recognition, not letter recognition.

4. How many classes are present?
   Answer: 10 classes, digits 0 to 9.

5. What is the image size?
   Answer: 28 x 28 pixels.

6. Why reshape images to 784?
   Answer: Dense layers require 1D input, and 28 x 28 equals 784.

7. Why divide by 255?
   Answer: To normalize pixel values from 0-255 to 0-1.

8. What is one-hot encoding?
   Answer: It converts class labels into binary vectors.

9. Why use softmax?
   Answer: Softmax gives probabilities for multiple classes.

10. Why use categorical crossentropy?
    Answer: It is suitable for multiclass classification with one-hot labels.

11. Why use ReLU?
    Answer: ReLU helps the network learn non-linear patterns.

12. What is Dropout?
    Answer: It randomly turns off neurons during training to reduce overfitting.

13. What is RMSprop?
    Answer: An optimizer that updates weights using adaptive learning rates.

14. What is EarlyStopping?
    Answer: It stops training when validation loss stops improving.

15. What is ModelCheckpoint?
    Answer: It saves the best model during training.

16. Why save original test labels?
    Answer: Classification report and confusion matrix need class numbers, not one-hot vectors.

17. What does `np.argmax()` do?
    Answer: It returns the index of the largest probability.

18. What is a confusion matrix?
    Answer: It shows actual classes versus predicted classes.

19. What is overfitting?
    Answer: When the model performs very well on training data but poorly on unseen data.

20. What does validation loss show?
    Answer: It shows model error on validation data.

21. What change is needed for Letter Recognition dataset?
    Answer: Use UCI Letter Recognition data and change output layer to 26 neurons.

22. Why is this not a CNN?
    Answer: It flattens images and uses only Dense layers, so spatial image structure is not directly preserved.

## 15. Examiner-Style Short Explanation

This program implements multiclass classification using a deep neural network on the MNIST handwritten digit dataset. Each 28 x 28 image is flattened into 784 input values and normalized between 0 and 1. The labels are one-hot encoded because the model uses categorical crossentropy. The model contains Dense layers with ReLU activation, Dropout layers to reduce overfitting, and a final Softmax layer with 10 neurons for digit classes. It is trained using RMSprop optimizer and evaluated using accuracy, classification report, confusion matrix, and training graphs. The file demonstrates multiclass DNN classification, but it uses MNIST digits instead of the required OCR Letter Recognition dataset.

## 16. Important Points to Remember

- This is multiclass classification.
- Dataset is MNIST.
- Images are 28 x 28 grayscale.
- Images are flattened to 784 values.
- Pixel values are normalized by dividing by 255.
- Labels are one-hot encoded.
- Softmax is used for multiclass output.
- Categorical crossentropy is used with one-hot labels.
- Confusion matrix shows class-wise mistakes.
- This file does not strictly use the required Letter Recognition dataset.

## 17. Possible Errors and Fixes

- Error: `ModuleNotFoundError: No module named 'tensorflow'`
  Fix: Install TensorFlow.

- Error: `ModuleNotFoundError: No module named 'seaborn'`
  Fix: Install seaborn.

- Error: Dataset download fails.
  Fix: Check internet connection.

- Error: Shape mismatch in labels.
  Fix: Use one-hot encoded labels with categorical crossentropy.

- Error: Model save warning for `.h5`.
  Fix: Use `"best_model.keras"` in newer Keras versions.

## 18. Code Improvements

- Use the required OCR Letter Recognition dataset if the practical strictly demands it.
- Use a separate validation set instead of using test data as validation data.
- Add `model.summary()` to show architecture.
- Use CNN for image data for better accuracy.
- Add class labels in the confusion matrix.
- Save graphs as image files for practical record.
- Add random seed for reproducible results.
