# Linear Regression Using Deep Neural Network

## 0. Beginner Roadmap and Deep Learning Focus

If you are new to Deep Learning, understand this practical in this simple way:

- **Data** means examples given to the computer.
- **Input features** are the values used for prediction, such as income, house age, rooms, and location.
- **Target/output** is the answer the model must learn to predict, here house price.
- **Model** means a mathematical system that learns patterns from data.
- **Neural network** means layers of connected neurons that learn from examples.
- **Training** means showing many examples to the model so it can adjust its weights.
- **Loss** means prediction error. Lower loss means better learning.
- **Optimizer** means the method used to improve the model by changing weights.
- **Evaluation** means testing the trained model on unseen data.

Subject focus:

This practical is from **Deep Learning** because it uses a neural network with multiple layers. It is also a **regression** problem because the output is a number, not a category. In the exam, first say: "This is a Deep Neural Network regression model used to predict house prices from numerical housing features."

## 0A. Core Theory: What, Why, How, and When

### What is Linear Regression?

Linear Regression is a supervised machine learning method used to predict a continuous numeric value. In simple words, it tries to find a relationship between input features and output value.

Example:

```text
House price = relation of income + rooms + location + house age + other features
```

Traditional linear regression uses a simple equation:

```text
y = w1*x1 + w2*x2 + ... + b
```

Here:

- `x` means input features.
- `w` means weights learned by the model.
- `b` means bias.
- `y` means predicted output.

### What is Deep Neural Network Regression?

A Deep Neural Network regression model also predicts a continuous value, but instead of using only one simple equation, it uses multiple layers. These layers help the model learn more complex relationships.

For example, house price may not depend on only one feature directly. Price can depend on a combination of income, location, rooms, and population. A DNN can learn such combinations.

### Why use a Deep Neural Network for house price prediction?

We use a DNN because real-world data is usually not perfectly linear. House prices may depend on many factors together. A DNN can learn non-linear patterns using hidden layers and activation functions.

### How does the model learn?

The learning process happens like this:

1. The model receives housing features.
2. It produces a predicted price.
3. The predicted price is compared with the actual price.
4. The difference is called loss.
5. Backpropagation calculates how each weight contributed to the error.
6. The optimizer updates weights to reduce future error.
7. This repeats for many epochs.

### Why is scaling needed?

Neural networks train better when input values are on a similar scale. If one feature has values from `0` to `1` and another has values from `0` to `100000`, the larger feature can dominate training. `StandardScaler` solves this by converting features to a common scale.

### Why is this called supervised learning?

It is supervised learning because the dataset contains both:

- Inputs: housing features.
- Correct answers: actual house values.

The model learns by comparing its predictions with the correct answers.

### When do we use regression?

Use regression when the answer is a continuous number, such as:

- House price.
- Temperature.
- Salary.
- Stock value.
- Electricity usage.

### When should we not use regression?

Do not use regression when the output is a category. For example, if the output is "dog/cat" or "positive/negative", that is classification, not regression.

## 1. Which Practical This File Belongs To

This file belongs to the **Linear Regression using Deep Neural Network** practical because it predicts a continuous numeric house price value using a neural network.

Important requirement check:

- Required practical: Boston Housing Price Prediction using Linear Regression with DNN.
- Actual code: Uses `fetch_california_housing()` from scikit-learn.
- Match status: **Partially matches**. The model and regression logic are correct for house-price prediction, but the dataset is **California Housing**, not **Boston Housing**.

To fully match the requirement, replace the California Housing dataset with Boston Housing, for example using Keras Boston Housing dataset or OpenML Boston data.

## 2. Aim of the Practical

To implement a Deep Neural Network regression model that predicts house prices from housing-related input features and evaluates the model using regression metrics such as MAE, MSE, RMSE, and R2 score.

## 3. Dataset Used

The code uses the **California Housing dataset**:

- Loaded using `fetch_california_housing(return_X_y=True)`.
- Input `X`: numerical housing features such as median income, house age, average rooms, population, latitude, longitude, etc.
- Target `y`: median house value.
- Purpose: predict house value from the given numerical features.

Exam note: The required practical says **Boston Housing dataset**, where input features include crime rate, average rooms, tax rate, pupil-teacher ratio, etc., and the target is median house price. The current file does not use Boston data.

## 4. Libraries Used

- `torch`: Main PyTorch library used for tensors and neural network training.
- `torch.nn`: Provides neural network layers, activation functions, and loss functions.
- `DataLoader`: Loads data in mini-batches during training and testing.
- `random_split`: Splits dataset into training and testing parts.
- `fetch_california_housing`: Loads the California housing dataset.
- `StandardScaler`: Standardizes numerical features so they have mean 0 and standard deviation 1.
- `mean_absolute_error`: Calculates average absolute prediction error.
- `mean_squared_error`: Calculates squared prediction error.
- `r2_score`: Measures how well the model explains the target variation.
- `numpy`: Used for square root calculation while finding RMSE.
- `matplotlib.pyplot`: Used to plot training loss.

