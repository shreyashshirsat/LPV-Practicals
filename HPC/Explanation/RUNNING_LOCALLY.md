# Running This Project Locally

This guide assumes you copy the full project folder to a new Desktop folder, for example:

```powershell
C:\Users\<your-name>\Desktop\access-copy
```

Run all commands in **PowerShell**.

## 1. Check Python

Try these one by one:

```powershell
python --version
py --version
py -3.12 --version
```

Use whichever command works on your system. In the rest of this guide, commands use `python`. If your system uses `py`, replace `python` with `py`.

## 2. Create and Activate Virtual Environment

Go to your copied project folder:

```powershell
cd "$env:USERPROFILE\Desktop\access-copy"
```

Create venv:

```powershell
python -m venv .venv
```

Activate venv:

```powershell
.\.venv\Scripts\Activate.ps1
```

If PowerShell blocks activation, run:

```powershell
Set-ExecutionPolicy -Scope Process -ExecutionPolicy Bypass
.\.venv\Scripts\Activate.ps1
```

Upgrade pip:

```powershell
python -m pip install --upgrade pip setuptools wheel
```

## 3. Install Common Python Dependencies

Install the packages needed for `p1.py`, `p2.py`, `p3.py`, `p4.py`, notebooks, and most mini-projects:

```powershell
python -m pip install numpy matplotlib scikit-learn seaborn pandas jupyterlab notebook ipykernel
python -m pip install tensorflow
python -m pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cpu
python -m pip install opencv-python pillow scikit-image requests tqdm joblib mtcnn keras-facenet
```

Optional, only for `human.py` in Google Colab style:

```powershell
python -m pip install kaggle deepface
```

Register the venv as a Jupyter kernel:

```powershell
python -m ipykernel install --user --name access-venv --display-name "Python (access-venv)"
```

## 4. Run Deep Learning Python Practical Files

Go into the `d` folder:

```powershell
cd "$env:USERPROFILE\Desktop\access-copy\d"
```

Run each file separately:

```powershell
python p1.py
python p2.py
python p3.py
python p4.py
```

What each file needs:

- `p1.py`: `torch`, `scikit-learn`, `numpy`, `matplotlib`
- `p2.py`: `tensorflow`, `keras`, `numpy`, `matplotlib`, `scikit-learn`
- `p3.py`: `tensorflow`, `numpy`, `matplotlib`, `scikit-learn`, `seaborn`
- `p4.py`: `tensorflow`, `numpy`, `matplotlib`, `scikit-learn`, `seaborn`

Notes:

- These files may download datasets automatically the first time.
- `p2.py`, `p3.py`, and `p4.py` can take time because they train neural networks.
- Plot windows may open for graphs. Close each graph window to let the program continue.
- On normal Windows TensorFlow will usually run on CPU. That is okay for practicals.

## 5. Run Jupyter Notebooks

From the `d` folder:

```powershell
jupyter lab
```

or:

```powershell
jupyter notebook
```

Open these files:

```text
Assignment1.ipynb
practical-1.ipynb
practical-2.ipynb
practical-3.ipynb
practical-4.ipynb
```

In Jupyter:

1. Open notebook.
2. Select kernel: `Python (access-venv)`.
3. Run cells from top to bottom.

Notebook dependency mapping:

- `Assignment1.ipynb`: `torch`, `pandas`, `scikit-learn`, `numpy`, `matplotlib`
- `practical-1.ipynb`: mostly same as `p1.py`
- `practical-2.ipynb`: mostly same as `p2.py`, plus `seaborn`
- `practical-3.ipynb`: mostly same as `p3.py`
- `practical-4.ipynb`: mostly same as `p4.py`

Important:

- `Assignment1.ipynb` appears to use `BostonHousing.csv`, so keep that CSV in the same `d` folder.
- If a notebook cannot find a file, check the notebook path and make sure the CSV/images are copied too.

## 6. Run ColorizeAI Project

Path:

```powershell
cd "$env:USERPROFILE\Desktop\access-copy\d\ColorizeAI"
```

Install its own requirements:

```powershell
python -m pip install -r requirements.txt
```

Train model:

```powershell
python colorize.py train
```

Colorize one image:

```powershell
python colorize.py predict --input dataset\test\test_00.jpg --output result.jpg
```

Colorize all test images:

```powershell
python colorize.py predict-all
```

Evaluate:

```powershell
python colorize.py evaluate
```

Notes:

- Existing `colorization_model.h5` is already present. If copied, prediction can work without retraining.
- If model file is missing, run training first.
- Training may download CIFAR-10 if training images are not found.

## 7. Run Mini-Project

