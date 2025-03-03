import subprocess

def test_integer_mode():
    result = subprocess.run(["../build/app.exe"], input="3 + 5 * 2\n", text=True, capture_output=True)
    assert result.stdout.strip() == "13"

def test_float_mode():
    result = subprocess.run(["../build/app.exe", "--float"], input="5 / 2\n", text=True, capture_output=True)
    assert result.stdout.strip() == "2.5"

if __name__ == "__main__":
    test_integer_mode()
    test_float_mode()
    print("All integration tests passed.")

