import numpy as np
import matplotlib.pyplot as plt
from keras.datasets import imdb
from keras import models, layers
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, confusion_matrix
import tensorflow as tf

# Load IMDB dataset (top 10,000 words)
(X_train, y_train), (X_test, y_test) = imdb.load_data(num_words=10000)

# Combine data
data = np.concatenate((X_train, X_test), axis=0)
labels = np.concatenate((y_train, y_test), axis=0)

# Vectorization (One-hot encoding)
def vectorize(sequences, dimension=10000):
    results = np.zeros((len(sequences), dimension))
    for i, sequence in enumerate(sequences):
        results[i, sequence] = 1
    return results

data = vectorize(data)
labels = np.array(labels).astype("float32")

# Train-Test Split (80-20)
X_train, X_test, y_train, y_test = train_test_split(
    data, labels, test_size=0.2, random_state=42
)

# Model Architecture (DNN)
model = models.Sequential([
    layers.Dense(50, activation="relu", input_shape=(10000,)),
    layers.Dropout(0.3),
    layers.Dense(50, activation="relu"),
    layers.Dropout(0.2),
    layers.Dense(50, activation="relu"),
    layers.Dense(1, activation="sigmoid")
])

# Compile Model
model.compile(
    optimizer="adam",
    loss="binary_crossentropy",
    metrics=["accuracy"]
)

# Early Stopping
callback = tf.keras.callbacks.EarlyStopping(monitor='loss', patience=3)

# Train Model
history = model.fit(
    X_train, y_train,
    epochs=2,
    batch_size=500,
    validation_data=(X_test, y_test),
    callbacks=[callback]
)

# Evaluate Model
loss, accuracy = model.evaluate(X_test, y_test)
print("\nTest Accuracy:", accuracy)

# Predictions
y_pred = (model.predict(X_test) > 0.5).astype("int32")

# Performance Metrics
print("\nClassification Report:")
print(classification_report(y_test, y_pred))

print("\nConfusion Matrix:")
print(confusion_matrix(y_test, y_pred))

# Plot Accuracy Graph
plt.plot(history.history['accuracy'])
plt.plot(history.history['val_accuracy'])
plt.title('Accuracy vs Epoch')
plt.xlabel('Epoch')
plt.ylabel('Accuracy')
plt.legend(['Train', 'Validation'])
plt.show()

# Plot Loss Graph
plt.plot(history.history['loss'])
plt.plot(history.history['val_loss'])
plt.title('Loss vs Epoch')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.legend(['Train', 'Validation'])
plt.show()

# Sample Predictions
print("\nSample Predictions:")
for i in range(5):
    print(f"Actual: {int(y_test[i])}, Predicted: {int(y_pred[i])}")