## 5. Complete Code Logic

The program first loads housing data, scales the input features, converts the data into PyTorch tensors, and wraps it inside a custom dataset class. Then it splits the dataset into training and testing sets. A feed-forward neural network is built using linear layers and ReLU activations. The model is trained for 20 epochs using mini-batches. After training, the model predicts prices for test data. Finally, regression metrics and sample predictions are printed, and a loss graph is displayed.

## 6. Step-by-Step Code Explanation

`class HousingDataset(torch.utils.data.Dataset):`

This creates a custom PyTorch dataset. PyTorch uses dataset classes to provide samples one by one to the `DataLoader`.

`X = StandardScaler().fit_transform(X)`

This scales all input features. Scaling is important because housing features have different ranges. For example, income and latitude are not on the same scale.

`self.X = torch.tensor(X, dtype=torch.float32)`

The scaled input data is converted into PyTorch tensors. Neural networks in PyTorch work with tensors.

`self.y = torch.tensor(y, dtype=torch.float32)`

The target house prices are also converted into float tensors because regression output is continuous.

`__len__`

Returns the number of samples in the dataset.

`__getitem__`

Returns one input-output pair at a given index.

`class MLP(nn.Module):`

This defines the neural network model. MLP means Multi-Layer Perceptron.

`nn.Linear(input_dim, 64)`

First dense layer. It accepts all housing features and produces 64 learned values.

`nn.ReLU()`

Adds non-linearity so the model can learn complex relationships.

`nn.Linear(64, 32)`

Second dense layer. It reduces 64 values to 32 learned values.

`nn.Linear(32, 1)`

Final output layer. It gives one predicted house price.

`X, y = fetch_california_housing(return_X_y=True)`

Loads the dataset as input features `X` and target values `y`.

`train_size = int(0.8 * len(dataset))`

80% of data is used for training.

`test_size = len(dataset) - train_size`

Remaining 20% is used for testing.

`train_loader = DataLoader(train_data, batch_size=10, shuffle=True)`

Training data is loaded in batches of 10. `shuffle=True` changes the sample order each epoch, which helps training.

`model = MLP(input_dim=X.shape[1])`

Creates the model. `X.shape[1]` gives the number of input features.

`loss_fn = nn.L1Loss()`

Uses Mean Absolute Error as the training loss.

`optimizer = torch.optim.Adam(model.parameters(), lr=1e-4)`

Adam optimizer updates model weights using gradients. Learning rate is `0.0001`.

Inside the training loop:

- `model.train()` sets the model to training mode.
- `targets = targets.view(-1, 1)` changes target shape to match output shape.
- `optimizer.zero_grad()` clears previous gradients.
- `outputs = model(inputs)` performs forward pass.
- `loss = loss_fn(outputs, targets)` calculates error.
- `loss.backward()` calculates gradients.
- `optimizer.step()` updates weights.

During evaluation:

- `model.eval()` sets evaluation mode.
- `torch.no_grad()` avoids gradient calculation.
- Predictions and actual values are collected into `y_pred` and `y_true`.

## 7. Data Preprocessing

Preprocessing steps used:

- Feature scaling with `StandardScaler`.
- Conversion from NumPy arrays to PyTorch tensors.
- Train-test split using 80% training and 20% testing.
- Mini-batch loading using `DataLoader`.

Important issue:

The scaler is fitted before splitting the data. This causes slight **data leakage** because information from test data is used during scaling. Better practice is to fit the scaler only on training data and transform test data separately.

## 8. Model Architecture

Architecture:

```text
Input layer: number of housing features
Dense layer: input_dim -> 64, ReLU
Dense layer: 64 -> 32, ReLU
Output layer: 32 -> 1
```

Layer explanation:

- Input layer receives housing feature values.
- First hidden layer learns 64 feature combinations.
- ReLU activation helps learn non-linear patterns.
- Second hidden layer learns deeper patterns.
- Final layer has one neuron because this is a regression problem.
- No activation is used in the output layer because house price is a continuous value.

## 9. Compilation

PyTorch does not use a separate `compile()` method like Keras. Instead, the code manually defines:

- Model: `MLP`
- Loss function: `nn.L1Loss()`
- Optimizer: `Adam`

Why `L1Loss`:

- It measures average absolute difference between actual and predicted values.
- It is less sensitive to very large errors than MSE.

Why Adam:

- Adam adapts learning rates during training.
- It usually works well for neural networks.

## 10. Training Process

The model is trained for `20` epochs.

In each epoch:

1. Data is loaded in batches of 10.
2. The model predicts output for each batch.
3. Loss is calculated.
4. Gradients are calculated using backpropagation.
5. Adam optimizer updates the weights.
6. Average epoch loss is printed.

The list `train_losses` stores the average loss for each epoch and is later used for plotting.

## 11. Evaluation and Prediction

The model is evaluated on test data.

The code calculates:

