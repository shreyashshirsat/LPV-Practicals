# Fashion MNIST Classification Using CNN

## 0. Beginner Roadmap and Deep Learning Focus

If you are new to Deep Learning, understand this practical in this simple way:

- A CNN is a special neural network for images.
- Instead of flattening the image immediately, CNN looks at small parts of the image.
- **Conv2D** layers detect patterns such as edges, curves, and shapes.
- **MaxPooling** reduces image size while keeping important information.
- **Flatten** converts extracted image features into a 1D vector.
- **Dense** layers use those features to classify the image.
- **Softmax** gives probabilities for 10 clothing classes.

Subject focus:

This practical is from **Deep Learning**, specifically **Convolutional Neural Networks**. CNNs are important because they preserve the spatial structure of images. In the exam, first say: "This program classifies Fashion MNIST clothing images using a CNN."

## 0A. Core Theory: What, Why, How, and When

### What is a CNN?

CNN stands for Convolutional Neural Network. It is a special type of neural network mainly used for image data.

Normal Dense networks treat an image as a flat list of numbers. CNNs are better because they look at small regions of the image and learn local patterns such as edges, corners, textures, and shapes.

### What is Convolution?

Convolution means sliding a small filter over the image and calculating feature values.

Example:

- One filter may detect vertical edges.
- Another filter may detect curves.
- Another filter may detect dark/light patterns.

The output of convolution is called a **feature map**.

### Why use Conv2D?

`Conv2D` is used for 2D image data. Fashion MNIST images are 28 x 28, so 2D convolution is suitable.

### What is MaxPooling?

MaxPooling reduces the size of feature maps by keeping the maximum value from small regions, usually 2 x 2.

Why it is used:

- Reduces computation.
- Keeps important features.
- Makes the model less sensitive to small shifts in the image.

### What is Flatten?

After convolution and pooling, the data is still in feature-map form. Dense layers need 1D input, so `Flatten` converts feature maps into a single vector.

### Why use CNN instead of only Dense layers?

CNN is better for images because it preserves spatial relationships. For example, nearby pixels together form edges and shapes. Dense layers lose this structure after flattening.

### Why use Softmax?

Fashion MNIST has 10 classes. Softmax gives probability for each class, and the class with the highest probability is selected.

### Why use Sparse Categorical Crossentropy?

This loss is used when:

- There are multiple classes.
- Labels are integer class numbers like `0`, `1`, `2`.
- Labels are not one-hot encoded.

### When do we use CNN?

Use CNN for image-related tasks such as:

- Clothing classification.
- Face recognition.
- Plant disease detection.
- Medical image analysis.
- Object detection.
- Handwritten digit recognition.

## 1. Which Practical This File Belongs To

This file belongs to the **Convolutional Neural Network** practical. Specifically, it implements **Fashion MNIST Classification using CNN**.

Requirement check:

- Required option: Fashion MNIST Classification using CNN.
- Actual code: Uses `keras.datasets.fashion_mnist` and a CNN model.
- Match status: **Matches the requirement**.

## 2. Aim of the Practical

To build a Convolutional Neural Network that classifies Fashion MNIST clothing images into one of 10 clothing categories.

## 3. Dataset Used

The code uses the **Fashion MNIST dataset**.

- Loaded using `keras.datasets.fashion_mnist.load_data()`.
- Training images: 60,000.
- Testing images: 10,000.
- Image size: 28 x 28 pixels.
- Image type: grayscale.
- Output classes: 10 fashion categories.

Common class names:

- 0: T-shirt/top
- 1: Trouser
- 2: Pullover
- 3: Dress
- 4: Coat
- 5: Sandal
- 6: Shirt
- 7: Sneaker
- 8: Bag
- 9: Ankle boot

## 4. Libraries Used

- `tensorflow`: Main deep learning library.
- `keras`: High-level API used to load dataset and build model.
- `numpy`: Used for prediction processing with `argmax`.
- `matplotlib.pyplot`: Used for plots and confusion matrix figure.
- `classification_report`: Gives precision, recall, F1-score, and support.
- `confusion_matrix`: Creates class-wise actual vs predicted table.
- `seaborn`: Draws confusion matrix as a heatmap.

## 5. Complete Code Logic

The program loads Fashion MNIST images, normalizes pixel values, reshapes images to include the channel dimension, builds a CNN using convolution, pooling, dropout, flatten, and dense layers, compiles the model with Adam optimizer and sparse categorical crossentropy loss, trains the model with early stopping and checkpoint saving, evaluates it on test data, prints classification metrics, displays a confusion matrix, plots accuracy/loss graphs, and prints sample predictions.