Path:

```powershell
cd "$env:USERPROFILE\Desktop\access-copy\d\Mini-Project"
```

Dependencies:

```powershell
python -m pip install tensorflow pandas numpy opencv-python
```

Run:

```powershell
python main.py
```

Important files/folders needed:

```text
Mini-Project\main.py
Mini-Project\UTKFace\
Mini-Project\s6.jpg
Mini-Project\gender_age_model.keras
```

Notes:

- If `gender_age_model.keras` exists, the program loads it.
- If the model file is missing, the program trains using the `UTKFace` folder.
- If `UTKFace` is missing, training will fail.
- If `s6.jpg` is missing, final sample prediction will fail.

## 8. About human.py

`human.py` is not a normal local script. It intentionally contains:

```python
if not IN_COLAB:
    raise EnvironmentError('This notebook is intended for Google Colab. Open it in Colab and run again.')
```

So locally this file will stop.

To run it properly:

1. Open Google Colab.
2. Paste/upload the code there.
3. Upload `kaggle.json` when asked.
4. Let the notebook install its own packages.

Local command only for checking that it stops:

```powershell
cd "$env:USERPROFILE\Desktop\access-copy\d"
python human.py
```

Expected result locally:

```text
EnvironmentError: This notebook is intended for Google Colab.
```

## 9. Compile and Run HPC C++ OpenMP Programs

Go to project root:

```powershell
cd "$env:USERPROFILE\Desktop\access-copy"
```

You need a C++ compiler with OpenMP support. Check:

```powershell
g++ --version
```

Compile and run BFS:

```powershell
g++ -fopenmp bfs.cpp -o bfs.exe
.\bfs.exe
```

Compile and run DFS:

```powershell
g++ -fopenmp dfs.cpp -o dfs.exe
.\dfs.exe
```

Compile and run Bubble Sort:

```powershell
g++ -fopenmp bubblesort.cpp -o bubblesort.exe
.\bubblesort.exe
```

Compile and run Bubble + Merge Sort:

```powershell
g++ -fopenmp mergesort.cpp -o mergesort.exe
.\mergesort.exe
```

Compile and run Parallel Reduction:

```powershell
g++ -fopenmp mmas.cpp -o mmas.exe
.\mmas.exe
```

If `g++` is not found:

- Install MSYS2 or MinGW-w64.
- Add the compiler `bin` folder to PATH.
- Reopen PowerShell and try `g++ --version` again.

If OpenMP does not work:

- Make sure you compile with `-fopenmp`.
- If `libgomp-1.dll` is missing, use the terminal/environment that came with your MinGW/MSYS2 installation or add its `bin` folder to PATH.

## 10. CUDA Programs

There are currently no `.cu` CUDA source files in this project.

The notes exist:

```text
cuda_vector_addition_explanation.md
cuda_matrix_multiplication_explanation.md
```

But actual CUDA code files are missing.

If you later create CUDA files, for example:

```text
vector_add.cu
matrix_mul.cu
```

You need:

- NVIDIA GPU.
- NVIDIA driver.
- CUDA Toolkit.
- `nvcc` compiler.

Check CUDA compiler:

```powershell
nvcc --version
```

Compile vector addition:

```powershell
nvcc vector_add.cu -o vector_add.exe
.\vector_add.exe
```

Compile matrix multiplication:

```powershell
nvcc matrix_mul.cu -o matrix_mul.exe
.\matrix_mul.exe
```

## 11. Quick One-Time Install Command

If you want one practical command for most Python files:

```powershell
python -m pip install numpy matplotlib scikit-learn seaborn pandas jupyterlab notebook ipykernel tensorflow opencv-python pillow scikit-image requests tqdm joblib mtcnn keras-facenet
python -m pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cpu
```

## 12. Common Problems

### `python` is not recognized

Try:

```powershell
py --version
py -3.12 --version
```

If `py` works, use `py` instead of `python`.

### `pip` installs globally instead of in venv

Make sure venv is activated. You should see `(.venv)` in PowerShell.

### TensorFlow is slow

That is normal on CPU. The practicals can still run.

### TensorFlow GPU not detected on native Windows

For modern TensorFlow on native Windows, CPU is normal. For NVIDIA GPU TensorFlow, use WSL2.

### Dataset download fails

Check internet connection. Keras and scikit-learn datasets download on first run.

### C++ program compiles but OpenMP seems ignored

Use:

```powershell
g++ -fopenmp file.cpp -o file.exe
```

### Jupyter does not show venv kernel

Run again:

```powershell
python -m ipykernel install --user --name access-venv --display-name "Python (access-venv)"
```