- MAE: average absolute error.
- MSE: average squared error.
- RMSE: square root of MSE, easier to interpret because it is in target units.
- R2 Score: tells how much variation in house price is explained by the model.

Predictions are made using:

```python
outputs = model(inputs)
```

The first five actual and predicted values are printed for quick checking.

## 12. Output Explanation

Expected output:

- Epoch-wise training loss.
- Performance metrics: MAE, MSE, RMSE, R2 Score.
- Loss vs Epoch graph.
- Five sample actual vs predicted values.

How to interpret:

- Lower MAE, MSE, and RMSE means better prediction.
- R2 closer to 1 means better model.
- Loss graph should generally go downward.
- If predicted values are close to actual values, the model is learning well.

## 13. Why This Practical Is Important

This practical shows how neural networks can solve regression problems. House price prediction is a real-world example used in real estate, finance, property valuation, and decision support systems.

## 14. Common Viva Questions and Answers

1. What type of problem is this?
   Answer: It is a regression problem because the output is a continuous house price value.

2. Which dataset is used in this code?
   Answer: The code uses California Housing dataset, not Boston Housing.

3. Does this file fully match the practical requirement?
   Answer: It partially matches. The regression DNN part is correct, but the required dataset is Boston Housing.

4. What is the target variable?
   Answer: The target is median house value.

5. Why is `StandardScaler` used?
   Answer: It scales all input features to similar ranges, which helps neural network training.

6. What is an MLP?
   Answer: MLP means Multi-Layer Perceptron, a feed-forward neural network with dense layers.

7. Why is ReLU used?
   Answer: ReLU adds non-linearity and helps the network learn complex patterns.

8. Why is the final layer size 1?
   Answer: Because the model predicts one continuous value.

9. Why is there no activation in the output layer?
   Answer: Regression output should be unrestricted continuous value.

10. What is `L1Loss`?
    Answer: It is Mean Absolute Error loss.

11. What is Adam optimizer?
    Answer: Adam is an optimization algorithm that updates weights using adaptive learning rates.

12. What is an epoch?
    Answer: One complete pass through the training dataset.

13. What is batch size?
    Answer: Number of samples processed before one weight update. Here it is 10.

14. What is `loss.backward()`?
    Answer: It calculates gradients using backpropagation.

15. What is `optimizer.step()`?
    Answer: It updates model weights using calculated gradients.

16. Why use `model.eval()`?
    Answer: It sets the model to evaluation mode.

17. Why use `torch.no_grad()`?
    Answer: It saves memory and computation during testing because gradients are not needed.

18. What is MAE?
    Answer: Mean Absolute Error, average absolute difference between actual and predicted values.

19. What is RMSE?
    Answer: Root Mean Squared Error, square root of MSE.

20. What is R2 score?
    Answer: It shows how well the model explains variation in the target values.

21. What is data leakage in this code?
    Answer: Scaling is done before train-test split, so test data information is used during preprocessing.

22. How can this code be corrected for Boston Housing?
    Answer: Replace `fetch_california_housing()` with a Boston Housing dataset loader.

## 15. Examiner-Style Short Explanation

This program implements a deep neural network regression model for house price prediction. It loads housing data, scales the numerical features using StandardScaler, splits the data into training and testing sets, and trains a Multi-Layer Perceptron with two hidden layers. The model uses ReLU activation in hidden layers and one output neuron for continuous price prediction. It is trained using L1 loss and Adam optimizer. After training, the model is evaluated using MAE, MSE, RMSE, and R2 score. The code demonstrates the required regression approach, but it uses California Housing instead of the required Boston Housing dataset.

## 16. Important Points to Remember

- This is a regression practical.
- Output is one continuous value.
- Actual dataset used is California Housing.
- Required dataset is Boston Housing, so mention this mismatch.
- Scaling is important for neural networks.
- ReLU is used in hidden layers.
- Final layer has one neuron and no activation.
- Adam updates model weights.
- MAE, MSE, RMSE, and R2 are regression metrics.
- Loss should decrease during training.

## 17. Possible Errors and Fixes

- Error: `ModuleNotFoundError: No module named 'torch'`
  Fix: Install PyTorch in the environment.

- Error: `ModuleNotFoundError: No module named 'sklearn'`
  Fix: Install scikit-learn.

- Error: Dataset download fails.
  Fix: Check internet connection or use a locally available dataset.

- Error: Shape mismatch between output and target.
  Fix: Keep `targets = targets.view(-1, 1)`.

- Error: Graph does not show.
  Fix: Run in an environment that supports plots, or save the plot using `plt.savefig()`.

## 18. Code Improvements

- Use the required Boston Housing dataset.
- Fit `StandardScaler` only on training data to avoid data leakage.
- Add `random_state` or generator seed for reproducible train-test split.
- Use a validation set for tuning.
- Try `MSELoss` because it is common for regression.
- Increase epochs and monitor validation loss.
- Save the trained model for later use.
- Add labels explaining feature names and target units.