## 6. Step-by-Step Code Explanation

`(x_train, y_train), (x_test, y_test) = keras.datasets.fashion_mnist.load_data()`

Loads Fashion MNIST training and testing data.

`x_train = x_train.astype('float32') / 255.0`

Converts pixel values to float and normalizes them between 0 and 1.

`x_train = x_train.reshape(-1, 28, 28, 1)`

Adds channel dimension. CNN expects input shape `(height, width, channels)`. Since images are grayscale, channel is `1`.

`keras.layers.Conv2D(32, (3,3), activation='relu', input_shape=(28,28,1))`

First convolution layer. It uses 32 filters of size 3 x 3 to detect simple patterns like edges.

`keras.layers.MaxPooling2D((2,2))`

Reduces image size by taking maximum value from each 2 x 2 region.

`keras.layers.Dropout(0.25)`

Disables 25% neurons during training to reduce overfitting.

`keras.layers.Conv2D(64, (3,3), activation='relu')`

Second convolution layer. It learns more complex patterns.

`keras.layers.Conv2D(128, (3,3), activation='relu')`

Third convolution layer. It learns even higher-level visual features.

`keras.layers.Flatten()`

Converts feature maps into a 1D vector before sending them to Dense layers.

`keras.layers.Dense(128, activation='relu')`

Fully connected layer that learns final combinations of extracted image features.

`keras.layers.Dense(10, activation='softmax')`

Output layer with 10 neurons. Softmax gives probabilities for 10 clothing classes.

`loss='sparse_categorical_crossentropy'`

Used because labels are integer class numbers, not one-hot encoded vectors.

`optimizer='adam'`

Adam optimizer updates model weights.

`EarlyStopping(monitor='val_loss', patience=3, restore_best_weights=True)`

Stops training if validation loss does not improve for 3 epochs.

`ModelCheckpoint("best_cnn_model.h5", save_best_only=True)`

Saves the best CNN model.

`np.argmax(model.predict(x_test), axis=1)`

Converts softmax probabilities into predicted class labels.

## 7. Data Preprocessing

Preprocessing steps:

- Convert images to `float32`.
- Normalize pixels from `0-255` to `0-1`.
- Reshape images from `(samples, 28, 28)` to `(samples, 28, 28, 1)`.
- Labels are kept as integers because sparse categorical crossentropy is used.

Why reshaping is important:

CNN layers need a channel dimension. For grayscale images, the channel value is 1.

Why normalization is important:

It makes training faster and more stable.

## 8. Model Architecture

Architecture:

```text
Input: 28 x 28 x 1
Conv2D: 32 filters, 3 x 3, ReLU
MaxPooling2D: 2 x 2
Dropout: 0.25
Conv2D: 64 filters, 3 x 3, ReLU
MaxPooling2D: 2 x 2
Dropout: 0.25
Conv2D: 128 filters, 3 x 3, ReLU
Flatten
Dense: 128 neurons, ReLU
Dropout: 0.3
Dense: 10 neurons, Softmax
```

Approximate shape flow:

- Input: 28 x 28 x 1
- After first Conv2D: 26 x 26 x 32
- After first pooling: 13 x 13 x 32
- After second Conv2D: 11 x 11 x 64
- After second pooling: 5 x 5 x 64
- After third Conv2D: 3 x 3 x 128
- After Flatten: 1152 values
- Output: 10 class probabilities

Why CNN is used:

CNN preserves spatial structure of images and learns local visual patterns better than a simple Dense network.

## 9. Compilation

Compilation settings:

- Optimizer: `adam`
- Loss: `sparse_categorical_crossentropy`
- Metric: `accuracy`

Why Adam:

- Adam is fast and reliable for many deep learning tasks.

Why sparse categorical crossentropy:

- It is used for multiclass classification when labels are integers.

Why accuracy:

- It directly shows how many clothing images are correctly classified.

## 10. Training Process

Training settings:

- `epochs=20`
- `batch_size=32`
- `validation_data=(x_test, y_test)`
- callbacks: EarlyStopping and ModelCheckpoint

During training:

1. Convolution layers extract image features.
2. Pooling layers reduce size and keep important features.
3. Dense layers classify the extracted features.
4. Softmax gives class probabilities.
5. Loss is calculated using sparse categorical crossentropy.
6. Adam updates weights.
7. Validation loss is monitored for early stopping.

## 11. Evaluation and Prediction

Evaluation:

```python
test_loss, test_acc = model.evaluate(x_test, y_test)
```

Prediction:

```python
y_pred = np.argmax(model.predict(x_test), axis=1)
```

The model outputs 10 probabilities for each image. `argmax` selects the class with the highest probability.

