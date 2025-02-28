import subprocess

def test_addition():
    result = subprocess.run(["./build/app.exe"], input="2+3\n", text=True, capture_output=True)
    assert result.stdout.strip() == "5"

def test_float_mode():
    result = subprocess.run(["./build/app.exe", "--float"], input="2.5+2.5\n", text=True, capture_output=True)
    assert abs(float(result.stdout.strip()) - 5.0) < 1e-6