## 12. Output Explanation

Expected output:

- Test accuracy.
- Classification report.
- Confusion matrix heatmap.
- Accuracy vs Epoch graph.
- Loss vs Epoch graph.
- Five sample actual and predicted labels.

How to interpret:

- High test accuracy means the CNN is classifying clothing images correctly.
- Confusion matrix shows which classes are often confused.
- Accuracy graph should generally increase.
- Loss graph should generally decrease.
- Sample predictions show quick real examples of model performance.

## 13. Why This Practical Is Important

This practical is important because CNNs are widely used in image classification, medical imaging, object detection, face recognition, quality inspection, and plant disease detection. Fashion MNIST is a beginner-friendly image classification dataset.

## 14. Common Viva Questions and Answers

1. What type of model is used?
   Answer: Convolutional Neural Network.

2. Which dataset is used?
   Answer: Fashion MNIST dataset.

3. How many classes are there?
   Answer: 10 clothing classes.

4. What is the image size?
   Answer: 28 x 28 pixels.

5. Are the images color or grayscale?
   Answer: Grayscale.

6. Why reshape to `(28,28,1)`?
   Answer: CNN expects height, width, and channel dimensions.

7. What does the channel value 1 mean?
   Answer: It means grayscale image.

8. Why normalize pixel values?
   Answer: To convert values from 0-255 to 0-1 for stable training.

9. What is Conv2D?
   Answer: A convolution layer that applies filters to extract image features.

10. What is a filter?
    Answer: A small matrix that detects patterns such as edges or textures.

11. Why use 3 x 3 filters?
    Answer: They are common and effective for detecting local image patterns.

12. What is MaxPooling2D?
    Answer: It reduces feature map size by selecting maximum values.

13. Why is pooling used?
    Answer: It reduces computation and keeps important features.

14. What is Dropout?
    Answer: It randomly disables neurons to reduce overfitting.

15. What is Flatten?
    Answer: It converts 2D feature maps into a 1D vector.

16. Why use Dense after convolution layers?
    Answer: Dense layers classify the features extracted by CNN layers.

17. Why use softmax?
    Answer: It gives probabilities for multiple classes.

18. Why use sparse categorical crossentropy?
    Answer: Labels are integer class numbers, not one-hot encoded.

19. What is Adam optimizer?
    Answer: An optimizer that updates weights using adaptive learning rates.

20. What is EarlyStopping?
    Answer: It stops training when validation loss stops improving.

21. What is ModelCheckpoint?
    Answer: It saves the best model during training.

22. Does this practical match the requirement?
    Answer: Yes, it matches the Fashion MNIST CNN option.

## 15. Examiner-Style Short Explanation

This program implements Fashion MNIST classification using a Convolutional Neural Network. The dataset contains 28 x 28 grayscale clothing images belonging to 10 classes. The images are normalized and reshaped to include the channel dimension. The CNN uses Conv2D layers to extract image features, MaxPooling layers to reduce feature size, Dropout layers to prevent overfitting, and Dense layers for final classification. The output layer uses Softmax activation with 10 neurons. The model is compiled using Adam optimizer and sparse categorical crossentropy loss, trained with early stopping, and evaluated using accuracy, classification report, confusion matrix, and graphs.

## 16. Important Points to Remember

- This is a CNN practical.
- Dataset is Fashion MNIST.
- Images are 28 x 28 grayscale.
- Input shape is `(28, 28, 1)`.
- Pixel values are normalized by dividing by 255.
- Conv2D extracts features.
- MaxPooling reduces size.
- Flatten converts feature maps to vector.
- Softmax is used for 10-class classification.
- Sparse categorical crossentropy is used because labels are integers.

## 17. Possible Errors and Fixes

- Error: `ModuleNotFoundError: No module named 'tensorflow'`
  Fix: Install TensorFlow.

- Error: `ModuleNotFoundError: No module named 'seaborn'`
  Fix: Install seaborn.

- Error: Shape error in Conv2D.
  Fix: Ensure images are reshaped to `(samples, 28, 28, 1)`.

- Error: Dataset download fails.
  Fix: Check internet connection.

- Error: Model save warning for `.h5`.
  Fix: Use `"best_cnn_model.keras"` in newer Keras versions.

- Error: Training is slow.
  Fix: Reduce epochs or use GPU if available.

## 18. Code Improvements

- Add class names when printing sample predictions.
- Use a separate validation split instead of using test data as validation data.
- Save plots using `plt.savefig()`.
- Add `model.summary()` for architecture explanation.
- Use data augmentation for stronger image classification.
- Add random seed for reproducibility.
- Change checkpoint filename to `.keras`.
